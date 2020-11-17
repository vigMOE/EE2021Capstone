#!/usr/bin/env python3
import serial
import time
if __name__ == '__main__':
    try:
        #drivetrain/arm (bottom right)
        dev2 = serial.Serial('/dev/ttyACM2', 115200) #, timeout = 1)
        dev2.flush()
        print("ACM2") 
    except:
        print("\t no AMC2")
   

    while(1):
        print('494')
        dev2.write(b'0:6:494\n')
        time.sleep(3)
        print('894')
        dev2.write(b'0:6:894\n')
        time.sleep(3)
        '''
        print("1:0:1") 
        dev2.write(b'1:0:1\n')
        time.sleep(.5)
        print("1:0:2")
        dev2.write(b'1:0:2\n')
    
        time.sleep(.5)
        print("1:0:5")
        dev2.write(b'1:0:5\n')
    
        time.sleep(.5)
        print("1:0:2")
        dev2.write(b'1:0:2\n')
    
        time.sleep(.5)
        print("1:0:1")
        dev2.write(b'1:0:1\n')
        '''
