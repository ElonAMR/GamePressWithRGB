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




void BtnAndLedRGB_setup() {
  pinMode(PinBlue, OUTPUT);
  pinMode(PinGreen, OUTPUT);
  pinMode(PinRed, OUTPUT);
  pinMode(Btn_R, INPUT_PULLUP);

  Serial.begin(9600); 
  TurnOffLED();
  wifiClient_Setup();

}

void BtnAndLedRGB_loop(){
  int buttonState = digitalRead(Btn_R);

  if (buttonState == LOW) {
      if (!isButtonPressed) {
          pressStartTime = millis(); 
          isButtonPressed = true;
      }
  } else {
      if (isButtonPressed) { 
          LastPress = millis() - pressStartTime; 
          isButtonPressed = false;

          valFromServer = GetData();

          Serial.print("Value from server: ");
          Serial.println(valFromServer);

          Serial.print("Press duration: ");
          Serial.print(LastPress); 
          Serial.println(" milliseconds");


          bool isNewRecord = (LastPress < valFromServer); 
          
          recordPress(LastPress, isNewRecord);  

          if (isNewRecord) { 
              ColorTurkiz(); 
              SetNewRecordToServer(LastPress); 
          } else {
              ColorOrange(); 
          }

          delay(100); 
      }
  }
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
