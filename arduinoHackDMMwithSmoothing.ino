const int numReadings = 50;

int maxCur = -999;
int minCur = 999;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
int diff = 0;
int v1 = A0;
int v2 = A1;

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
}

void loop() {
 // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(v2) - analogRead(v1);
  // add the reading to the total:
  total = total + readings[readIndex];

  if(readIndex == 49){
    minCur = 999;
    maxCur = -999;
    for(int i = 0; i<50; i++){
      if(readings[i]<minCur){
       //replace min if current reading is lower
          minCur = readings[i];
          //Serial.println(readings[i]);
       }
       if(readings[i]>maxCur){
       //replace max if current reading is higher
          maxCur = readings[i];
        }
    }
    //Serial.println(maxCur-minCur);
  }
  
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  Serial.println(average);
  
  Serial.println(maxCur-minCur);
  Serial.print("max:");
  Serial.println(maxCur);
  Serial.print("min:");
  Serial.println(minCur);
  
  
  delay(50);        // delay in between reads for stability
}
