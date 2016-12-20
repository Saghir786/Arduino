int gPin=12;
int fPin=11;
int ePin=10;
int dPin=9;
int cPin=8;
//int dpPin=6;
int bPin=7;
int aPin=6;
int readPin = 1;
int readValue = 0;
int intervalDelay = 3000;

int num_array[10][7] = {  { 0,0,0,0,0,0,1 },    // 0 { 1,1,1,1,1,1,0 }
                          { 1,0,0,1,1,1,1 },    // 1 { 0,1,1,0,0,0,0 }
                          { 0,0,1,0,0,1,0 },    // 2 { 1,1,0,1,1,0,1 }
                          { 0,0,0,0,1,1,0 },    // 3 { 1,1,1,1,0,0,1 }
                          { 1,0,0,1,1,0,0 },    // 4 { 0,1,1,0,0,1,1 }
                          { 0,1,0,0,1,0,0 },    // 5 { 1,0,1,1,0,1,1 }
                          { 0,1,0,0,0,0,0 },    // 6 { 1,0,1,1,1,1,1 }
                          { 0,0,0,1,1,1,1 },    // 7 { 1,1,1,0,0,0,0 },
                          { 0,0,0,0,0,0,0 },    // 8 { 1,1,1,1,1,1,1 }
                          { 0,0,0,0,1,0,0 }};   // 9 { 1,1,1,0,0,1,1 }

int level_array[5] { -1,-1,-1,-1,-1 };
void Num_Write(int);
void addReadingToArray(int currentReading);
int getAverageValue();

void setup(){
  pinMode(gPin,OUTPUT);
  pinMode(fPin,OUTPUT);
  pinMode(ePin,OUTPUT);
  pinMode(dPin,OUTPUT);
  pinMode(cPin,OUTPUT);
  //pinMode(dpPin,OUTPUT);
  pinMode(bPin,OUTPUT);
  pinMode(aPin,OUTPUT);
  //Start off with everything off
  for (int i=6; i < 13; i++) {
    digitalWrite(i, 1);
  }
  Serial.begin(9600); 
  Serial.println("--- Start Serial Monitor SEND_RCVE ---");

}

void loop(){

  // read the value from the sensor:
  readValue = analogRead(readPin);
  Serial.println(readValue);
  addReadingToArray(readValue);

  int avgValue=getAverageValue();
  //int avgValue=readValue;

/*
  if (avgValue<49){
    Num_Write(1);
  } else if (avgValue>50 && avgValue<99){
    Num_Write(2);
  } else if (avgValue>100 && avgValue<149){
    Num_Write(3);
  } else if (avgValue>150 && avgValue<199){
    Num_Write(4);
  } else if (avgValue>200  & avgValue<249){
    Num_Write(5);
  } else if (avgValue>250 && avgValue<299){
    Num_Write(6);
  } else if (avgValue>300 && avgValue<349){
    Num_Write(7);
  } else if (avgValue>350 && avgValue<399){
    Num_Write(8);
  } else if (avgValue>400 && avgValue<449){
    Num_Write(9);
  } else if (avgValue>500){
    Num_Write(10);
  }
*/
  if (avgValue<99){
    Num_Write(1);
  } else if (avgValue>100 && avgValue<199){
    Num_Write(2);
  } else if (avgValue>200 && avgValue<299){
    Num_Write(3);
  } else if (avgValue>300 && avgValue<399){
    Num_Write(4);
  } else if (avgValue>400  & avgValue<499){
    Num_Write(5);
  } else if (avgValue>500 && avgValue<599){
    Num_Write(6);
  } else if (avgValue>600 && avgValue<699){
    Num_Write(7);
  } else if (avgValue>700 && avgValue<799){
    Num_Write(8);
  } else if (avgValue>800 && avgValue<899){
    Num_Write(9);
  } else if (avgValue>900){
    Num_Write(10);
  }

    delay(intervalDelay);


  //counter loop
  /*
  for (int counter = 10; counter > 0; --counter) 
  {
   delay(1000);
   Num_Write(counter-1); 
  }
  
  //Num_Write(0);
  //delay(3000);
  exit(0);
  */
}

// this functions writes values to the sev seg pins  
void Num_Write(int number) 
{
  int pin= 6;
  for (int j=0; j < 7; j++) {
   digitalWrite(pin, num_array[number][j]);
   pin++;
  }
}


void addReadingToArray(int currentReading){
  for (int j=1; j < 6; j++) {
    level_array[j-1]=level_array[j];
  }
  level_array[4]=currentReading;
}

int getAverageValue(){
  int valueCount=0;
  int sumOfValues=0;
  for (int j=0; j < 5; j++) {
    if (level_array[j] != -1) {
      valueCount++;
      sumOfValues=sumOfValues+level_array[j];
      //Serial.print(level_array[j]+",");
    }
  }
  //Serial.println();
  
  return sumOfValues/valueCount;
}
