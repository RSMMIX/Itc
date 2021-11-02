#include <Wire.h>
#define SLAVE_ADDR 10

char msg[7] = "HELLO1";

void setup()
{
 	Serial.begin(9600);
	Wire.begin(SLAVE_ADDR);
 	Wire.onReceive(receiveEvent); // Function to run when data received from master
 	Wire.onRequest(requestEvent);
}

void loop()
{
    
}

void receiveEvent(int bytes) 
{
    for (size_t i = 0; i < bytes-1; i++)
    {
        msg[i] = Wire.read();
    }
    msg[5]++;
    if (msg[5] > '9')
    {
        msg[5] = '1';
    }
}

void requestEvent() 
{
    Wire.write(msg);
}