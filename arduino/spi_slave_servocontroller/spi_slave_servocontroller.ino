#include<Servo.h>
#include<SPI.h>

// volatile 선언을 통해 업데이트된 값이 정확하게 반영되도록 한다. 
volatile byte pos; // 수신 버퍼에 문자를 기록할 위치
volatile boolean data_end; // 데이터수신이 끝나면 true

char slv_buf[12] = {0,};
Servo slv_servo[11];

void setup() {
//  MOSI = 11;
//  MISO = 12;
//  SCK = 13;
  pos =0; //write from first index of buffer
  data_end = false; //data receiving not completed

  Serial.begin(9600);
  pinMode(MOSI, OUTPUT);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  // SPI 통신을 위한 레지스터를 설정
  SPCR |= _BV(SPE); // SPI 활성화
  SPCR &= ~_BV(MSTR); // Slave 모드 선택
  SPCR |= _BV(SPIE); // 인터럽트 허용

  
  slv_servo[0].attach(A3);
  slv_servo[1].attach(A2);
  slv_servo[2].attach(A1);
  slv_servo[3].attach(A0);
  slv_servo[4].attach(13);
  slv_servo[5].attach(12);
  slv_servo[6].attach(2);
  slv_servo[7].attach(3);
  slv_servo[8].attach(4);
  slv_servo[9].attach(5);
  slv_servo[10].attach(6);
}
//이벤트처리
ISR (SPI_STC_vect)
{
  char input= SPDR;
  if (pos < sizeof(slv_buf)){  //if buffer available
    slv_buf[pos++] = input;  // receive one character
    //Serial.println(slv_buf[pos]);
     
    if (input == '\0'){
      data_end = true;
    }
  }
}

//매번수행
void loop() {
  if(data_end){
    //Serial.println(slv_buf);
    pos = 0;
    data_end = false;
  }
  moveServo(11); //print
}

void moveServo(int amount){
  for(int i=0;i<amount;i++){
    //slv_servo[i].write(slv_buf[i]);
  }
  delay(500);
//  for(int i=0;i<amount;i++){
//    slv_servo[i].write(180);
//  }
//  delay(500);
}
