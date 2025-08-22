import sys
import os
import numpy
from enum import Enum
import signal
import asyncio
from bleak import BleakScanner, BleakClient
from threading import Thread
from PIL import Image
import matplotlib.pyplot as plt
from datetime import datetime
from matplotlib import animation


class Gestures(Enum):
    IDLE = 1
    UNKNOWN = 2
    SWIPE_RIGHT = 3
    SWIPE_LEFT = 4
    DOUBLE_SHAKE = 5
    DOUBLE_THUMB = 6
    ROTATION_RIGHT = 7
    ROTATION_LEFT = 8


async def discover_services(device_name, characteristic_uuid):
    scanner = BleakScanner()

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


async def start_listening(client, characteristic):
    def notification_handler(sender: int, data: bytearray):
        # This function will be called when notifications/indications are received
        # The received data will be available in the 'data' parameter.

        ble_str = data.decode("utf-8").strip()
        print(ble_str)

        predicted_class_str = str(ble_str.split(",")[0])
        probability_str = ble_str.split(",")[1].strip()

        class_label_raw = (
            int(predicted_class_str) + 1
        )  # Lable starts from 1 but on device starts from 0
        prob_percentage = int(probability_str)

        class_label = Gestures(class_label_raw)
        class_name = gestures_string_names[class_label]

        state.update_image = (
            False
            if state.current_activity == class_label and class_label == Gestures.UNKNOWN
            else True
        )
        state.current_activity = class_label

        process_device_output_message(f"{class_name}, {prob_percentage}%")
        print("{0}, probability {1} %".format(class_name, prob_percentage))

    # Subscribe to notifications/indications for the characteristic
    await client.start_notify(characteristic.uuid, notification_handler)
    # Keep the program running to continue listening for data
    while True:
        await asyncio.sleep(5)


def thread_ble():
    asyncio.run(
        discover_services(
            "Neuton NRF RemoteControl", "516a51c4-b1e1-47fa-8327-8acaeb3399eb"
        )
    )


def signal_handler(sig, frame):
    sys.exit(0)


class State:
    def __init__(self, current_activity=Gestures.UNKNOWN, update_image=True) -> None:
        self.current_activity = current_activity
        self.update_image = update_image


def resize_icon_image(image, resize_percent=25):
    original_width, original_height = image.size
    new_width = int(original_width * resize_percent / 100)
    new_height = int(original_height * resize_percent / 100)
    return image.resize((new_width, new_height))


def prepare_image(current_activity=Gestures.UNKNOWN, update_image=False):
    result_image = main_img.copy()
    if update_image == True:
        images = dict()
        images[Gestures.UNKNOWN] = activity_unknown_img
        images[Gestures.SWIPE_RIGHT] = activity_swipe_right_img
        images[Gestures.SWIPE_LEFT] = activity_swipe_left_img
        images[Gestures.DOUBLE_SHAKE] = activity_double_shake_img
        images[Gestures.DOUBLE_THUMB] = activity_double_thumb_img
        images[Gestures.ROTATION_RIGHT] = activity_rotation_right_img
        images[Gestures.ROTATION_LEFT] = activity_rotation_left_img
        images[Gestures.IDLE] = activity_idle_img

        current_activity_image = images[current_activity]

        white_field_center_x = 320
        white_field_center_y = 250

        icon_width, icon_height = current_activity_image.size
        icon_x_position = white_field_center_x - (icon_width // 2)
        icon_y_position = white_field_center_y - (icon_height // 2)

        if current_activity_image.mode == "RGBA":
            result_image.paste(
                current_activity_image,
                (icon_x_position, icon_y_position),
                current_activity_image,
            )
        else:
            result_image.paste(
                current_activity_image, (icon_x_position, icon_y_position)
            )

    return result_image


def get_image(current_activity=Gestures.UNKNOWN, update_image=False):
    prepared_image = prepare_image(current_activity, update_image)
    return prepared_image


def show_realtime_inference_labels():
    y_offset = 22 * 3
    # Display the last 3 lines and timestamps as text labels in reverse order
    for i, (line, timestamp) in enumerate(reversed(model_inferences_str_buffer)):
        ax.text(60, 508 + y_offset, f"({timestamp}) {line}", color="yellow", size=12)
        y_offset -= 22


def update_realtime_inference_labels(new_inference_string):
    # Format the timestamp as minutes:seconds:milliseconds
    timestamp = datetime.now().strftime("%M:%S:%f")[:-3]

    if len(model_inferences_str_buffer) == 3:
        # If the list has 3 lines, remove the oldest line
        model_inferences_str_buffer.pop(0)

        # Add the new line to the list
    model_inferences_str_buffer.append((new_inference_string, timestamp))


def animate(i):
    image_to_show = get_image(state.current_activity, state.update_image)

    open_cv_image = numpy.array(image_to_show)
    ax.clear()
    ax.imshow(open_cv_image)

    if state.current_activity != None:
        label_str = gestures_string_names[state.current_activity]
        ha = "center"
        color = "white"
        ax.text(320, 420, label_str, ha=ha, color=color, size=16)

    show_realtime_inference_labels()
    plt.axis("off")


def process_device_output_message(read_str):
    update_realtime_inference_labels(read_str)


# ========================================================================================


dir_path = os.path.dirname(os.path.abspath(__file__))
material_path = os.path.join(dir_path, "assets")

gestures_string_names = dict()
gestures_string_names[Gestures.UNKNOWN] = "UNKNOWN GESTURE"
gestures_string_names[Gestures.SWIPE_RIGHT] = "SWIPE RIGHT"
gestures_string_names[Gestures.SWIPE_LEFT] = "SWIPE LEFT"
gestures_string_names[Gestures.DOUBLE_SHAKE] = "DOUBLE SHAKE"
gestures_string_names[Gestures.DOUBLE_THUMB] = "DOUBLE THUMB"
gestures_string_names[Gestures.ROTATION_RIGHT] = "ROTATION RIGHT"
gestures_string_names[Gestures.ROTATION_LEFT] = "ROTATION LEFT"
gestures_string_names[Gestures.IDLE] = "NO MOVEMENTS"

main_img = Image.open(os.path.join(material_path, "Background.png"))

activity_idle_img = resize_icon_image(
    Image.open(os.path.join(material_path, "Idle.png"))
)
activity_unknown_img = resize_icon_image(
    Image.open(os.path.join(material_path, "Unknown.png"))
)
activity_swipe_right_img = resize_icon_image(
    Image.open(os.path.join(material_path, "SwipeRight.png"))
)
activity_swipe_left_img = resize_icon_image(
    Image.open(os.path.join(material_path, "SwipeLeft.png"))
)
activity_double_shake_img = resize_icon_image(
    Image.open(os.path.join(material_path, "DoubleShake.png"))
)  #
activity_double_thumb_img = resize_icon_image(
    Image.open(os.path.join(material_path, "DoubleThumb.png"))
)  #
activity_rotation_right_img = resize_icon_image(
    Image.open(os.path.join(material_path, "RotationRight.png"))
)  #
activity_rotation_left_img = resize_icon_image(
    Image.open(os.path.join(material_path, "RotationLeft.png"))
)

state = State()

model_inferences_str_buffer = []

fig, ax = plt.subplots(1, figsize=(15, 10))
ax.axis("off")
plt.box(False)
plt.axis("off")

ani = animation.FuncAnimation(fig, animate, interval=50)

signal.signal(signal.SIGINT, signal_handler)


# Comment out for testing - Bluetooth functionality
x = Thread(target=thread_ble)
x.start()

# Testing functionality - File reading
# x = Thread(target=thread_file)
# x.start()

plt.show()
