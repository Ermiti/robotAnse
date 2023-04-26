#include <RTClib.h>
#include "RTClib.h"



#include <SoftwareSerial.h>
SoftwareSerial SoftSerial(10, 11); // RX | TX pins.  Can be reassigned to other pins if needed
int motorSpeed;
int BAUDRATE = 9600;
int motorStatus;


char Get;




const int sensorPin_R = A0;    // pin that the sensor is attached to
const int ledPin_R = 7;        // pin that the LED is attached to
const int ledPin_L = 8;
const int sensorPin_L = A1;




// variables:
int sensorValue_R = 0;         // the sensor value
int sensorValue_L = 0;
int sensorCalib_R = 600;           // maximum sensor value
int sensorCalib_L = 600;
// variavles of that sensor is sensitive of human presention
int ledPin = 13;                // choose the pin for the LED
int inputPin = A2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status



RTC_DS1307 rtc;
String internTime(){
   DateTime now = rtc.now();
     
    Serial.println("new intern at: ");
   
    // calculate a date which is 7 days & 30 seconds into the future
    DateTime future (now + TimeSpan(7,0,0,30));
     
    
    Serial.print(future.year(), DEC);
    Serial.print('/');
    Serial.print(future.month(), DEC);
    Serial.print('/');
    Serial.print(future.day(), DEC);
    Serial.print(' ');
    Serial.print(future.hour(), DEC);
    Serial.print(':');
    Serial.print(future.minute(), DEC);
    Serial.print(':');
    Serial.print(future.second(), DEC);
    Serial.println();
     
    Serial.println();
    delay(1000);
  
  }






void setup() {
  // put your setup code here, to run once:
  SoftSerial.begin(BAUDRATE);  // Init soft serial object
  Serial.begin(9600);
  Serial.println("Test started - Enter something to send to computer or Android phone");
  // moving motors
pinMode(22, OUTPUT);
 pinMode(44, OUTPUT);
 pinMode(23, OUTPUT);
 pinMode(24, OUTPUT);
 pinMode(25, OUTPUT);

}




void loop() {
  // put your main code here, to run repeatedly:

  while (SoftSerial.available() )
  {
    Get = SoftSerial.read();
    Serial.write(Get);
    if (Get == '1')
    {
      Serial.print("state 1 running");
      ///////////////////////////////////////////////////////////c
      while (Get != '9') {

sensorValue_L = analogRead(sensorPin_L);
      sensorValue_R = analogRead(sensorPin_R);

      if (sensorValue_L >= sensorCalib_L && sensorValue_R >= sensorCalib_R)
      {
        Serial.print("forward");
        delay(1000);
        // ROBOT Forward
//        digitalWrite(ledPin_R, HIGH);
//        digitalWrite(ledPin_L, HIGH);
      //  Serial.print("for");
        digitalWrite(24 , 1);
        digitalWrite(25 , 0);

        digitalWrite(22 , 1);
        digitalWrite(23 , 0);
        analogWrite(44 ,200);
        delay(20);
      }
      else if(sensorValue_L >= sensorCalib_L && sensorValue_R <= sensorCalib_R) {
        Serial.print("left");
        delay(1000);
       // Serial.print("left");
        digitalWrite(24 , 1);
        digitalWrite(25 , 1);

       digitalWrite(22 , 1);
       digitalWrite(23 , 0);
       analogWrite(44 ,200);
       delay(20);
      }
      else if (sensorValue_L <= sensorCalib_L && sensorValue_R >= sensorCalib_R){
       Serial.print("right");
       delay(1000);
       //Serial.print("right");
        digitalWrite(24 , 1);
        digitalWrite(25 , 0);

        digitalWrite(22 , 1);
        digitalWrite(23 , 1);
        analogWrite(44 ,200);
        delay(20);
      }
      else{
        Serial.print("stop");
        delay(1000);
      // Serial.print("stop");
        digitalWrite(24 , 0);
        digitalWrite(25 , 0);

        digitalWrite(22 , 0);
        digitalWrite(23 , 0);
      //  analogWrite(44 ,0);
        //Serial.print("motors off");
      }


      
        while (SoftSerial.available() )
        {

          Get = SoftSerial.read();
          Serial.write(Get);

        }

      }
      Serial.print("exite state 1 running");
    }



    
    else if (Get == '2')
    {
      Serial.print("state 2 running");
      //////////////////////////////////////////////////////c



      while (Get != '9') {
        
      val = digitalRead(A2);  // read input value
      if (val == HIGH) {            // check if the input is HIGH
        digitalWrite(ledPin, HIGH);  // turn LED ON
        if (pirState == LOW) {
          // we have just turned on
          Serial.println("Motion detected!");
          // We only want to print on the output change, not state
          pirState = HIGH;
          //******************NEW ADDITION
          internTime();
        }
      }
      else {
        digitalWrite(ledPin, LOW); // turn LED OFF
        if (pirState == HIGH) {
          // we have just turned of
          Serial.println("Motion ended!");
          // We only want to print on the output change, not state
          pirState = LOW;
        }
      }


        while (SoftSerial.available() )
        {

          Get = SoftSerial.read();
          Serial.write(Get);

        }

      }
      Serial.print("exite state 2 running");

    }
    else if (Get == '3')
    {
      Serial.print("state 3 running");
      ///////////////////////////////////////////////////////////c

      while (Get != '9') {

        while (SoftSerial.available() )
        {

          Get = SoftSerial.read();
          Serial.write(Get);

        }

      }
      Serial.print("exite state 3 running");
    }
    else if (Get == '4')
    {
      Serial.print("state 4 running");
      ///////////////////////////////////////////////////////////





      while (Get != '9') {

        while (SoftSerial.available() )
        {
          

      if (Get == 'f')
      {
        Serial.print("Robot Forward");
        // ROBOT Forward
        //    digitalWrite(ledPin_R,HIGH);
        //    digitalWrite(ledPin_L,HIGH);
        //       // ROBOT Forward
        //    digitalWrite(ledPin_R,HIGH);
        //    digitalWrite(ledPin_L,HIGH);

        digitalWrite(24 , 1);
        digitalWrite(25 , 0);

        digitalWrite(22 , 1);
        digitalWrite(23 , 0);
        analogWrite(44 ,220);

      }
      else if (Get == 'b')
      {
        Serial.print("Robot backward");
        digitalWrite(24 , 0);
        digitalWrite(25, 1);

        digitalWrite(22, 0);
        digitalWrite(23, 1);
        analogWrite(44 ,220);

      }
      else if (Get == 'l')
      {
        Serial.print("Robot left");
        digitalWrite(24, 1);
        digitalWrite(25 , 0);

        digitalWrite(22, 1);
        digitalWrite(23 , 1);
        analogWrite(44 ,220);
      }
      else if (Get == 'r')
      {
        Serial.print("Robot right");
        digitalWrite(24, 1);
        digitalWrite(25, 1);

        digitalWrite(22, 1);
        digitalWrite(23, 0);
        analogWrite(44 ,220);
      }
      else if (Get == 's')
      {
        Serial.print("Robot right");
        digitalWrite(24, 0);
        digitalWrite(25, 0);

        digitalWrite(22, 0);
        digitalWrite(23, 0);
        analogWrite(44 ,220);
      }


          Get = SoftSerial.read();
          Serial.write(Get);

        }

      }
      Serial.print("exite state 4 running");
    }

  }

  if ( Serial.available() ) {
    SoftSerial.write(Serial.read());

  }
}








