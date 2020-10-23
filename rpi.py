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
#needs lidars, gyro, and motor controller
def drive(target_distance, direction):
    #PID loop to account for distance error and theta error
    distance_init=lidar.getDistance()
    gyro_init=gyro.getAngle()
    itteration_time = #arbitrary value

    #linear variable init
    linear_error_prior = 0
    linear_integral_prior = 0
    linear_KP = #arbitrary value
    linear_KI = #arbitrary value
    linear_KD = #arbitrary value
    linear_tolerance = #arbitrary value
    #angular variable init
    angular_error_prior = 0
    angular_integral_prior = 0
    angular_KP = #arbitrary value
    angular_KI = #arbitrary value
    angular_KD = #arbitrary value
    angular_tolerance = #arbitrary value

    for(linear_error=linear_tolerance+1;linear_error>linear_tolerance;) 
        linear_error = target_distance – (distance_init-lidar.getDistance())
        angular_error = gyro_init – gyro.getAngle()

        linear_integral = linear_integral_prior + linear_error * iteration_time
        angular_integral = angular_integral_prior + angular_error * iteration_time

        linear_derivative = (linear_error – linear_error_prior) / iteration_time
        angular_derivative = (angular_error – angular_error_prior) / iteration_time

        linear_output = linear_KP*linear_error + linear_KI*linear_integral + linear_KD*linear_derivative
        angular_output = angular_KP*angular_error + angular_KI*angular_integral + angular_KD*angular_derivative

        if(direction = 1)
            x=linear_output
            y=0
        elif(direction = 2)
            x=0
            y=linear_output
        elif(direction = 3)
            x=-linear_output
            y=0
        elif(direction = 4)
            x=0
            y=-linear_output

        Serial.send(encode(arduino.drive, x, y, angular_output))
        linear_error_prior = linear_error
        angular_error_prior = angular_error

        linear_integral_prior = linear_integral
        angular_integral_prior = angular_integral

        sleep(iteration_time)
    
    

#needs motor control and gyro
def rotate(target_angle):
    itteration_time = #arbitrary value
    #angular variable init
    angular_error_prior = 0
    angular_integral_prior = 0
    angular_KP = #arbitrary value
    angular_KI = #arbitrary value
    angular_KD = #arbitrary value
    angular_tolerance = #arbitrary value
    for(angular_error=angular_tolerance+1;angular_error>angular_tolerance;) 
        angular_error = target_angle – gyro.getAngle()
        angular_integral = angular_integral_prior + angular_error * iteration_time
        angular_derivative = (angular_error – angular_error_prior) / iteration_time
        angular_output = angular_KP*angular_error + angular_KI*angular_integral + angular_KD*angular_derivative
        Serial.send(encode(arduino.drive, 0, 0, angular_output))
        angular_error_prior = angular_error
        angular_integral_prior = angular_integral
        sleep(iteration_time)
    
    
