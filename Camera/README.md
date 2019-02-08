Hello, You can initiate the project from this part.
The camera module used is OV7670 1/5-Inch 0.3-Megapixel Camera Module. You can check its description <a href="https://hackerstore.nl/PDFs/camera.pdf">here</a>.

### Components Required :

1. Arduino Uno Board and USB cable
2. OV7670 Arduino Camera Sensor Module
3. 10K resistor X 2
4. 4.7K Resistor X2
5. Breadboard
6. Jumper Cables (18 Male to Female & 10 Male to Male)

### Pin connection (OV7670>>>Arduino Uno) :

You can refer the pin diagram from ![alt text](https://i.imgur.com/KyPlsRB.png)

### Steps to proceed further :

1. Download the JDK file from <a href="https://cdn.instructables.com/ORIG/FDI/07P7/IUOHOM44/FDI07P7IUOHOM44.rar">here</a>. 
By default, this will be install to your C drive in your program files folder. As for mine, it is stored in C:\Program Files\Java\jdk1.8.0_74. 

2. Download the Arduino IDE application from <a href="https://www.arduino.cc/download.php?f=/arduino-nightly-windows.zip">here</a>. (For Windows) OR you can simply visit the official Arduino website--https://www.arduino.cc/

3. Open the Code folder and open the 'UNO.ino' or 'Mega_OR_UNO.ino' file (both are working).

4. In the Arduino IDE application you can see the port in which your Arduino UNO/MEGA 2560 is connected. It is in the bottom right corner. eg: Arduino/Genuino Mega on COM1. You can change the port by following the below steps : Control Panel > Device Manager > Ports (COM & LPT) > right click > Properties > Port Settings > Advanced > COM Port Number > /Select Your Port Number/.

5. Now according to your port number copy the 'com_X' folder. eg: Mine is 'com_1'. And paste the com folder to this destination "C:\Program Files\Java\jdk1.8.0_74\bin".

6. Create a "out" folder in your C drive ("C:\"). The captured frames will be stored here.

7. Open the "Extra" folder and copy "win32com.dll" in the "C:\Program Files\Java\jdk1.8.0_74\jre\bin" directory.

8. In the same folder(Extra) open the "lib" folder, there are two files--"comm.jar" and "javax.comm.properties".
9. First copy and paste "comm.jar" in "C:\Program Files\Java\jdk1.8.0_74\jre\lib\ext".
10. Then, copy and paste "comm.jar" and "javax.comm.properties" in the "C:\Program Files\Java\jdk1.8.0_74\jre\lib" directory.

9. Open cmd and open the folder wherein the code folder is by writing its address. Mine is "C:\Program Files\Java\jdk1.8.0_74\bin".  Click enter and it will give u "C:\Program Files\Java\jdk1.8.0_74\bin>". Now, write "java code.SimpleRead". It supposed to be like this---> ### C:\Program Files\Java\jdk1.8.0_74\bin>java code.SimpleRead

10. You can see the picture taken from your OV7670 Camera Module Sensor in your "out" folder in c drive. It will display in the cmd, something like this-

 - Port name: COM2
 - Looking for image
 - Found image: 0
 - Saved image: 0
 - Looking for image
 - Found image: 1
 - Saved image: 1.......

