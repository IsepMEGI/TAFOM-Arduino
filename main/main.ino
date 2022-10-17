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
#define DHTPIN 2      // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11

// MFRC Setup
#define SS_PIN 10 //slave select pin
#define RST_PIN 5 // reset pin. we need to study the pin layout

#define DOOR_OPEN_TIME 3000 // milliseconds, must be greater than openning time: 20*90 ms
#define DHT_SENSOR_COOLDOWN 2000

// TODO Decide pin layout
#define SERVO_PIN 3
#define SCREEN_PIN 4
#define DC_MOTOR_SPEED_PIN 5
#define DC_MOTOR_DIR_A_PIN 3
#define DC_MOTOR_DIR_B_PIN 4
#define LIGHT_GREEN_PIN 7
#define LIGHT_YELLOW_PIN 8
#define LIGHT_RED_PIN 9
#define VALID_ID "33 98 34 56"

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

float temperature;
float humidity;

void setup()
{
  Serial.begin(9600);

  // System objects' setup
  interface.setup();
  ventilator.setup();
  repository.setup();
  door.setup();
  rfid.setup();
}

void loop()
{
  // --- Handle door
  if (rfid.checkCard() == true)
  {
    //cardID = rfid.ID; //Probably this line is useless, we can text rfid.ID == VALID_ID direcly in the if condition
    if (rfid.ID == VALID_ID && !door.isOpen()) // ANA credenciais validas e porta fechada, abre a porta
    {
      door.open();
      entryCounter++; // ANA conta as pessoas que entram
    }
  }

  currentTime = millis();

  if ((door.lastOpen + DOOR_OPEN_TIME > currentTime || currentTime < door.lastOpen) && door.isOpen()) // ANA é quando a porta vai fechar?
  {
    door.close();
  }
  // --- End handle door

  // --- Handle sensor
  // If the sensor is doing its first measurement or
  // it's passed more time than cooldown, it will measure again
  if (lastRead == 0 || currentTime > lastRead + DHT_SENSOR_COOLDOWN || currentTime < lastRead)
  {
    temperature = tempHumSensor.readTemperature();
    humidity = tempHumSensor.readHumidity();
    lastRead = currentTime;
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
    break;
  default:
    ventilatorSpeed = VentilatorSpeed::MINIMUM;
    lightColor = LightColor::GREEN;
    break;
  }
  lightInterface.set(lightColor);
  ventilator.run(ventilatorSpeed);
  // --- End handle ventilator

  // --- Handle interfaces
  interface.display(temperature, humidity, entryCounter);
  // ---

  // --- Handle saving data
  repository.save(temperature, humidity);
  // ---
}