"""
This script creates a combined firmware file which contains a header and firmware files for all MCUs.
The format of the file looks like this:
[HEADER][TLV][FIRMWARE1][TLV][FIRMWARE2]

HEADER = GAGGIUINO_FW
TLV =
  TAG - uint8, default value 0x01
  LENGTH - uint32, length of the firmware in bytes

FIRMWARE must be ordered in the same way as they are flashed, that means backend firmware first and frontend firmware as the last one
"""

import sys
import os
import struct
import binascii

def get_uint(number, nbits: int = 8):

  if nbits == 8:
    s = struct.Struct("<B")
    return s.pack(number)
  elif nbits == 16:
    s = struct.Struct("<I")
    return s.pack(number)
  elif nbits == 32:
    s = struct.Struct("<Q")
    return s.pack(number)
  else:
    print("ERROR: Trying to get uint of size > 32 bits")
    return 0

output_file = sys.argv[1]
input_fw_files = sys.argv[2:]

print("Output file: " + output_file)
print("Combining these firmware files: " + ', '.join(input_fw_files))

with open(output_file,'wb') as out:
  out.write(b'GAGGIUINO_FW')
  for in_fw in input_fw_files:
    with open(in_fw, 'rb') as input:
      tag = get_uint(1)
      length = get_uint(os.path.getsize(in_fw), 32)
      print(binascii.hexlify(tag))
      print(binascii.hexlify(length))
      out.write(tag)
      out.write(length)
      while True:
        buf=input.read(102400)
        if buf:
          out.write(buf)
        else:
          break


