#include "Door.h"
#include "ScreenInterface.h"
#include "Interface.h"
#include "Repository.h"
#include "Ventilator.h"
#include "SerialInterface.h"
#include "Environment.h"
#include "LightInterface.h"
#include "RFID.h"

// DHT Setup
#include "DHT.h"
#define DHTPIN A1      // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11

// MFRC Setup
#define SS_PIN 53 //slave select pin
#define RST_PIN 6 // reset pin. we need to study the pin layout

#define DOOR_OPEN_TIME 5000 // milliseconds, must be greater than openning time: 20*90 ms
#define DHT_SENSOR_COOLDOWN 3000

// TODO Decide pin layout
#define SERVO_PIN A2
#define DC_MOTOR_SPEED_PIN 5
#define DC_MOTOR_DIR_A_PIN 3
#define DC_MOTOR_DIR_B_PIN 4
#define LIGHT_GREEN_PIN 9
#define LIGHT_YELLOW_PIN 8
#define LIGHT_RED_PIN 7

String validCardIDs[2] = {"E2A83F1B", "D570A53"};

// Auxiliary variables
static int entryCounter = 0;
static unsigned long currentTime;
static unsigned long lastRead = 0;
static String cardID;
static EnvironmentStatus environmentStatus;
static VentilatorSpeed ventilatorSpeed;
static LightColor lightColor;

// System objects
DHT tempHumSensor(DHTPIN, DHTTYPE);
RFID rfid(SS_PIN, RST_PIN);
Door door(SERVO_PIN);
// change true to false to use Serial interface instead of Screen
#if true
ScreenInterface interface(16, 2); // 16x2 Screen
#else
SerialInterface interface();
#endif
Repository repository;
Ventilator ventilator(DC_MOTOR_SPEED_PIN, DC_MOTOR_DIR_A_PIN, DC_MOTOR_DIR_B_PIN);
LightInterface lightInterface(LIGHT_GREEN_PIN, LIGHT_YELLOW_PIN, LIGHT_RED_PIN);

float temperature = 0.0, temperatureAux;
float humidity = 0.0, humidityAux;

bool validate(String element)
{
  for (size_t i = 0; i < 2; i++)
  {
    if (element == validCardIDs[i])
    {
      return true;
    }
  }
  return false;
}

void setup()
{
  Serial.begin(9600);

  // System objects' setup
  interface.setup();
  ventilator.setup();
  repository.setup();
  door.setup();
  rfid.setup();
  tempHumSensor.begin();
  lightInterface.setup();
}

void loop()
{
  // --- Handle door

  if (rfid.checkCard() == true)
  {
    cardID = rfid.ID;
    
    if (validate(cardID) && !door.isOpen()) 
    {
      door.open();
      entryCounter++;

      // Refresh interface
      interface.display(temperature, humidity, entryCounter);
    }
  }
  currentTime = millis();

  if ((door.lastOpen + DOOR_OPEN_TIME < currentTime || currentTime < door.lastOpen) && door.isOpen()) 
  {
    door.close();
  }

  // --- End handle door

  // --- Handle sensor
  // If the sensor is doing its first measurement or
  // it's passed more time than cooldown, it will measure again
  if (lastRead == 0 || currentTime > lastRead + DHT_SENSOR_COOLDOWN || currentTime < lastRead)
  {
    temperatureAux = tempHumSensor.readTemperature();
    humidityAux = tempHumSensor.readHumidity();

    if (!isnan(temperatureAux))
    {
      temperature = temperatureAux;
    }
    if (!isnan(humidityAux))
    {
      humidity = humidityAux;
    }

    lastRead = currentTime;

    // Save data and refresh interface
    if (!isnan(temperature) && !isnan(humidity))
    {
      repository.save(temperature, humidity);
      interface.display(temperature, humidity, entryCounter);
    }
    
  }
  // ---

  // --- Handle ventilator
  environmentStatus = Environment::evaluate(temperature, humidity);
  switch (environmentStatus)
  {
  case EnvironmentStatus::CONFORMANT:
    ventilatorSpeed = VentilatorSpeed::MINIMUM;
    lightColor = LightColor::GREEN;
    break;
  case EnvironmentStatus::IRREGULAR:
    ventilatorSpeed = VentilatorSpeed::MEDIUM;
    lightColor = LightColor::YELLOW;
    break;
  case EnvironmentStatus::DANGER:
    ventilatorSpeed = VentilatorSpeed::MAXIMUM;
    lightColor = LightColor::RED;
    door.open();
    break;
  default:
    ventilatorSpeed = VentilatorSpeed::MINIMUM;
    lightColor = LightColor::GREEN;
    break;
  }
  lightInterface.set(lightColor);
  ventilator.run(ventilatorSpeed);
  // --- End handle ventilator

}