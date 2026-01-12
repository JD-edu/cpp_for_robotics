import serial
import struct

SERIAL_PORT = "/dev/ttyUSB0"  # 환경에 맞게 수정 (예: COM3)
BAUD_RATE = 115200

def read_sensor_data():
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        ser.reset_input_buffer()
        print(f"Connected to {SERIAL_PORT}. Waiting for sync...")

        while True:
            # 1. 첫 번째 헤더 0xF5 찾기
            if ser.read(1) == b'\xf5':
                # 2. 곧바로 두 번째 헤더 0xFA 확인
                if ser.read(1) == b'\xfa':
                    # 두 헤더가 모두 일치하면 나머지 16바이트 읽기
                    remaining_data = ser.read(16)
                    
                    if len(remaining_data) == 16:
                        # ">hhhhhhhh" (2바이트 정수 8개)
                        data = struct.unpack(">hhhhhhhh", remaining_data)
                        
                        accel = data[0:3]
                        gyro = data[3:6]
                        enc1, enc2 = data[6], data[7]
                        
                        print(f"Enc: [{enc1}, {enc2}] | IMU: {accel} | Gyro: {gyro}")
                    else:
                        print("Packet lost: incomplete data")
                        ser.reset_input_buffer()
                else:
                    # 0xF5 다음에 0xFA가 아니면 동기화 실패이므로 버퍼 비움
                    ser.reset_input_buffer()

    except Exception as e:
        print(f"Error: {e}")
    finally:
        if 'ser' in locals() and ser.is_open:
            ser.close()
            print("Serial port closed.")

if __name__ == "__main__":
    read_sensor_data()