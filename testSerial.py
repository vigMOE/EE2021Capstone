#!/usr/bin/env python3
import serial
import time
if __name__ == '__main__':
    try:
        #sensor board (top right)
        dev0 = serial.Serial('/dev/ttyACM0', 115200, timeout = 1)
        dev0.flush()
        print("ACM0")
    except:
        print("\t no AMC0")
    
    try:
        #sound board (top left)
        dev1 = serial.Serial('/dev/ttyACM1', 115200, timeout = 1)
        dev1.flush()
        print("ACM1")
    except:
        print("\t no AMC1")
    
    try:
        #drivetrain/arm (bottom right)
        dev2 = serial.Serial('/dev/ttyACM2', 115200) #, timeout = 1)
        dev2.flush()
        print("ACM2") 
    except:
        print("\t no AMC2")
    
    try:
        dev3 = serial.Serial('/dev/ttyACM3', 115200, timeout = 1)
        dev3.flush()
        print("ACM3")
    except:
        print("\t no AMC3")
    
    
    
     
    #jank = 0
    while True:
        #jank = jank + 1
        #print("jank\t"+str(jank))
        #if jank % 22 == 0:
        #    print("sending 1:0:1")
        #    dev2.write(b'1:0:1\x00')
        #time.sleep(1)
        '''
        try:
            print("AMC0\t"+dev0.readline().decode('utf-8').rstrip())
        except KeyboardInterrupt:
            break
        except:
            continue

        try:
            print("AMC1\t"+dev1.readline().decode('utf-8').rstrip())
        except KeyboardInterrupt:
            break
        except:
            continue
        '''
        try:
            print("AMC2\t"+dev2.readline().decode('utf-8').rstrip())
        except KeyboardInterrupt:
            break
        except:
            continue
        '''
        try:
            print("AMC3\t"+dev3.readline().decode('utf-8').rstrip())
        except KeyboardInterrupt:
            break
        except:
            continue
    ''' 
