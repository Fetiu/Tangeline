#include <Servo.h>
#include <SPI.h>

//시리얼 출력은 동작 시간을 저해하는 요소. 최종버전에선 주석처리하기.

#define SLAVES 2

byte pixel_data[64] ={0,};
byte offset[64];
char mst_buf[48];
char slv_buf[2][9]; //for serial monitoring
int slave[2] = {9,10};
Servo mst_servo[48];

void setup() {
  Serial.begin(9600);
  mst_servo[0].attach(53);
  mst_servo[1].attach(51);
  mst_servo[2].attach(49);
  mst_servo[3].attach(47);
  mst_servo[4].attach(45);
  mst_servo[5].attach(43);
  mst_servo[6].attach(41);
  mst_servo[7].attach(39);//1~8
  mst_servo[8].attach(52);
  mst_servo[9].attach(50);
  mst_servo[10].attach(48);
  mst_servo[11].attach(46);
  mst_servo[12].attach(44);
  mst_servo[13].attach(42);
  mst_servo[14].attach(40);
  mst_servo[15].attach(38);//9~16
  mst_servo[16].attach(36);
  mst_servo[17].attach(34);
  mst_servo[18].attach(32);
  mst_servo[19].attach(30);
  mst_servo[20].attach(28);
  mst_servo[21].attach(26);
  mst_servo[22].attach(24);
  mst_servo[23].attach(22);//17~24
  mst_servo[24].attach(A0);
  mst_servo[25].attach(A1);
  mst_servo[26].attach(A2);
  mst_servo[27].attach(A3);
  mst_servo[28].attach(A4);
  mst_servo[29].attach(A5);  
  mst_servo[30].attach(A6);
  mst_servo[31].attach(A7);//25~32
  mst_servo[32].attach(A8);
  mst_servo[33].attach(A9);
  mst_servo[34].attach(A10);
  mst_servo[35].attach(A11);
  mst_servo[36].attach(A12);
  mst_servo[37].attach(A13);
  mst_servo[38].attach(A14);
  mst_servo[39].attach(A15);//33~40
  mst_servo[40].attach(23);
  mst_servo[41].attach(25);
  mst_servo[42].attach(27);
  mst_servo[43].attach(29);
  mst_servo[44].attach(31);
  mst_servo[45].attach(33);
  mst_servo[46].attach(35);
  mst_servo[47].attach(37);//41~48
  Serial.println("Master servos successfully initalized.");
  for(int i=0; i<SLAVES; i++)
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
  moveServo(48);
  //if Serial.available을 여기까지 씌우면 왠지 모르게 한바이트가 일단 잘려버린다.
}

void dataPartition(){
  memcpy(mst_buf,pixel_data,sizeof(mst_buf));
  memcpy(slv_buf[0],pixel_data+48,sizeof(slv_buf[0]));
  memcpy(slv_buf[1],pixel_data+56,sizeof(slv_buf[1]));
  for(int i=0; i < 5; i++) slv_buf[i][11]="\0"; // null signal
  mst_buf[9]="\0";
}

void moveServo(int amount){
  for(int i=0;i<amount;i++){
    mst_servo[i].write(50/*180-mst_buf[i]*/);
    delay(50);
  }
  delay(1000);
  for(int i=0;i<amount;i++){
    mst_servo[i].write(180);
  }
  delay(1000);
}

