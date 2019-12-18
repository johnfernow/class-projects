#include <Arduino.h>

// button noises
#define NOTE0 880   // NOTE_A5
#define NOTE1 988   // NOTE_B5
#define NOTE2 1047  // NOTE_C6
#define NOTE3 1175  // NOTE_D6

// note used for victory noise
#define NOTE_AS6 932

// configure pairs of input pins (for a pushbutton) and corresponding LED pins
int inPin0 = 12;
int ledPin0 = 13;

int inPin1 = 9;
int ledPin1 = 10;

int inPin2 = 6;
int ledPin2 = 5;

int inPin3 = 2;
int ledPin3 = 3;

int speakerPin4 = 4; // choose the pin for the speaker

// set variables for reading the status of each pin
int val0 = 0;
int val1 = 0;
int val2 = 0;
int val3 = 0;

void setup() {
  Serial.begin(9600);
  // declare the LED pins as output adn the pushbutton pins as input
  pinMode(ledPin0, OUTPUT);
  pinMode(inPin0, INPUT);

  pinMode(ledPin1, OUTPUT);
  pinMode(inPin1, INPUT);

  pinMode(ledPin2, OUTPUT);
  pinMode(inPin2, INPUT);

  pinMode(ledPin3, OUTPUT);
  pinMode(inPin3, INPUT);

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
   * or starts them over from the beginning.
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
   */
  String userPattern;
  // while userPattern < length of pattern
  while (userPattern.length() < (3 + level)){
    int currentLen = userPattern.length();

    // read input button values
    val0 = digitalRead(inPin0);
    val1 = digitalRead(inPin1);
    val2 = digitalRead(inPin2);
    val3 = digitalRead(inPin3);

    while (val0 == HIGH || val1 == HIGH || val2 == HIGH || val3 == HIGH){
      // TODO: refactor
      // LED/button 0
      if (val0 == HIGH) {         // check if the input is HIGH (button released)
        digitalWrite(ledPin0, HIGH);  // turn LED ON
        userPattern.concat("0");
        while (val0 == HIGH){
          tone(4,NOTE0);              // play sound
          val0 = digitalRead(inPin0); // read input value
        }
        noTone(4);
        digitalWrite(ledPin0, LOW);   // turn LED OFF
      }

      // LED/button 1
      if (val1 == HIGH) {         // check if the input is HIGH (button released)
        digitalWrite(ledPin1, HIGH);  // turn LED ON
        userPattern.concat("1");
        while (val1 == HIGH){
          tone(4,NOTE1);              // play sound
          val1 = digitalRead(inPin1); // read input value
        }
        noTone(4);
        digitalWrite(ledPin1, LOW);  // turn LED OFF
      }

      // LED/button 2
      if (val2 == HIGH) {         // check if the input is HIGH (button released)
        digitalWrite(ledPin2, HIGH);  // turn LED ON
        userPattern.concat("2");
        while (val2 == HIGH){
          tone(4,NOTE2);              // play sound
          val2 = digitalRead(inPin2); // read input value
        }
        noTone(4);
        digitalWrite(ledPin2, LOW);   // turn LED OFF
      }

      // LED/button 3
      if (val3 == HIGH) {         // check if the input is HIGH (button released)
        digitalWrite(ledPin3, HIGH);  // turn LED ON
        userPattern.concat("3");
        while (val3 == HIGH){
          tone(4,NOTE3);              // play sound
          val3 = digitalRead(inPin3); // read input value
        }
        noTone(4);
        digitalWrite(ledPin3, LOW);   // turn LED OFF
      }
    }
  }
  Serial.println(userPattern);
  return userPattern;
}

String playPattern(int level){
  /*
   * Generate pattern (by creating string) for the machine to play (will light
   * up those LEDs as well as play the sounds associated with each LED).
   * Almorithicly determines the length of the pattern, as well as how much time
   * is in-between each note. While the length is algmorithically determined,
   * the order the notes play each level is randomly generated.
   */
  delay(1000);

  int len = 3 + level;
  int pace = 500;        // time between each note being played
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
    // TODO: refactor
    if (pattern.charAt(i) == '0'){
      tone(4,NOTE0,duration);         // play sound
      startTime = millis();
      timeElapsed = millis();

      while (timeElapsed - startTime < 1000){
        digitalWrite(ledPin0, HIGH);  // turn LED ON
        timeElapsed = millis();
      }
      digitalWrite(ledPin0, LOW);     // turn LED OFF
    }
    if (pattern.charAt(i) == '1'){
      tone(4,NOTE1,duration);         // play sound
      startTime = millis();
      timeElapsed = millis();
      while (timeElapsed - startTime < 1000){
        digitalWrite(ledPin1, HIGH);  // turn LED ON
        timeElapsed = millis();
      }
      digitalWrite(ledPin1, LOW);     // turn LED OFF
    }
    if (pattern.charAt(i) == '2'){
      tone(4,NOTE2,duration);         // play sound
      startTime = millis();
      timeElapsed = millis();
      while (timeElapsed - startTime < 1000){
        digitalWrite(ledPin2, HIGH);  // turn LED ON
        timeElapsed = millis();
      }
      digitalWrite(ledPin2, LOW);     // turn LED OFF
    }
    if (pattern.charAt(i) == '3'){
      tone(4,NOTE3,duration);         // play sound
      startTime = millis();
      timeElapsed = millis();
      while (timeElapsed - startTime < 1000){
        digitalWrite(ledPin3, HIGH);  // turn LED ON
        timeElapsed = millis();
      }
      digitalWrite(ledPin3, LOW);     // turn LED OFF
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
    // output short happy sound/tune since the player entered it correctly
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

    level += 1;
    return level;
  }
  // sad sound/tune
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
