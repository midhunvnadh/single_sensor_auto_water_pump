#define sensor 12 
#define relay 6
#define precision_tries 10
#define precision_delay 100
#define debug true

int i, tankFull, takes[precision_tries];

void setup() {
  Serial.begin(9600);
  pinMode (sensor, INPUT);
  pinMode (relay, OUTPUT);
  relay_switch(0);
}

int tankStatus(){
  for (i = 0; i < precision_tries; i++){
    takes[i] = digitalRead(sensor);
    if(i > 0 && takes[i-1] != takes[i]){
      return tankStatus();
    }
    delay(precision_delay);
  }
  return takes[0];
}

void relay_switch(int status){
    digitalWrite(relay, !status);
}

void loop() {
  tankFull = tankStatus();
  if(tankFull){
    #if debug
      Serial.println("Tank is full");
    #endif
    relay_switch(0);
  }
  else{
    #if debug
      Serial.println("Tank is low!");
    #endif
    relay_switch(1);
    #if debug
      Serial.println("Pump On!");
    #endif
    delay(60000); // Pump on for 60 seconds
    #if debug
      Serial.println("Pump Off!");
    #endif
    relay_switch(0);
  }
}
