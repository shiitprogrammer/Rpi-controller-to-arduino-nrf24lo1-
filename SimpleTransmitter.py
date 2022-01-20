import RPi.GPIO as GPIO
import time

import spidev
from  lib_nrf24 import NRF24

GPIO.setmode(GPIO.BCM)

pipes = [0xe8 ,0xe8 ,0xf0 ,0xf0 ,0xe1]
radio = NRF24(GPIO, spidev.SpiDev())
radio.begin(0,5)
radio.setPayloadSize(32)
radio.setChannel(0x77)
radio.setDataRate(NRF24.BR_1MBPS)
radio.setPALevel(NRF24.PA_MIN)

radio.setAutoAck(False)
radio.enableDynamicPayloads()
radio.enableAckPayload()

radio.openWritingPipe(pipes)
radio.printDetails()
radio.stopListening()
radio.flush_tx()

char text = "Hello Fuckers"

while True: 

    radio.write(text)
    radio.flush_tx()
    
