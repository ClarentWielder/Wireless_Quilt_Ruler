from aiocoap import *
import time
import asyncio

async def main():
    client = await Context.create_client_context()
    request = Message(code=Code(1), uri='coap://192.168.1.23/read_distance')
    # while True:
    # print("Waiting Response")
    response = await client.request(request).response
    # print(response.payload)
    # print(type(response.payload))
    #foo = int.from_bytes(response.payload)
    foo = int(response.payload.decode())
    # print(foo)
    # print(type(foo))
    time.sleep(0.5)
    return foo


if __name__ == "__main__":
    bar = asyncio.run(main())
    print(bar)
