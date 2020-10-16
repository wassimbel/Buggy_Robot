from time import sleep
import RPi.GPIO as gpio


left_back = 7
left_forward = 11
right_back = 13
right_forward = 15
left_sensor = 3
right_sensor = 8


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


def forward():
    """ function to drive the robot forward """
    setup()
    gpio.output(7, False)
    gpio.output(11, True)
    gpio.output(13, False)
    gpio.output(15, True)


def backward():
    """ function to drive the robot backward """
    setup()
    gpio.output(7, True)
    gpio.output(11, False)
    gpio.output(13, True)
    gpio.output(15, False)


def pivot_right():
    """ function to make the robot pivot to the right """
    setup()
    gpio.output(7, True)
    gpio.output(11, False)
    gpio.output(13, False)
    gpio.output(15, True)


def pivot_left():
    """ function to make the robot pivot to the left """
    setup()
    gpio.output(7, False)
    gpio.output(11, True)
    gpio.output(13, True)
    gpio.output(15, False)


def turn_left():
    """ function to make the robot turn to the left """
    setup()
    gpio.output(7, False)
    gpio.output(11, False)
    gpio.output(13, False)
    gpio.output(15, True)


def turn_right():
    """ function to make the robot pivot to the right """
    setup()
    gpio.output(7, False)
    gpio.output(11, True)
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


def test():
    """ just testing some stuff """
    setup()
    if gpio.input(3) == 0:
        print('on')
    else:
        pivot_left()
        sleep(1)
    cleanup()

follow_line()
