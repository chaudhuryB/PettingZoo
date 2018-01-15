// These are the basic moves that the roomba can do
void goForward(float speedFactor){
 if(!DEBUG){
   Roomba.write(137);   // DRIVE
   Roomba.write((byte)0x00);   // 0x00c8 == 200
   Roomba.write(byte(0xc8 * speedFactor));
   Roomba.write(0x80);
   Roomba.write((byte)0x00);
 }
}

void goBackward(float speedFactor) {
 if(!DEBUG){
   Roomba.write(137);   // DRIVE
   Roomba.write(0xff);   // 0xff38 == -200
   Roomba.write(byte(0x38 / speedFactor)); 
   Roomba.write(0x80);
   Roomba.write((byte)0x00);
 }
}

void turnCW(float speedFactor) {
 // turn right
 if(!DEBUG){
   Roomba.write(137);   // DRIVE
   Roomba.write((byte)0x00);   // 0x00c8 == 200
   Roomba.write(byte(0xc8 * speedFactor)); 
   Roomba.write(0xff);
   Roomba.write((byte)0xff);
 }
}
void turnCCW(float speedFactor) {
 // turn left
 if(!DEBUG){
   Roomba.write(137);   // DRIVE
   Roomba.write((byte)0x00);   // 0x00c8 == 200
   Roomba.write(byte(0xc8 * speedFactor)); 
   Roomba.write((byte)0x00);
   Roomba.write((byte)0x01);
 }
}

void glideLeft(){
 if(!DEBUG){
   Roomba.write(137);   // DRIVE
   Roomba.write((byte)0x00);   // 0x00c8 == 200
   Roomba.write(0xc8);
   Roomba.write((byte)0x00);
   Roomba.write((byte)0x64);  // 100mm radius
 }
}

void glideRight(){
  if(!DEBUG){
   Roomba.write(137);   // DRIVE
   Roomba.write((byte)0x00);   // 0x00c8 == 200
   Roomba.write(0xc8);
   Roomba.write(0xff);
   Roomba.write((byte)0x9c);  // -100mm radius
  }
}

void halt(){
byte j = 0x00;
Roomba.write(137);  
Roomba.write(j);  
Roomba.write(j);
Roomba.write(j);
Roomba.write(j);
}

void doStartMove()
{
 // The start routine that will give a visual indication
 // that the rooma is initialised and started by the arduino
 goForward();
 delay (500);
 halt();
 delay(800);
 goBackward();
 delay (500);
 halt();
 delay(800);
}


