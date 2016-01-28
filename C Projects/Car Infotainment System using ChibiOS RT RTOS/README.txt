/**************************************************************************************************
  * Carduino v1.0 is a simple car infotainment system implemented using Arduino Uno and
    ChibiOS/RT RTOS. 
  
  * The system provides extra security to the car as it requires the user
    to enter a password to start the car in addition to the traditional key. If not, the car 
    beeps continuously alerting the user that the car is being theft.
  
  * The infotainment system provides the user with temperature and humidity details inside
    the car.
    
  * The system also alerts the user about any object in close proximity to the car. 
    This can be useful while parking the vehicle and also to avoid collisions with other vehicles.
    
  * The entire system is based on the ChibiOS/RT RTOS. Two tasks namely Thread1 and Thread2 are 
    registered with the Scheduler. Thread1 is used for object detection using the HC SR-04 
    Ultrasound sensor. When the object is nearing the car, a Green LED will switch on and when the 
    object is very close to the car, a Red LED will switch on and a piezoelectric buzzer will beep.
    Thread2 is used for obtaining humidity and temperature values from the DHT11 Humidity & 
    Temperature sensor. The values from these sensors are printed on the Serial Monitor.
    
/***************************************************************************************************
