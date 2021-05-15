int ledPIN = 11;
int ledStayPIN = 12;
int motionPIN = 8; // PIR sensor pin
int motionStatus = 0;
int speakerPIN = 4;

int Do = 261;
int Re = 294;
int Mi = 329;
int Fa = 349;
int So = 392;
int La = 440;
int Si = 493;
int Do2 = 523;
int Re2 = 587;
int Mi2 = 659;
int Fa2 = 698;
int So2 = 784;
int La2 = 880;
int Si2 = 988;
int Do3 = 1047;
int Re3 = 1175;
int Mi3 = 1319;
int Fa3 = 1397;
int So3 = 1568;
int mario[13] = {Mi2, Mi2, 0, Mi2, 0, Do2, Mi2, 0, So2, 0, 0, 0, So};




void setup() {
  pinMode(ledPIN, OUTPUT);
  pinMode(ledStayPIN, OUTPUT);
  pinMode(motionPIN, INPUT);
  Serial.begin(9600);
  pinMode(speakerPIN, OUTPUT);
}


void loop() {
    motionStatus = digitalRead(motionPIN);
    if (motionStatus == HIGH) { // When motion is detected
        digitalWrite(ledPIN, HIGH); // turn LED ON
        digitalWrite(ledStayPIN, LOW);

        for (int i = 0; i < 13; i++) {
          tone(speakerPIN, mario[i], 80);
          delay(100);
        }
        delay(3000);
        Serial.println("Motion detected.");
    }
    else {
        digitalWrite(ledPIN, LOW);
        digitalWrite(ledStayPIN, HIGH);
        Serial.println("All clear.");
    }
}
