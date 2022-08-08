"""
This script creates a combined firmware file which contains a header and firmware files for all MCUs.
The format of the file looks like this:
[HEADER][TLV][FIRMWARE1][TLV][FIRMWARE2]

HEADER = GAGGIUINO_FW
TLV =
  TAG - uint8, 0x01 backend firmware, 0x0A frontend fw
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
input_fw_files = {}
for arg in sys.argv[2:]:
  priority = arg.split(':')[0].strip()
  firmware = arg.split(':')[1].strip()
  input_fw_files[priority] = firmware

print("Output file: " + output_file)
print("Combining these firmware files: " + ', '.join(input_fw_files.values()))

with open(output_file,'wb') as out:
  out.write(b'GAGGIUINO_FW')
  for prio in sorted(input_fw_files, reverse=True):
    with open(input_fw_files[prio], 'rb') as input:
      print("Processing file: " + input_fw_files[prio] + " with prio: " + prio)
      tag = get_uint(int(prio))
      length = get_uint(os.path.getsize(input_fw_files[prio]), 32)
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


