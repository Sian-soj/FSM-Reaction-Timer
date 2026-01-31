// ================== PINS ==================
const int ledPin = 12;
const int SBpin  = 11;   // Session Button
const int RBpin  = 10;   // Reaction Button

// ================== STATES ==================
enum State { IDLE, WAIT, ACTIVE, RESULT };
State currentState = IDLE;

// ================== BUTTON STATES ==================
bool SB_current, SB_prev = HIGH;
bool RB_current, RB_prev = HIGH;

// ================== TIMING ==================
unsigned long waitStartTime = 0;
unsigned long waitDuration  = 0;
unsigned long reactStartTime = 0;
unsigned long reactionTime  = 0;

// ================== FLAGS ==================
bool falseStart = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(SBpin, INPUT_PULLUP);
  pinMode(RBpin, INPUT_PULLUP);

  Serial.begin(9600);
  randomSeed(analogRead(A0)); // entropy
  Serial.println("System Ready - IDLE");
}

void loop() {
  // -------- READ BUTTONS --------
  SB_current = digitalRead(SBpin);
  RB_current = digitalRead(RBpin);

  bool SB_justPressed = (SB_prev == HIGH && SB_current == LOW);
  bool RB_justPressed = (RB_prev == HIGH && RB_current == LOW);

  SB_prev = SB_current;
  RB_prev = RB_current;

  // -------- FSM --------
  switch (currentState) {

    case IDLE:
      digitalWrite(ledPin, LOW);
      if (SB_justPressed) {
        waitDuration = random(2000, 5000);
        waitStartTime = millis();
        falseStart = false;
        currentState = WAIT;
        Serial.println("WAIT");
      }
      break;

    case WAIT:
      digitalWrite(ledPin, HIGH);

      if (RB_justPressed) {
        falseStart = true;
        currentState = RESULT;
        Serial.println("FALSE START");
      }
      else if (millis() - waitStartTime >= waitDuration) {
        reactStartTime = millis();
        currentState = ACTIVE;
        Serial.println("ACTIVE");
      }
      break;

    case ACTIVE:
      digitalWrite(ledPin, LOW);

      if (RB_justPressed) {
        reactionTime = millis() - reactStartTime;
        currentState = RESULT;
        Serial.print("Reaction Time: ");
        Serial.print(reactionTime);
        Serial.println(" ms");
      }
      break;

    case RESULT:
      // simple blink pattern
      static unsigned long blinkTimer = 0;
      static bool ledState = false;

      if (millis() - blinkTimer > 300) {
        blinkTimer = millis();
        ledState = !ledState;
        digitalWrite(ledPin, ledState);
      }

      if (SB_justPressed) {
        currentState = IDLE;
        Serial.println("IDLE");
      }
      break;
  }
}
