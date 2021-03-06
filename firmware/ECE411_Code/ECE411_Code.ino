/* ECE 411 Practicum Project - Jian Meng
   =========================
   Automatic Watering system
   =========================
   November 18 2018
*/

// Initialize the variables
int soilpin = A5; // Declare a pin for the soil moisture sensor
int UserSet = A4; // Declare a pin for the user to set water amount
int Soilpower = 4; // Declare the power pin of the sensor
int UserPower = 12; //Declare the power ping for user setting
int Valvepower = 1;
int count = 0;
int M_UpperBound = 857;  // Upper bound of the moisture level
int M_LowerBound = 750;  // Lower bound of the moisture level
int sensorValue;         // The variable of the moisture value
int UserValue;           // The variable of the user setting value


void setup() {
  // Initial Setup
  Serial.begin(9600); // Serial port
  pinMode(Soilpower, OUTPUT);  // Set the power pin of the sensor as the output
  pinMode(Valvepower, OUTPUT); // Set the power pin of the valve as the output
  digitalWrite(Valvepower, LOW); // Set to LOW so no power is flowing through the valve
  digitalWrite(Soilpower, LOW); // Set to LOW so no power is flowing through the sensor

}

// Moisture Reading Function
int readMoisture()
{
  digitalWrite(Soilpower, HIGH);  // Turn on the transistor
  delay(300); // Wait 10 milliseconds
  int val = analogRead(soilpin);  // Read the moisture value
  Serial.print("Moisture value = ");
  Serial.println(val);   // Print the value back to the serial port
  digitalWrite(Soilpower, LOW); // Turn off the transistor
  return val;  // Return the moisture value
}

int readUserSetting()
{
  digitalWrite(UserPower, HIGH);  // Turn on voltage divider
  delay(10); // Wait 10 milliseconds
  int val2 = ((pow(analogRead(UserSet), 3) / 13000) - 1000); // Read the user valve open time setting non-linear
  Serial.print("Valve open value = ");
  Serial.println(val2);   // Print the value back to the serial port
  digitalWrite(UserPower, LOW); // Turn off voltage divider
  return val2;  // Return the moisture value
}

// Valve control function
int valveControl()
{
  digitalWrite(Valvepower, HIGH);
  Serial.println("Valve is on, delaying...");
  delay(UserValue);
}

void loop() {
  // The loop will keep check the moisture level of the soil
  Serial.println("Wait for two seconds");
  delay(2000);
  // serial print "done waiting two seconsd - reading moisture"
  sensorValue = readMoisture(); // Read the moisture level
  UserValue   = readUserSetting(); //Read the user setting
  if (sensorValue <= M_LowerBound && (sensorValue > 600)) {
  Serial.print("Current moisture value = ");
    Serial.println(sensorValue);
    Serial.print("Current user value = ");
    Serial.println(UserValue);
    // If the moisture value lower than the lower bound, turn on the valve for 30 seconds
    valveControl();
    digitalWrite(Valvepower, LOW); // Turn off the valve.
  }
}
