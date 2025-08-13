/**
 *
 * @defgroup ble_gatt Bluetooth GATT interface
 * @{
 * @ingroup ble
 *
 *
 */
#ifndef __BLE_GATT_H__
#define __BLE_GATT_H__

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus


/**
 * @brief BLE connection callback, this callback will be called when state of the connection is changed
 * 
 * @param connected     BLE connected state, true if connected, otherwise false
 */
typedef void (*ble_connection_cb_t)(bool connected);

/**
 * @brief BLE data received callback, this callback will be called when new data is received from the BLE GATT profile
 * 
 * @param data          Received data
 * @param len           Length of the received data
 */
typedef void (*ble_data_received_cb_t)(const char* data, size_t len);

/**
 * @brief Initialize BLE GATT profile and start advertasing
 * 
 * @param cb        Connection callback @ref ble_connection_cb_t
 * 
 * @return Operation status, 0 for success 
 */
int ble_gatt_init(ble_connection_cb_t connection_cb, ble_data_received_cb_t data_received_cb);

/**
 * @brief Send Neuton out to BLE GATT profile
 * 
 * @param out      Neuton out string
 * 
 * @return Operation status, 0 for success 
 */
int ble_gatt_send_raw_data(const uint8_t* data, size_t len);


#ifdef __cplusplus
}
#endif // __cplusplus


#endif // __BLE_GATT_H__

/**
 * @}
 */
