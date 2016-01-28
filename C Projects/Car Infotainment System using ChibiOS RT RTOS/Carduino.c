/*
* Module : Carduino v1.0 - Car Infotainment System using ChibiOS/RT RTOS
*
* Author : Krishnaswamy Kannan
*
* Copyright (c) 2016, Krishnaswamy Kannan
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*   * Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in the
*     documentation and/or other materials provided with the distribution.
*   * Neither the name of Redis nor the names of its contributors may be used
*     to endorse or promote products derived from this software without
*     specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*/
//-----------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------- Headers -------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
#include <ChibiOS_AVR.h> // ChibiOS/RT APIs
#include <Keypad.h> // 4X4 Keypad APIs
#include <dht.h> // DHT11 Humidity & Temperature Sensor APIs
#include <pitches.h> // Notes for Welcome Tone Melody (Frequencies)

//-------------------------------------------------------------------------------------------------------------------
//------------------ GPIO Pin Assignments ------------------
//-------------------------------------------------------------------------------------------------------------------
#define dht_apin A0 // DHT11 Data pin (Pin No.2)
const uint8_t GREEN_LED_PIN = 11; // Green LED to indicate that an object is near the car
const uint8_t RED_LED_PIN = 13; // Red LED to indicate that an object is very close to the car
const uint8_t BUZZER_PIN = 12; // Piezoelectric Buzzer used for multiple purposes
int authentication_flag = 0; // Authentication Flag to prevent theft of Car
int wrong_pass_count = 0; // Buzzer will continuously beep if an incorrect password is entered for > 3 times 
//-------------------------------------------------------------------------------------------------------------------
//-------------------------- Keypad initializations --------------------------
//-------------------------------------------------------------------------------------------------------------------
const byte numRows= 4; // number of rows on the keypad
const byte numCols= 4; // number of columns on the keypad
char keymap[numRows][numCols]= // Keymap defines the key pressed according to the row and columns
{
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};
//-------- Connections to Arduino GPIO --------
byte rowPins[numRows] = {9,8,7,6}; // Rows 0, 1, 2 & 3 
byte colPins[numCols]= {5}; // Columns 0 
//-------- Initialize an instance of the Keypad class --------
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols); 
//-------------------------------------------------------------------------------------------------------------------
//-------------------------- DHT11 initializations --------------------------
//-------------------------------------------------------------------------------------------------------------------
dht DHT;
//-------------------------------------------------------------------------------------------------------------------
//-------------------------- Buzzer Melody initializations --------------------------
//-------------------------------------------------------------------------------------------------------------------
// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
//-------------------------------------------------------------------------------------------------------------------
//--------------------------Ultrasound sensor HC Sr-04 initializations --------------------------
//-------------------------------------------------------------------------------------------------------------------
const int trigPin = 3;
const int echoPin = 4;
long duration, distance_cm;
long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
//-------------------------------------------------------------------------------------------------------------------
//-------------------------- RTOS APIs --------------------------
//-------------------------------------------------------------------------------------------------------------------
//----------------- Thread 1 for Obstacle sensing and Alert -----------------
//-------------------------------------------------------------------------------------------------------------------
static WORKING_AREA(waThread1, 64);
static msg_t Thread1(void *arg) {  
	while(1){	  
	  delay(100);
	  digitalWrite(trigPin, LOW);
	  delayMicroseconds(2);
	  digitalWrite(trigPin, HIGH);
	  delayMicroseconds(10);
	  digitalWrite(trigPin, LOW);
	  duration = pulseIn(echoPin, HIGH);
	  distance_cm = microsecondsToCentimeters(duration);
	  
	  if((distance_cm < 25) && (distance_cm>10))
	  {
		 Serial.println("Object Nearing!!!!");
		 digitalWrite(GREEN_LED_PIN, HIGH);
	  }
	  else if (distance_cm<=10)
	  {
		Serial.println("Warning! Object very close...");
		digitalWrite(GREEN_LED_PIN, LOW);
		 digitalWrite(RED_LED_PIN, HIGH);
		 tone(BUZZER_PIN,440);
		 delay(400);
		 noTone(BUZZER_PIN);
	  }
	  else{
		  digitalWrite(RED_LED_PIN, LOW);
		 digitalWrite(GREEN_LED_PIN, LOW);  
	  }
		chThdSleepMilliseconds(20); // Sleep for 20 milliseconds
	  }
	  return 0;
	}
//-------------------------------------------------------------------------------------------------------------------
//----------------- Thread 2 for providing Humidity and Temperature inside the Car -----------------
//-------------------------------------------------------------------------------------------------------------------
static WORKING_AREA(waThread2, 64);
static msg_t Thread2(void *arg) {
  
  while (1) {
	char keypressed = myKeypad.getKey();
	if(keypressed == '*')
	{
	delay(1000);
	DHT.read11(dht_apin); 
	Serial.print("Humidity = ");  
	Serial.print(DHT.humidity);
	Serial.print("%  ");
	Serial.print("  Temperature = ");
	Serial.print(DHT.temperature); 
	Serial.println("C  ");   
   }  
  return 0;  
}
//-------------------------------------------------------------------------------------------------------------------
//-------------------------- Arduino Setup Function --------------------------
//-------------------------------------------------------------------------------------------------------------------
void setup() {
	Serial.begin(9600);
	pinMode(RED_LED_PIN, OUTPUT);
	pinMode(GREEN_LED_PIN, OUTPUT);
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
//-----------------------------------------------------------------------------
//------------------- User Authentication -------------------
//-----------------------------------------------------------------------------	
	Serial.print("Enter the password : ");
	String pass ="";
	int key_count = 0;
	while(1)
	{
	char keypressed = myKeypad.getKey();
	if (keypressed != NO_KEY)
	{
	key_count++;
	pass=pass + keypressed;
	Serial.print(keypressed);
	}
	if(pass == "117") // Set the authentication_flag only if password matches
	{
	authentication_flag = 1;
	Serial.println("");
	Serial.println("Authenticated");
	Serial.println("Welcome to Carduino!");
	for (int thisNote = 0; thisNote < 8; thisNote++) // Play Welcome Tone
	{
		int noteDuration = 1000 / noteDurations[thisNote];
		tone(BUZZER_PIN, melody[thisNote], noteDuration);
		int pauseBetweenNotes = noteDuration * 1.30;
		delay(pauseBetweenNotes);
		noTone(BUZZER_PIN);
	}
	break;
	}
	else if(key_count == 3)
	{
	wrong_pass_count++;
	Serial.println("");
	Serial.println("Wrong password. One more try!!!");
	tone(BUZZER_PIN,440);
	delay(600);
	noTone(BUZZER_PIN);
	key_count = 0;
	pass = "";
	}
	if (wrong_pass_count > 2) // if password doesn't match for > 3 attempts, beep indefinitely
	{
	while(1) // Continuously beep if password entered is wrong for > 3 attempts
	{
	tone(BUZZER_PIN,2093);
	delay(200);
	noTone(BUZZER_PIN);
	}
	}

	}
	delay(1000);
	
	chBegin(chSetup); // RTOS Thread Registration with the Scheduler
	while(1) {
	}
	}
	//------------------------------------------------------------------------------
	void chSetup()
	{
		// Thread 1 with Higher priority starts 
		chThdCreateStatic(waThread1, sizeof(waThread1),
		NORMALPRIO + 2, Thread1, NULL);
		// Thread 2 with Lower priority starts 
		chThdCreateStatic(waThread2, sizeof(waThread2),
		NORMALPRIO + 1, Thread2, NULL);
}
//------------------------------------------------------------------------------
void loop() {
  // not used
}
