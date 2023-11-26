import asyncio
from bleak import BleakScanner


async def main():
    devices = await BleakScanner.discover()
    for d in devices:
        print(d)

asyncio.run(main())

# MAC Arduino E4:A7:60:CE:AB:79 or 6B:9E:3C:72:A1:91