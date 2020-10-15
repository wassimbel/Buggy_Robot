from gpiozero import Robot
from time import sleep
from signal import pause
import RPi.GPIO as gpio


left_back = 7
left_forward = 11
right_back = 13
right_forward = 15


def setup():
    gpio.setmode(gpio.BOARD)
    gpio.setup(left_back, gpio.OUT)
    gpio.setup(left_forward, gpio.OUT)
    gpio.setup(right_back, gpio.OUT)
    gpio.setup(right_forward, gpio.OUT)


def forward(t=1):
    setup()
    gpio.output(7, False)
    gpio.output(11, True)
    gpio.output(13, False)
    gpio.output(15, True)
    sleep(t)


def backward(t=1):
    setup()
    gpio.output(7, True)
    gpio.output(11, False)
    gpio.output(13, True)
    gpio.output(15, False)
    sleep(t)


def pivot_right(t=1):
    setup()
    gpio.output(7, True)
    gpio.output(11, False)
    gpio.output(13, False)
    gpio.output(15, True)
    sleep(t)


def pivot_left(t=1):
    setup()
    gpio.output(7, False)
    gpio.output(11, True)
    gpio.output(13, True)
    gpio.output(15, False)
    sleep(t)


def turn_left(t=1):
    setup()
    gpio.output(7, False)
    gpio.output(11, False)
    gpio.output(13, False)
    gpio.output(15, True)
    sleep(t)


def turn_right(t=1):
    setup()
    gpio.output(7, False)
    gpio.output(11, True)
    gpio.output(13, False)
    gpio.output(15, False)
    sleep(t)


def cleanup():
    """ always cleanup """
    gpio.cleanup()
    sleep(1)

"""forward()
cleanup()
backward()
cleanup()
pivot_left(10)
cleanup()
pivot_right(10)
cleanup()
turn_left()
cleanup()
turn_right()
cleanup()"""
forward(3)
cleanup()
backward(3)
cleanup()
