#include<Servo.h>
#include<string.h>
#define SLAVES 2

byte init_buf= 0xFF;
byte pixel_data[64];
char frame_buf[48];//+1?
char slv_buf[2][65]; //8+1?
Servo mst_servo[48];
int PORT[]={53,51,49,47,45,43,41,39,52,50,48,46,44,42,40,38,36,34,32,30,28,26,24,22,A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,8,9,10,11,12,13,23,25,27,29,31,33,35,37};


void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  for(int i =0; i<48; i++){
    mst_servo[i].attach(PORT[i]);
  }
  //Serial.clear();
  //Serial.println(0xFE);
  resetValue();
}
/*Serial.print(pixel_data[i]);
        if(i%8 == 7)
          Serial.println();*/
void loop() { //1번? 아님 젤마지막? 왜 움직이는거지... 1번인거같은데
  //receive
  if(Serial.available()){
    init_buf = Serial.read();
    if(init_buf==0xFE)
      for(int i=0; i < 64; i++)
        pixel_data[i]=Serial.read(); //시리얼 리드 도중에 시간이?
    else if(init_buf == 0xDD)
       moveServo2(48);
  }
  else{
    resetValue();//or configurated values
  }
  dataPartition();
  
  Serial1.write(slv_buf[0],sizeof(slv_buf[0]));//slv1
  Serial2.write(slv_buf[1],sizeof(slv_buf[1]));//slv2
   //wait for reading
  
  moveServo(48);
  delay(150); //딜레이는 안정적인 데이터 해석을 위해 필요?..
}

void moveServo(int amount){
  for(int i=0;i<amount;i++){
    mst_servo[i].write((byte)frame_buf[i]);
    //delay(50);
  }
}

void moveServo2(int amount){
  for(int i=0;i<amount;i++){
    mst_servo[i].write(100/*180-mst_buf[i]*/);
    delay(50);
  }
  delay(1000);
  for(int i=0;i<amount;i++){
    mst_servo[i].write(180);
  }
}

void dataPartition(){
  memcpy(frame_buf,pixel_data,sizeof(frame_buf));
  memcpy(slv_buf[0]+1,pixel_data,sizeof(slv_buf[0]));
  memcpy(slv_buf[1]+1,pixel_data,sizeof(slv_buf[1]));
  slv_buf[0][0]= 0xFE; 
  //slv_buf[0][8] = '\0';
  slv_buf[1][0]= 0xFE; 
  //slv_buf[1][8] = '\0';
  //Serial.println(slv_buf[1]);
}

void resetValue(){//or configurated values
  for(int i =0; i<64; i++)
    pixel_data[i] =180; //or configurated values
  //moveServo(48);
}

