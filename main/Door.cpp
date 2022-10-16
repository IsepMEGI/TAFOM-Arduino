#include "Door.h"
Servo servo; // criar um objeto servo 
int angle= 0; // posição inicial da porta

// TODO Implement door opening and closing

Door::Door(uint8_t pin) // funçao que se chama door e tem variavel PIN é a funçao door servo pin.
{
    this->pin = pin; 
  
}

void Door::setup(){
servo.attach(SERVO_PIN); // Associar o objeto servo ao pin de controlo
}

void Door::open()
{
    // Implement door opening method
   for(angle = 0; angle < 90; angle++) // abre 90 ou 180?
  {
        servo.write(angle); // update do servo para o angulo em especifico
        delay(20); // Tempo que demora a mover um grau
  } 

}

void Door::close()
{
    // Implement door closing method 
    for(angle = 90; angle > 0; angle--) 
    {
        servo.write(angle);
        delay(20); 
    }
}