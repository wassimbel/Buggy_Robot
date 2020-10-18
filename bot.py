from time import sleep, time
import RPi.GPIO as gpio

left_forward = 7
left_back = 11
right_forward = 13
right_back = 15
left_sensor = 29
right_sensor = 33
servo_pin = 18
pinTrigger = 
pinEcho = 


def setup():
    """ initialize the robot with input and output pins
        from the raspberry pi 3 b+ """

    """ the mode in which we will use the pins """
    gpio.setmode(gpio.BOARD)
    """ setup the left wheels to spin backward """
    gpio.setup(left_back, gpio.OUT)
    """ setup the left wheels to spin forward """
    gpio.setup(left_forward, gpio.OUT)
    """ setup the right wheels to spin backward """
    gpio.setup(right_back, gpio.OUT)
    """ setup the right wheels to spin forward """
    gpio.setup(right_forward, gpio.OUT)
    """ setup the left sensor to receive input state """
    gpio.setup(left_sensor, gpio.IN)
    """ setup the right sensor to receive input state """
    gpio.setup(right_sensor, gpio.IN)
    """ servomotot setup"""
    gpio.setup(servo_pin, gpio.OUT)
    """ setup sound sensor """
    gpio.setup(pinTrigger, GPIO.OUT)  # Trigger
    gpio.setup(pinEcho, GPIO.IN)  # Echo


def forward():
    """ function to drive the robot forward """
    setup()
    gpio.output(7, True)
    gpio.output(11, False)
    gpio.output(13, True)
    gpio.output(15, False)


def backward():
    """ function to drive the robot backward """
    setup()
    gpio.output(7, False)
    gpio.output(11, True)
    gpio.output(13, False)
    gpio.output(15, True)


def pivot_right():
    """ function to make the robot pivot to the right """
    setup()
    gpio.output(7, False)
    gpio.output(11, True)
    gpio.output(13, True)
    gpio.output(15, False)


def pivot_left():
    """ function to make the robot pivot to the left """
    setup()
    gpio.output(7, True)
    gpio.output(11, False)
    gpio.output(13, False)
    gpio.output(15, True)


def turn_left():
    """ function to make the robot turn to the left """
    setup()
    gpio.output(7, False)
    gpio.output(11, False)
    gpio.output(13, True)
    gpio.output(15, False)


def turn_right():
    """ function to make the robot pivot to the right """
    setup()
    gpio.output(7, True)
    gpio.output(11, False)
    gpio.output(13, False)
    gpio.output(15, False)


def follow_line():
    """ function to make the robot follow a line (black or white) """
    setup()
    try:
        while True:
            if not gpio.input(3) and not gpio.input(8):
                forward()
            if gpio.input(3) and not gpio.input(8):
                turn_right()
            if not gpio.input(3) and gpio.input(8):
                turn_left()
    except KeyboardInterrupt:
        pass
    finally:
        cleanup()


def cleanup():
    """ restart the pins to starting state"""
    gpio.cleanup()


def servo1():
    setup()
    servo1 = gpio.PWM(18, 50)
    servo1.start(0)
    sleep(1)
    servo1.ChangeDutyCycle(2)
    duty = 2
    while duty <= 12:
        servo1.ChangeDutyCycle(duty)
        sleep(0.3)
        servo1.ChangeDutyCycle(0)
        sleep(0.7)
        duty += 1
    servo1.stop()


def distance():
    gpio.output(pinTrigger, true)
    time.sleep(0.00001)
    gpio.output(pinTrigger, false)
    when_start = time()
    while not gpio.input(pinEcho):
        when_finished = when_start
    while gpio.input(pinEcho):
        when_finished = time()
    if when_finished - when_start >= 0.08
        
