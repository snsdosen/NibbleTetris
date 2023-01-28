# NibbleTetris

![Screenshot](showcase.png?raw=true "1")\

## Controls
* Left/Right - Move tetromino
* Up/Down - Speed up
* A - Rotate left
* B - Rotate right
* Menu - Pause/Start

## Installing the game
Download Arduino IDE for your operating system:
>https://www.arduino.cc/en/software

After you are done installing it go to "File"->"Preferences" and paste the following in the "Additional Boards Manager URLs":

> https://raw.githubusercontent.com/CircuitMess/Arduino-Packages/master/package_circuitmess.com_esp8266_index.json

Now go to "Tools"->"Board"->"Boards manager" and search for "Nibble" and install "CircuitMess ESP8266 Boards".

Now clone this repository to your computer and open "NibbleTetris.ino" with Arduino IDE.\
Select Nibble board ("Tools"->"Board"->"CircuitMess ESP8266 Boards"->"Nibble").\
Choose COM port for the console and start uploading by pressing Sketch->Upload.

Sketch will now compile and upload to your nibble console.
