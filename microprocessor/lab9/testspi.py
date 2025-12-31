import spidev
import time

spi7 = spidev.SpiDev()
spi7.open(0, 0)
spi7.max_speed_hz = 5000
spi7.mode = 0b00

# initialize 7-seg display
spi7.writebytes([0x76])

# set colon byte
colon = 0x10

while True:
    hour = int(time.strftime("%H", time.localtime()))
    min = time.localtime().tm_min

    # preprocess time digit
    # divide numbers by 10 and take the quotient for high, the remain for low
    hrH = hour // 10
    hrL = hour % 10
    mnH = min // 10
    mnL = min % 10

    # write time data to 7-seg
    spi7.writebytes([hrH, hrL, mnH, mnL])

    # blink colon
    time.sleep(1)
    colon = colon ^ 0x10
    spi7.writebytes([0x77, colon])
