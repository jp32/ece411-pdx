/* ECE 411 Practicum Project - Jian Meng 
   =========================
   Automatic Watering system
   =========================
   November 18 2018
*/

// Initialize the variables
int soilpin = A5; // Declare a pin for the soil moisture sensor
int Soilpower = 4; // Declare the power pin of the sensor
int Valvepower = 12;
int count = 0;
int M_UpperBound = 500;  // Upper bound of the moisture level
int M_LowerBound = 250;  // Lower bound of the moisture level
int sensorValue;         // The variable of the moisture value

// Moisture Reading Function
int readMoisture()
{
  digitalWrite(Soilpower, HIGH);  // Turn on the transistor
  delay(100); // Wait 10 milliseconds
  int val = analogRead(soilpin);  // Read the moisture value
  digitalWrite(Soilpower, LOW); // Turn off the transistor
  return val;  // Return the moisture value
}

// Valve control function
int valveControl()
{
  digitalWrite(Valvepower, HIGH);
  for(count=0;count<30;count++)
  {
    delay(1000);
    if (sensorValue >= M_UpperBound){
      digitalWrite(Valvepower, LOW); // During the watering, if the water level is higher than the upper bound, then turn of the valve
      }
  }
}


void setup() {
  // Initial Setup 
  pinMode(Soilpower, OUTPUT);  // Set the power pin of the sensor as the output
  pinMode(Valvepower, OUTPUT); // Set the power pin of the valve as the output
  digitalWrite(Valvepower, LOW); // Set to LOW so no power is flowing through the valve
  digitalWrite(Soilpower, LOW); // Set to LOW so no power is flowing through the sensor
  
}


void loop() {
  // The loop will keep check the moisture level of the soil
  
  sensorValue = readMoisture(); // Read the moisture level

  if (sensorValue <= M_LowerBound){
    // If the moisture value lower than the lower bound, turn on the valve for a minute
    valveControl(); 
    digitalWrite(Valvepower, LOW); // Turn off the valve.
    } 
}
