# Wireless Communication Using Arduino (To do List)
![A project photo](/Images/Wireless%20With%20Arduino.png)
### **Firstly let's talk about wireless transmission.**
This is the era of wireless communication/technology. We can see the rise in the number of devices that are using Bluetooth and WiFi these days. With the IoT revolution in the electronics industry as well as the ever-increasing devices that needed internet connectivity we had to shift to IPv6 from IPv4.

With these technological advances, we are forgetting about some simpler and older radio frequency devices and schemes. More and more people are publishing sophisticated projects which use IoT, Lora-WAN, and stuff even when it is not required in that project. A small project doesn't need such powerful wireless technology. It is a waste of resources.
![A project photo](/Images/1673176765335.jpg)

Now let's learn a bit about our RF Tx/Rx pair.

The Tx/Rx pair that is used in this project uses a frequency of 433MHz which falls in the ISM band. ISM stands for Industrial, Scientific, and Medical. This band of frequency is free to use and is unlicensed.

The Tx/Rx pair employs an ASK modulation scheme for transmitting and receiving data. ASK stands for Amplitude shift keying which is one of the digital modulation techniques others being Frequency shift keying (FSK) and Phase shift keying (PSK).

Let's learn more about ASK. As I have mentioned earlier that ASK is a digital modulation technique, which means it can be used to transmit digital data wirelessly over a carrier of 433 MHz. The carrier is a sine wave of 433MHz which is switched on or off depending on the digital bit that is to be transmitted. In this way, by switching the carrier on and off one can transmit 0 or 1 respectively.

For example, If I want to send 1010, I will first switch on the carrier, this carrier will be received on the receiver and it will interpret that a bit 1 has been transmitted. Similarly, if I now switch off the carrier, the receiver will not receive the signal and it will interpret that a 0 has been transmitted. See the picture for understanding the concept clearly.

# Things used in this project
## Hardware components
### - Arduino Uno 
![Arduino Uno](/Images/arduino-uno-r3.png)
### - Arduino Nano 
![Arduino Nano](/Images/Arduino-Nano-V3.0-CH340-Chip-Mini-USB-Cable.jpg)
### - RF Module(433MHZ) 
![RF Module](/Images/RF%20Module%20433MHZ.png)
### - LCD 20x4 with I2C 
![LCD](/Images/I2C.png)
### - BreadBoard 
![BreadBoard](/Images/41nCh+ZtGxL._SL1004_.jpg)
### - Jumper wires 
![Jumpers](/Images/1.jpg)
### - Rocker Switch 
![Switch](/Images/Switch.jpg)
### - 9V battery 
![Battery](/Images/61tHo16P1ZL._AC_UF894,1000_QL80_.jpg)
## Software components
### - Arduino IDE
### - Autodesk Fusion 360
## Hand tools and fabrication machines
### - Multitool, Screwdriver
### - Laser cutter (generic)

## You can see the full tutorial video before you read the Doc
[![IMAGE ALT TEXT](/Images/Wireless%20With%20Arduino.png)](https://youtu.be/cRjwFIYLE_Y "Youtube Video")

# Explanation

![ASK](/Images/2.jpg)

### Amplitude Shift Keying

ASK

ASK is a type of Amplitude Modulation that represents the binary data in the form of variations in the amplitude of a signal.

Any modulated signal has a high-frequency carrier. The binary signal when ASK modulated, gives a zero value for Low input while it gives the carrier output for High input.

The following figure represents the ASK modulated waveform along with its input.

To find the process of obtaining this ASK modulated wave, let us learn about the working of the ASK modulator.

### ASK Modulator
The ASK modulator block diagram comprises of the carrier signal generator, the binary sequence from the message signal and the band-limited filter. Following is the block diagram of the ASK Modulator.

The carrier generator, sends a continuous high-frequency carrier. The binary sequence from the message signal makes the unipolar input to be either High or Low. The high signal closes the switch, allowing a carrier wave. Hence, the output will be the carrier signal at high input. When there is low input, the switch opens, allowing no voltage to appear. Hence, the output will be low.

The band-limiting filter shapes the pulse depending upon the amplitude and phase characteristics of the band-limiting filter or the pulse-shaping filter.

![ASK Modulator](/Images/3.png)
### ASK Demodulator
There are two types of ASK Demodulation techniques. They are −

● Asynchronous ASK Demodulation/Detection

● Synchronous ASK Demodulation/Detection

The clock frequency at the transmitter matches with the clock frequency at the receiver, it is known as a Synchronous method, as the frequency gets synchronized. Otherwise, it is known as Asynchronous.

### Asynchronous ASK Demodulator
The Asynchronous ASK detector consists of a half-wave rectifier, a low pass filter, and a comparator. Following is the block diagram for the same.

The modulated ASK signal is given to the half-wave rectifier, which delivers a positive half output. The low pass filter suppresses the higher frequencies and gives an envelope-detected output from which the comparator delivers a digital output.
![Asynchronous](/Images/4.jpg)

### Synchronous ASK Demodulator
Synchronous ASK detector consists of a Square law detector, a low pass filter, a comparator, and a voltage limiter. Following is the block diagram for the same.
The ASK-modulated input signal is given to the Square law detector. A square law detector is one whose output voltage is proportional to the square of the amplitude-modulated input voltage. The low pass filter minimizes the higher frequencies. The comparator and the voltage limiter help to get a clean digital output.

![Synchronous](/Images/5.png)

# Wiring

![Reciever](/Images/Reciever.png)

## For the Receiver (Arduino Nano)
On the I2C adapter
Device----------> Nano
VCC 5v
GND GND
SDA A4
SCL A5
On the RF chip (Reciever)
VCC 5v or D12
GND GND
Data* D11
On the switch
Middle pin Gnd
Other pin Power Supply-GND
Other
Power Supply+ VIN

![Transimmeter](/Images/Sender.png)

## On the RF chip (Transmitter)
Device--------> Uno
GND D8
VCC D9
DATA D10

# CAD Design

![Cad](/Images/Transmitter%20Enclosure%20v4.png)
![Cad](/Images/Transmitter%20Enclosure%20v4.1.png)
![Cad](/Images/Reciver%20Enclosure%20v5.png)

I used Fusion 360 To make the Enclosure of the sender and receiver circuit then I sent the DXF files to a laser-cutting machine that made the Enclosure parts.
The Part is made with wood of 3 mm in thickness.

# Coding and Testing

![Sender Algorithm](/Images/Reciver%20Algorithm.png)

![Recieving Algorithm](/Images/Sender%20Algorithm.png)

For Coding, first, you need to test the I2C and take the address
you can make that by the following Code and uploading it on the Arduino Nano that connected to LCD

'''
#include <Wire.h>

void setup()
 {
   Wire.begin();
  Serial.begin(115200);
   Serial.println("\nI2C Scanner");
 }

void loop()
 {
   byte error, address;
   int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;

   for(address = 0; address <= 127; address++ )
  {

     Wire.beginTransmission(address);
     error = Wire.endTransmission();

    if (error == 0)
     {
       Serial.print("I2C device found at address 0x");
       if (address<16)
        Serial.print("0");
       Serial.print(address,HEX);
       Serial.println(" !");

      nDevices++;
     }

     else if (error==4)
    {
       Serial.print("Unknow error at address 0x");
       if (address<16)
        Serial.print("0");
       Serial.println(address,HEX);
     }

   }

   if (nDevices == 0)
     Serial.println("No I2C devices found\n");
   else
     Serial.println("done\n");

  delay(8000);    
        
 }
'''
