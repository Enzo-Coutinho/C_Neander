
with open("test.mem", "rb") as f:
  data = f.read()

# Skip 4-byte header (03 4E 44 52), then take every 2nd byte
print(hex(data[:4]))
memory = list(data[4::2])

print([hex(b) for b in memory[:4]])  # ['0x10', '0xf0', ...]
