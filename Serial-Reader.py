import serial
import time
import struct
from datetime import datetime

with open(f'IVDR-Data_{datetime.now().strftime("%Y_%m_%d-%H_%M_%S")}.csv', 'w') as f:
    with serial.Serial("COM5", 115200) as s:
        print("Estableciendo Conexion...")
        s.timeout = 1
        total_processed = 0
        last_timestamp = 0
        #time.sleep(0.5)
        while True:
            sync = s.read(1)
            s.write(sync)
            print(f"Byte recibido: {sync.hex()}")
            sync = s.read(1)
            print(f"Byte recibido de respuesta: {sync.hex()}")
            if sync == bytes([0xFF]):
                break
        s.timeout = None
        print("Dispositivos sincronizados.")
        while True:
            line = s.read(12)
            b = bytearray(line)
            #print(f"Length: {len(b)} Bytes: {line.hex()}")
            timestamp = 0
            for i in range(4):
                timestamp = timestamp * (2 ** 8) + int(b[i])
            voltaje = struct.unpack('<f', b[4:8])
            corriente = struct.unpack('<f', b[8:12])
            f.write(f"{timestamp},{voltaje:.4f},{corriente:.4f}")
            f.write("\n")
            last_timestamp = timestamp
            total_processed += 1
            if total_processed % 10 == 0:
                print(f"Procesado {total_processed} mensajes. Ultimo timestamp: {last_timestamp} Bytes en el buffer: {s.in_waiting}")
