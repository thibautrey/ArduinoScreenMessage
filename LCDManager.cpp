#include "LCDManager.h"
#include "Arduino.h"
#include <LiquidCrystalSPI.h>

LCDManager::LCDManager(int line, int col, int pin) : theScreen(pin){
	theScreen.begin(line, col);
	lines = line;
	cols = col;
	lastTimer = millis();
    timeBetweenRefresh = 1500;
}

LiquidCrystalSPI LCDManager::screen(){
	return theScreen;
}

// Clear one line of the LCD screen
void LCDManager::clearLine(int line){
  if(line<lines){
    theScreen.setCursor(0, line); // Set the cursor of the LCD screen to the line required
    
    // For each columns of the screen display a space (i.e nothing)
    for(int i = 0; i < cols; i++){
      theScreen.print(" ");
    }
  }
}

// Turn on the backlight of the LCD screen
void LCDManager::backlight(bool status){
	digitalWrite(pinBacklight, status);
}

void LCDManager::setBacklightPin(int pin){
	pinBacklight = pin;
}

void LCDManager::refreshDisplay(){
    if(millis()-lastTimer>timeBetweenRefresh){
		displayMessage();
		lastTimer = millis();
	}
}

void LCDManager::message(String message){
	currentTextScrollPosition = 0;
	currentTextChar = 0;
	messageBuffer = "";
	messageBuffer = message;
	hasDisplayFirstLoop = false;
	displayMessage();
}

void LCDManager::displayMessage(){
	int messageLength = messageBuffer.length();
	
	// Avoid refreshing the screen if the text can fit in the screen
	if(!hasDisplayFirstLoop || (messageLength>cols*lines)){
		hasDisplayFirstLoop = true;
		int nbLines = 0;
		float decimal = 0;
		int ignore = 0;
		
		theScreen.clear();
		nbLines = messageLength/cols;
		decimal = (float)messageLength/cols - nbLines;
		
		if(decimal > 0){
			nbLines++;
		}
		
		for(int i = 0; i < lines; i++){
			for(int j = 0; j < cols; j++){
				if(currentTextChar >= messageLength){
					j = cols;
					i = lines;
					currentTextChar = 0;
					Serial.println(messageLength);
				}else{
					// A line never starts with a space it is useless.
					if((j == 0) && (messageBuffer.charAt(currentTextChar) == ' ')){
						currentTextChar+=1;
						j = -1;
					}else{
						bool wordWillFit = false;
						int wordEndPosition = 0;
						// Calculate when is the next space
						for(int k = 1; k <= cols-j; k++){
							if((messageBuffer.charAt(currentTextChar+k) == ' ') || currentTextChar+k == messageLength){
								wordWillFit = true;
								wordEndPosition = currentTextChar+k;
							}
						}
						
						// Display text by word instead to display by letter
						if(wordWillFit){
							theScreen.setCursor(j, i);
							
							// Display the word
							for(int k = currentTextChar; k < wordEndPosition; k++){
								theScreen.print(messageBuffer[currentTextChar]);
								currentTextChar+=1;
								j++;	
							}
							
							// If we run over the limit get back to normal
							if(currentTextChar >= messageLength){
								currentTextChar = 0;
								j = cols;
								i = lines;
								Serial.println(messageLength);
							}
							
						}else{
							// Go to next line
							j = cols;
							
							// If we run over the limit get back to normal
							if(currentTextChar >= messageLength){
								currentTextChar = 0;
								j = cols;
								i = lines;
							}
						}
					}
				}
			}
		}
	}
}