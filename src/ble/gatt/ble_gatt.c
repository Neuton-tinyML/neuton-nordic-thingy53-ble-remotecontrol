#include "ble_gatt.h"

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/settings/settings.h>

//////////////////////////////////////////////////////////////////////////////

static ssize_t on_data_received_(struct bt_conn *conn,
                                 const struct bt_gatt_attr *attr,
                                 const void *buf,
                                 uint16_t len,
                                 uint16_t offset,
                                 uint8_t flags);

//////////////////////////////////////////////////////////////////////////////

#if CONFIG_SAMPLE_BT_USE_AUTHENTICATION
/* Require encryption using authenticated link-key. */
#define SAMPLE_BT_PERM_READ BT_GATT_PERM_READ_AUTHEN
#define SAMPLE_BT_PERM_WRITE BT_GATT_PERM_WRITE_AUTHEN
#else
/* Require encryption. */
#define SAMPLE_BT_PERM_READ BT_GATT_PERM_READ_ENCRYPT
#define SAMPLE_BT_PERM_WRITE BT_GATT_PERM_WRITE_ENCRYPT
#endif

//////////////////////////////////////////////////////////////////////////////

static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA_BYTES(BT_DATA_UUID16_ALL,
                  BT_UUID_16_ENCODE(BT_UUID_BAS_VAL)),
};

static const struct bt_data sd[] = {
    BT_DATA(BT_DATA_NAME_COMPLETE, CONFIG_BT_DEVICE_NAME, sizeof(CONFIG_BT_DEVICE_NAME) - 1),
};

static bool ble_connected_ = false;
static ble_connection_cb_t user_conn_callback_ = NULL;
static ble_data_received_cb_t user_data_received_callback_ = NULL;

static bool ccc_enabled_ = false;

//////////////////////////////////////////////////////////////////////////////

static void on_cccd_changed(const struct bt_gatt_attr* attr, uint16_t value)
{
    printk("Input CCCD %s\n", value == BT_GATT_CCC_NOTIFY ? "enabled" : "disabled");
    printk("Input attribute handle: %d\n", attr->handle);

    ccc_enabled_ = (value == BT_GATT_CCC_NOTIFY);
}

//////////////////////////////////////////////////////////////////////////////

//Declaration of custom GATT service and characteristics UUIDs
#define NEUTON_SERVICE_UUID \
    BT_UUID_128_ENCODE(0xa5d4f351, 0x9d11, 0x419f, 0x9f1b, 0x3dcdf0a15f4d)

#define NEUTON_OUT_CHARACTERISTIC_UUID \
    BT_UUID_128_ENCODE(0x516a51c4, 0xb1e1, 0x47fa, 0x8327, 0x8acaeb3399eb)   

#define NEUTON_IN_CHARACTERISTIC_UUID \
    BT_UUID_128_ENCODE(0x516a51c4, 0xb1e1, 0x47fa, 0x8327, 0x8acaeb3399ec)    

#define BT_UUID_NEUTON_SERVICE          BT_UUID_DECLARE_128(NEUTON_SERVICE_UUID)
#define BT_UUID_NEUTON_CHAR_OUT         BT_UUID_DECLARE_128(NEUTON_OUT_CHARACTERISTIC_UUID)
#define BT_UUID_NEUTON_CHAR_IN          BT_UUID_DECLARE_128(NEUTON_IN_CHARACTERISTIC_UUID)

//Sensor hub Service Declaration and Registration
BT_GATT_SERVICE_DEFINE(neuton_gatt,
    BT_GATT_PRIMARY_SERVICE(BT_UUID_NEUTON_SERVICE),
    
    BT_GATT_CHARACTERISTIC(BT_UUID_NEUTON_CHAR_OUT,
                    BT_GATT_CHRC_NOTIFY,
                    BT_GATT_PERM_READ,
                    NULL, NULL, NULL),

    BT_GATT_CCC(on_cccd_changed, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),

    BT_GATT_CHARACTERISTIC(BT_UUID_NEUTON_CHAR_IN,
                    BT_GATT_CHRC_WRITE_WITHOUT_RESP,
                    SAMPLE_BT_PERM_WRITE,
                    NULL, on_data_received_, NULL)
);

//////////////////////////////////////////////////////////////////////////////

