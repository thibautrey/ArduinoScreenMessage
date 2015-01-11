#ifndef LCDManager_h
#define LCDManager_h

#include "Arduino.h"
#include <LiquidCrystalSPI.h>

class LCDManager{
	public :
		LCDManager(int line, int cols, int pin);
		LiquidCrystalSPI screen();
		void clearLine(int line);
		void backlight(bool status);
		void setBacklightPin(int pin);
		void message(String message);
		void refreshDisplay();
		
	private :
		void displayMessage();
		
		String messageBuffer;
		LiquidCrystalSPI theScreen;
		int lines;
		int cols;
		int currentTextScrollPosition;
		int currentTextChar;
		bool hasDisplayFirstLoop;
		int pinBacklight;
		long lastTimer;
        int timeBetweenRefresh;
};

#endif