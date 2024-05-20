# Wireless Communication Using Arduino (To do List)
![A project photo](/Images/1673176765335.jpg)
### Firstly let's talk about wireless transmission.
This is the era of wireless communication/technology. We can see the rise in the number of devices that are using Bluetooth and WiFi these days. With the IoT revolution in the electronics industry as well as the ever-increasing devices that needed internet connectivity we had to shift to IPv6 from IPv4.

With these technological advances, we are forgetting about some simpler and older radio frequency devices and schemes. More and more people are publishing sophisticated projects which use IoT, Lora-WAN, and stuff even when it is not required in that project. A small project doesn't need such powerful wireless technology. It is a waste of resources.

Now let's learn a bit about our RF Tx/Rx pair.

The Tx/Rx pair that is used in this project uses a frequency of 433MHz which falls in the ISM band. ISM stands for Industrial, Scientific, and Medical. This band of frequency is free to use and is unlicensed.

The Tx/Rx pair employs an ASK modulation scheme for transmitting and receiving data. ASK stands for Amplitude shift keying which is one of the digital modulation techniques others being Frequency shift keying (FSK) and Phase shift keying (PSK).

Let's learn more about ASK. As I have mentioned earlier that ASK is a digital modulation technique, which means it can be used to transmit digital data wirelessly over a carrier of 433 MHz. The carrier is a sine wave of 433MHz which is switched on or off depending on the digital bit that is to be transmitted. In this way, by switching the carrier on and off one can transmit 0 or 1 respectively.

For example, If I want to send 1010, I will first switch on the carrier, this carrier will be received on the receiver and it will interpret that a bit 1 has been transmitted. Similarly, if I now switch off the carrier, the receiver will not receive the signal and it will interpret that a 0 has been transmitted. See the picture for understanding the concept clearly.