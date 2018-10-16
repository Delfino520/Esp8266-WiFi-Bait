

1. Introduction

WiFi Bait is a firmware for Esp8266, whose function is similar with wifiphisher. Esp8266 with this firmware creates a fake wireless network that looks similar to a legitimate network, and all the devices connected to the wireless network be disconnected. when people connect to the fake wireless network, then the fake webpage will pop up and request all the people to input wifi password. After people input wifi password, WiFi Bait will compare it with handshake captured, if the password is right then the attack will be ceased, people can reconnect to the real WIFI, and the fake WIFI will be disappear. After that we can log in the backend to check the wifi password.



2. Installation

How to make a WIFI BAIT with ESP8266?

1). First of all you need one piece of ESP8266 development board with
MicroUSB port, like this one below:

![](https://github.com/Delfino520/Pictures/blob/master/15063564774943.jpg)

2). Upload the WIFI BAIT firmware to ESP8266
* Install dirver for your ESP8266 (CH341SER.zip, i have uploaded on Github for you guys to use)
* You need flash_download_tools_v3.6.5 and WIFI BAIT firmware,
which I have attach it here
* Plug in your ESP8266 into your computer with windows system
and go to device manager checking serial ports of ESP8266, like
this:

![](https://github.com/Delfino520/Pictures/blob/master/15063566049135.png)

* Extract flash_download_tools_v3.6.5 and open it, and click
ESP8266 DownloadTool

![](https://github.com/Delfino520/Pictures/blob/master/15063566169652.png)

![](https://github.com/Delfino520/Pictures/blob/master/15063567062317.png)

All the configuration please refer to the image above:

Download Path configuration: please key in the path of your WIFI bait
firmware on your computer

CrystalFreq: 26M

SPI SPEED: 80MHz

SPI MODE: QIO

FLASH SIZE: 32 Mbit

Tick: “DoNotChgBIN”

COM (depend on your serial port of esp8226)

BAUD: 115200

After configuration, click START button to upload the firmware to your
esp8226, when the upload is done, you will find a WIFI ‘HH’ that is
coming from ESP8226, if this HH wifi do not show up, then please press
reset button and wait a few second, it will be appear, now you can
connect to HH, wifi password is : m1234567

Remark: if the HH wifi does not appear eventually, then please erase it
and upload the firmware again.



3). Upload webpages to esp8266 using Arduino
You need webpages and webpage upload tools, which I have
attached here

* go to File -> Preferences add the URLs in Additional Boards
Manager URLs
http://arduino.esp8266.com/stable/package_esp8266com_index.j
son

* Go to Tools -> Board -> Boards Manager, search "esp8266" and
install esp8266 version 2.0.0 (please pay attention, you have to 
install version 2.0.0)

* Open webpages upload tools then you will find tools folder inside
it, then go to installation directory of Arduino on your computer
and find tools folder, copy all the files in the tools folder under
webpages upload tools folder and paste into the tools folder
under installation directory of Arduino(overwrite).

* Go back to Arduino and create a new project and save it to
desktop or wherever you like, then go to menu bar click tool then
click esp8266 sketch data upload, then pop up a window, select
NO, then you will find an empty data folder under your project
folder you just create. copy all the files in webpages\data you
downloaded and paste into the empty data under your project
folder.

4). Go back to Arduino
Click tools and check the configuration, just follow the configuration
in the picture, except Port (choose port according to your real
situation) and development board (you should choose base on the
type of your development board)
![](https://github.com/Delfino520/Pictures/blob/master/15063571576506.png)

5). After that, please click upload button, it is starting uploading the
webpages and wait about 1 minute when the led light does not
twinkle, it means the firmware has been uploaded.

6). Connect to HH wifi SSID and input 192.168.1.1/backdoor.html to your
browser address bar (wifi password is : m1234567), then you will see the backend
![](https://github.com/Delfino520/Pictures/blob/master/BaiduShurufa_2018-10-16_21-31-57.png)

So far the firmware has been upload to esp8266 successfully


3. How to use?

* Logging in Esp8266 backend by Connecting to wifi SSID: HH 
(192.168.1.1/backdoor.html, wifi password is : m1234567)

* When you log in esp8226, you need to select one wifi ssid to attack,
and key in the number in the front of the wifi SSID and press ‘yes ’
button, then esp8226 will create a fake AP that has same name with
the WIFI SSID we want to attack, and all the devices connected to the
router will be disconnected, once they connect to the fake AP that
ESP8226 created, log in webpage will pop up and require people to
input their right wifi password. Once they key in the wifi password,
ESP8226 will check whether the wifi password is right or wrong with
handshake captured from the wifi, if the wifi password is right, then
the attack will be ceased, and you need to reconnect to HH wifi SSID
and log in backend to check WIFI password.  

![](http://image.3001.net/images/20170926/15063572156097.png!small)

![](http://image.3001.net/images/20170926/15063573181364.png!small)



4. Statement

WIFI Bait is a project developed by a Chinese developer--The X. It is a useful firmware for ESP8266, whose function is similar with wifiphisher. I found it on one of Chinese forum, and there is no similar project on Github, so i upload and share it here, hope you guys are interested in it and try your best to improve it.

If you decide to improve this project, i strongly recommend you to combine the webpages of wifiphisher with this project, because in this project you cannot choose webpages you like, such as Browser Connection Reset, Firmware Upgrade page, Browser plugin update and so on.The most important thing is that these webpages is in Chinese. By the way the webpages in this project is too lousy.I have upload compiled WIFI Bait and source code on Github.


5. Disclaimer

Usage of Wifiphisher for attacking infrastructures without prior mutual consistency can be considered as an illegal activity. It is the final user's responsibility to obey all applicable local, state and federal laws. Authors assume no liability and are not responsible for any misuse or damage caused by this program.
