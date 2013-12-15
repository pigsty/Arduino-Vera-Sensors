////
//
// Micasaverde and arduino input output interaction 
// original code by @Mic from the Micasaverde forum
// trigger timeouts added by Chris Birkinshaw (@chrisbirkinshaw)
//
////

#include <SPI.h>
#include <Ethernet.h>
boolean reading = false;

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x19 }; // Be sure this address is unique in your network
//IPAddress ip(172,16,0,245); //Address ip valid on your network

// Define the Vera device ids for the sensors (in this example first 5 are motion, 6th is a door contact closure)
#define DEVID1 "151" 
#define DEVID2 "152"
#define DEVID3 "153"
#define DEVID4 "154"
#define DEVID5 "155"
#define DEVID6 "156"
#define DEVID7 "218"
#define DEVID8 "219"
#define DEVID9 "220"
#define DEVID10 "221"
#define DEVID11 "222"

//Numeric Pin where you connect your sensor to Arduino
#define pinDevid1 2 
#define pinDevid2 3
#define pinDevid3 8
#define pinDevid4 5
#define pinDevid5 6
#define pinDevid6 7
#define pinDevid7 A0
#define pinDevid8 A1
#define pinDevid9 A2
#define pinDevid10 A3
#define pinDevid11 A4

// Enable serial console debugging mode
#define DEBUG false

// Setup variables for the sensors
char serverName[] = "172.16.1.1"; //Vera ip address
boolean pinDevid1State = false;
boolean pinDevid2State = false;
boolean pinDevid3State = false;
boolean pinDevid4State = false;
boolean pinDevid5State = false;
boolean pinDevid6State = false;

unsigned long pinDevid1Tripped = false;
unsigned long pinDevid2Tripped = false;
unsigned long pinDevid3Tripped = false;
unsigned long pinDevid4Tripped = false;
unsigned long pinDevid5Tripped = false;
unsigned long pinDevid6Tripped = false;

unsigned long time;
unsigned long lastRead = 0;

// Setup the timeout for motion sensors (30 secs is suggested to avoid overloading vera with requests)
int timeout = 30000;

String securitySid = "urn:micasaverde-com:serviceId:SecuritySensor1";
String lightSensorSid = "urn:micasaverde-com:serviceId:LightSensor1";

// Initialize the Ethernet client library
// with the IP address and port of the server
EthernetServer server = EthernetServer(80); //port 80
EthernetClient client;

void setup() {
  delay(250);
  Serial.begin(9600);
  pinMode(pinDevid1, INPUT);
  pinMode(pinDevid2, INPUT);
  pinMode(pinDevid3, INPUT);
  pinMode(pinDevid4, INPUT);
  pinMode(pinDevid5, INPUT);
  pinMode(pinDevid6, INPUT);
  
  // Enable the pullup resitors to protect against false positives on open circuit
  digitalWrite(pinDevid1, HIGH);
  digitalWrite(pinDevid2, HIGH);
  digitalWrite(pinDevid3, HIGH);
  digitalWrite(pinDevid4, HIGH);
  digitalWrite(pinDevid5, HIGH);
  digitalWrite(pinDevid6, HIGH);
  digitalWrite(pinDevid7, HIGH);
  digitalWrite(pinDevid8, HIGH);
  digitalWrite(pinDevid9, HIGH);
  digitalWrite(pinDevid10, HIGH);
  digitalWrite(pinDevid11, HIGH);
  
  // Disable the SD card
  digitalWrite(4, HIGH);
  
  delay(1000);
  
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    while(true);
  }
  else{
    Serial.println("Ethernet ready local IP:");
    Serial.println(Ethernet.localIP());
  }
  
  // give the Ethernet shield a second to initialize:
  delay(1000);
  
  // Reset devices on vera
  sendToVera(DEVID1, securitySid, "Tripped", 0);
  sendToVera(DEVID2, securitySid, "Tripped", 0);
  sendToVera(DEVID3, securitySid, "Tripped", 0);
  sendToVera(DEVID4, securitySid, "Tripped", 0);
  sendToVera(DEVID5, securitySid, "Tripped", 0);
  sendToVera(DEVID6, securitySid, "Tripped", 0);
  
  server.begin();
}

void loop()

{
  SensorDetection();
  statusServer();
  }


