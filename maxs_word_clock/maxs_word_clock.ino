/* Max's Word Clock
 * v1.0
 * 30 November 2015
 * Written by Max Maltzman and Kristof Aldenderfer
 * 
 * Word clock grid layout:
 *     ONETWOFOURSIX
 *     FIVESEVENNINE
 *     EIGHTTHREETEN
 *     ELEVENTWELVEO
 *     MTWENTHIRFORA
 *     FIFTYONETHREE
 *     TWOSEVENEIGHT
 *     XFOURFIVESIXM
 *     NINETENELEVEN
 *     TEENTWELVEAPM
 * 
 * TODO:
 *     - add pretty animations
 */

//========================================================================================
// begin globals

#include <avr/power.h>
#include <Adafruit_NeoPixel.h>
#include <TimeLib.h>

#define LEDSPIN          20
#define NUMPIXELS       130
#define TIME_HEADER     "T"   // Header tag for serial time sync message

boolean verboseMode = true;
byte brightness = 255;
unsigned long timeCheck = 0;
const String hours =                               "ONETWOFOURSIXFIVESEVENNINEEIGHTTHREETENELEVENTWELVE";
const String minutes = "OMTWENTHIRFORAFIFTYONETHREETWOSEVENEIGHTXFOURFIVESIXMNINETENELEVENTEENTWELVEAPM";

Adafruit_NeoPixel leds = Adafruit_NeoPixel(NUMPIXELS, LEDSPIN, NEO_GRB + NEO_KHZ800);

// end globals
//========================================================================================
// begin setup and loop

void setup() {
	// set the Time library to use Teensy 3.0+'s RTC to keep time
	setSyncProvider(getTeensy3Time);
  
	Serial.begin(115200);
	while (!Serial);  // Wait for Arduino Serial Monitor to open
	delay(100);
	if (timeStatus()!= timeSet) {
		Serial.println("Unable to sync with the RTC");
	} else {
		Serial.println("RTC has set the system time");
	}

	//Neopixel setup
	leds.begin();
	leds.show();
}

void loop() {
	// used to set the time
	if (Serial.available()) {
		time_t t = processSyncMessage();
		if (t != 0) {
			Teensy3Clock.set(t); // set the RTC
			setTime(t);
		}
  }
	if (micros() - timeCheck > 1000000 || timeCheck > micros() ) updateTime();
}

// end setup and loop
//========================================================================================
// begin parsing section

void updateTime() {
	//clearStrip();
	updateHour();
	updateMinute();
	//leds.show();
	if (verboseMode) digitalClockDisplay();
	timeCheck = micros();
}

boolean isItAM(byte hr) {
	return (hr <= 11);
}

void updateHour() {
	byte hr = hour();
	String type = "antepost";
	if (isItAM(hr))     turnOn(type, "AM");
	else                turnOn(type, "PM");
	type = "hours";
	if (hr > 12) hr-=12;
	else if (hr == 0) hr = 12;
	if (hr == 1)       turnOn(type, "ONE");
	else if (hr == 2)  turnOn(type, "TWO");
	else if (hr == 3)  turnOn(type, "THREE");
	else if (hr == 4)  turnOn(type, "FOUR");
	else if (hr == 5)  turnOn(type, "FIVE");
	else if (hr == 6)  turnOn(type, "SIX");
	else if (hr == 7)  turnOn(type, "SEVEN");
	else if (hr == 8)  turnOn(type, "EIGHT");
	else if (hr == 9)  turnOn(type, "NINE");
	else if (hr == 10) turnOn(type, "TEN");
	else if (hr == 11) turnOn(type, "ELEVEN");
	else if (hr == 12) turnOn(type, "TWELVE");	
}

