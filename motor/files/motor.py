import RPi.GPIO as gpio
import time
import sys

gpio.setwarnings(False)
gpio.cleanup()
gpio.setmode(gpio.BCM)

PIN=21
command=str(sys.argv[1])
command=command.lower()
gpio.setup(PIN,gpio.OUT)

if command == "on":
    gpio.output(PIN,True)
    print("Motor On")
elif command == "off" :
    gpio.output(PIN,False)
    print("Motor Off")

exit (0)
