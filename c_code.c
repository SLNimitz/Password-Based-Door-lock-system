#include<Keypad.h> // KEYPAD LIBRARY FOR KEYPAD INTERFACING 
#include<LiquidCrystal.h> // LIBRARY FOR LCD INTERFACING
#include<Servo.h>// LIBRARY FOR SERVO MOTOR
//#include<String.h>
#define buzzer 20 // DEFINING PIN FOR BUZZER.

LiquidCrystal lcd(14,15,16,17,18,19); // PINS FOR LCD

char keys[4][4]={ // LAYOUT OF KEYPAD
 {'1','2','3'},
 {'4','5','6'},
 {'7','8','9'},
 {'*','0','#'}};
 
byte rowPin[4]={1,2,3,4}; // ROW PINS OF KEYPAD
byte colPin[3]={5,6,7}; // COLUMN PINS OF KEYPAD

Servo servo_Motor; 
String password = "123456";  // SETTING DEFAULT PASSWORD.
int position = 0; // VARIABLE FOR DETERMINING THE POSITION.

int wrong = 0; // VARIABLE FOR CALCULATING THE WRONG INPUT.

int redPin = 9; // DEFINING PIN FOR RED LED
int greenPin = 8; // DEFINING PIN FOR GREEN LED
 
Keypad keypad=Keypad(makeKeymap(keys),rowPin,colPin,4,4);
// MAPPING THE KEYPAD.


int total = 0; // VARIABLE TO DETERMINE THE NUMBER OF WRONG ATTEMPTS.

void setup()
{
 pinMode(redPin,OUTPUT);
 pinMode(greenPin,OUTPUT);
 
lcd.begin(16,2);
lcd.print("DOOR LOCK SYSTEM");
lcd.setCursor(0,2);
lcd.print("       BY:");
delay(2000);
lcd.clear();
lcd.print("Creative");
lcd.setCursor(0,2);
lcd.print("    Engineer");
delay(2000);
lcd.clear();
servo_Motor.attach(3);
setLocked(true);
delay(1000);

pinMode(buzzer, OUTPUT);
}

void loop()
{
  
  lcd.clear();
  lcd.print("Enter Password:");
  delay(100);
  
 char pressed=keypad.getKey();// TAKING THE INPUT FROM KEYPAD
 String key[3];
  
 if(pressed) // IF THE KEY IS PRESSED
 {
  lcd.clear();
  lcd.print("Enter Password:");
  lcd.setCursor(position,2);
  lcd.print(pressed);
  delay(500);
    if(pressed == '*' || pressed == '#')
      {
          position = 0;
          setLocked(true);
          lcd.clear();
      }

    else if(pressed == password[position])
      {
          key[position]=pressed;
          position++;
      }
 
    else if (pressed != password[position] )
      {// IN CASE OF WRONG INPUT INCREMENT BOTH WRONG AND POSITION.
          wrong++;
          position ++;
      }

    if(position == 3)
      {// WHEN POSITION == 3 THEN CHECK THE FOLLOWING
          if( wrong >0) // IF ANY WRONG INPUT IF GIVEN THEN INCREMENT TOTAL AND
          // SET WRONG AND POSITION TO ZERO.
            {
                total++;
                wrong = 0;
                position = 0;
                lcd.clear();
                lcd.print("WRONG");
                lcd.setCursor(5,2);
                lcd.print("PASSWORD");
                delay(1000);
                setLocked(true);
            }

          else if(position == 3 && wrong == 0)
            {// IF NO WRONG VALUE IS GIVEN THEN DISPLAY THE ACCEPTED PASSWORD AND
              // MOVE THE SERVO MOTOR.
                position = 0;
                wrong = 0;
                lcd.clear();
                lcd.print("PASSWORD");
                lcd.setCursor(6,2);
                lcd.print("ACCEPTED");
                delay(2000);
                lcd.clear();
                lcd.print("Door Open");
                delay(2000);
                setLocked(false);
            }

          if(total ==3)// IF TOTAL OF 3 ATTEMPTS ARE DONE BY ENTERING WRONG PASS
          //WORD THEN SOUND A BUZZER AND SET TOTAL TO 0.
            {
                total=0;
                buzzer_beep();
                delay(500);
            }

        }

   }

   
}

void setLocked(int locked)// FUNCTION TO CHANGE STATUS OF SERVO MOTOR.
  {
    if (locked)
      {
          digitalWrite(redPin, HIGH);
          digitalWrite(greenPin, LOW);
          delay(1000);
          servo_Motor.attach(3);
          servo_Motor.write(10);
          delay(1000);
          servo_Motor.detach();
      }
    else
      {
          digitalWrite(redPin, LOW);
          digitalWrite(greenPin, HIGH);
          delay(1000);
          servo_Motor.attach(3);
          servo_Motor.write(90);
          delay(1000);
          servo_Motor.detach();
      }
  }
void buzzer_beep()// FUNCTION TO BEEP THE BUZZER.
{
   digitalWrite(buzzer,HIGH);
   delay(1000);
   digitalWrite(buzzer,LOW);
   delay(1000);
   lcd.clear();
   lcd.setCursor(16,0);
   lcd.print("Door locked");
   lcd.setCursor(16,1);
   lcd.print("Thank You");
   delay(2000);
   while(1)
   {
   lcd.scrollDisplayLeft();
   delay(200);
   }
}