//    if (Get == '1') {
//
//
//    Serial.print("state 1 running");
//      delay(200);
//
//
//      while (Get != '9') {
//
//         while (SoftSerial.available() )
//  {
//    // motorStatus = SoftSerial.parseInt();
//    Get = SoftSerial.read());
//    Serial.write(Get);
//    //delay(10);
//    }
//
//
//        Serial.print("state 1 running");
//        delay(200);
//
//        // The IR sensore
//        // read the sensor:
//
//        sensorValue_L = analogRead(sensorPin_L);
//        sensorValue_R = analogRead(sensorPin_R);
//
//
//
//        if (sensorValue_L <= sensorCalib_L && sensorValue_R <= sensorCalib_R)
//        {
//          // ROBOT Forward
//          digitalWrite(ledPin_R, HIGH);
//          digitalWrite(ledPin_L, HIGH);
//        }
//        else if (sensorValue_L >= sensorCalib_L && sensorValue_R >= sensorCalib_R)
//        {
//          // ROBOT Stop
//          digitalWrite(ledPin_R, LOW);
//          digitalWrite(ledPin_L, LOW);
//        }
//        else if (sensorValue_L >= sensorCalib_L && sensorValue_R <= sensorCalib_R)
//        {
//          // ROBOT moving Right
//          digitalWrite(ledPin_R, HIGH);
//          digitalWrite(ledPin_L, LOW);
//        }
//        else if (sensorValue_L <= sensorCalib_L && sensorValue_R >= sensorCalib_R)
//        {
//          // ROBOT moving Left
//          digitalWrite(ledPin_R, LOW);
//          digitalWrite(ledPin_L, HIGH);
//        }
//
//
//      }
//    }
//
//
//
//    if (Get == '2') {
//
//    Serial.print("state 2 running");
//      delay(200);
//
//
//      while (Get != '9') {
//
//   while (SoftSerial.available() )
//  {
//    // motorStatus = SoftSerial.parseInt();
//    Get = SoftSerial.read());
//    Serial.write(Get);
//    //delay(10);
//    }
//
//
//        val = digitalRead(A2);  // read input value
//        if (val == HIGH) {            // check if the input is HIGH
//          digitalWrite(ledPin, HIGH);  // turn LED ON
//          if (pirState == LOW) {
//            // we have just turned on
//            Serial.println("Motion detected!");
//            // We only want to print on the output change, not state
//            pirState = HIGH;
//            //******************NEW ADDITION
//            SoftSerial.write("new intern");
//          }
//        }
//        else {
//          digitalWrite(ledPin, LOW); // turn LED OFF
//          if (pirState == HIGH) {
//            // we have just turned of
//            Serial.println("Motion ended!");
//            // We only want to print on the output change, not state
//            pirState = LOW;
//          }
//        }
//      }
//
//
//    }
//
//
//

//
//
//
//  if (Get == '4') {}








//}
