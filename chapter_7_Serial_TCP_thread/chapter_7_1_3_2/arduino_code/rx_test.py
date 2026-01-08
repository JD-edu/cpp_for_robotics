import serial
import struct
import time

# 설정 (환경에 맞게 수정하세요)
SERIAL_PORT = "/dev/ttyUSB0" 
BAUD_RATE = 115200
HEADER_BYTE = 0xAA  # 아두이노 코드의 HEADER와 일치시킴
EXPECTED_SIZE = 0x06 # 아두이노 코드의 PACKET_SIZE

def read_arduino_data():
    ser = None
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        print(f"Connected to {SERIAL_PORT} at {BAUD_RATE} baud.")

        while True:
            # 1. 헤더(0xAA) 찾기
            byte = ser.read(1)
            if not byte:
                continue

            if ord(byte) == HEADER_BYTE:
                # 2. 헤더 이후의 전체 데이터 읽기 
                # (PACKET_SIZE 1바이트 + 데이터 4바이트 + 체크섬 1바이트 = 총 6바이트)
                packet_rest = ser.read(6)
                
                if len(packet_rest) == 6:
                    # 데이터 분리
                    p_size = packet_rest[0]
                    p_data = packet_rest[1:5] # 4바이트 데이터 부분
                    p_checksum = packet_rest[5]

                    # 3. 패킷 크기 확인
                    if p_size != EXPECTED_SIZE:
                        print(f"Size mismatch: expected {EXPECTED_SIZE}, got {p_size}")
                        continue

                    # 4. 체크섬 검증 (데이터 4바이트를 XOR 연산)
                    # 아두이노: packet[2]^packet[3]^packet[4]^packet[5]
                    calculated_checksum = p_data[0] ^ p_data[1] ^ p_data[2] ^ p_data[3]

                    if calculated_checksum == p_checksum:
                        # 5. 데이터 해석 (Big-endian 4바이트 정수: >i)
                        # 아두이노에서 (value >> 24) 순으로 보냈으므로 Big-endian입니다.
                        final_value = struct.unpack(">i", p_data)[0]
                        print(f"수신 성공 - 값: {final_value} (Hex: 0x{p_data.hex()})")
                    else:
                        print(f"Checksum Error: Calc(0x{calculated_checksum:02X}) != Recv(0x{p_checksum:02X})")
                else:
                    print(f"Incomplete packet: expected 6 bytes after header, got {len(packet_rest)}")

    except serial.SerialException as e:
        print(f"Error: {e}")
    except KeyboardInterrupt:
        print("\nExiting...")
    finally:
        if ser and ser.is_open:
            ser.close()
            print("Serial port closed.")

if __name__ == "__main__":
    read_arduino_data()