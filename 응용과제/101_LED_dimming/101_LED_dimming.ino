void setup(){  
  ledcSetup(0, 5000, 8);    
  ledcAttachPin(2, 0);    
}  
 void loop(){  
  for(int i = 0; i <= 255; i++){     
    ledcWrite(0, i);  
    delay(15);  
  }  
delay(1000);  
}  
