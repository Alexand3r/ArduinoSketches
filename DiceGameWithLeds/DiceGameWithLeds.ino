int buttonPin = 7;
int button = 0;
int PINS[] = {10, 11, 12};
int pinCount = 3;
boolean runFlag = false;
const unsigned long DebounceTime = 20;

void setup() {
  for (int i = 0; i < pinCount; i++)
    pinMode(PINS[i], OUTPUT);
  pinMode(buttonPin, INPUT);
}

void handleButton(void)
{
  static boolean pressed = false;
  int currentState = digitalRead(buttonPin);

  if (!pressed && currentState == HIGH)
  {
    delay(DebounceTime);
    if (digitalRead(buttonPin) == HIGH)
    {
      runFlag = !runFlag;
      pressed = true;
    }
  }
  if (pressed && currentState == LOW)
  {
    delay(DebounceTime);
    if (digitalRead(buttonPin) == LOW)
    {
      pressed = false;
    }
  }
}
void lightUp (boolean reverse) {
  for (int i = 0; i < pinCount; i++)
  {
    if (reverse)
    {
      digitalWrite(PINS[i], HIGH);
    }
    else
    { int count = pinCount - i - 1;
      digitalWrite(PINS[count], HIGH);
    }
    delay(100);
  }
}
void lightDown(boolean reverse) {
  for (int i = 0; i < pinCount; i++)
  {
    if (reverse)
    {
      digitalWrite(PINS[i], LOW);
    }
    else
    {
      int count = pinCount - i - 1;
      digitalWrite(PINS[count], LOW);
    }
    delay(100);
  }
}
void gameAnimation() {
  for (int spin = 0; spin < 3; spin++)
  {
    if (spin % 2 == 0) {
      lightUp(true);
      lightDown(true);
      delay(100);
    }
    else {
      lightUp(false);
      lightDown(false);
      delay(100);
    }
  }
}
void gameStart() {
  gameAnimation();
  int randomPick = random(0, pinCount * 2 - 1) / 2;
  digitalWrite(PINS[randomPick], HIGH);
  delay(3000);
  lightDown(false);
}

void loop() {
  handleButton();
  if (!runFlag)
  {
    //do nothing
  }
  else {
    gameStart();
    runFlag = false;
  }
}
