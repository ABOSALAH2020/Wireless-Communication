#include <VirtualWire.h>
#include <Wire.h> //IIC Library
#include <LiquidCrystal_I2C.h>//For the screen
#include <elapsedMillis.h>//For the Status
LiquidCrystal_I2C lcd(0x3F,20,4);  // set the parameters
boolean constat=1;//Status Variable 1=On at start, 0=off at start
int line;//Status code moves cursor, variable to store DESIRED line number 
boolean splashcleared;//Bool to hold if splash screen has been cleared
String text = " ";//String to hold the text
elapsedMillis packettimer;//The timer for status
#define interval 1500//The threshold for how long it can go without "6"(The connection indicator)

//initialize the symbols
 

void setup()
{
  pinMode(12, OUTPUT); //Module VCC 
  digitalWrite(12, HIGH);   // turn the VCC to High 
  vw_set_rx_pin(11);// set you rx pin
  vw_setup(2500);	 // Bits per sec. Lower for further distance. Make sure this matches the number on the transmitter
  vw_rx_start();       // Start the receiver PLL running
  splashcleared=0;//make sure that this is 0
  lcd.init();//start the screen
  //initialize the symbols 
  //setCursor comands note- Counting starts at 0 NOT 1
  lcd.createChar(0, cchar); //Rf symbol
  lcd.createChar(1, bar1); //Bar 1 and 2
  lcd.createChar(2, bar2); //Bar 3 and 4
  Serial.begin(9600);//Open serial port, add the !serial thing for leonardo
  lcd.backlight();//Turn on the backlight
  lcd.clear();//Clear the screen
  lcd.home();//go home

    //display Home screen This will be cleared once The siglal indicator "6" is sent
  lcd.setCursor (5,0);
  lcd.print("RF--Screen"); 
  lcd.setCursor (0,1); 
  lcd.print("By ICARUS"); 
  lcd.setCursor (0,2);
  lcd.print("Connection Status-"); 
  lcd.setCursor (0,3);
  lcd.print("Inactive"); 
  delay (1200);//set this to the interval
}


  void loop()
  {
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;


    if (packettimer< interval){//It the status of the connection is good and "6" was recieved in the last 1.5 secs.
      if (splashcleared==0){//if screen hasn't been cleared of status
        lcd.clear();//clear it
        splashcleared=1;//make sure it won't be again  
      } 
    }//make sure the screen wont clear again


    if (constat==1){  //If the status bar is enabled
      if (packettimer< interval){//It the status of the connection is good and "6" was recieved in the last 1.5 secs.

        lcd.setCursor (17,0); //go to 3rd last position    
        lcd.write(0); //RF symbol
        lcd.write(1);//bar one
        lcd.write(2);//Bar two
      }

      else if (packettimer > interval) {//It the status of the connection is bad and "6" was not recieved in the last 1.5 secs.
        //we will blink a X by the rf symbol
        lcd.setCursor (17,0);//go to 3rd last position  
        lcd.write(0);  //RF symbol    
        lcd.setCursor (18,0);//go to 2nd last position 
        lcd.print ("X ");//To add the X
        delay (450);// wait
        lcd.setCursor (18,0);////go to 2nd last position 
        lcd.print ("  ");//To erase the X
        delay (400);//wait

      }
    }


    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
      packettimer = 0;//Reset timer when data is recieved
      text.remove(0);//clear all text from string: text
      text=(char*)buf;//put new data into string "text"


      text.remove(buflen-1);//Remove garbage after the end of the text
      lcd.setCursor(0,line);//Restore cursor to original position
      //Most of these commands are self explanitory...

      if (text.startsWith("1")) {
        lcd.setCursor(0,0);
        line=0;
      } 

      else if (text.startsWith("2")) {
        lcd.setCursor(0,1);
        line=1;

      } 
      else if (text.startsWith("3")) {
        lcd.setCursor(0,2);
        line=2;

      } 
      else if (text.startsWith("4")) {
        lcd.setCursor(0,3);
        line=3;

      }
      else if (text.startsWith("clear")) {
        lcd.clear();
      } 
      else if (text.startsWith("6")) {//"6" is sent every 300 ms to check the signal, and we dont want it to display
        packettimer = 0;//Reset timer when data is recieved
        if (splashcleared==0){//if screen hasn't been cleared of status
          lcd.clear();
          splashcleared=1;//make sure the screen wont clear again
        }  
      }
      else if (text.startsWith("backlight")) {
        lcd.backlight();
      } 
      else if (text.startsWith("nobacklight")) {
        lcd.noBacklight();
      }  
      else if (text.startsWith("status")) {
        lcd.setCursor (17,0);//Go to the third last spot
        lcd.write(0);//Show the Rf symbol
        lcd.write(1);//Show bar set 1
        lcd.write(2);//Show bar set 2
        constat=1;//(ConnectionStatus)this variable will make the signal show
      } 
      else if (text.startsWith("nostatus")) {
        lcd.setCursor (17,0);//Go to the third last spot
        lcd.print ("   ");//write it over with 3 spaces
        constat=0;//(ConnectionStatus)this variable will block the signal from showing

      }

      else if (text.startsWith("{")) {//if we want to sen a command word to display on screen, we precede it with{
        text.remove (1); //remove the"{", This must be second last of if statements
      } 
      else {//this MUST be last statement
        packettimer = 0;//Reset timer when data is put onto the screen
        lcd.setCursor(0,line);//Go to the specified line
        lcd.print(text);//If word isn't a command print it
      }

    }
  }
