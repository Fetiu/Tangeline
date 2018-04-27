import processing.serial.*;
import de.voidplus.leapmotion.*;
import de.voidplus.leapmotion.LeapMotion;

public static int frame_cnt;

public static byte[] data= new byte[65];  
byte[] tmp = new byte[64];
LeapMotion leap;

char pixel[]={ 
   100,160,180,180,160,100,50,0,
   100,160,180,180,160,100,50,0,
   100,160,180,180,160,100,50,0,
   100,160,180,180,160,100,50,0,
   100,160,180,180,160,100,50,0,
   100,160,180,180,160,100,50,0,
   100,160,180,180,160,100,50,0,
   100,160,180,180,160,100,50,0 
   };
Serial port;

void setup(){
  try{
    port = new Serial(this, Serial.list()[1], 9600);
    println(Serial.list()[0]);
  }
  catch(ArrayIndexOutOfBoundsException e){
    println("port not available");
  }
  
  leap =new LeapMotion(this);
  size(800, 500);
  resetValue();
}

void draw(){
  int cnt=0;
  
  //title();
  //msg();
  port.clear();
  switch(key){
    case 't':
      tangeline();
      break;
    case 'c': 
      config();
      break;
    case 'z':
      pit();
      break;
    case 'x':
      wave(cnt);
      cnt++;
      break;
    case 'p':
      heart();
      break;
    case 'h':  default:
      title();
      resetValue();
  }
  //println(key);
  
  //println(data[0],data[1]);
}

void title(){
  clear();
  background(255);
  strokeWeight(3);
  fill(250, 250, 250);
  rect(5, 5, 790, 70, 20, 20, 20, 20);
  fill(250, 120, 0);
  textFont(createFont("orbitron",50));
  text("Tangeline Control Panel",60,55);
  
  fill(0, 0, 0);
  textFont(createFont("product sans",30));
  text("c. Open Display Configuration.",10,150);
  text("v. Play 'Leap Motion Visualizer'.",10,200);
  text("x. Play 'The WAVE'.",10,250);
  text("z. Play 'The PIT'.",10,300);
  text("p. Play 'The Heart'.",10,350);
  text("t. Play 'Tangeline'.",10,400);
  
  //resetValue();
}

void tangeline(){
  clear();
  background(0);
  fill(250, 250, 250);
  textFont(createFont("orbitron",50));
  text("Tangeline",60,55);

  fill(250, 250, 250);
  textFont(createFont("product sans",30));
  text("Press 'h' to retrun Home",60,480);
}

void config(){
  clear();
  background(0);
  fill(250, 250, 250);
  textFont(createFont("orbitron",50));
  text("Configuration Page",60,55);

  fill(250, 250, 250);
  textFont(createFont("product sans",30));
  text("Press 'h' to retrun Home",60,480);
  
  port.write(0xDD);
  
  //int zpos;
  //for(Hand hand : leap.getHands()){
  //  Finger[] fingers = leap.getFingers(leap.getId());
  //  //Finger.drawJoints();
  //}
  
  //if(frame_cnt>=64)
  //  frame_cnt=0;
    
  ////if(data[frame_cnt+1]>100)
  //  data[frame_cnt+1]=(byte)100;
  ////else
  //  //data[frame_cnt+1]=(byte)180;

  //frame_cnt++;
  //println(frame_cnt);
  
  //data[0]=(byte)0xFE;
  //port.write(data);
  //delay(50);
}


void pit(){
  char pixel[]={
    180,180,180,180,180,180,180,180,
    180,140,140,140,140,140,140,180 ,
    180,140,100,100,100,100,140,180 ,
    180,140,100,100,100,100,140,180 ,
    180,140,100,100,100,100,140,180 ,
    180,140,100,100,100,100,140,180 ,
    180,140,140,140,140,140,140,180 ,
    180,180,180,100,100,180,180,180 };
  //byte[] frame = new byte[64];
  
  //user code here
  //resetValue();
  for(int i =0; i< 64;i++)
    data[i+1] = (byte)pixel[i];
  //data[1]=(byte)180;
  
  data[0]=(byte)0xFE;
  port.write(data);
  
  clear();
  background(0);
  fill(250, 250, 250);
  textFont(createFont("orbitron",50));
  text("Pit",60,55);

  fill(250, 250, 250);
  textFont(createFont("product sans",30));
  text("Press 'h' to retrun Home",60,480);
  
  //delay(500);
}

