#include <Arduino.h>

// button noises
#define NOTE0 880 // NOTE_A5
#define NOTE1 988 // NOTE_B5
#define NOTE2 1047 // NOTE_C6
#define NOTE3 1175 // NOTE_D6

// notes used for victory noise
#define NOTE_AS6 932

int inPin0 = 12;   // choose the input pin (for a pushbutton)
int ledPin0 = 13; // choose the pin for the LED

int inPin1 = 9;   // choose the input pin (for a pushbutton)
int ledPin1 = 10; // choose the pin for the LED

int inPin2 = 6;   // choose the input pin (for a pushbutton)
int ledPin2 = 5; // choose the pin for the LED

int inPin3 = 2;   // choose the input pin (for a pushbutton)
int ledPin3 = 3; // choose the pin for the LED

int speakerPin4 = 4; // choose the pin for the speaker

int val0 = 0;     // variable for reading the pin status
int val1 = 0;     // variable for reading the pin status
int val2 = 0;     // variable for reading the pin status
int val3 = 0;     // variable for reading the pin status

void setup() {
  Serial.begin(9600);
  pinMode(ledPin0, OUTPUT);  // declare LED as output
  pinMode(inPin0, INPUT);    // declare pushbutton as input

  pinMode(ledPin1, OUTPUT);  // declare LED as output
  pinMode(inPin1, INPUT);    // declare pushbutton as input

  pinMode(ledPin2, OUTPUT);  // declare LED as output
  pinMode(inPin2, INPUT);    // declare pushbutton as input

  pinMode(ledPin3, OUTPUT);  // declare LED as output
  pinMode(inPin3, INPUT);    // declare pushbutton as input

  pinMode(speakerPin4, OUTPUT);  // declare speaker as output
}

void loop(){
  /*
   * Main loop of program. If reset ever becomes true or the pattern
   * is ever incorrect, it will break the while loop, thus repeating
   * function (starting over from the beginning.)
   * Function works by playing a pattern (and saving that pattern as
   * a string), then saves user input, then compares if the user input
   * was the correct pattern, and then progresses them to the next level
   * or starts them over from the beginning. Will likely add "home screen"
   * where user has to press a button to start, and it'll just play a pattern.
   */
  bool reset = 0;
  bool patternCorrect = 1;
  int level = 1;
  while (reset == 0 && patternCorrect == 1){
    // clear previous pattern and input
    String correctPattern = "";
    String userPattern = "";

    // play new pattern and gather input
    correctPattern = playPattern(level);
    userPattern = readInput(level);

    // verify input and proceed to next level
    level = checkInput(correctPattern, userPattern, level);
    if (!level)
      patternCorrect = 0;
  }
}
String readInput(int level){
  /*
   * Gathers user input and returns it. While gathering user input, it will
   * turn on the LED corresponding to the button they press, as well play
   * the sound that corresponds with that LED.
   * //NOTE: Check test_led_and_button1 for finding out how to fix this.
   */
  String userPattern;
  while (userPattern.length() < (3 + level)) { // while userPattern < length of pattern
    int currentLen = userPattern.length();

    // read button values
    val0 = digitalRead(inPin0);  // read input value
    val1 = digitalRead(inPin1);  // read input value
    val2 = digitalRead(inPin2);  // read input value
    val3 = digitalRead(inPin3);  // read input value

    while (val0 == HIGH || val1 == HIGH || val2 == HIGH || val3 == HIGH){
      // LED/button 0
      if (val0 == HIGH) {         // check if the input is HIGH (button released)
        digitalWrite(ledPin0, HIGH);  // turn LED ON
        userPattern.concat("0");
        while (val0 == HIGH){
          tone(4,NOTE0);      // play sound
          val0 = digitalRead(inPin0);  // read input value
        }
        noTone(4);
        digitalWrite(ledPin0, LOW);  // turn LED OFF
      }

      // LED/button 1
      if (val1 == HIGH) {         // check if the input is HIGH (button released)
        digitalWrite(ledPin1, HIGH);  // turn LED ON
        userPattern.concat("1");
        while (val1 == HIGH){
          tone(4,NOTE1);      // play sound
          val1 = digitalRead(inPin1);  // read input value
        }
        noTone(4);
        digitalWrite(ledPin1, LOW);  // turn LED OFF
      }

      // LED/button 2
      if (val2 == HIGH) {         // check if the input is HIGH (button released)
        digitalWrite(ledPin2, HIGH);  // turn LED ON
        userPattern.concat("2");
        while (val2 == HIGH){
          tone(4,NOTE2);      // play sound
          val2 = digitalRead(inPin2);  // read input value
        }
        noTone(4);
        digitalWrite(ledPin2, LOW);  // turn LED OFF
      }

      // LED/button 3
      if (val3 == HIGH) {         // check if the input is HIGH (button released)
        digitalWrite(ledPin3, HIGH);  // turn LED ON
        userPattern.concat("3");
        while (val3 == HIGH){
          tone(4,NOTE3);      // play sound
          val3 = digitalRead(inPin3);  // read input value
        }
        noTone(4);
        digitalWrite(ledPin3, LOW);  // turn LED OFF
      }
    }
  }
  Serial.println(userPattern);
  return userPattern;
}

