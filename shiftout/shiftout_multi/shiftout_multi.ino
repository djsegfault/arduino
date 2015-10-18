//**************************************************************//
//  Name    : shiftOutCode, Hello World                                
//  Author  : Carlyn Maw,Tom Igoe, David A. Mellis 
//  Date    : 25 Oct, 2006    
//  Modified: 23 Mar 2010                                 
//  Version : 2.0                                             
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255                           
//****************************************************************

//Pin connected to ST_CP of 74HC595
//int latchPin = 8;
int latchPin = 4;
//Pin connected to SH_CP of 74HC595
//int clockPin = 12;
int clockPin = 2;
//Pin connected to DS of 74HC595
//int dataPin = 11;
int dataPin = 3;

// Set current display pattern
int pattern='1';


void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  Serial.begin(9600);
  Serial.print("Starting\n");
}

void loop() {
  Serial.print("Top of loop\n");
  // Are we changing mode?
  if (Serial.available() > 0) {
    // read the incoming byte:
    pattern = Serial.read();
    
    // say what you got:
    Serial.print("I received: ");
    Serial.println(pattern, DEC);
  } 

  switch (pattern) {
    case '1':
      chaseOneMode();
      break;
    case '2':
      chaseTwoMode();
      break;
    case '3':
      crossOneMode();
      break;
    case '4':
      crossTwoMode();
      break;
    case '5':
      binaryCountOneMode();
      break;
  }
}


void binaryCountOneMode() {
  // count from 0 to 255 and display the number 
  // on the LEDs
  for (int numberToDisplay = 0; numberToDisplay < 255; numberToDisplay++) {
    Serial.print(numberToDisplay);
    3Serial.print("\n");
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);  
    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:
    delay(500);
  }
}

void chaseOneMode() {
  Serial.print("----------- Starting loop \n");
  long data = 1;
  
  for (int n = 0; n < 16; n++)
  {
    Serial.print(data);
    Serial.print("\n");
    
    sendTwoBits(data);
    
    data = data * 2;
    
  }
  Serial.print("----------- Ending loop \n");
}

void chaseTwoMode() {
  int seq[14] = {1,2,4,8,16,32,64,128,64,32,16,8,4,2  };       //The byte sequence

  for (int n = 0; n < 14; n++)
  {
    sendOneBit(seq[n]);
    delay(75);
  }
}

void crossOneMode() {
  // 128 +  1  = 129
  //  64 +  2  = 66
  //  32 +  4  = 36
  //  16 +  8  = 24
  
  int seq[14] = {129, 66, 36, 24, 36, 66, 129 };       //The byte sequence

  for (int n = 0; n < 6; n++)
  {
    digitalWrite(latchPin, LOW);             //Pull latch LOW to start sending data
    shiftOut(dataPin, clockPin, MSBFIRST, seq[n]);          //Send the data
    digitalWrite(latchPin, HIGH);            //Pull latch HIGH to stop sending data
    delay(75);
  }
}

void crossTwoMode() {
  Serial.print("----------- Starting loop \n");
  long rightData = 1;
  long leftData = 32768;
  
  for (int n = 0; n < 8; n++)
  {
    long data = rightData + leftData;
    Serial.print("[");
    Serial.print(leftData);
    Serial.print("][");
    Serial.print(rightData);
    Serial.print("][");
    Serial.print(data);
    Serial.print("]\n");
    
    sendTwoBits(data);
    
    rightData = rightData * 2;
    leftData = leftData / 2;
    
  }

  for (int n = 0; n < 8; n++)
  {
    long data = rightData + leftData;
    Serial.print("[");
    Serial.print(leftData);
    Serial.print("][");
    Serial.print(rightData);
    Serial.print("][");
    Serial.print(data);
    Serial.print("]\n");
    
    sendTwoBits(data);
    
    rightData = rightData / 2;
    leftData = leftData * 2;
    
  }
  Serial.print("----------- Ending loop \n");
}





//////////////////// Utilities 

void sendOneBit(int data) {
    digitalWrite(latchPin, LOW);             //Pull latch LOW to start sending data
    shiftOut(dataPin, clockPin, MSBFIRST, data);          //Send the data
    digitalWrite(latchPin, HIGH);            //Pull latch HIGH to stop sending data
}

void sendTwoBits(long data) {
    digitalWrite(latchPin, LOW);             //Pull latch LOW to start sending data
    // shift out highbyte
    shiftOut(dataPin, clockPin, MSBFIRST, (data >> 8));  
    // shift out lowbyte
    shiftOut(dataPin, clockPin, MSBFIRST, data);
    digitalWrite(latchPin, HIGH);            //Pull latch HIGH to stop sending data
    delay(75);
}


