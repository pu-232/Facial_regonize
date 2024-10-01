//WITH BACKSLASH 
#include "KT403A_Player.h"

#ifdef _AVR_
  #include <SoftwareSerial.h>
  SoftwareSerial SSerial(2, 3); // RX, TX
  #define COMSerial SSerial
  #define ShowSerial Serial

  KT403A<SoftwareSerial> Mp3Player;
#endif

#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
  #define COMSerial Serial1
  #define ShowSerial SerialUSB

  KT403A<Uart> Mp3Player;
#endif

#ifdef ARDUINO_ARCH_STM32F4
  #define COMSerial Serial
  #define ShowSerial SerialUSB

  KT403A<HardwareSerial> Mp3Player;
#endif

int x;

void setup() {
  ShowSerial.begin(9600);
  COMSerial.begin(9600);
  while (!ShowSerial);
  while (!COMSerial);
  Mp3Player.init(COMSerial);
  
  // Set volume to maximum (assuming 30 is the maximum value)
  Mp3Player.volume(30);
  Serial.println("Volume set to maximum.");
  
  printMenu();
  Serial.begin(115200);
  Serial.setTimeout(1);
}

// void  loop() {
//   while (!Serial.available());
//   x = Serial.readString().toInt();
//   Serial.print(x + 1);
// }

void loop() {
    if (Serial.available()) {
        char chr = Serial.read(); // Read single character input

        if (chr == '\\') { // Check if the first character is a backslash
            while (!Serial.available()); // Wait for the next character
            chr = Serial.read(); // Read the next character after the backslash
            
            if (chr >= '1' && chr <= '9') { // Check if input is between '1' and '9'
                int trackNumber = chr - '0'; // Convert character to number
                Mp3Player.playSongIndex(trackNumber); // Play the corresponding track
                Serial.print("Playing track ");
                Serial.println(trackNumber);
            } else {
                Serial.println("Invalid input. Please enter a number between 1 and 9 after the backslash.");
            }
        } else {
            Serial.println("Invalid input format. Please use \\ followed by a number (1-9).");
        }
    }
    delay(200);
}

void printMenu() {
  Serial.println("Grove - Serial MP3 Demo");
  Serial.println("Input");
 //     "Input a command in the format \\ followed by a number (1-9) to play the corresponding track.\r\n"
  //    "Other keys for print menu\r\n");
  delay(100);
}