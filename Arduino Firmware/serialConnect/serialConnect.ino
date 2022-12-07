#define CH1 2
#define CH2 3
#define CH3 4
#define CH4 5
#define CH5 6
#define CH6 7
#define CH7 8
#define CH8 9

bool newData = false;
const byte numChars = 32;
char recvChar[numChars];
char tempChars[numChars];
const char sp[2] = ",";

int channel;
int state;

void setup() {
  Serial.begin(9600);
  pinMode(CH1, OUTPUT);
  pinMode(CH2, OUTPUT);
  pinMode(CH3, OUTPUT);
  pinMode(CH4, OUTPUT);
  pinMode(CH5, OUTPUT);
  pinMode(CH6, OUTPUT);
  pinMode(CH7, OUTPUT);
  pinMode(CH8, OUTPUT);

  digitalWrite(CH1, HIGH);
  digitalWrite(CH2, HIGH);
  digitalWrite(CH3, HIGH);
  digitalWrite(CH4, HIGH);
  digitalWrite(CH5, HIGH);
  digitalWrite(CH6, HIGH);
  digitalWrite(CH7, HIGH);
  digitalWrite(CH8, HIGH);
}

void loop() {
  recvWithMarks();

  if (newData == true) {
    strcpy(tempChars, recvChar);
    parseData();

    int ch;
    int st;

    switch (channel) {
      case 1: ch = CH1; break;
      case 2: ch = CH2; break;
      case 3: ch = CH3; break;
      case 4: ch = CH4; break;
      case 5: ch = CH5; break;
      case 6: ch = CH6; break;
      case 7: ch = CH7; break;
      case 8: ch = CH8; break;
    }

    switch (state) {
      case 0: st = LOW; break;
      case 1: st = HIGH; break;
    }


    digitalWrite(ch, st);

    newData = false;
  }
}

void recvWithMarks() {
  static bool recvProgress = false;
  static byte ndx = 0;
  char startMark = '<';
  char endMark = '>';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (recvProgress == true) {
      if (rc != endMark) {
        recvChar[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      } else {
        recvChar[ndx] = '\0';
        recvProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == startMark) {
      recvProgress = true;
    }
  }
}

void parseData() {
  char *strtokIndex;

  strtokIndex = strtok(recvChar, sp);
  channel = atoi(strtokIndex);
  strtokIndex = strtok(NULL, sp);
  state = atoi(strtokIndex);
}