#include <Servo.h>
#include <LiquidCrystal.h>

int fanPin = 9;
int trigPin = 3;
int echoPin = 4;

long duration;
int distance;

Servo myServo;
int servoAngle = 90;
int direction = 1;

LiquidCrystal lcd(12,11,5,6,7,8);

void setup()
{
  Serial.begin(9600);

  pinMode(fanPin, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myServo.attach(10);

  lcd.begin(16,2);
  lcd.print("Smart Fan");
  delay(2000);
  lcd.clear();
}

void loop()
{
  // Thermistor Reading
  int temperature = analogRead(A0);

  // Ultrasonic Sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  // Serial Monitor
  Serial.print("Temp Sensor: ");
  Serial.print(temperature);
  Serial.print("  Distance: ");
  Serial.println(distance);

  // LCD First Row
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print(" D:");
  lcd.print(distance);
  lcd.print("   ");

  // Fan ON condition
  if (temperature > 535 && distance > 2 && distance < 20)
  {
    analogWrite(fanPin, 255);

    lcd.setCursor(0, 1);
    lcd.print("Cooling ON    ");

    // Servo Oscillation
    myServo.write(servoAngle);

    servoAngle += direction;

    if (servoAngle >= 150)
    {
      direction = -1;
    }

    if (servoAngle <= 30)
    {
      direction = 1;
    }

    delay(15);
  }
  else
  {
    digitalWrite(fanPin, LOW);

    myServo.write(90);

    lcd.setCursor(0, 1);
    lcd.print("Standby       ");

    delay(100);
  }
}