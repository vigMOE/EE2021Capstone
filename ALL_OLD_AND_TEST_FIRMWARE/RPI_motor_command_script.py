import time
import serial


if __name__ == '__main__':

    try:
        # motor and servo arm board
        dev2 = serial.Serial('/dev/ttyACM2', 115200) #, timeout = 1)
        dev2.flush()
        print("ACM2 Motor Input Initialized") 
        dev2.isOpen()
        print("Enter your commands below.\r\nInsert 'exit' to leave the application.")
		
    except:
        print("\t no AMC2 Motor Serial Port")

    #input = 1
    while True:
        #print("AMC2\t"+dev2.readline().decode('utf-8').rstrip())
        inputt = input(">> ")
		
        if inputt == "exit":
            print("exiting...")
            dev2.close()
            exit()
			
		#halt command
		if inputt == "e"
			dev2.write("1:0:1")
			dev2.write("1:0:1")
			dev2.write("1:0:1")
			inputt = ""
			
		#move forward command
		if inputt == "w"
			dev2.write("1:0:2")
			dev2.write("1:0:2")
			dev2.write("1:0:2")
			inputt = ""
		
		#move backward command
		if inputt == "s"
			dev2.write("1:0:5")
			dev2.write("1:0:5")
			dev2.write("1:0:5")
			inputt = ""
			
		#move left command
		if inputt == "a"
			dev2.write("1:0:8")
			dev2.write("1:0:8")
			dev2.write("1:0:8")
			inputt = ""
			
		#move right command
		if inputt == "s"
			dev2.write("1:0:11")
			dev2.write("1:0:11")
			dev2.write("1:0:11")
			inputt = ""
			
		#yeet command
		if inputt == "r"
			dev2.write("1:0:14")
			
        else:
            # send the character to the device
            # (note that I happend a \r\n carriage return and line feed to the characters - this is requested by my device)
            inputt = inputt + "\n"
            inputt = inputt.encode()
            dev2.write(inputt)
            dev2.write(inputt)
            dev2.write(inputt)
            print(inputt)
                #out = ''
            # let's wait one second before reading output (let's give device time to answer)
            #time.sleep(1)
            inputt = ""
           # while ser.inWaiting() > 0:
            #    out += ser.read(1)

            #if out != '':
            #    print(">>" + out)
			
		
