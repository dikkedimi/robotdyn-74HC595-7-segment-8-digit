// https://forum.arduino.cc/index.php?topic=518797.0
// ST_CP = SCK
// SH_CP = RCK
// SDI   = DIO
// Common anode
#define DS 12
#define STCP 15
#define SHCP 14
#define SPEED 500
boolean numbersDef[10][8] = 
{
  {1,1,1,1,1,1,0}, //zero
  {0,1,1,0,0,0,0}, //one
  {1,1,0,1,1,0,1}, //two
  {1,1,1,1,0,0,1}, //three
  {0,1,1,0,0,1,1}, //four
  {1,0,1,1,0,1,1}, //five
  {1,0,1,1,1,1,1}, //six
  {1,1,1,0,0,0,0}, //seven
  {1,1,1,1,1,1,1}, //eight
  {1,1,1,1,0,1,1}  //nine
};

boolean digitsTable[8][8] =
{
  {0,0,0,0,1,0,0,0}, // first digit
  {0,0,0,0,0,1,0,0}, // second
  {0,0,0,0,0,0,1,0}, // third
  {0,0,0,0,0,0,0,1},  // 8th 
  {1,0,0,0,0,0,0,0}, // forth
  {0,1,0,0,0,0,0,0}, // fifth
  {0,0,1,0,0,0,0,0},  // sixth  
  {0,0,0,1,0,0,0,0} // 7th

   
};

void setup() {
  pinMode(DS, OUTPUT);
  pinMode(STCP, OUTPUT);
  pinMode(SHCP, OUTPUT);
  digitalWrite(DS, LOW);
  digitalWrite(STCP, LOW);
  digitalWrite(SHCP, LOW);
}

boolean display_buffer[32];
void prepareDisplayBuffer(int number, int digit_order, boolean showDot)
{
  for(int index=7; index>=0; index--)
  {
    display_buffer[index] = digitsTable[digit_order-1][index];
  }
  for(int index=14; index>=8; index--)
  {
    display_buffer[index] = !numbersDef[number-1][index]; //because logic is sanity, right?
  }
  if(showDot == true)
    display_buffer[15] = 0;
  else
    display_buffer[15] = 1;
}

void writeDigit(int number, int order, bool showDot = false)
{
  prepareDisplayBuffer(number, order, showDot);
  digitalWrite(SHCP, LOW);
  for(int i=15; i>=0; i--)
  {
      digitalWrite(STCP, LOW);
      digitalWrite(DS, display_buffer[i]); //output LOW - enable segments, HIGH - disable segments
      digitalWrite(STCP, HIGH);
   }
  digitalWrite(SHCP, HIGH);
}

void loop() {
  writeDigit(0, 1,true); // write 0 on first digit
  writeDigit(1, 2,false); // write 1 on second digit
  writeDigit(2, 3,false); // write 7 on third digit
  writeDigit(3, 4, false);
  writeDigit(4, 5,true);
  writeDigit(5, 6, false);
  writeDigit(6, 7,false);
  writeDigit(7, 8,false);
//  writeDigit(8, 8);
//  writeDigit(9, 8);
//  writeDigit(1, 9);
//  writeDigit(0, 10);
//  writeDigit(1, 11);
//  writeDigit(1, 12);
//  writeDigit(1, 13);
//  writeDigit(2, 14);
//  writeDigit(1, 15);
}
