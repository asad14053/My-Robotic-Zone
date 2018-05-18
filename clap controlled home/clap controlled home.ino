//Please first, open new code page (new sketch) from Arduino IDE
//Copy the following code and paste it into the new sketch
//Then save and verify

int sound_sensor= 4;
int relay= 5;
int clap= 0;
long detection_range_start = 0;
long detection_range = 0;
boolean status_lights = false;

const int motor1Pin = 3;    // H-bridge leg 1 (pin 2, 1A)
const int motor2Pin = 6;  // H-bridge leg 2 (pin 7, 2A)
 
void setup() {
  pinMode(sound_sensor, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);
 pinMode(12, OUTPUT);
  Serial.begin  (9600);
}
 
void loop() {
 
  int status_sensor = digitalRead(sound_sensor);
 
  if (status_sensor == 0)
  {
    if (clap == 0)
    {
      detection_range_start = detection_range = millis();
      clap++;
    }
    else if (clap > 0 && millis()-detection_range >= 50)
    {
      detection_range = millis();
      clap++;
    }
  }
 
  if (millis()-detection_range_start >= 400)
  {
    if (clap == 1)
    {
      if (!status_lights)
        {
          status_lights = true;
          digitalWrite(relay, HIGH);
          
          digitalWrite(motor1Pin, HIGH);   // set leg 1 of the H-bridge low
          digitalWrite(motor2Pin, LOW);
         digitalWrite(12, HIGH);
        }
        else if (status_lights)
        {
          status_lights = false;
          digitalWrite(relay, LOW);
           digitalWrite(motor1Pin, LOW);   // set leg 1 of the H-bridge low
          digitalWrite(motor2Pin, LOW);
         digitalWrite(12, HIGH);
        }
    }
    clap = 0;
  }
}

// end code