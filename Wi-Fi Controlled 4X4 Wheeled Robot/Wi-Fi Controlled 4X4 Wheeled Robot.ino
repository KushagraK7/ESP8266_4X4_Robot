/*
 * Arduino code for controlling a 4X4 wheeled robot with an ESP8266 using a browser on a device in local network.
 *
 * 
 * Made by KushagraK7: https://www.instructables.com/member/KushagraK7/
 * 
 * The ESP8266 and the controlling device such as the laptop or the smartphone should be in the same local network.
 * 
 * 
 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "PageIndex.h"; //--> Include the contents of the User Interface Web page, stored in the same folder as the .ino file

#define LEDonBoard 2  //--> Defining an On Board LED, used as an indicator during the process of connecting to a wifi router

//PWM outputs for the motors
#define Out1 4
#define Out2 14
#define Out3 12
#define Out4 15

//----------------------------------------SSID and Password of your WiFi router
const char *ssid = "WiFi_SSID";
const char *password = "WiFi_Password";
//----------------------------------------

int p = 0;
int m = 1;
int ld = 0;
int rd = 0;
int sp;
float spe = 0;

int acc = 1; //The rate at which the speed of the motors change.

int LeftSpeed = 0;
int RightSpeed = 0;

String POS;
String LDir;
String RDir;

ESP8266WebServer server(80);  //--> Server on port 80

//----------------------------------------This routine is executed when you open NodeMCU ESP8266 IP Address in browser
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
//----------------------------------------

//----------------------------------------Procedure for handling servo control
void setSpeed()
{
  POS = server.arg("POS");
  
  p = POS.toInt(); 
  
  Serial.print("Position:  ");
  Serial.print(p);
  Serial.print("  Direction:  ");
  Serial.println(m);
  server.send(200, "text/plane","");

  
}

void setLDir()
{
  LDir = server.arg("LDir");

  if(LDir.length()  != 0) ld = LDir.toInt();

  
  Serial.print("Position:  ");
  Serial.print(p);
  Serial.print("  Direction:  ");
  Serial.println(m);
  server.send(200, "text/plane","");
  
}

void setRDir()
{
  RDir = server.arg("RDir");

  if(RDir.length()  != 0) rd = RDir.toInt();

  
  Serial.print("Position:  ");
  Serial.print(p);
  Serial.print("  Direction:  ");
  Serial.println(m);
  server.send(200, "text/plane","");
  
}


void run(int ls, int rs)
{
  if(ls > 0 && ls <= 255)
  {
    digitalWrite(Out2, LOW);
    analogWrite(Out1, ls);
  }

  if(ls < 0 && ls >= -255)
  {
    digitalWrite(Out1, LOW);
    analogWrite(Out2, -ls);
  }

  else
  {
    digitalWrite(Out2, LOW);
    digitalWrite(Out1, LOW);
  }


  if(rs > 0 && rs <= 255)
  {
    digitalWrite(Out4, LOW);
    analogWrite(Out3, rs);
  }

  if(rs < 0 && rs >= -255)
  {
    digitalWrite(Out3, LOW);
    analogWrite(Out4, -rs);
  }

  else
  {
    digitalWrite(Out4, LOW);
    digitalWrite(Out3, LOW);
  }

}


//----------------------------------------
//----------------------------------------Setup----------------------------------------
void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(Out1, OUTPUT);
  pinMode(Out2, OUTPUT);
  pinMode(Out3, OUTPUT);
  pinMode(Out4, OUTPUT);
  
  
  WiFi.begin(ssid, password); //--> Connect to your WiFi router
  Serial.println("");
    
  pinMode(LEDonBoard,OUTPUT); //--> On Board LED port Direction output
  digitalWrite(LEDonBoard, HIGH); //--> Turn off Led On Board

  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(LEDonBoard, LOW);
    delay(250);
    digitalWrite(LEDonBoard, HIGH);
    delay(250);
    //----------------------------------------
  }
  //----------------------------------------
  digitalWrite(LEDonBoard, HIGH); //--> Turn off the On Board LED when it is connected to the wifi router.
  //----------------------------------------If connection is successful then show IP address in serial monitor
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //----------------------------------------

  //----------------------------------------Initialize Webserver
  server.on("/",handleRoot);  //--> Routine to handle at root location. This is to display web page.
  server.on("/setPOS", setSpeed);
  server.on("/setLDir", setLDir);
  server.on("/setRDir", setRDir);
  server.begin();  
  Serial.println("HTTP server started");
}
//------------------------------------------------------------------------------------
//----------------------------------------Loop----------------------------------------
void loop() {
 server.handleClient();

 sp = map(p, 0, 100, 0, 254);//Mapping max speed from range of 0-100 to range of 0-254.


 if(LeftSpeed < sp*ld) LeftSpeed+= acc;
 if(LeftSpeed > sp*ld) LeftSpeed-= acc;

 if(RightSpeed < sp*rd) RightSpeed+= acc;
 if(RightSpeed > sp*rd) RightSpeed-= acc;

 run(LeftSpeed, RightSpeed);
}
//------------------------------------------------------------------------------------
