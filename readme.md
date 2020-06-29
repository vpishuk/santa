# Introduction

Sometime ago, someone gave a cute santa-toy for my kids. They were playing with it a lot.
Suddenly, santa stop to sing a song. My daughter was frustrated because she loves that toy.
I decided to repair it, because I was not able to buy the same santa again. They were sold out.

This repo contains the code for a simple santa-toy.

To repair a toy I used:
- Arduino Pro Micro
- H-bridge TB6616FNG
- DFRobot Voice Module DFR0534
- DC Motor from the old toy
- 4.5V AC
- Speaker from the old toy
- Buttons from the old toy


# Circuit diagram
![https://www.youtube.com/watch?v=JPPTRj0KWbg](./assets/diagram.png?raw=1)

The diagram is super simple. AC is connected to Arduino through 5V pin. All shields are connected to Arduino's 5V and ground.

TB6616FNG has a separate pin for motor's power and ground (VM and GND close to it). You can watch a pretty good [video](https://www.youtube.com/watch?v=JPPTRj0KWbg) about how to use TB6616FNG. I'm sure you noticed that there is one more set of inputs and outputs on a motor shield. Yeah, TB6616FNG supports two motors. You can use H-bridge which supports only one motor, but I hope to add additional features for the Santa.

DFRobot's voice module has great documentation. Follow instructions on [wiki](https://wiki.dfrobot.com/Voice_Module_SKU__DFR0534) to properly connect and use it.
