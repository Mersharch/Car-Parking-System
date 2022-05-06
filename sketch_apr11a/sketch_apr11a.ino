#include <LiquidCrystal.h>

#include <Servo.h>


LiquidCrystal lcd(9, 8, 4, 3, 2, 1);

int entryIR = 13;   //entry sensor
int exitIR = 12;   //exit sensor
int spot1 = 7;    //spot 1 sensor
int spot2 = 6;   //spot 2 sensor
int spot3 = 5;  //spot 3 sensor

int S1, S2, S3;

Servo entryservo; //entry motor
Servo exitservo; //exit motor

int pos = 90;    // variable to store the servo position for entry at default

int dpos = -90; // servo position for exit at default


int spots = 3;   //total number of spots
int filled;



void setup() {
  // put your setup code here, to run once:
  lcd.begin(20,4);
  lcd.setCursor(4,0);
  lcd.print("Welcome To");
  lcd.setCursor(3,1);
  lcd.print("City Car Park :)");
  pinMode(entryIR, INPUT);
  pinMode(exitIR, INPUT);
  pinMode(spot1, INPUT);
  pinMode(spot2, INPUT);
  pinMode(spot3, INPUT);
  entryservo.attach(11);
  exitservo.attach(10);
  entryservo.write(pos);
  exitservo.write(dpos);


}

void loop() {

  if(digitalRead(entryIR) == HIGH){
    Read_Sensors();

    if(filled == spots) {
        lcd.clear();
        lcd.setCursor(6,0);
        lcd.print("Sorry,");
        lcd.setCursor(1,1);
        lcd.print("No Parking Space");
        lcd.setCursor(4,2);
        lcd.print("Available!");
    }

    else {
        Entry_Barrier();
        delay(150);

        Read_Sensors();
        
          lcd.clear();
          lcd.setCursor(4,0);
          lcd.print("Welcome To");
          lcd.setCursor(3,1);
          lcd.print("City Car Park :)");
      
        lcd.setCursor (0, 2);
        if (S1 == 1) {
          lcd.print("S1:FULL");
        }
        else {
          lcd.print("S1:EMPTY");
        }
      
        lcd.setCursor (12, 2);
        if (S2 == 1) {
          lcd.print("S2:FULL");
        }
        else {
          lcd.print("S2:EMPTY");
        }
      
        lcd.setCursor (5, 3);
        if (S3 == 1) {
          lcd.print("S3:FULL");
        }
        else {
          lcd.print("S3:EMPTY");
        }

        
     }
  }

  else {
    Read_Sensors();
   }


  if (digitalRead(exitIR) == HIGH){
      Exit_Barrier();//exit motor lifts to allow car to exit the car park
      //wait a few seconds and close
      delay(150);

      Read_Sensors();
        
          lcd.clear();
          lcd.setCursor(4,0);
          lcd.print("Welcome To");
          lcd.setCursor(3,1);
          lcd.print("City Car Park :)");
      
        lcd.setCursor (0, 2);
        if (S1 == 1) {
          lcd.print("S1:FULL");
        }
        else {
          lcd.print("S1:EMPTY");
        }
      
        lcd.setCursor (12, 2);
        if (S2 == 1) {
          lcd.print("S2:FULL");
        }
        else {
          lcd.print("S2:EMPTY");
        }
      
        lcd.setCursor (5, 3);
        if (S3 == 1) {
          lcd.print("S3:FULL");
        }
        else {
          lcd.print("S3:EMPTY");
        }
      
    
  }

  else {
    Read_Sensors();
   }

  

  

}



void Entry_Barrier(){
  for (pos = 90; pos >= 0; pos -= 1) { // goes from 90 degrees to 180 degrees
    // in steps of 1 degree
    entryservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(3);                       // waits 15 ms for the servo to reach the position
  }
  
  
  
  for (pos = 0; pos <= 90; pos += 1) { // goes from 180 degrees to 90 degrees
    entryservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(3);                       // waits 15 ms for the servo to reach the position
  }
}

void Exit_Barrier(){
  for (dpos = -90; dpos <= 0; dpos += 1) { // goes from 90 degrees to 180 degrees
    // in steps of 1 degree
    exitservo.write(dpos);              // tell servo to go to position in variable 'pos'
    delay(3);                       // waits 15 ms for the servo to reach the position
  }
  
  
  
  for (dpos = 0; dpos >= -90; dpos -= 1) { // goes from 180 degrees to 90 degrees
    exitservo.write(dpos);              // tell servo to go to position in variable 'pos'
    delay(3);                       // waits 15 ms for the servo to reach the position
  }
}



void Read_Sensors(){
S1=0, S2=0, S3=0;

if(digitalRead(spot1) == HIGH){S1=1;}
if(digitalRead(spot2) == HIGH){S2=1;}
if(digitalRead(spot3) == HIGH){S3=1;} 

filled = S1 + S2 + S3;

}
