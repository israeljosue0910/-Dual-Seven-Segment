// www.TinkerHobby.com
// Original author: Natalia Fargasch Norman 
// Dual seven-segment LED Display adapted to fit KPD-3261B
// Common Anode digit 1 pin 10
// Common Anode digit 2 pin 5
// Modifications made by: Israel J. Lopez Toledo

//       CA1 B  C  E  D
//        |  |  |  |  |      -> pins and segments they control
//   ---------    ---------
//   |   A   |    |   A   |
//  F|       |B  F|       |B
//   |---G---|    |---G---|
//  E|       |C  E|       |C
//   |   D   |    |   D   |
//   ---------    ---------
//        |  |  |  |  |      -> pins and segments they control
//        G  DP A  F CA2         

// Segments that make each number when lit:
// 0 => -FEDCBA
// 1 => ----BC-
// 2 => G-ED-BA
// 3 => G--DCBA
// 4 => GF--CB-
// 5 => GF-DC-A
// 6 => GFEDC-A
// 7 => ----CBA
// 8 => GFEDCBA
// 9 => GF-DCBA

// Arduino digital pins used to light up
// corresponding segments on the LED display
#define A 7
#define B 5
#define C 4
#define D 2
#define E 3
#define F_SEG 6
#define G 8

// Pins driving common anodes
#define CA1 13
#define CA2 12

// Pins for A B C D E F G, in sequence
const int segs[7] = { A, B, C, D, E, F_SEG, G };

// Segments that make each number, sends a 0(low) to the segment that will be turned on to display the numbers
const byte numbers[10] = { 0b1000000, 0b1111001, 0b0100100, 0b0110000, 0b0011001, 0b0010010,
0b0000010, 0b1111000, 0b0000000, 0b0010000 };  

void setup() {
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F_SEG, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(CA1, OUTPUT);
  pinMode(CA2, OUTPUT);
}

void loop() {
  for (int digit1=0; digit1 < 10; digit1++) {
    for (int digit2=0; digit2 < 10; digit2++) {
      unsigned long startTime = millis();
      for (unsigned long elapsed=0; elapsed < 1000; elapsed = millis() - startTime) { //changes numbers every second (1000ms)
        lightDigit1(numbers[digit1]);
        delay(5);
        lightDigit2(numbers[digit2]);
        delay(5);
      }
    }
  }
}

void lightDigit1(byte number) { // turns on left side (CA1) and turns off rightside (CA2)
  digitalWrite(CA1, LOW); 
  digitalWrite(CA2, HIGH);
  lightSegments(number);
}

void lightDigit2(byte number) { // turns off left side (CA1) and turns on rightside (CA2)
  digitalWrite(CA1, HIGH);
  digitalWrite(CA2, LOW);
  lightSegments(number);
}

void lightSegments(byte number) { //writes each bit of the numbers in the digital pins
  for (int i = 0; i < 7; i++) {
    int bit = bitRead(number, i);
    digitalWrite(segs[i], bit);
  }
}
