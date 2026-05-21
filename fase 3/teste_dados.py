import time
import math
from influxdb_client import InfluxDBClient, Point
from influxdb_client.client.write_api import SYNCHRONOUS

TOKEN = "XU0j8rGvmQxH31LtEJVdkzSgll9x15D613ur2G3scpYpYlTDkMIDD3pGA1W2MBbi"
ORG = "labyrinth"
BUCKET = "mesa"
URL = "http://163.176.174.73:8086"

client = InfluxDBClient(url=URL, token=TOKEN, org=ORG)
write_api = client.write_api(write_options=SYNCHRONOUS)

print("Enviando dados simulados... (Ctrl+C para parar)")

t = 0
while True:
    pitch = round(math.sin(t) * 30, 2)
    roll = round(math.cos(t) * 20, 2)

    point = (
        Point("orientacao")
        .field("pitch", pitch)
        .field("roll", roll)
    )
    write_api.write(bucket=BUCKET, record=point)
    print(f"Enviado: pitch={pitch}, roll={roll}")

    t += 0.90
    time.sleep(0.90)