 void readSDSettings(){
   // reads the personality setting
   File confFile = SD.open(F("config.txt"));
   String check;
   if (confFile) {
     if (confFile.available()) { 
        check = check + char(confFile.read());
        personality= uint8_t(check.toInt());
        Serial.println(personality);
        }
     // close the file:
     confFile.close();
 }
}

