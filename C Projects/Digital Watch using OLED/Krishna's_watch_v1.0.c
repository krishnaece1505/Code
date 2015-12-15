/*
* Module : Krishna's Watch v1.0 -----> Customized Digital Watch with Arduino Pro Mini and 0.96" I2C OLED display
*
* Author : Krishnaswamy Kannan
*
* Copyright (c) 2015, Krishnaswamy Kannan
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

// -------------- Headers --------------
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// -------------- Alter OLED display size in Adafruit_SSD1306.h --------------
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// -------------- Global Variables --------------
// ------- LDR variables --------------
int sensorPin = A0; // Input pin for ldr
int sensorValue = 0; // Stores the value coming from the sensor
// ------- Watch variables -------
int hour = 00;
int minute = 00;
int day = 1;
int month = 1;
int year = 2015;
// ------- Flag to shift from Time settings to Date settings -------
int setTime_done = 0;
// ------- Flag to shift from Date settings to Watch -------
int setDate_done = 0;
// ------- Count value that decides when to shift from Hour adjustment to Minute adjustment -------
int count_time = 0;
// ------- Count value that decides when to shift from Day adjustment to Month adjustment -------
int count_date = 0;

// -------------- Arduino Setup function to initialize display --------------
void setup()  
{   
  Serial.begin(9600);
  // ------- Set the I2C OLED device address -------
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  // ------- Welcome Text -------
  display.clearDisplay();
  display.setCursor(34,8);
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.println("Hi!");
  display.setCursor(15,50);
  display.setTextSize(1);
  display.print("(c) Krishnaswamy");
  display.display();
  delay(5000);
  // ------- Clear the display buffer -------
 /* display.clearDisplay();
  display.setCursor(19,0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("KRISHNA'S WATCH");
  display.display();*/
  // ------- Initialize the LED pin -------
  pinMode(6, OUTPUT);
}  
// -------------- Arduino Loop function that contains live code --------------
void loop() 
{ 
  // -------- Check if Time is set --------
  if (setTime_done == 0)
  {
    // -------- Call the function to set the time --------
    setTime();
  }
  else if (setDate_done == 0)
  {
  // -------- Call the function to set the date --------
    setDate(); 
  }
  else
  {
    // -------- Call the function to display the time --------
    displayTime(); 
  }
}
// -------------- Function that allows the user to set the time --------------
void setTime()
{
  display.clearDisplay();
  display.setCursor(5,0);
  display.setTextSize(1);
  display.println("Set time:");
  display.setCursor(5,9);
  display.println("  HOUR       MINUTE");
  display.setCursor(5,22);
  display.setTextSize(4);
  display.setTextColor(WHITE);
  if(hour < 10){
  display.print("0");
  }
  display.print(hour);
  display.print(":");
  if(minute < 10){
  display.print("0");
  }
  display.print(minute);
  display.display();
  // -------- Time adjustment based on LDR values --------
  if(setTime_done == 0)
  {
  // -------- If the LDR value decreases beyond 600, then the user's hand is in close proximity -------- 
  if (analogRead(sensorPin) < 600)
  {
    // -------- Hour adjustment --------
    if(count_time == 0)
    {
    if(hour < 23)
    {
    hour++;
    delay(400);
    }
    }
    // -------- Minute Adjustment --------
    else 
    {
    if(minute < 60)
    {
    minute++;
    delay(400);
    }
    }
  }
  // -------- Use a flashlight to shift from Time adjustment to Watch --------
  // -------- Flashing on the LDR increases the value beyond 1000 --------
  else if (analogRead(sensorPin) > 1000) 
  {
    count_time++;
    if(count_time == 2)
    {
    setTime_done = 1;
    }
    // -------- Glow the LED to indicate Time adjustment is complete --------
    digitalWrite(6, HIGH);
    delay(2000);
    digitalWrite(6, LOW); 
    }
    }
}
// -------------- Function that allows the user to set the date --------------
void setDate()
{
  display.clearDisplay();
  display.setCursor(5,0);
  display.setTextSize(1);
  display.println("Set date:");
  display.setCursor(5,9);
  display.println("   DAY       MONTH");
  display.setCursor(5,22);
  display.setTextSize(4);
  display.setTextColor(WHITE);
  if(day < 10){
  display.print("0");
  }
  display.print(day);
  display.print(":");
  if(month < 10){
  display.print("0");
  }
  display.print(month);
  display.display();
  // -------- Time adjustment based on LDR values --------
  if(setDate_done == 0)
  {
  // -------- If the LDR value decreases beyond 600, then the user's hand is in close proximity -------- 
  if (analogRead(sensorPin) < 600)
  {
    // -------- Hour adjustment --------
    if(count_date == 0)
    {
    if(day < 31)
    {
    day++;
    delay(400);
    }
    }
    // -------- Minute Adjustment --------
    else 
    {
    if(month < 12)
    {
    month++;
    delay(400);
    }
    }
  }
  // -------- Use a flashlight to shift from Time adjustment to Watch --------
  // -------- Flashing on the LDR increases the value beyond 1000 --------
  else if (analogRead(sensorPin) > 1000) 
  {
    count_date++;
    if(count_date == 2)
    {
    setDate_done = 1;
    }
    // -------- Glow the LED to indicate Time adjustment is complete --------
    digitalWrite(6, HIGH);
    delay(2000);
    digitalWrite(6, LOW); 
    }
    }
}
// -------------- Function that displays the Time --------------
void displayTime()
{
  if(hour == 23 && minute == 60)
  {
    hour = 0;
    minute = 0;
  if(day<32)
  {
    day++;
  }
  else
  {
    day = 1;
    if(month < 13)
    {
    month++;
    }
  }
  }
  else if(minute == 60 && hour != 23)
  {
    hour++;
    minute = 0;
  }
  display.clearDisplay();
  display.setCursor(19,0);
  display.setTextSize(1);
  display.println("KRISHNA'S WATCH");
  display.setCursor(5,16);
  display.setTextSize(4);
  display.setTextColor(WHITE);
  if (hour < 10)
  {
    display.print("0");
  }
  display.print(hour);
  display.print(":");
  if (minute < 10)
  {
  display.print("0");
  }
  display.print(minute);
  display.setCursor(34,52);
  display.setTextSize(1);
  if (day < 10)
  {
    display.print("0");
  }
  display.print(day);
  display.print(".");
  if (month < 10)
  {
  display.print("0");
  }
  display.print(month);
  display.print(".2015");
  display.display();
  // -------- Increment the minute after 60K milliseconds, i.e. 60 seconds --------
  delay(60000);
  minute++;
}