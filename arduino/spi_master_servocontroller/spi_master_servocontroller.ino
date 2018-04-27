#include <Servo.h>
#include <SPI.h>

//시리얼 출력은 동작 시간을 저해하는 요소. 최종버전에선 주석처리하기.

#define SLAVES 5

byte pixel_data[64] ={0,};
char mst_buf[10];
char slv_buf[5][12]; //for serial monitoring
int slave[5] = {6,7,8,9,10};
Servo mst_servo[10];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mst_servo[0].attach(A0);
  mst_servo[1].attach(A1);
  mst_servo[2].attach(A2);
  mst_servo[3].attach(A3);
  mst_servo[4].attach(A4);
  mst_servo[5].attach(A5);
  mst_servo[6].attach(2);
  mst_servo[7].attach(3);
  mst_servo[8].attach(4);
  mst_servo[9].attach(5);
  Serial.println("Master servos successfully initalized.");
  for(int i=0; i<5; i++)
    pinMode(slave[i],OUTPUT); //핀모드설정 안하면 6789핀 못씀...
//  MOSI = 11;
//  MISO = 12;
//  SCK = 13;
  SPI.begin();
  for(int i = 0; i < SLAVES; i++)  digitalWrite(slave[i],HIGH);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
}

void loop() {
  volatile boolean data_end =false;
  //read data from Serial
  if(Serial.available()){
    for(int i=0; i < 64; i++){
      pixel_data[i]=Serial.read(); //시리얼 리드 도중에 시간이?
      Serial.print((char)pixel_data[i]);
      if (i%8==7) Serial.println(); //line feed after print a row.
    }
  }
  dataPartition();
/*
  Serial.println("\n----Curent Data----");  
    Serial.println(mst_buf);
    Serial.println(slv_buf[0]);
    Serial.println(slv_buf[1]);
    Serial.println(slv_buf[2]);
    Serial.println(slv_buf[3]);
    Serial.println(slv_buf[4]);
*/  
  //transmit data to slaves
  for(int i = 0; i < SLAVES; i++){
    //char msg[20];
    digitalWrite(slave[i],LOW);
    for(int k = 0; k < 12; k++){ //+1, for the null sign
      SPI.transfer(slv_buf[i][k]);
    }
    digitalWrite(slave[i],HIGH);
/*  
    //make message
    sprintf(msg,"Slave %d : %d", i, ()? "success":"failed"); //연결상태만 뜨게?
    Serial.println(msg);
*/
  }
  moveServo(9);
  //if Serial.available을 여기까지 씌우면 왠지 모르게 한바이트가 일단 잘려버린다.
}

void dataPartition(){
  memcpy(mst_buf,pixel_data,sizeof(mst_buf));
  memcpy(slv_buf[0],pixel_data+9,sizeof(slv_buf[0]));
  memcpy(slv_buf[1],pixel_data+20,sizeof(slv_buf[1]));
  memcpy(slv_buf[2],pixel_data+31,sizeof(slv_buf[2]));
  memcpy(slv_buf[3],pixel_data+42,sizeof(slv_buf[3]));
  memcpy(slv_buf[4],pixel_data+53,sizeof(slv_buf[4]));
  for(int i=0; i < 5; i++) slv_buf[i][11]="\0"; // null signal
  mst_buf[9]="\0";
}

void moveServo(int amount){
  for(int i=0;i<amount;i++){
    mst_servo[i].write(0/*180-mst_buf[i]*/);
    delay(50);
  }
  delay(1000);
  for(int i=0;i<amount;i++){
    mst_servo[i].write(180);
  }
  delay(1000);
}

