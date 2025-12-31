import smbus
import time

# Define the I2C bus
i2c = smbus.SMBus(1)

# Device addresses
ROM = 0x50   
SEG = 0x0b     

# Declare messages
mesg1 = 'micro-processor 2024 fall semester'
mesg2 = 'Laboratory Exercise Number 10'
mesg3 = 'Kwangwoon University - CE'
mesg4 = 'Minseok Choi - 2020202090'

data = [ord(char) for char in (mesg1 + '\n' + mesg2 + '\n' + mesg3 + '\n' + mesg4)]
len = len(data)

# Write data to EEPROM
def write_to_eeprom(data, rom_addr=0x00):
    for i, byte in enumerate(data):
        high_addr = (rom_addr + i) >> 8 
        low_addr = (rom_addr + i) & 0xFF 
        i2c.write_i2c_block_data(ROM, high_addr, [low_addr, byte])
        time.sleep(0.05)

# Read data from EEPROM
def read_from_eeprom(len, rom_addr=0x00):
    read_data = []
    for i in range(len):
        high_addr = (rom_addr + i) >> 8 
        low_addr = (rom_addr + i) & 0xFF
        i2c.write_i2c_block_data(ROM, high_addr, [low_addr])
        byte = i2c.read_byte(ROM)
        read_data.append(byte)
        time.sleep(0.05)
    return read_data

# Display data on 7-segment display
def display_on_7seg(data):
    i2c.write_byte(SEG, 0x76)
    for byte in data:
        i2c.write_byte(SEG, byte)
        time.sleep(0.5)

write_to_eeprom(data)
rData = read_from_eeprom(len)
display_on_7seg(rData)
