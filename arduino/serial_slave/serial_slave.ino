#include<Servo.h>

byte init_buf=0xFF;
char frame_buf[64];
Servo slv_servo[8];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int i=0; i <8; i++){
    slv_servo[i].attach(i+2);
  }
  for(int i=0; i<64;i++)
    frame_buf[i]= 180;
  //frame_buf[8]='\0';
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    init_buf = Serial.read();
    if(init_buf==0xFE)
      for(int i =0; i <64; i++)
        frame_buf[i]= Serial.read();
  }
  //Serial.println(frame_buf);
  moveServo(8);
}


void moveServo(int amount){
  for(int i=0;i<amount;i++){
    slv_servo[i].write((byte)frame_buf[i+56]);
  }
  //delay(200);  
}
