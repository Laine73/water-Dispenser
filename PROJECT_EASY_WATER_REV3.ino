#include <U8glib.h>

// Define OLED display
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);

 #define outputA 6
 #define outputB 7
 #define pinSW 5
 #define relayPin 15

 int counter = 0; 
 int aState;
 int aLastState; 
 int pinLED = 16; 
 String other_message = "Ounces to dispense";

 void setup() { 
   pinMode(pinLED, OUTPUT);
   pinMode (outputA,INPUT_PULLUP);
   pinMode (outputB,INPUT_PULLUP);
   pinMode (pinSW, INPUT_PULLUP);
   pinMode (relayPin, OUTPUT);
   
   // Reads the initial state of the outputA
   aLastState = digitalRead(outputA);  
   digitalWrite(pinLED, LOW); 

    //WELCOME MESSAGE
    String welcome_message = "Welcome";
    int firstCursor = (128-welcome_message.length()*10)/2;
    u8g.firstPage();
    do {
      // Print the counter value on the display
      u8g.setFont(u8g_font_10x20);
      u8g.drawStr(firstCursor, 40, String(welcome_message).c_str());
    } while (u8g.nextPage());

    delay(2000);

    u8g.firstPage();
 } 

 void loop() { 
   aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
  if (aState != aLastState && aState == 1) {     
     // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
    if (digitalRead(outputB) != aState) { 
       counter ++;
     } else {
       counter --;
     }

    // Clear the display
    u8g.firstPage();
    do {
      // Print the counter value on the display
      u8g.setFont(u8g_font_profont15);
      u8g.drawStr(0, 20, String(other_message).c_str());

      u8g.setFont(u8g_font_profont22);
      u8g.drawStr(60, 50, String(counter).c_str());
    } while (u8g.nextPage());     
  } 
   aLastState = aState; // Updates the previous state of the outputA with the current state
  if (counter <= 0) {
    counter = 0;
  }
  if (digitalRead(pinSW) == LOW) {
      digitalWrite(pinLED, HIGH);
      digitalWrite(relayPin, HIGH);
      delay(counter*1000*1.5);
      digitalWrite(pinLED, LOW);
      digitalWrite(relayPin, LOW);
  }
   delay(1);
 
 
 }