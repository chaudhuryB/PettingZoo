// This contains all the reaction functions giving  
// the moves and playing of sound for each personality
void turnCCW(float speedFactor=1);
void turnCW(float speedFactor=1);
void goForward(float speedFactor=1);
void goBackward(float speedFactor=1);
void halt();
void glideLeft();
void glideRight();
/*
// Memory analyzer to check memory leaks
int freeRAM(){
  extern int __heap_start, *__brkval;
  int v;
  return(int)&v-(__brkval==0?(int)&__heap_start:(int)__brkval);
}
*/
void playSound()
{  
  //This functions reads the soundFile and plays it
  // Just be sure there to switch off what was playing before
  digitalWrite(tmrpcm.speakerPin, LOW);
  tmrpcm.disable();
  delay(200);
  tmrpcm.play(soundFile);
  delay(300);
  tmrpcm.loop(0);
}


void reactExcited(bool rightBumper)
{
  /* Turn & start playing sound together, 
   * stop, move forward gliding once or twice 
   * pick one randomly 
  */
  uint8_t loopTime = random(1,3);
  delay(100);
  sprintf(soundFile, "sndExci%d.wav", random(1,7));
  if(rightBumper)
  {
    turnCCW(0.8);
  }
  else{
    turnCW(0.8);
  }
  delay(150);
  playSound();
  delay(1000);
  halt();
  delay(200);
  for(uint8_t i=0; i<loopTime; i++){
    // random swivvel choice
    if(rightBumper){
      //swivvel start left
      glideLeft();
      delay(500);
      halt();
      delay(150);
      glideRight();
      delay(500);
      halt();
      delay(150);
    }
    else{
      // swivvel start right
      glideRight();
      delay(500);
      halt();
      delay(150);
      glideLeft();
      delay(500);
      halt();
      delay(150);
    }
  }
}
void reactHappy(bool rightBumper)
{// Try turn 180, stop, play sound, move on
  delay(100);
  sprintf(soundFile, "sndHapp%d.wav", random(1,7));
  delay(50);
  if(rightBumper)
  {
    turnCCW(0.7);
  }
  else{
    turnCW(0.7);
  }
  delay(150);
  playSound();
  delay(1500);
  halt();
  delay(500); 
}

void reactSurprise(bool rightBumper)
{
  //Move back fast & play sound , turn, move on
  sprintf(soundFile, "sndSurp%d.wav\0", random(1,7)); 
  delay(100);
  goBackward(2);
  playSound();
  delay(500);
  halt();  
  delay(1000);
  if(rightBumper)
  {
    turnCCW(0.5);
  }
  else{
    turnCW(0.5);
  }
  delay(700);
  halt();
  delay(200);
}

void reactSorry(bool rightBumper)
{
  //Move back slow, sound, turn, sound, turn other way, sound, turn and move
  sprintf(soundFile, "sndApol%d.wav\0", random(1,7));
  goBackward(0.3);
  delay(1000);
  playSound();
  halt();
  delay(100);
  if(rightBumper)
  {
    turnCCW();
    delay(500);
    halt();
    delay(500);
    turnCW();
    delay(500);
    halt();
    delay(500);
    turnCCW();
    delay(1000);
  }
  else{
    turnCW();
    delay(500);
    halt();
    delay(500);
    turnCCW();
    delay(500);
    halt();
    delay(500);
    turnCW();
    delay(1000);
  }
  halt();
  delay(150);
}

void reactScared(bool rightBumper)
{
  //Move back fast, stop, sound and wiggle in place, fast turn, move off
  uint8_t loopTime = random(2,4);
  sprintf(soundFile, "sndFear%d.wav\0", random(1,7));
  delay(100);
  goBackward(2);
  delay(500);
  halt();
  delay(200);
  playSound();
  for(uint8_t i=0; i<loopTime; i++){
      turnCCW(0.8);
      delay(200);
      halt();
      delay(50);
      turnCW(0.8);
      delay(200);
      halt();
      delay(50);
    }
  if(rightBumper)
  {    
    turnCCW(0.8);
    delay(700);
    halt();
  }
  else{
    turnCW(0.8);
    delay(700);
    halt();
  }  
  delay(100);
  //Serial.println(freeRAM());
}


void reactAngry(bool rightBumper)
{
  // Sound and Fast backward and forward re bump and repeat 
  // (2-3 times random) re-bumping 
  uint8_t loopTime = random(2, 4);
  sprintf(soundFile, "sndAngr%d.wav\0", random(1,7));
  playSound();
  for(uint8_t i=0; i<loopTime; i++)
  {
    goBackward();
    delay(500);
    halt();
    delay(100);
    goForward();
    delay(550);
    halt();
    delay(100);
  }
  goBackward();
  delay(700);
  if(rightBumper)
  {
    turnCCW(0.8);
  }
  else{
    turnCW(0.8);
  }
  delay(1000);
  halt();
  delay(200);
}
void bumpReact(bool rightBumper)
{
  // select the personality to play
  switch(personality)
  {
    case 1: reactExcited(rightBumper);
            break;
    case 2: reactSurprise(rightBumper);
            break;
    case 3: reactHappy(rightBumper);
            break;
    case 4: reactSorry(rightBumper);
            break;
    case 5: reactScared(rightBumper);
            break;
    case 6: reactAngry(rightBumper);
            break;
    default:Serial.println(F("No personality"));
            // Something went wrong read again
            //readSDSettings();
            delay(100);
            resetFunc();
            break;
  }
}






