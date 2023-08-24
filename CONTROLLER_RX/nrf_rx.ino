#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t pipeIn = 0xE8E8F0F0E1LL;
RF24 radio(9,8);
struct Received_data {
  int s1;
  int s2;
  int s3;
  int s4;
  int b1; 
  int b2; 
  int b3;
};

int ch1_value = 0;
Received_data received_data;


/**************************************************/

void setup()
{
  Serial.begin(9600);
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);  
  radio.openReadingPipe(1,pipeIn);
  radio.startListening();
}

unsigned long last_Time = 0;
void receive_the_data()
{
  while ( radio.available() ) {
  radio.read(&received_data, sizeof(Received_data));
  last_Time = millis();
  }
}

void loop()
{
  receive_the_data();
  
  Serial.print(received_data.s1);
  Serial.print("\t");
  Serial.print(received_data.s2);
  Serial.print("\t");
  Serial.print(received_data.s3);
  Serial.print("\t");
  Serial.print(received_data.s4);
  Serial.print("\t");
  Serial.print(received_data.b1);
  Serial.print("\t");
  Serial.print(received_data.b2);
  Serial.print("\t");
  Serial.println(received_data.b3);
}
