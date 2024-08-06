#define PinBlue D5
#define PinGreen D6
#define PinRed D7

#define Btn_R D4

const int MAX_SIZE=10 ; 

int valFromServer;
unsigned long pressStartTime = 0; 
unsigned long LastPress = 0; 
int pressDuration = 0; 
bool isButtonPressed = false;     
bool isLEDOn = false;             


unsigned long pressRecords[MAX_SIZE] = {0}; 
bool isRecordNew[MAX_SIZE] = {false}; 
int recordIndex = 0; 




void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}


void ColorOrange() {
  analogWrite(PinRed, 255);
  analogWrite(PinGreen, 165);
  analogWrite(PinBlue, 0);
}

void ColorTurkiz() {
  analogWrite(PinRed, 0);
  analogWrite(PinGreen, 255);
  analogWrite(PinBlue, 255);
}

void TurnOffLED() {
  analogWrite(PinRed, 0);
  analogWrite(PinGreen, 0);
  analogWrite(PinBlue, 0);
}


void recordPress(unsigned long duration, bool isNewRecord) {
  pressRecords[recordIndex] = duration;
  isRecordNew[recordIndex] = isNewRecord;
  recordIndex = (recordIndex + 1) % MAX_SIZE;
}