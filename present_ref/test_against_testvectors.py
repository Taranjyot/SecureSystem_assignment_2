#!/usr/bin/python
import serial
import time
import sys

BLOCK_SIZE = 8
KEY_SIZE = 10
CPU_FREQUENCY = 125e6

BAUDRATE = 9600

if len(sys.argv) != 2:
    sys.exit("Usage: python3 ./test_against_testvectors.py [COMPORT, e.g. /dev/ttySX on WSL]")

COM_PORT = sys.argv[1]

ser = serial.Serial(COM_PORT, BAUDRATE, timeout=1)

tv_pt = [
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,	
    0x45, 0x84, 0x22, 0x7B, 0x38, 0xC1, 0x79, 0x55,
]

tv_key = [
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x3c, 0xf4, 0x00, 0xd8, 0x28, 0xf1, 0x08, 0x7a, 0x60, 0x26,
]

tv_ct = [
    0x45, 0x84, 0x22, 0x7B, 0x38, 0xC1, 0x79, 0x55,
    0x49, 0x50, 0x94, 0xF5, 0xC0, 0x46, 0x2C, 0xE7,
    0x7B, 0x41, 0x68, 0x2F, 0xC7, 0xFF, 0x12, 0xA1,
    0xD2, 0x10, 0x32, 0x21, 0xD3, 0xDC, 0x33, 0x33,
    0xd0, 0x44, 0x6a, 0x0a, 0xc9, 0x13, 0x35, 0xd4,
]

TV_COUNT = int(len(tv_pt) / BLOCK_SIZE)

def unpack_le(s):
    return sum((s[i]) << (8 * i) for i in range(len(s)))

debug = False

print("[+] Using com port " + COM_PORT)

for tv in range(TV_COUNT):
    
    print("== Testvector " + str(tv))
    
    # Initial command
    buf = str.encode("e")
    
    # Assemble key and plaintext
    buf += bytes(tv_key[tv*KEY_SIZE:(tv+1)*KEY_SIZE])
    buf += bytes(tv_pt[tv*BLOCK_SIZE:(tv+1)*BLOCK_SIZE])

    if debug:
        print("[i] TX: " + buf.hex())

    # Do operation
    ser.write(buf)

    # Get answer
    rx = ser.read(8 + BLOCK_SIZE)

    # duration in CPU cycles and seconds
    duration = unpack_le(rx[BLOCK_SIZE:])

    if debug:
        print("[i] RX: " + rx.hex())
    
    print("[+] Cycle count = " + str(duration) + " = " + str(duration/CPU_FREQUENCY) + " s")
    
    # Check result
    r_ref = bytes(tv_ct[tv*BLOCK_SIZE:(tv+1)*BLOCK_SIZE])
    r_comp = rx[:BLOCK_SIZE]
    
    if r_ref == r_comp:
        print("[OK] Result correct: " + ''.join('{:02x} '.format((x)) for x in r_comp).upper())
    else:
        print ("[FAILED]")
        print ("Got  : " + ''.join('{:02x} '.format((x)) for x in r_comp).upper())
        print ("Exp't: " + ''.join('{:02x} '.format((x)) for x in r_ref).upper())
     
    print()
	
    time.sleep(0.1)

ser.close()
