#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t my_radio_pipe = 0xE8E8F0F0E1LL;

RF24 radio(9,8);

// The sizeof this struct should not exceed 32 bytes
struct Data_to_be_sent {
  int s1;
  int s2;
  int s3;
  int s4;
  int b1; 
  int b2; 
  int b3; 
};

Data_to_be_sent sent_data;

void setup()
{
  Serial.begin(9600);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(my_radio_pipe);  
}

void loop()
{
  sent_data.s1 = analogRead(A0);
  sent_data.s2 = analogRead(A1);
  sent_data.s3 = analogRead(A2);
  sent_data.s4 = analogRead(A3);
  sent_data.s4 = analogRead(A3);
  sent_data.b1 = digitalRead(3);
  sent_data.b2 = digitalRead(4);
  sent_data.b3 = digitalRead(5);
  Serial.print(sent_data.s1);
  Serial.print("\t");
  Serial.print(sent_data.s2);
  Serial.print("\t");
  Serial.print(sent_data.s3);
  Serial.print("\t");
  Serial.print(sent_data.s4);
  Serial.print("\t");
  Serial.print(sent_data.b1);
  Serial.print("\t");
  Serial.print(sent_data.b2);
  Serial.print("\t");
  Serial.println(sent_data.b3);
  radio.write(&sent_data, sizeof(Data_to_be_sent));
}
