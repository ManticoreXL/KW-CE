CC = gcc
CFLAGS = -Wall
UTILS = utils.c
CRC8 = crc8.c
HAMMING = hamming74.c
TWOLAYER = twolayer.c

all: crc8_encoder crc8_decoder hamming_encoder hamming_decoder twolayer_encoder twolayer_decoder

# CRC-8 encoder
crc8_encoder:
	$(CC) $(CFLAGS) -DTEST_CRC8_ENC $(CRC8) $(UTILS) -o crc8_encoder

# CRC-8 decoder
crc8_decoder:
	$(CC) $(CFLAGS) -DTEST_CRC8_DEC $(CRC8) $(UTILS) -o crc8_decoder

# Hamming(7,4) encoder
hamming_encoder:
	$(CC) $(CFLAGS) -DTEST_HAMMING74_ENC $(HAMMING) $(UTILS) -o hamming74_encoder

# Hamming(7,4) decoder
hamming_decoder:
	$(CC) $(CFLAGS) -DTEST_HAMMING74_DEC $(HAMMING) $(UTILS) -o hamming74_decoder

# Two-layer encoder (CRC-8 → Hamming)
twolayer_encoder:
	$(CC) $(CFLAGS) -DTEST_TWOLAYER_ENC $(TWOLAYER) $(CRC8) $(HAMMING) $(UTILS) -o twolayer_encoder

# Two-layer decoder (Hamming → CRC-8)
twolayer_decoder:
	$(CC) $(CFLAGS) -DTEST_TWOLAYER_DEC $(TWOLAYER) $(CRC8) $(HAMMING) $(UTILS) -o twolayer_decoder

# Clean build artifacts
clean:
	rm -f *.o crc8_encoder crc8_decoder hamming_encoder hamming_decoder twolayer_encoder twolayer_decoder