String playPattern(int level){
  /*
   * Generate pattern (by creating string) for the machine to play (will light up those
   * LEDs as well as play the sounds associated with each LED). Almorithicly determines
   * the length of the pattern, as well as how much times is in-between each note (may
   * also add feature that determines how long each note is played for). While the length
   * is algmorithically determined, the order the notes place each level is random.
   */

  // TODO: ADD short pause after 2nd for loop bc need to make clear if playing same note
  delay(1000);

  int len = 3 + level;
  int pace = 500;        // time between each note being played; probably adjust this val
  int duration = 1000;
  String pattern = "";
  int randNumber = 0;
  int startTime = 0;
  int timeElapsed = 0;

  // generate pattern
  for (int i = 0; i < len; i++){
    randNumber = random(0,3);
    pattern.concat(String(randNumber));
  }

  Serial.println("pattern: " + pattern);

  // play pattern
  for (int i = 0; i < len; i++){

    if (pattern.charAt(i) == '0'){
      tone(4,NOTE0,duration);       // play sound
      startTime = millis();
      timeElapsed = millis();

      while (timeElapsed - startTime < 1000){
        digitalWrite(ledPin0, HIGH);  // turn LED ON
        timeElapsed = millis();
      }
      digitalWrite(ledPin0, LOW);   // turn LED OFF
    }
    if (pattern.charAt(i) == '1'){
      tone(4,NOTE1,duration);       // play sound
      startTime = millis();
      timeElapsed = millis();
      while (timeElapsed - startTime < 1000){
        digitalWrite(ledPin1, HIGH);  // turn LED ON
        timeElapsed = millis();
      }
      digitalWrite(ledPin1, LOW);   // turn LED OFF
    }
    if (pattern.charAt(i) == '2'){
      tone(4,NOTE2,duration);       // play sound
      startTime = millis();
      timeElapsed = millis();
      while (timeElapsed - startTime < 1000){
        digitalWrite(ledPin2, HIGH);  // turn LED ON
        timeElapsed = millis();
      }
      digitalWrite(ledPin2, LOW);   // turn LED OFF
    }
    if (pattern.charAt(i) == '3'){
      tone(4,NOTE3,duration);       // play sound
      startTime = millis();
      timeElapsed = millis();
      while (timeElapsed - startTime < 1000){
        digitalWrite(ledPin3, HIGH);  // turn LED ON
        timeElapsed = millis();
      }
      digitalWrite(ledPin3, LOW);   // turn LED OFF
    }
    delay(100);
  }
  return pattern;
}

int checkInput(String correctPattern, String userPattern, int level){
  /*
   * Function makes sure the buttons the user touched were in the correct order.
   * If they were, it moves them on to the next level, if not, it sends them to
   * level 0 (which quits the game.)
   */
  if (correctPattern == userPattern){
    Serial.println("it's correct!");
    // add outputting short happy sound/tune if the player entered it correct
    // A, B flat, B, C

    delay(500);
    tone(4,NOTE0,500);
    delay(125);
    tone(4,NOTE_AS6,500);
    delay(125);
    tone(4,NOTE1,500);
    delay(125);
    tone(4,NOTE2,500);
    delay(500);
    
    // add wait (so the player can catch their breath before the next level
    level += 1;
    return level;
  }
  // add sad sound/tune
  tone(4,392,500);
  delay(500);
  tone(4,196,500);
  delay(500);
  tone(4,98,500);
  delay(500);
  tone(4,49,500);
  delay(500);

  return 0;
}
