import serial


#Establish Connection to RPI
try:
    usb = serial.Serial(USB_PORT, 9600, timeout=2)
    #usb.write(b'')
    #usb.readline()
except:
    print("error connecting")
    exit()

#Execution Loop
while True:
    command = input("Enter command: ")
    if command == "a":  # read Arduino A0 pin value
        print("Arduino A0 value:", value)
    elif command == "x":  # exit program
        print("Exiting program.")
    else:
        exit()


'''
import serial
import RPi.GPIO as GPIO
import time
ser=serial.Serial("/dev/ttyACM0",9600)  #change ACM number as found from ls /dev/tty/ACM*
'''
