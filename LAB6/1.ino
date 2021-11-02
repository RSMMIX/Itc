#include <Wire.h>
#define SLAVE_ADDR1 9
#define SLAVE_ADDR2 10

char msg[7] = "HELLO1";
// msg[5] is number

void setup()
{
    Serial.begin(9600);
    Wire.begin(); //Initialize I2C communications as Master
}

int slaveAddrs[2] = {SLAVE_ADDR1, SLAVE_ADDR2};
int slave = 1;

void loop()
{
    slave = (slave + 1) % 2;
    Wire.beginTransmission(slaveAddrs[slave]);
    Wire.write(msg);
    Serial.println(msg);
    Wire.endTransmission();
    Wire.requestFrom(slaveAddrs[slave], 6); // send request and wait until receive from the slave
    int i = 0;
    while (Wire.available())
    {
        msg[i++] = Wire.read();
    }
    delay(500);
}