void SensorDetection(){
      ////
      // Arduino input detection code
      ////
      time = millis();
      
      if (digitalRead(pinDevid1) == HIGH && pinDevid1State == false) // this seems weird, should reset time even if already tripped
      {
        if(DEBUG){Serial.println("pinDevid1 is HIGH");}
        pinDevid1Tripped = time;
        if (pinDevid1State == false)
        {
          //Sending request to Vera
          sendToVera(DEVID1, securitySid, "Tripped", 1);
          pinDevid1State = true;
        }
      }

        if ((time - pinDevid1Tripped) > timeout && pinDevid1State == true)
        {
          pinDevid1State = false;
          //Sending request to Vera
          sendToVera(DEVID1, securitySid, "Tripped", 0);
        }
      
      if (digitalRead(pinDevid2) == HIGH && pinDevid2State == false) 
      {
        if(DEBUG){Serial.println("pinDevid2 is HIGH");}
        pinDevid2Tripped = time;
        if (pinDevid2State == false)
        {
          //Sending request to Vera
          sendToVera(DEVID2, securitySid, "Tripped", 1);
          pinDevid2State = true;
        }
      }

        if ((time - pinDevid2Tripped) > timeout && pinDevid2State == true)
        {
          pinDevid2State = false;
          //Sending request to Vera
          sendToVera(DEVID2, securitySid, "Tripped", 0);
        }
      
      if (digitalRead(pinDevid3) == HIGH && pinDevid3State == false) 
      {
        if(DEBUG){Serial.println("pinDevid3 is HIGH");}
        pinDevid3Tripped = time;
        if (pinDevid3State == false)
        {
          //Sending request to Vera
          sendToVera(DEVID3, securitySid, "Tripped", 1);
          pinDevid3State = true;
        }
      }

        if ((time - pinDevid3Tripped) > timeout && pinDevid3State == true)
        {
          pinDevid3State = false;
          //Sending request to Vera
          sendToVera(DEVID3, securitySid, "Tripped", 0);
        }
      
      if (digitalRead(pinDevid4) == HIGH && pinDevid4State == false) 
      {
        if(DEBUG){Serial.println("pinDevid4 is HIGH");}
        pinDevid4Tripped = time;
        if (pinDevid4State == false)
        {
          //Sending request to Vera
          sendToVera(DEVID4, securitySid, "Tripped", 1);
          pinDevid4State = true;
        }
      }
 
        if ((time - pinDevid4Tripped) > timeout && pinDevid4State == true)
        {
          pinDevid4State = false;
          //Sending request to Vera
          sendToVera(DEVID4, securitySid, "Tripped", 0);
        }
      
      if (digitalRead(pinDevid5) == HIGH && pinDevid5State == false) 
      {
        if(DEBUG){Serial.println("pinDevid5 is HIGH");}
        pinDevid5Tripped = time;
        if (pinDevid5State == false)
        {
          //Sending request to Vera
          sendToVera(DEVID5, securitySid, "Tripped", 1);
          pinDevid5State = true;
        }
      }

        if ((time - pinDevid5Tripped) > timeout && pinDevid5State == true)
        {
          pinDevid5State = false;
          //Sending request to Vera
          sendToVera(DEVID5, securitySid, "Tripped", 0);
        }
        
      
      // We want different behaviour for the door contact closure sensor to avoid toggling
      
      if (digitalRead(pinDevid6) == HIGH && pinDevid6State == false) 
      {
        if(DEBUG){Serial.println("pinDevid6 is HIGH");}
        //Sending request to Vera
        sendToVera(DEVID6, securitySid, "Tripped", 1);
        pinDevid6State = true;
      }

        if (digitalRead(pinDevid6) == LOW && pinDevid6State == true) 
        {
          if(DEBUG){Serial.println("pinDevid6 is LOW");}
          //Sending request to Vera
          sendToVera(DEVID6, securitySid, "Tripped", 0);
          pinDevid6State = false;
        }      
    
      // Read light sensors if 30 secs has passed
      
      if ((time - timeout) > lastRead)
      {
        lastRead = time;
        sendToVera(DEVID7, lightSensorSid, "CurrentLevel", (vToLightLevel(analogRead(pinDevid7))));
        sendToVera(DEVID8, lightSensorSid, "CurrentLevel", (vToLightLevel(analogRead(pinDevid8))));
        sendToVera(DEVID9, lightSensorSid, "CurrentLevel", (vToLightLevel(analogRead(pinDevid9))));
        sendToVera(DEVID10, lightSensorSid, "CurrentLevel", (vToLightLevel(analogRead(pinDevid10))));
        sendToVera(DEVID11, lightSensorSid, "CurrentLevel", (vToLightLevel(analogRead(pinDevid11))));
      }
 }
 
void statusServer()
{
  EthernetClient client = server.available();
  if (client) {
    // an http request ends with a blank line
    boolean current_line_is_blank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        // if we've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so we can send a reply
        if (c == '\n' && current_line_is_blank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          
          // output the value of each digital input pin
          for (int i = 2; i < 13; i++) {
            client.print("digital input ");
            client.print(i);
            client.print(" is ");
            client.print(digitalRead(i));
            client.println("<br />");
          }
          
          // output the value of each analog input pin
          for (int i = 0; i < 5; i++) {
            int analogReading = analogRead(i);
            client.print("analog input ");
            client.print(i);
            client.print(" is ");
            client.print(analogReading);
            client.print(" or ");
            client.print(vToLightLevel(analogReading));
            client.println("<br />");
          }
          
          break;
        }
        if (c == '\n') {
          // we're starting a new line
          current_line_is_blank = true;
        } else if (c != '\r') {
          // we've gotten a character on the current line
          current_line_is_blank = false;
        }
      }
    }
    client.stop();
  }
}

void sendToVera(String devid, String serviceId, String variable, int target){
  
  Serial.print("READING,");
  Serial.print(devid);
  Serial.print(",");
  Serial.print(serviceId);
  Serial.print(",");
  Serial.print(variable);
  Serial.print(",");
  Serial.println(target);
  
    if(DEBUG){Serial.println("connecting...");}

  if (client.connect(serverName, 49451)) {
    if(DEBUG){Serial.println("connected to Vera");}

    if(DEBUG){Serial.println("sending request");}
    client.print("GET /data_request?id=lu_variableset&DeviceNum=");
    client.print(devid);
    client.print("&serviceId=");
    client.print(serviceId);
    client.print("&Variable=");
    client.print(variable);
    client.print("&Value=");
    client.print(target);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(serverName);
    client.println("User-Agent: Arduino");
    client.println();
  }
  else {
    if(DEBUG){Serial.println("connection failed");}
  }
  
  // if there are incoming bytes available
  // from the server, read them and print them:
  if(DEBUG){
    if (client.available()) {
    char c = client.read();
    Serial.print(c);
    }
  }

    if(DEBUG){Serial.println();}
    if(DEBUG){Serial.println("disconnecting.");}
    client.stop();
}

int vToLightLevel(int reading){
  reading = 1023 - reading; // invert
  float fReading = 0.00;
  fReading = reading / 1023.00; // convert to fraction
  reading = (int)(fReading * 100); // convert to percentage and back to integer
  return reading;
}







