import sys
import os
import numpy
from enum import Enum
import signal
import time
import asyncio
from bleak import BleakScanner, BleakClient
from threading import Thread

class Gestures(Enum):
    IDLE = 1
    UNKNOWN = 2
    SWIPE_RIGHT = 3
    SWIPE_LEFT = 4
    DOUBLE_SHAKE = 5
    DOUBLE_THUMB = 6
    ROTATION_RIGHT = 7
    ROTATION_LEFT = 8


gestures_string_names = dict()
gestures_string_names[Gestures.UNKNOWN]       = "UNKNOWN GESTURE"
gestures_string_names[Gestures.SWIPE_RIGHT]   = "SWIPE RIGHT"
gestures_string_names[Gestures.SWIPE_LEFT]    = "SWIPE LEFT"
gestures_string_names[Gestures.DOUBLE_SHAKE]  = "DOUBLE SHAKE"
gestures_string_names[Gestures.DOUBLE_THUMB]  = "DOUBLE THUMB"
gestures_string_names[Gestures.ROTATION_RIGHT] = "ROTATION RIGHT"
gestures_string_names[Gestures.ROTATION_LEFT]  = "ROTATION LEFT"
gestures_string_names[Gestures.IDLE]           = "NO MOVEMENTS"

################################################################################################

async def discover_services(device_name, characteristic_uuid):
    scanner = BleakScanner()

    # Scan for devices
    devices = await scanner.discover()
    for device in devices:
        if device.name == device_name:
            print("{0} device found".format(device_name))
            async with BleakClient(device) as client:
                await client.is_connected()
                print("Device Connected!")

                services = await client.get_services()

                for service in services:
                    for char in service.characteristics:
                        if char.uuid == characteristic_uuid:
                            print("Neuton characteristic found")
                            print("Ready to work")
                            await start_listening(client, char)
                            return

################################################################################################

async def start_listening(client, characteristic):
    def notification_handler(sender: int, data: bytearray):
        # This function will be called when notifications/indications are received
        # The received data will be available in the 'data' parameter.

        ble_str = data.decode('utf-8').strip()
        print(ble_str)

        predicted_class_str = str(ble_str.split(",")[0])
        probability_str = ble_str.split(",")[1].strip()

        class_label_raw = int(predicted_class_str) + 1 # Lable starts from 1 but on device starts from 0
        prob_percentage = int(probability_str)

        class_label = Gestures(class_label_raw)
        class_name = gestures_string_names[class_label]

        print("{0}, probability {1} %".format(class_name, prob_percentage))


    # Subscribe to notifications/indications for the characteristic
    await client.start_notify(characteristic.uuid, notification_handler)

    # Keep the program running to continue listening for data
    while True:
        await asyncio.sleep(5)

################################################################################################

def thread_ble():
    asyncio.run(discover_services("Neuton NRF RemoteControl", "516a51c4-b1e1-47fa-8327-8acaeb3399eb"))


################################################################################################

def signal_handler(sig, frame):
        sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

x = Thread(target=thread_ble)
x.start()
