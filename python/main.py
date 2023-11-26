import asyncio
from bleak import BleakClient

address = "6B:9E:3C:72:A1:91"  # obtained from find_devices
MODEL_NBR_UUID = "19b10000-e8f2-537e-4f6c-d104768a1214"


async def main(address):
    async with BleakClient(address) as client:
        model_number = await client.read_gatt_char(MODEL_NBR_UUID)
        print("Model Number: {0}".format("".join(map(chr, model_number))))

asyncio.run(main(address))