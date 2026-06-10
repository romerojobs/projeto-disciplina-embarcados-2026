import serial

#SERIAL_PORT = "COM6"  # Windows
SERIAL_PORT = "/dev/tty.usbmodem1301" # MacOS
#SERIAL_PORT = "/dev/ttyACM0" # Linux

BAUD_RATE = 115200

print(f"Aguardando dados na porta {SERIAL_PORT}...")

with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as ser:
    while True:
        line = ser.readline().decode("utf-8", errors="ignore").strip()
        if not line:
            continue
        print(f"Recebido: {line}")