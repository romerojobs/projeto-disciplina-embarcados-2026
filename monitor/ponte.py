import serial
import json
from influxdb_client import InfluxDBClient, Point
from influxdb_client.client.write_api import SYNCHRONOUS

#SERIAL_PORT = "COM3" #porta random, necessário trocar dps
SERIAL_PORT = "/dev/tty.usbmodem1301"
BAUD_RATE = 115200
TOKEN = "XU0j8rGvmQxH31LtEJVdkzSgll9x15D613ur2G3scpYpYlTDkMIDD3pGA1W2MBbi"
ORG = "labyrinth"
BUCKET = "mesa"
URL = "http://localhost:8086"

client = InfluxDBClient(url=URL, token=TOKEN, org=ORG)
write_api = client.write_api(write_options=SYNCHRONOUS)

print("Aguardando dados da serial...")

with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:
    while True:
        line = ser.readline().decode("utf-8").strip()
        if not line:
            continue
        try:
            data = json.loads(line)
            point = (
                Point("orientacao")
                .field("pitch", float(data["pitch"]))
                .field("roll", float(data["roll"]))
            )
            write_api.write(bucket=BUCKET, record=point)
            print(f"Enviado: pitch={data['pitch']}, roll={data['roll']}")
        except Exception as e:
            print(f"Erro: {e} | Linha recebida: {line}")