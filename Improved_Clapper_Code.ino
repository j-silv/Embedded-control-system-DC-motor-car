int reading;
bool clap1=false;
bool clap2=false;
unsigned long checkClap;
unsigned long currentTimer;
int clapShortInterval= 500;
int clapLongInterval = 1000;
int silenceShortInterval= 200;
int silenceLongInterval= 500;
int lowerLimit = 230;
int higherLimit = 660;

void setup() {
  
Serial.begin(115200);

pinMode(2,OUTPUT);
digitalWrite(2,LOW);

pinMode(LED_BUILTIN,OUTPUT);
digitalWrite(LED_BUILTIN,LOW);

}

void loop() {  

checkReading();
triggerRelay();

}
