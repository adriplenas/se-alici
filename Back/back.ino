#include <MsTimer2.h>

/*  ----------------------------------------------------------------
    http://www.prometec.net/duplex-nrf2401
    Prog_79B_Emisor
    
    Usando un NRF2401 para comunicar dos Arduinos en modo Duplex
    Programa Receptor:
--------------------------------------------------------------------  
*/ 

#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include <TimerOne.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
Adafruit_MMA8451 mma = Adafruit_MMA8451();
RF24 radio(9,10);
const uint64_t pipes[2] = { 0xF0F0F0E0E1LL, 0xF0F0F0E0D2LL };
int ledint = 0;
int buttonizq = 0;
int buttonder = 0;
int trasm = 0;
boolean parp;
boolean acc;
float ac = 0;
int estadostop = 0;
int zumbador = 0;
int lost =0 ;
int inicio = 0;
void setup(void)
{
     Serial.begin(9600);
    pinMode(10, OUTPUT); 
    pinMode(3, OUTPUT);
        pinMode(5, OUTPUT);
     pinMode(6, OUTPUT); 
     pinMode(7, OUTPUT);
   // Serial.begin(9600);
     Timer1.initialize(200);
    Timer1.attachInterrupt(zumbar);
     MsTimer2::set(500, parpadeo); 
  MsTimer2::start();
    radio.begin();
    radio.setRetries(15,15);
    //radio.setPayloadSize(8);
    radio.startListening();
    radio.openWritingPipe(pipes[1]);
    radio.openReadingPipe(1,pipes[0]);
     if (! mma.begin()) 

  
  mma.setRange(MMA8451_RANGE_2_G);  // cuantas G ponemos?  
}

void loop(void)
{
    if (inicio = 0){
          while ( ! radio.available());
   
    unsigned long started_waiting_at = millis();
     bool timeout = false;
     while ( ! radio.available() && ! timeout )       // Esperamos 200ms
          if (millis() - started_waiting_at > 200 ){
              timeout = true;
              lost = 1;
           }
    }
    if ( radio.available() )  // Si hay datos disponibles
    {
         lost = 0;
        unsigned long recib;
        bool done = false;
        while (!done)        // Espera aqui hasta recibir algo
           {

              done = radio.read( &recib, sizeof(unsigned long) );
              Serial.print("Dato Recibido =");

              Serial.println(recib);
              if (recib == 11)
                trasm == 0;                
              if (recib == 1){
                trasm = 1;
                buttonder = 1;}
              else if (recib == 10){
                trasm = 10;
                buttonizq = 1;}
              else {
                trasm =0;
                buttonizq = 0;
                buttonder = 0;
                }
                
              delay(20);  // Para dar tiempo al emisor
           }
    
      radio.stopListening();  // Dejamos d escuchar para poder hablar
      radio.write( &ledint, sizeof(int) );
     Serial.println("Enviando Respuesta");
      radio.startListening();    // Volvemos a la escucha para recibir mas paquetes
    }
     if (acc == 1){
      acc = 0;
        mma.read();
       sensors_event_t event; 
        mma.getEvent(&event);
       ac =  event.acceleration.z;       
    //   Serial.print(ac);
     //  Serial.print("\n");
       if (ac > 2){
          digitalWrite(6, HIGH);
          estadostop = 1;
       }
       if (estadostop = 1 && ac < -0.1){
          estadostop = 0;
          digitalWrite(6, LOW);
       }
    }
}

void zumbar () {
   if (lost == 1){
    zumbador = !zumbador;
    digitalWrite(3, zumbador);
  }
}

void parpadeo () {
 
  if( parp == 1){
    if (buttonizq == HIGH) {
      digitalWrite(5, ledint);
    }
     else if (buttonder == HIGH) {
      digitalWrite(7, ledint);
    }
     else {
      digitalWrite(5, LOW);
       digitalWrite(7, LOW);
     }
     ledint = !ledint;
  }
  parp = 1;
  acc = 1;

}

