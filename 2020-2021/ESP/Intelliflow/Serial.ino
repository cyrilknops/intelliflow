void serialConfig(){  
  if(Serial.available() > 0){
    if(Serial.readStringUntil('\n') == "admin"){
      readEEPROM();
      Serial.print("P1: ");
      Serial.println(passwordCounter);
      Serial.print("P2: ");
      Serial.println(passwordTerror);
      Serial.print("MK: ");
      Serial.println(mastercode);
      Serial.print("H: ");
      Serial.println(hours);
      Serial.print("M: ");
      Serial.println(minutes);
      Serial.print("S: ");
      Serial.println(seconds);
      Serial.print("A: ");
      Serial.println(alarm);
      Serial.print("AW: ");
      Serial.println(alarmWarning);
      Serial.println("end");
    }
    else{
      passwordCounter = Serial.readStringUntil(';').toInt();
      Serial.read();
      passwordTerror = Serial.readStringUntil(';').toInt();
      Serial.read();
      mastercode = Serial.readStringUntil(';').toInt();
      Serial.read();
      hours = Serial.readStringUntil(';').toInt();
      Serial.read();
      minutes = Serial.readStringUntil(';').toInt();
      Serial.read();
      seconds = Serial.readString().toInt();
      Serial.read();
      alarm = Serial.readString().toInt();
      Serial.read();
      alarmWarning = Serial.readString().toInt();
      Serial.println("end");
      writeEEPROM();
      timeSet();
    }
  }
}  
