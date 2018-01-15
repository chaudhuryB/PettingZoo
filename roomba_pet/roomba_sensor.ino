// This file is for reading Roomba sensors
bool checkLowBattery(){
  // Checks for Low battery or if the roomba is on the charger.
  // @returns bool: True if charge is equal/below quarter of the battery capcity or if the roomba 
  //                is on the charger
  char sensorbytes[10]; // variable to hold the returned 10 bytes
  // from iRobot Create
  Roomba.write((byte)142); // get sensor packets
  Roomba.write((byte)3); // sensor group packet ID 3, size 10
  // 25
  delay(64);
  // wipe old sensor data
  uint8_t i = 0;
  while (i < 10) {
  sensorbytes[i++] = 0;
  }
  i = uint8_t(0);
  while(Roomba.available()) {
      sensorbytes[i++] = Roomba.read();;
  }
  //battery charge is a quarter of battery capacity
  return ((byte(sensorbytes[0])&(byte)0x07) > 0 || (byte)sensorbytes[6] <= byte(sensorbytes[8]/4));
}

void updateSensor(){
  // Detects a hit on the left or right bumper and calls the bump reaction 
  // It will also lets the bump reaction know which bumper got hit so that the reaction
  // moves can try and get the roomba out of the bump situation
  uint8_t bumpRight = 0;
  uint8_t bumpLeft = 0;  
  char sensorbytes[10]; // variable to hold the returned 10 bytes
  // from iRobot Create
  Roomba.write((byte)142); // get sensor packets
  Roomba.write((byte)1); // sensor group packet ID 1, size 10
  // bytes, contains packets: 7-16
  delay(64);
  // wipe old sensor data
  uint8_t i = 0;
  while (i < 10) {
  sensorbytes[i++] = 0;
  }
  i = uint8_t(0);
  while(Roomba.available()) {
      sensorbytes[i++] = Roomba.read();
  }
  bumpRight = sensorbytes[0] & 0x01;
  // if right bumper is triggered sensorbytes[0] is: 00000001
  // bitwise AND with 0x01, i.e. 00000001 equals 1
  // see: http://arduino.cc/en/Reference/BitwiseAnd
  bumpLeft = sensorbytes[0] & 0x02;
  // if left bumper is triggered sensorbytes[0] is: 00000010
  // bitwise AND with 0x02, i.e. 00000010 equals 2
  // So if the right bumper is triggered bumpRight is 1
  // (if not triggered then 0)
  // if the left bumper is triggered bumpLeft is 2
  // (if not triggered then 0)
  if (bumpRight>0){
    digitalWrite(bumpPin, HIGH);
    delay(200);
    Roomba.write(131);
    delay(200);
  }
  if (bumpLeft>0) {
    digitalWrite(bumpPin, HIGH);
    delay(200);
    Roomba.write(131); 
    delay(200);
  }
  if(bumpRight+bumpLeft > 0){
    bumpReact(bumpRight>0);  
    delay(500);
    digitalWrite(bumpPin, LOW);
    if(!DEBUG){Roomba.write(135);}
    delay(500);
  }
  else{
    delay(200);
  }
}


