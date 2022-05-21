#include "Keyboard.h"
#include <Keypad.h>
#include <Encoder.h>

const byte ROWS = 2; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
{'1','2','3','4'},
{'5','6','7','8'},
};

int modePushCounter = 0;       // counter for the number of button presses
int buttonState = 0;           // current state of the button
int lastButtonState = 0;       // previous state of the button

Encoder RotaryEncoder(10, 16);
long positionEncoder  = -999; //encoderA LEFT position variable

const int ModeButton = A0;     // the pin that the Modebutton is attached to
const int pot = A1;           // pot for adjusting attract mode demoTime or mouseMouse pixel value

byte rowPins[ROWS] = {4, 5 };    //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9 };  //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);
  Serial.println("TwoKnobs Encoder Test:");
  Keyboard.begin();
  pinMode(ModeButton, INPUT_PULLUP);
}

void loop() {
  //char key = keypad.getKey();

  //encoder0();
  //keys0();

checkModeButton();

switch (modePushCounter){
  case 0: 
    encoder0();
    keys0();
    break;

  case 1:
    //encoder1();
    keys1();
    break;
}

}

void checkModeButton(){
  buttonState = digitalRead(A0);
  //Serial.println(buttonState);
  if (buttonState != lastButtonState) { // compare the buttonState to its previous state
    if (buttonState == LOW) { // if the state has changed, increment the counter
      // if the current state is LOW then the button cycled:
      modePushCounter++;
      Serial.println("pressed");
      Serial.print("number of button pushes: ");
      Serial.println(modePushCounter);
      //colorUpdate = 0;      // set the color change flag ONLY when we know the mode button has been pressed. 
                            // Saves processor resources from updating the neoPixel colors all the time
    } 
    delay(50); // Delay a little bit to avoid bouncing
  }
  lastButtonState = buttonState;  // save the current state as the last state, for next time through the loop
  if (modePushCounter >1){       //reset the counter after 4 presses CHANGE THIS FOR MORE MODES
      modePushCounter = 0;}
}


//-------------------------------encoder modes-----------------------------------
void encoder0(){
  long newPos = RotaryEncoder.read();

  //Serial.println(newPos);
  if (newPos > positionEncoder && (newPos % 4 == 0)) {
    positionEncoder = newPos;
    //Serial.println(positionEncoderA);
    Keyboard.press(KEY_RIGHT_ARROW);
    Keyboard.release(KEY_RIGHT_ARROW);
  }
  if (newPos < positionEncoder && (newPos % 4 == 0)) {
    positionEncoder = newPos;
    //Serial.println(positionEncoderA);
    Keyboard.press(KEY_LEFT_ARROW);
    Keyboard.release(KEY_LEFT_ARROW);
  }
}

void encoder1(){

}


//-------------------------------key modes-----------------------------------
void keys0(){
  char key = keypad.getKey();

    if (key) {
    //Serial.println(key);
      switch (key) {
        case '1': 
          Keyboard.press(KEY_TAB);     //tab
          Keyboard.release(KEY_TAB);
          break;
          
        case '2': 
          //Keyboard.println('Key 2');
          Keyboard.press(KEY_UP_ARROW);     //UP ARROW
          Keyboard.release(KEY_UP_ARROW);  
          break;
          
        case '3': 
          Keyboard.press(KEY_LEFT_ALT);     //ALT TAB
          Keyboard.press(KEY_TAB);
          Keyboard.releaseAll();
          break;
          
        case '4': 
          Keyboard.press(KEY_LEFT_ALT);     //ALT F4
          Keyboard.press(KEY_F4);
          Keyboard.releaseAll();
          break;
          
        case '5': 
          Keyboard.press(KEY_DELETE);     //delete
          Keyboard.release(KEY_DELETE);
          break;
          
        case '6': 
          //Keyboard.println('Key 6');
          Keyboard.press(KEY_DOWN_ARROW);     //DOWN ARROW
          Keyboard.release(KEY_DOWN_ARROW);  
          break;
          
        case '7': 
          Keyboard.press(KEY_LEFT_CTRL);      //COPY
          Keyboard.print('c');
          Keyboard.release(KEY_LEFT_CTRL);
          break;
          
        case '8': 
          Keyboard.press(KEY_LEFT_CTRL);      //PASTE
          Keyboard.print('v');
          Keyboard.release(KEY_LEFT_CTRL);
          break;
      }
  }
    //delay(100); 
  Keyboard.releaseAll();
}

void keys1(){
  char key = keypad.getKey();
  if (key){
  Serial.println(key);
    switch (key){
      case '1':
        Keyboard.write('1');
        break;
      case '2':
        Keyboard.write('2');
        break;
      case '3':
        Keyboard.write('3');
        break;
      case '4':
        Keyboard.write('4');
        break;
      case '5':
        Keyboard.write('5');
        break;
      case '6':
        Keyboard.write('6');
        break;
      case '7':
        Keyboard.write('7');
        break;
      case '8':
        Keyboard.write('8');
        break;
    }
  } 
  Keyboard.releaseAll();
}
