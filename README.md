# Safe Freedom Arduino Software
Projeto de sensor de movimento para a disciplina de Objetos Inteligentes do segundo semestre de 2022

## Hardware

- NodeMCU ESP8266 v2
- Sensor de presença/movimento PIR HC-SR501
- Buzzer sonoro passivo
- Led vermelho 5mm
- Protoboard 830 pontos
- Jumpers macho-macho e macho-fêmea
- Cabo USB

## Software
Implementação do código feita via Arduino IDE 2.0.0

## Bibliotecas utilizadas
Para a implementação do código foram utilizadas bibliotecas terceiras para realizar conexão wifi e requisições via mqtt e http

| Biblioteca | Doc |
| ------ | ------ |
| PubSubClient | https://github.com/knolleary/pubsubclient |
| ESP8266 WiFi |https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html |
