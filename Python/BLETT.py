import asyncio
from bleak import BleakClient
import mysql.connector
import numpy as np
address = "D0:89:7D:1E:A1:8B"
characteristic_uuid = "00001526-1212-efde-1523-785feabcd123"

last_received_time = 0
paska = []

db_connection = mysql.connector.connect(
    host="",    
    user="",           
    password="",   
    database=""      
)

def notification_handler(sender, data):
    global paska, last_received_time
    value_str = bytearray(data).decode("ascii")
    
    try:
        
        value = int(value_str)
        paska.append(value)
        print(f"the values: {value}")
        
        if len(paska) == 4:
            a, x, y, z = paska
            print(f"le datat: a={a}, x={x}, y={y}, z={z}")        
            
            cursor = db_connection.cursor()
            cursor.execute("INSERT INTO data (a, x, y, z) VALUES (%s, %s, %s, %s)", (a, x, y, z))
            db_connection.commit()
        
            paska = []
             
    except ValueError:
        print("Received data is wrong!")    



    
    last_received_time = asyncio.get_event_loop().time()    
        
        
        
        
# Asynkroninen pääfunktio
async def main():
    global last_received_time

    async with BleakClient(address) as client:
        connected = client.is_connected
        last_received_time = asyncio.get_event_loop().time()
        print(f"Connected: {connected}")

        # Käynnistä ilmoitukset
        await client.start_notify(characteristic_uuid, notification_handler)

        # Aikaraja 30 s
        timeout = 30
        while True:
            # katoaaa onko menny 30s
            if asyncio.get_event_loop().time() - last_received_time > timeout:
                print("No data received in the last 30 seconds, stopping...")
                break  # Lopeta ohjelma

            # odotetaan
            await asyncio.sleep(1)

        # Lopeta ilmoitukset ja sulje yhteys
        await client.stop_notify(characteristic_uuid)
        print ("there aint coming more data so we close this shit ") 

asyncio.run(main())