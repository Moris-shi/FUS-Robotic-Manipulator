#include "Wire.h"       
#include "I2Cdev.h"     
#include "MPU6050.h"    
#include <Wire.h>
#include <VL53L0X.h>
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

VL53L0X sensor;
int fsrPin = 0;     // the FSR and 10K pulldown are connected to a0
int fsrReading;     // the analog reading from the FSR resistor divider
int fsrVoltage;     // the analog reading converted to voltage
unsigned long fsrResistance;  // The voltage converted to resistance, can be very big so make "long"
unsigned long fsrConductance; 
long fsrForce;       // Finally, the resistance converted to force

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;
struct MyData {
  int X;
  int Y;
  int Z;
};

MyData data;

void setup()
{
  pinMode(12,INPUT_PULLUP);
  digitalWrite(12,HIGH);
  Serial.begin(9600);
  Wire.begin();
  lcd.begin(16, 2);
  sensor.init();
  sensor.setTimeout(500);

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
  //pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  fsrReading = analogRead(fsrPin);  
  // analog voltage reading ranges from about 0 to 1023 which maps to 0V to 5V (= 5000mV)
  fsrVoltage = map(fsrReading, 0, 1023, 0, 5000);
 
  if (fsrVoltage == 0) {
    Serial.println("No pressure");  
  } else {
    // The voltage = Vcc * R / (R + FSR) where R = 10K and Vcc = 5V
    // so FSR = ((Vcc - V) * R) / V        yay math!
    fsrResistance = 5000 - fsrVoltage;     // fsrVoltage is in millivolts so 5V = 5000mV
    fsrResistance *= 10000;                // 10K resistor
    fsrResistance /= fsrVoltage;
 
    fsrConductance = 1000000;           // we measure in micromhos so 
    fsrConductance /= fsrResistance;
 
    // Use the two FSR guide graphs to approximate the force
    if (fsrConductance <= 1000) {
      fsrForce = fsrConductance / 80;
      Serial.print("Force in Newtons: ");
      Serial.println(fsrForce);      
    } else {
      fsrForce = fsrConductance - 1000;
      fsrForce /= 30;
      Serial.print("Force in Newtons: ");
      Serial.println(fsrForce);            
    }
  }
  Serial.println("--------------------");
  delay(1000);
  int distance =sensor.readRangeContinuousMillimeters();
  //int distance =sensor.startContinuous(100);
  
  distance = distance-64;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print("mm");
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  Serial.println();
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  data.X = map(ax, -17000, 17000, 0, 255 )-140; // X axis data
  data.Y = map(ay, -17000, 17000, 0, 255)-2; 
  data.Z = map(az, -17000, 17000, 0, 255);  // Y axis data
  Serial.print("X-Tilt = ");
  Serial.print(data.X);
  Serial.print("  ");
  Serial.print("Y-Tilt = ");
  Serial.print(data.Y);
  Serial.print("  ");
  Serial.print("  ");
  Serial.println();
  lcd.setCursor(0, 0);
  lcd.print("xTilt ");
  lcd.print(data.X);
  lcd.setCursor(11, 0);
  lcd.print(distance);
  lcd.print("mm");
  lcd.setCursor(0, 1);
  lcd.print("yTilt ");
  lcd.print(data.Y);
  lcd.setCursor(11, 1);
  lcd.print(fsrForce);
  lcd.print("N");

}
