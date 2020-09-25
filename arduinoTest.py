import serial
import RPi.GPIO as GPIO
import time
ser=serial.Serial("/dev/ttyACM0",9600)  #change ACM number as found from ls /dev/tty/ACM*