static void connected(struct bt_conn* conn, uint8_t err)
{
    char addr[BT_ADDR_LE_STR_LEN];

    bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

    if (err)
    {
        printk("Failed to connect to %s (%u)\n", addr, err);
        return;
    }

    printk("Connected %s\n", addr);

    if (bt_conn_set_security(conn, BT_SECURITY_L2))
    {
        printk("Failed to set security\n");
    }

    ble_connected_ = true;

    if (user_conn_callback_)
        user_conn_callback_(ble_connected_);
}

//////////////////////////////////////////////////////////////////////////////

static void disconnected(struct bt_conn* conn, uint8_t reason)
{
    char addr[BT_ADDR_LE_STR_LEN];

    bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

    printk("Disconnected from %s (reason 0x%02x)\n", addr, reason);

    ble_connected_ = false;
    ccc_enabled_ = false;

    if (user_conn_callback_)
        user_conn_callback_(ble_connected_);
}

//////////////////////////////////////////////////////////////////////////////

static void security_changed(struct bt_conn* conn, bt_security_t level,
                             enum bt_security_err err)
{
    char addr[BT_ADDR_LE_STR_LEN];

    bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

    if (!err)
    {
        printk("Security changed: %s level %u\n", addr, level);
    } else
    {
        printk("Security failed: %s level %u err %d\n", addr, level,
               err);

        bt_unpair(BT_ID_DEFAULT, BT_ADDR_LE_ANY);
    }
}

//////////////////////////////////////////////////////////////////////////////

BT_CONN_CB_DEFINE(conn_callbacks) = {
    .connected = connected,
    .disconnected = disconnected,
    .security_changed = security_changed,
};

//////////////////////////////////////////////////////////////////////////////

static void bt_ready(int err)
{
    if (err)
    {
        printk("Bluetooth init failed (err %d)\n", err);
        return;
    }

    printk("Bluetooth initialized\n");

    if (IS_ENABLED(CONFIG_SETTINGS))
    {
        settings_load();
    }

    err = bt_le_adv_start(BT_LE_ADV_CONN, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
    if (err)
    {
        printk("Advertising failed to start (err %d)\n", err);
        return;
    }

    printk("Advertising successfully started\n");
}

//////////////////////////////////////////////////////////////////////////////

static void auth_passkey_display(struct bt_conn* conn, unsigned int passkey)
{
    char addr[BT_ADDR_LE_STR_LEN];

    bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

    printk("Passkey for %s: %06u\n", addr, passkey);
}

//////////////////////////////////////////////////////////////////////////////

static void auth_cancel(struct bt_conn* conn)
{
    char addr[BT_ADDR_LE_STR_LEN];

    bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

    printk("Pairing cancelled: %s\n", addr);
}

//////////////////////////////////////////////////////////////////////////////

static struct bt_conn_auth_cb auth_cb_display = {
    .passkey_display = auth_passkey_display,
    .passkey_entry = NULL,
    .cancel = auth_cancel,
};

//////////////////////////////////////////////////////////////////////////////

static ssize_t on_data_received_(struct bt_conn *conn,
                                const struct bt_gatt_attr *attr,
                                const void *buf,
                                uint16_t len,
                                uint16_t offset,
                                uint8_t flags)
{
    if (user_data_received_callback_)
    {
        user_data_received_callback_((const char*)buf, len);
    }
    else
    {
        printk("Data received but no callback registered\n");
    }

    return len; // Indicate all data was consumed
}

//////////////////////////////////////////////////////////////////////////////

int ble_gatt_init(ble_connection_cb_t connection_cb, ble_data_received_cb_t data_received_cb)
{
    int err;
    err = bt_enable(bt_ready);

    if (err)
    {
        printk("Bluetooth init failed (err %d)\n", err);
        return err;
    }

    user_conn_callback_ = connection_cb;
    user_data_received_callback_ = data_received_cb;

    if (IS_ENABLED(CONFIG_SAMPLE_BT_USE_AUTHENTICATION))
    {
        bt_conn_auth_cb_register(&auth_cb_display);
    }

    return err;
}

//////////////////////////////////////////////////////////////////////////////

int ble_gatt_send_raw_data(const uint8_t* data, size_t len)
{
    int res = -1;

    if (!ble_connected_ || !ccc_enabled_)
        return -1;

    if (data == NULL || len == 0)
    {
        printk("Invalid data or length\n");
        return -1;  
    }  

    const struct bt_gatt_attr* attr = &neuton_gatt.attrs[2];

    res = bt_gatt_notify(NULL, attr, data, len);

    return res;
}