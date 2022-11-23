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
Implementação do código feita via Arduino IDE 2.0.0.

Antes de executar, substituir no código os valores "WIFI-NAME" e "PASSWORD" pelo nome da rede WiFi que será utilizada e senha da mesma, respectivamente.

Para execução do código é necessário conectar o cabo USB no controlador NodeMCU ESP8266, instalar o driver específico do modelo pela própria IDE e então clicar em "Upload" para enviar o binário ao microcontrolador para execução.

## Bibliotecas utilizadas
Para a implementação do código foram utilizadas bibliotecas terceiras para realizar conexão wifi e requisições via mqtt e http

| Biblioteca | Doc |
| ------ | ------ |
| PubSubClient | https://github.com/knolleary/pubsubclient |
| ESP8266 WiFi |https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html |

## Funcionamento básico 

- setup() - Função responsável por mapear portas de entrada e saída e criar conexão WiFi e MQTT
- loop() - Função principal com o loop de execução do programa, responsável por detectar constantemente mudanças de sinal de entrada (porta do sensor), publicar mensagens no tópico MQTT e ativar os atuadores (led e buzzer)
- callback() - Função responsável por tratar mensagens recebidas via MQTT

