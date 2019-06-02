
6502 emulator EhBASIC on ESP32.

(Derived from EhBASIC)

<pre>
tools:

fork
Arduino 6502 emulator + BASIC interpreter
http://forum.arduino.cc/index.php?topic=193216.0

assembly tools:
- Arduino IDE 1.8.8
- Arduino core for the ESP32 1.0.2
- Arduino ESP32 filesystem uploader
https://github.com/me-no-dev/arduino-esp32fs-plugin

library Arduino IDE titanium bicycle for button. v14.1
https://github.com/Klapautsiy/titanium-bicycle-for-button/releases/tag/BUTTON-v14.1

- 6502 EhBASIC V2.22
https://github.com/Klapautsiy/6502_EhBASIC_V2.22/tree/master/patched

- Macro Assembler, Simulator, and Debugger 6502 ver. 1.2.11
http://www.exifpro.com/utils.html

save RAM.65b

- Bin2C.exe
https://www.segger.com/free-utilities/bin2c/

convert RAM.65b to RAM.h

- ESP32_6502_EhBASIC_LCD1602_pinmap.txt
button HARD_RESET(EN    ) - reboots ESP32
button WARM_RESET(GPIO0 ) - reboots EhBASIC 2.22
button SAVE_RAM  (GPIO4 ) - save the contents of the RAM to the SPIFFS ESP32
button READ_RAM  (GPIO12) - read the contents of the RAM from SPIFFS ESP32
button INPUT_LIST(GPIO13) - input from LIST.txt
buttons to GND

POKE $FF10,0
POKE $FF10,1
blink LED board

POKE $FF00,0
POKE $FF00,1
print LCD1602

</pre>

![](https://raw.githubusercontent.com/Klapautsiy/6502_EhBASIC_ESP32_Arduino/master/6502_EhBASIC_ESP32.gif)

