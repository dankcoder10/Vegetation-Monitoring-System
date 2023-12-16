 #include <SPI.h>  
 #include <Wire.h>  
 #include <Adafruit_GFX.h>  
 #include <Adafruit_SSD1306.h>  
 #include <SimpleDHT.h>  

 int LDRInput=A0;           //Set Analog Input A0 for LDR.
 int duration=500; 
 int pinDHT11 = 2;  
 const int sensor_pin = A1; /* Soil moisture sensor O/P pin */
 
 SimpleDHT11 dht11(pinDHT11);  
 #define screen_width 128 // OLED display width, in pixels  
 #define screen_height 64 // OLED display height, in pixels  
 #define OLED_RESET 4  
 Adafruit_SSD1306 display(screen_width, screen_height);  
 void setup ()  
 {  
   Serial.begin(9600);  
   //Serial.println("CLEARDATA");
   Serial.println("LABEL, Time, Started Time, Date, TEMPERATURE (in *c), HUMIDITY (in %) ,MOISTURE (in %),LIGHT");
   Serial.println("RESETTIMER");
   pinMode(8, OUTPUT);  //relay
   pinMode(7, OUTPUT);  //buzzer
   pinMode(LDRInput,INPUT);  //LDR
    
   display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
   display.clearDisplay();  
 }  
 void loop ()  
 {  
  byte temperature = 0;  
  byte humidity = 0;  
  
  float moisture_percentage;
  int sensor_analog= analogRead(sensor_pin);;
  int value=analogRead(LDRInput);
  moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );

   
  int err = SimpleDHTErrSuccess;  
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {  
   Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);  
   return;  
  }  
  
  Serial.print("DATA, TIME, TIMER, DATE, ");
  Serial.print((int)temperature); //display first variable
  Serial.print(" , "); //move to next column
  Serial.print((int)humidity); //display second variable
  Serial.print(" , "); //move to next column
  Serial.print((float)moisture_percentage); //display third variable
  Serial.print(" , "); //move to next column
  Serial.print((int)value); //display fourth variable
  Serial.println(); // move to next row
    
  
  // DHT11 sampling rate is 1HZ.  
   display.clearDisplay();  
   display.setTextSize(1);  
   display.setTextColor(SSD1306_WHITE);  
   display.setCursor(0, 0);  
   display.print("  PLANT MONITORING          SYSTEM");  
   
   display.setCursor(0, 25);  
   display.print(" TEMPERATURE : ");  
   display.setCursor(90, 25);  
   display.print((int)temperature);
   display.setCursor(99, 25);  
   display.print(" C");

   display.setCursor(0, 35);  
   display.print(" MOISTURE : "); 
   display.setCursor(75, 35);  
   display.print((float)moisture_percentage);
   display.setCursor(99, 35);  
   display.print(" %");  
     
   display.setCursor(0, 45);  
   display.print(" HUMIDITY  : ");  
   display.setCursor(85, 45);  
   display.print((int)humidity);
   display.setCursor(99, 45);  
   display.print(" %");

   display.setCursor(0, 55);  
   display.print(" LIGHT    :"); 
   display.setCursor(75, 55);  
   display.print((int)value);
   
   //FOR RELAY
   if((float)moisture_percentage<10.00)
   digitalWrite(8, LOW);
   else 
   digitalWrite(8, HIGH);

   //FOR BUZZER 
   if( !( (int)humidity>40 && (int)humidity<70 ) || !( (float)moisture_percentage>30.00 && (float)moisture_percentage<100.00 )|| !((int)temperature>20 && (int)temperature<35 ))
   tone(7,1400,duration);
   delay(200);
     
   display.display();  
   delay(1000);
 }  
