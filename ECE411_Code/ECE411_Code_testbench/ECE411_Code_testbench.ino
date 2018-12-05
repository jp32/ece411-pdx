/* ECE 411 Practicum Project - Jian Meng
   =========================
   Automatic Watering system
   =========================
   November 18 2018
*/

// Initialize the variables
int soilpin = A5; // Declare a pin for the soil moisture sensor
int Soilpower = 4; // Declare the power pin of the sensor
int Valvepower = 1;
int count = 0;
int M_UpperBound = 850;  // Upper bound of the moisture level
int M_LowerBound = 757;  // Lower bound of the moisture level
int sensorValue;         // The variable of the moisture value

void setup() {
  // Initial Setup
  Serial.begin(9600); // Serial port
  pinMode(Soilpower, OUTPUT);  // Set the power pin of the sensor as the output
  pinMode(Valvepower, OUTPUT); // Set the power pin of the valve as the output
  digitalWrite(Valvepower, LOW); // Set to LOW so no power is flowing through the valve
  digitalWrite(Soilpower, LOW); // Set to LOW so no power is flowing through the sensor

  while (!Serial);
  Serial.println("Enter Mode of Operation: \n1. run - start normal operating procedure \n2. test - enter test bench mode");
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

// Valve control function
int valveControl()
{
  digitalWrite(Valvepower, HIGH);
  Serial.println("Valve is on");
  for (count = 0; count < 10; count++)
  {
    // serial.print "Valve is on - 30 seconds - current time: print count - analg val(val)"
    delay(1000);
  }
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readString();

    if (cmd == "run\n") {
      // The loop will keep check the moisture level of the soil
      Serial.print("Wait for two seconds");
      delay(2000);
      // serial print "done waiting two seconsd - reading moisture"
      sensorValue = readMoisture(); // Read the moisture level
      if (sensorValue <= M_LowerBound) {
        Serial.print("Current moisture value = ");
        Serial.println(sensorValue);
        // If the moisture value lower than the lower bound, turn on the valve for 30 seconds
        valveControl();
        digitalWrite(Valvepower, LOW); // Turn off the valve.
      }
    }
    else if (cmd == "test\n") {
      Serial.println("* ENTERED DEBUG MODE *");
      Serial.println("* Choose debug function");
      Serial.println("* Press 1 for valve functions \n* Press 2 for sensor functions");
      Serial.println("* Waiting for user input...");
      String testcmd = Serial.readString();

      if(testcmd == "1\n"){
        Serial.println("** ENTERED VALVE MODE *");
        Serial.println("** Choose debug function");
        Serial.println("** Press 1 to open valve \n** Press 2 to close valve \n** Press 3 to open valve for 5-30 seconds (potentiometer)");
        String valvecmd = Serial.readString();

        if(valvecmd == "1\n"){
          Serial.println("*** Opening valve");
          digitalWrite(Valvepower, HIGH);
        }
        else if(valvecmd == "2\n"){
          Serial.println("*** Closing valve");
          digitalWrite(Valvepower, LOW);
        }
        else if(valvecmd == "3\n"){
          Serial.println("*** Opening valve for ");
          
        }

      }
      else if(testcmd == "2\n"){
        // TODO:
        
      }
    }
    else {
      return;
    }

  }
  else {

  }
}
