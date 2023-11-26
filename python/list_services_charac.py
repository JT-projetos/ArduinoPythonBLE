import asyncio
from bleak import BleakClient, BleakScanner, BleakError

max_retries = 5

async def main(address):
    device = await BleakScanner.find_device_by_address(address, timeout=12.0)
    if not device:
        raise BleakError(f"A device with address {address} could not be found.")
    print(f"Found {device.address}: {device.name}")
    async with BleakClient(address) as client:
        if not client.is_connected:
            raise "client not connected"

        services = await client.get_services()

        for service in services:
            print('service', service.handle, service.uuid, service.description)


if __name__ == "__main__":
    address = "E4:A7:60:CE:AB:79"
    asyncio.run(main(address))
