#include <VirtualWire.h>
#include <elapsedMillis.h> //For the status on the reciever

String serialdata; //Holds data coming in
char msg[50]; //Char array to send data out with
String statustext="6"; //This is the text sent every interval
elapsedMillis packettimer;//this is the timer
#define interval 50//Lower this if you send long packets

void setup()
{
  pinMode(8, OUTPUT);//Module GND
  pinMode(9, OUTPUT); //Module VCC 
  digitalWrite(9, HIGH);   // turn the VCC to HIGH, set to LOW for default off
  digitalWrite(8, LOW);   // turn the GND to LOW 
  vw_set_tx_pin(10);
  vw_setup(2500);       // Bits per sec
  Serial.begin(9600);
  packettimer = 0;//Reset the timer
  Serial.println ("Serial Port Open");
}

void loop()
{

  if (Serial.available()){
    delay (50);
    Serial.println ("I found Serial Data");// If you are having issues, these will help you find where your code doesnt work.
    serialdata=Serial.readString();//put text from serial in serialdata string

      if (serialdata.startsWith("off")) {
      digitalWrite(9, LOW);   // turn the VCC to LOW
      digitalWrite(8, LOW);   // turn the GND to LOW 
      Serial.println("");     
      Serial.println("Module OFF"); 
      Serial.println("");  
    } 
    else if (serialdata.startsWith("on")) {
      digitalWrite(9, HIGH);   // turn the VCC to HIGH 
      digitalWrite(8, LOW);   // turn the GND to LOW 
      Serial.println("");
      Serial.println("Module ON");
      Serial.println("");  
    } 

    else {

      serialdata.toCharArray(msg, 50);//convert serialdat the the msg char array
      Serial.println ("I converted it to a CHAR ARRAY");
      Serial.println("Text to be Sent-");//debugging
      Serial.println("");//debugging
      Serial.print(msg);//debugging
      Serial.println("");//debugging
      vw_send((uint8_t *)msg, strlen(msg));
      vw_wait_tx();
      Serial.println ("MSG send request");
      // driver.waitPacketSent();//wait until it is sent
      Serial.println ("Data Sent");
    }
  }

  if (packettimer > interval) {

    statustext.toCharArray(msg, 50);//convert the statustext string to msg char array
    vw_send((uint8_t *)msg, strlen(msg)); //line that sends the msg variable
    vw_wait_tx();//wait untill sent
  }
}
//Code mainly From Arduino.cc and VW examples
