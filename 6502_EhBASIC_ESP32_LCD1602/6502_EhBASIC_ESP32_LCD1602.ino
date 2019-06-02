

#include <LiquidCrystal.h>
// LiquidCrystal lcd(RS,  E, D4, D5, D6, D7)
   LiquidCrystal lcd(32, 33, 25, 26, 27, 14);


uint8_t LCD_VIDEO_RAM[16];


boolean blank_LCD_VIDEO_RAM() {
for (int i = 0; i < 16; i++) {if (LCD_VIDEO_RAM[i] != ' ') return (1);}
                                                           return (0);}

uint8_t lcd_x = 0;
// uint8_t LCD_y = 0;


#include "RAM.h"


void print_LCD1602(uint8_t value) {

// POKE $FF00,0
// POKE $FF00,1
if (RAM[0xFF00] == 1) {

/*

BS  \b  8 на один символ назад

Enter == 13, 10
CR  \r 13 в крайнее левое положение
LF  \n 10 на одну строку вниз

*/

if (value ==  7) {/*beep*/}

if (value ==  8 && lcd_x != 0) {

lcd_x -=1;
LCD_VIDEO_RAM[lcd_x] = ' ';
lcd.setCursor(lcd_x, 1);
lcd.print(' ');
lcd.setCursor(lcd_x, 1);

}

if (value == 13) {lcd_x = 0; lcd.setCursor(lcd_x, 1);}

if (value == 10 && blank_LCD_VIDEO_RAM() != 0) {

lcd.setCursor(0, 0);
for (int i = 0; i < 16; i++) {lcd.write(LCD_VIDEO_RAM[i]); LCD_VIDEO_RAM[i] = ' ';}

lcd.setCursor(0, 1);
for (int i = 0; i < 16; i++) {lcd.print(' ');}

}

if (value >= 32 && value <= 126 && lcd_x < 16) {

lcd.setCursor(lcd_x, 1);
lcd.write(value);

LCD_VIDEO_RAM[lcd_x] = value;

lcd_x += 1;

}

}

}


void serout(uint8_t value) {
Serial.write(value);

print_LCD1602(value);

}


#include "FS.h"
#include "SPIFFS.h"

File LIST;


uint8_t getkey() {
if (LIST == 0) {if (Serial.available()) {return (Serial.read());}}
else           {if (  LIST.available()) {return (  LIST.read());}
                else                    {          LIST.close();}}
                                         return (0);
}


#include "cpu.h"


void HARD_RESET() {}


void WARM_RESET() {
Serial.println();
Serial.print("WARM RESET");
reset6502();
}


void SAVE_RAM() {
SPIFFS.remove("/RAM.ram");
File RAMw = SPIFFS.open("/RAM.ram", FILE_WRITE);
if (RAMw) {
Serial.println();
Serial.print("SAVE RAM [");
reset6502();
for(int i= 0; i < RAM_SIZE; i++) {
RAMw.write(RAM[i]);
if (i % 1024 == 0) {Serial.print('~');}
}
RAMw.close();
Serial.print(']');
}
}


void READ_RAM() {
File RAMr = SPIFFS.open("/RAM.ram");
if (RAMr.size() >= RAM_SIZE) {
Serial.println();
Serial.print("READ RAM [");
for(int i= 0; i < RAM_SIZE; i++) {
RAM[i] = RAMr.read();
if (i % 1024 == 0) {Serial.print('~');}
}
RAMr.close();
Serial.print(']');
reset6502();
}
}


void INPUT_LIST() {
Serial.println();
Serial.print("INPUT LIST");
LIST = SPIFFS.open("/LIST.txt");
}


#include <Button.h>

Button button;


#define pin_WARM_RESET  0
#define pin_SAVE_RAM    4
#define pin_READ_RAM   12
#define pin_INPUT_LIST 13


void setup() {

button.NO(); // N.O. Normal Open
button.pullUp();
button.duration_bounce(100);

button.button(pin_WARM_RESET, pin_SAVE_RAM, pin_READ_RAM, pin_INPUT_LIST); // arduino pins connected to button

lcd.begin(16, 2);
// lcd.cursor();
lcd.clear();

// LED on the board
pinMode( 2, OUTPUT);
digitalWrite( 2, 1);

SPIFFS.begin(true);

Serial.begin(115200);

Serial.println();
Serial.print("HARD RESET");

reset6502();

// TEST
// lcd.setCursor(0, 0);
// lcd.print  ("TEST lcd");

for (int i = 0; i < 16; i++) {LCD_VIDEO_RAM[i] = ' ';}

digitalWrite( 2, 0); // погасить LED

}


void loop () {

button.read();
                                 // HARD_RESET();
if (button.event_click_Up(0) == 1) {WARM_RESET();}
if (button.event_click_Up(1) == 1) {SAVE_RAM();}
if (button.event_click_Up(2) == 1) {READ_RAM();}
if (button.event_click_Up(3) == 1) {INPUT_LIST();}

exec6502();

// POKE $FF10,0 // LED
// POKE $FF10,1 // LED
digitalWrite( 2, RAM[0xFF10]);

}