void heart(){
  char pixel[]={    
   180, 140,140,180,180,140,140,180 ,
   140, 120,100,140,140,100,100,140 ,
   140, 100, 60,100,100, 120,100,140 ,
   140, 100, 60, 60,60, 60, 100,140 ,
   140, 100, 60, 60,60, 60, 100,140 ,
   180, 140, 60, 60,60,100, 140,180 , 
   180,180, 140,100,100,140,180,180 ,
   180,180,180, 140,140,180,180,180 };
  //byte[] frame = new byte[64];
  
  //user code here
  //if(frame_cnt%2)
  //resetValue();
  for(int i =0; i< 64;i++)
    data[i+1] = (byte)pixel[i];

  clear();
  background(0);
  fill(250, 250, 250);
  textFont(createFont("orbitron",50));
  text("Heart",60,55);

  fill(250, 250, 250);
  textFont(createFont("product sans",30));
  text("Press 'h' to retrun Home",60,480);
  
  data[0]=(byte)0xFE;
  port.write(data);
  //delay(50);
}

void pyramid(){
  
  char pixel[]={
   180,180,180,180,180,180,180,180 ,
   180, 60, 60, 60, 60, 60, 60, 60 ,
   180, 60,100,100,100,100,100, 60 ,
   180, 60,100,140,140,140,100, 60 ,
   180, 60,100,140,180,140,100, 60 ,
   180, 60,100,140,140,140,100, 60 ,
   180, 60,100,100,100,100,100, 60 ,
   180, 60, 60, 60, 60, 60, 60, 60 };
   
  clear();
  background(0);
  fill(250, 250, 250);
  textFont(createFont("orbitron",50));
  text("Pyramid",60,55);

  fill(250, 250, 250);
  textFont(createFont("product sans",30));
  text("Press 'h' to retrun Home",60,480);
  
  
  for(int i =0; i< 64;i++)
    data[i+1] = (byte)pixel[i];
    
}

void wave(int cnt){
  int k,j;
  
  byte[] frame = new byte[64];

  char pixel[]={
   100,160,180,180,160,100,80,50,
   100,160,180,180,160,100,80,50,
   100,160,180,180,160,100,80,50,
   100,160,180,180,160,100,80,50,
   100,160,180,180,160,100,80,50,
   100,160,180,180,160,100,80,50,
   100,160,180,180,160,100,80,50,
   100,160,180,180,160,100,80,50
   };
  //resetValue();
  
  for(int i = 0; i < 64; i++)
    frame[i] = (byte)pixel[i];

  if(cnt==0){
    for(int i = 0; i < 64; i++)
      tmp[i] = (byte)pixel[i];
  }
  else{
    for(int i = 0; i < 64; i++)
      frame[i] = tmp[(i+1)%8];
    
    for(int i = 0; i < 64; i++)
      tmp[i] = frame[i];
  }

  //System.arraycopy( frame, 0, data, 1, frame.length );
  data[0]=(byte)0xFE;
  
  for(int i =0; i< 64;i++)
    data[i+1] = (byte) frame[i];
    
  port.write(data);


  clear();
  background(0);
  fill(250, 250, 250);
  textFont(createFont("orbitron",50));
  text("wave",60,55);
  
  text((char)cnt,60,200);
  
  fill(250, 250, 250);
  textFont(createFont("product sans",30));
  text("Press 'h' to retrun Home",60,480);
  
  //delay(500);

}

void resetValue(){
  data[0]= (byte)0xFE;
  for(int i=0; i<64;i++){
    data[i+1]=(byte)180;
    //print(data[i]);
  }
  port.clear();
  //port.write(data);
}

void msg(){
  if(port.available()>0){
  println(port.read());
  }
}