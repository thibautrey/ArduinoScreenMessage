# ArduinoScreenMessage
Display and format a message on an LCD screen for arduino. Automatically scrolls the message on the screen.

This library will help to you to set up a simple messaging display service for an Arduino using an LCD screen. You can also set up multiple screens and display different messages. The library will automatically format the text and display it corretly on the screen. It will also take care of scrolling through the message in case the screen is not big enough to display the entire message. 


**SETUP and PREPARATION**

This library implies that you wire your LCD screen to the default SPI pins of your arduino. For more information on how to wire your LCD screen please refer to the official arduino LiquidCrystal page [Visit Arduino!](http://playground.arduino.cc/Main/LiquidCrystal)

Import the following libraries in your project : 
```
#include <SPI.h>
#include <LCDManager.h>
```

**INITIALISE**

####Initialise an LCD screen with the following constructor :#### 
```
LCDManager lcdManager(LCD_NB_LINES, LCD_NB_COLS, /* Pin number for SS */);
lcdManager.setBacklightPin(10); // TO SET BEFORE SETTING THE BACKLIGHT STATUS
lcdManager.backlight(LOW); // HIGH OR LOW DEPENDING IF YOU WANT TO TURN ON OR OFF THE BACKLIGHT
```
You can create as many LCDManager instances as you want as long as you specify a different SS pin for each of them. If you decide to display the same message on multiple screens just specify the same SS pin instead. 

####In order to be able to scroll through a long message the library requires that you call a method in your loop function :####
```
lcdManager.refreshDisplay();
```
####You need to call this method for each of your LCDManager instances.#### 
```
void loop(){
lcdManager1.refreshDisplay();
lcdManager2.refreshDisplay();
}
```

**HOW TO USE**

####Display a message on the screen :####
```
lcdManager.message("My message");
```

The library will take care of formatting the text no matter what the size of the string is. 

####Clear a line of the screen :####
```
lcdManager.clearLine(0);
```

clearLine will clear one line of the screen starting from 0 where 0 equal to the first line of the screen. 



** EXAMPLE SKETCH **
```
#include <SPI.h>
#include <LCDManager.h>

LCDManager lcdManager(2, 16, 7);

void setup(){
    lcdManager.clear();
    lcdManager.message("My very very very very long which requires more than a page to display message");
    lcdManager.setBacklightPin(10);
    lcdManager.backlight(LOW);
}

void loop(){
    lcdManager.refreshDisplay();
}
```