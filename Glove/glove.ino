/*  ----------------------------------------------------------------
    http://www.prometec.net/duplex-nrf2401
    Prog_79B_Emisor
    
    Usando un NRF2401 para comunicar dos Arduinos en modo Duplex
    Programa Emisor:
--------------------------------------------------------------------  
*/ 
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <TimerOne.h>

RF24 radio(9,10);
int ledder;
int ledizq;
int camb = 0;
int ledint= 0;
int debonce = 0;
unsigned long led; //unidades derecha, decenas izq
volatile unsigned long last_micros;
const uint64_t pipes[2] = { 0xF0F0F0E0E1LL, 0xF0F0F0E0D2LL };

void setup(void)
{
    pinMode(10, OUTPUT); 
     pinMode(6, OUTPUT); //izq
      pinMode(5, OUTPUT); //der 
    pinMode(A3, OUTPUT);  //izquierda
    pinMode(A2, OUTPUT); //derecha
     Timer1.initialize(500000);
    Timer1.attachInterrupt(parpadeo) ;
    //attachInterrupt( 0, debonceizq, FALLING);
    //attachInterrupt( 1, debonceder, FALLING);
    radio.begin();
    Serial.begin(9600);
    radio.setRetries(15,15);    // Maximos reintentos 
    //radio.setPayloadSize(8);   // Reduce el payload de 32 si tienes problemas
  
    // Open pipes to other nodes for communication
    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1,pipes[1]);
}

void loop(void)
{
    radio.stopListening();    // Paramos la escucha para poder hablar
    led = 10*ledizq + ledder;
    if ( led == 11)
      led  = 0;
    bool ok = radio.write( &led, sizeof(unsigned long) );
    Serial.println(led);
    radio.startListening();   //Volvemos a la escucha
    unsigned long started_waiting_at = millis();
   bool timeout = false;
   while ( ! radio.available() && ! timeout )       // Esperamos 200ms
        if (millis() - started_waiting_at > 200 )
            timeout = true;
   if ( timeout );
  else  {       
        unsigned long  recib;
        radio.read( &recib, sizeof(unsigned long) );     
      if (recib == 1){
        ledizq = 0;
        ledder = 1;
      }
      else if (recib == 10){
        ledizq = 1;
        ledder = 0;
      }
      else {
        ledizq = 0;
        ledder = 0;
      }
     }
  if ( digitalRead(5) == LOW && digitalRead(4) == LOW)
      debonce == 0;
  if ( digitalRead(5) == HIGH && debonce != 1){
      ledder = !ledder;
      debonce == 1;
  }
  if ( digitalRead(6) == HIGH && debonce != 1){
      ledizq = !ledizq;    
      debonce == 1;
  }
 /* unsigned long wait_trasm = millis();    //timmer para esperar a transmitir
  while(  (millis() - wait_trasm < 250) && camb == 0){
    } 
  camb = 0;
  */
}

/*void debonceizq() {
  if((long)(micros() - last_micros) >= 15000) {
    intermizq();
    last_micros = micros();
  }
}

void debonceder() {
  if((long)(micros() - last_micros) >= 15000) {
    intermder();
    last_micros = micros();
  }
}
void intermizq() {
    ledizq=!ledizq ;
    camb = 1;
        Serial.println("holaizq");
   }
void intermder() {
    ledder=!ledder ;
    camb = 1;
            Serial.println("holader");
   }   
 */
void parpadeo () {
    if (ledizq == HIGH) {
      digitalWrite(A3, ledint);
    }
     else if (ledder == HIGH) {
      digitalWrite(A2, ledint);
    }
     else {
      digitalWrite(A3, LOW);
       digitalWrite(A2, LOW);
     }
     ledint = !ledint;

}

