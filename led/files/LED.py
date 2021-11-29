import RPi.GPIO as GPIO
import time
import sys

pin = 18

# Setting the GPIO pins referring mode to BCM GPIO.setmode (GPIO.BCM)
GPIO.setmode(GPIO.BCM)

# Setting the GPIO pin 18 to output mode
GPIO.setup(pin, GPIO.OUT)

state=str(sys.argv[1])
state=state.lower()

if state == "on":
    GPIO.output(pin,False)
elif state == "off":
    GPIO.output(pin,True)


