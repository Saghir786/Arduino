int gPin=12;
int fPin=11;
int ePin=10;
int dPin=9;
int cPin=8;
//int dpPin=6;
int bPin=7;
int aPin=6;

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

void Num_Write(int);

void setup(){
  pinMode(gPin,OUTPUT);
  pinMode(fPin,OUTPUT);
  pinMode(ePin,OUTPUT);
  pinMode(dPin,OUTPUT);
  pinMode(cPin,OUTPUT);
  //pinMode(dpPin,OUTPUT);
  pinMode(bPin,OUTPUT);
  pinMode(aPin,OUTPUT);
}

void loop(){
  //Start off with everything off
  for (int i=6; i < 13; i++) {
    digitalWrite(i, 1);
  }
  
  //counter loop
  
  for (int counter = 10; counter > 0; --counter) 
  {
   delay(1000);
   Num_Write(counter-1); 
  }
  
  //Num_Write(0);
  //delay(3000);
  exit(0);
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

