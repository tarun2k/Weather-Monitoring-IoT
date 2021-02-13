<h1>IoT based Weather Monitoring System </h1>

<h2>The following are the requirements for this project:</h2>

<h2> Software Requirements: </h2>

1.) Arduino IDE

<h2> Hardware Requirements: </h2>

1.)	 Arduino Uno 

2.)	 Wifi Module (ESP8266)

3.)	 Humidity and Temperature sensor (DHT11)

4.)	 Solar Cell, 5V 

5.)	 Breadboard 

6.)	 Jumper Wires

7.)	 CO sensor (MQ7 and MQ9)

8.)	 DC Step down converter LM2596

<h2> Schematic Diagram </h2> 

![alt text](https://github.com/tarun2k/Weather-Monitoring-IoT/blob/master/Schematic%20Diagram/Schematic%20Diagram.JPG?raw=true)

<h2> Deploying and Testing </h2>


1.) <b> Programming Arduino UNO </b>

-> Connect the board to your computer using the USB cable. The green power LED (labelled PWR) should go on.

-> In tools, select the board as Arduino UNO on Arduino IDE, if not selected automatically and select the port.

-> Open the Arduino program attached above in the Arduino IDE.

-> Now, simply click the "Upload" button in the environment. Wait a few seconds - you should see the RX and TX leds on the board flashing. If the upload is successful, the message "Done uploading." will appear in the status bar.


2.) <b> Programming Wifi Module ESP8266 </b>

-> Connect the board to your computer using the USB cable.

-> Open Arduino IDE, click on 'File' and then 'Preferences'.

-> In addiditional boards manager urls, add url for ESP8266 board and click 'OK'.

-> Now on the IDE, go to 'Tools' and then 'board->boards manager', and then type esp8266 and click on install.

-> Select the ESP8266 board from the tools.

-> Open the ESP8266 program from above on the Arduino IDE.

-> Enter your google spreadsheet id, wifi name and password. 

-> Now, simply click the "Upload" button in the environment. Wait a few seconds - you should see the RX and TX leds on the board flashing. If the upload is successful, the message "Done uploading." will appear in the status bar.

3.) <b> Deploying web app on google sheets </b>

-> Make sure that you use the same google sheet whose id you have typed in the ESP8266 program.

-> Now give Headings on the spreadsheet as 'Date', 'Temperature(in <sup>o</sup>C)', 'Humidity', 'Gas Reading' and 'Solar Cell (in V)'.

-> Click on tools and then click on Script Editor.

-> Enter the code given above in the editor.

-> Click on publish and then deploy as web app.

<hr>

Power your Arduino UNO using a power adaptor and observe sensors' readings being published on the google sheets. 
