from aiocoap import *
import asyncio
import random
import math

def get_width_measurement():
    # width = random.randint(36,72)
    width = asyncio.run(measure())
    return width

def get_height_measurement():
    # height = random.randint(36,72)
    height = asyncio.run(measure())
    return height

async def measure():
    client = await Context.create_client_context()
    request = Message(code=Code(1), uri='coap://192.168.1.23/read_distance')
    response = await client.request(request).response
    measurement = int(response.payload.decode())
    measurement = math.ceil(measurement/25.4)
    return measurement