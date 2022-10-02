#include "RFID.h"
#include "Door.h"
#include "Screen.h"
#include "Repository.h"
#include "Ventilator.h"

#include "DHT.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

DHT tempHumSensor(DHTPIN, DHTTYPE);

#define MAX_TEMPERATURE_THRESHOLD 25

#define SERVO_PIN 3 // depois ver qual dos pinos será
#define SCREEN_PIN 4
#define DC_MOTOR_PIN 5
#define RFID_PIN 6
#define VALID_CREDENTIALS String("i am a boss")

static int entryCounter = 0;
static String cardInfo;

RFID rfid(RFID_PIN); // talvez precise do pino de ligação
Door door(SERVO_PIN);
Screen screen(SCREEN_PIN); // precisa de 1 ou mais pinos?
Repository repository; // o que é que isto precisa? serve para guardar os dados excel
Ventilator ventilator(DC_MOTOR_PIN);

float temperature;
float humidity;

void setup( )
{
  Serial.begin( 9600);
}

void loop( )
{
  temperature = tempHumSensor.readTemperature();
  humidity = tempHumSensor.readHumidity();
  
  // Handle door
  if(rfid.checkCard() == true){
    cardInfo = rfid.cardInfo; // assumir que cartão tem alguma informação
    if(cardInfo == VALID_CREDENTIALS){
      door.open();
      entryCounter++;
    }
  }

  // Handle ventilator
  if(temperature > MAX_TEMPERATURE_THRESHOLD){
    ventilator.run();
  }

  screen.refresh(entryCounter);
  
  repository.save(temperature, humidity);

}