void updateMinute() {
	byte mn = minute();
	String type = "minutes";
	// everything but ten through nineteen can be handled fairly easily
	if (mn < 10 || mn > 19) {
    if (mn == 0) ;
		else if (mn < 10)      turnOn(type, "O");
		else {
			if (mn<30)           turnOn(type, "TWEN");
			else if (mn<40)      turnOn(type, "THIR");
			else if (mn<50)      turnOn(type, "FOR");
			else if (mn<60)      turnOn(type, "FIF");
			turnOn(type, "TY");
		}
		byte remain = mn%10;
		if (remain == 0)       turnOn("maxm", "MAXM");
		else if (remain == 1)  turnOn(type, "ONE");
		else if (remain == 2)  turnOn(type, "TWO");
		else if (remain == 3)  turnOn(type, "THREE");
		else if (remain == 4)  turnOn(type, "FOUR");
		else if (remain == 5)  turnOn(type, "FIVE");
		else if (remain == 6)  turnOn(type, "SIX");
		else if (remain == 7)  turnOn(type, "SEVEN");
		else if (remain == 8)  turnOn(type, "EIGHT");
		else if (remain == 9)  turnOn(type, "NINE");
	}
	// ten through nineteen are a pain
	else {
		if (mn == 10)          turnOn(type, "TEN");
		else if (mn == 11)     turnOn(type, "ELEVEN");
		else if (mn == 12)     turnOn(type, "TWELVE");
		else {
			if (mn == 13)      turnOn(type, "THIR");
			else if (mn == 14) turnOn(type, "FOUR");
			else if (mn == 15) turnOn(type, "FIF");
			else if (mn == 16) turnOn(type, "SIX");
			else if (mn == 17) turnOn(type, "SEVEN");
			else if (mn == 18) turnOn(type, "EIGHT");
			else if (mn == 19) turnOn(type, "NINE");
			turnOn(type, "TEEN");
		}
	}
}

// end parsing section
//========================================================================================
// begin indexing section

// type can be "hour", "minute", "anteposte", or "maxm"
// antepost is a hack to get around the separation of the two strings, maxm is special characters
void turnOn(String type, String val) {
	String thisOne;
	int numIndex = 0;
	int indexOffset = 0;
	uint32_t c;
		if (verboseMode) {
//    Serial.print(type);
//    Serial.print(" ");
		Serial.print(val);
		Serial.print("\t");
//    if (type != "hours") numIndex-=indexOffset;
//    if(thisOne.substring(numIndex, numIndex+val.length()) == val) Serial.print("found it! index: ");
//    Serial.print(numIndex);
//    Serial.print(" ");
	}
	if (type == "antepost" || type == "maxm") turnOnSpecial(type, val);
	else {
		if (type == "hours") {
		thisOne = hours;
		c = leds.Color(brightness, 0, 0);
		}
		else {
			thisOne = minutes;
			indexOffset += hours.length();
			c = leds.Color(0, brightness, 0);
		}
		numIndex = thisOne.indexOf(val) + indexOffset;
		showNumber(numIndex, numIndex+val.length()-1, c);
	}
}

void turnOnSpecial(String type, String val) {
	int maxIndex = hours.length()+minutes.length()-1;
	uint32_t c = leds.Color(0, 0, brightness);
	if (type == "antepost") {
		if (val == "PM") showNumber(maxIndex-1, maxIndex, c);
		else {
			showNumber(maxIndex-2, maxIndex-2, c);
			showNumber(maxIndex, maxIndex, c);
		}
	}
	else {
		int indices[4] = { 13*4, 13*5-1, 13*8, 13*9-1 };
		showNumber(indices[0], indices[0], c);
		showNumber(indices[1], indices[1], c);
		showNumber(indices[2], indices[2], c);
		showNumber(indices[3], indices[3], c);
	}
}

// end indexing section
//========================================================================================
// begin neopixel section

void clearStrip() {
	for (int i = 0 ; i<leds.numPixels() ; i++) {
		leds.setPixelColor(i, leds.Color(0, 0, 0) );
	}
}

void showNumber(int m, int n, uint32_t c) {
	for (int i = m ; i<=n ; i++) {
		leds.setPixelColor(i, c);
	}
	if (verboseMode) {
			Serial.print("m: ");
			Serial.print(m);
			Serial.print("\tn: ");
			Serial.println(n);
	}
}

// end neopixel section
//========================================================================================
// begin clock-specific code

// digital clock display of the time
void digitalClockDisplay() {
	Serial.print(hour());
	printDigits(minute());
	printDigits(second());
	Serial.print(" ");
	Serial.print(day());
	Serial.print(" ");
	Serial.print(month());
	Serial.print(" ");
	Serial.print(year()); 
	Serial.println();
}

// Pulls time from the RTC
// note that this is in 24-hour time, so a conversion must be made
time_t getTeensy3Time() {
	return Teensy3Clock.get();
}

/*  code to process time sync messages from the serial port   */
unsigned long processSyncMessage() {
	unsigned long pctime = 0L;
	const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013 

	if(Serial.find(TIME_HEADER)) {
		pctime = Serial.parseInt();
		return pctime;
		if( pctime < DEFAULT_TIME) { // check the value is a valid time (greater than Jan 1 2013)
			pctime = 0L; // return 0 to indicate that the time is not valid
		}
	}
	return pctime;
}

void printDigits(int digits){
	// utility function for digital clock display: prints preceding colon and leading 0
	Serial.print(":");
	if(digits < 10)
		Serial.print('0');
	Serial.print(digits);
}

// end clock-specific code
//========================================================================================
