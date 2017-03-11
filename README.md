
# Español
## SEÑALICI
Un proyecto univeristario que consiste en un sistema de comunicación, basado en arduino, entre un guante y una pequeña caja para para controlar luces intermitentes y de freno mientras vas en bicicleta.
Los intermitentes son controlados por el usuario con dos botones que lleva en el guante. La luz de freno es controlada a través de un acelerómetro.
Tiene dos bloques principales:

## GUANTE
  Una pequeña PCB que el usuario lleva en un guante, le da al ciclista el control de los intermitentes.
  Contiene:
  - ATMEGA 328p 32MLF para correr el código arduino
  - Un módulo RF para comunicarse con la PCB de la espalda
  - Dos botones para controlar los intermitentes
  - Leds SMD indicadores para el usuario

## ESPALDA
  Está formada por dos PCBs, una de ellas tiene las luces intermitentes dispuestas en forma de flecha apuntando a ambos lados derecha e   izquierda, además de la luz de freno.
  La otra tiene el microcontrolador que correra el código arduino y gestionara el sistema de comunicación, el acelerómetro y otra serie   de bloques.
  Contiene: 
  - ATMEGA 328p para correr el código arduino
  - Un módulo RF para comunicarse con la PCB del guante
  - Un zumbador para avisar al usuario si la comunicación se pierde
  - Un acelerómetro para controlar de forma automática la luz de freno y el apagado de los intermitentes

# English
## SEÑALICI
An university project which consists in a communication system, based on arduino, between a glove and a small box to signal driven lights while cycling.
Signal lights are controlled by the user with two buttons in the glove. Brake light is controlled by an accelerometer.
It has two parts:
## GLOVE
  A small PCB which the user wears inside a glove, it gives the cyclist the control of the indicators.
  Includes:
  - ATMEGA 328p 32MLF to run the arduino code
  - An RF module to communicate with BACK PCB
  - Two buttons to control driven lights
  - SMD leds indicators for user

## BACK
  Includes two PCBs, one of them has the lights placed as an arrow pointing to both sides left and right and the drake light.
  The other one has the microcontroller to run the arduino code that manages the RF communicator, the accelerometer and other blocks.
  Includes:
  - ATMEGA 328p to run the arduino code
  - An RF module to communicate with GLOVE PCB
  - A buzz to advise the user if the communication gets lost
  - An accelerometer to control automatically the break light and the indicators turn off
