#include "RFID.h"
#include "Door.h"
#include "ScreenInterface.h"
#include "Interface.h"
#include "Repository.h"
#include "Ventilator.h"
#include "SerialInterface.h"
#include "Environment.h"
#include "LightInterface.h"
#include <SPI.h>
#include <MFRC522.h>

// DHT Setup
#include "DHT.h"
#define DHTPIN 2      // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11 // DHT 11

#define DOOR_OPEN_TIME 3000 // milliseconds

//RFID Setup
#define RST_PIN 9
#define SS_PIN 10
RFIDMF mfrc522(SS_PIN, RST_PIN); 

// TODO Decide pin layout
#define SERVO_PIN 3
#define SCREEN_PIN 4
#define DC_MOTOR_PIN 5
#define RFID_PIN1 9
#define RFID_PIN2 10
#define LIGHT_PIN 7
#define CARD_ID 12345

// Auxiliary variables
static int entryCounter = 0;
static unsigned long currentTime;
static String cardInfo;
static EnvironmentStatus environmentStatus;
static VentilatorSpeed ventilatorSpeed;
static LightColor lightColor;

// System objects
DHT tempHumSensor(DHTPIN, DHTTYPE);
Door door(SERVO_PIN);
// change true to false to use Serial interface instead of Screen
#if true
ScreenInterface interface(16, 2); // 16x2 Screen
#else
SerialInterface interface();
#endif
Repository repository;     // o que é que isto precisa? serve para guardar os dados excel
Ventilator ventilator(DC_MOTOR_PIN);
LightInterface lightInterface(LIGHT_PIN);

float temperature;
float humidity;

void setup()
{
  Serial.begin(9600);
  interface.setup();
	while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop()
{

  // --- Handle door
  if (rfid.checkCard(CARD_ID) == true)
  {
    cardInfo = rfid.cardInfo;
    if (cardInfo == VALID_CREDENTIALS && !door.isOpen)
    {
      door.open();
      entryCounter++;
    }
  }

  currentTime = millis();

  if ((door.lastOpen + DOOR_OPEN_TIME > currentTime || currentTime < door.lastOpen) && door.isOpen)
  {
    door.close();
  }
  // --- End handle door

  // --- Handle sensor
  temperature = tempHumSensor.readTemperature();
  humidity = tempHumSensor.readHumidity();
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