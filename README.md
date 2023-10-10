# Robô de telepresença FPV

Para replicar o projeto deve-se mudar o nome do arquivo configExample.h para config.h
e depois colocar as configurações do servidor MQTT de sua escolha.

## Tecnologias utilizadas e conhecimentos adquiridos

- Eletrônica básica para conectar microcontrolador, motores e círcuito elétrico.

- Criação de algoritmos em c++ para conectar o hardware a Internet, receber comandos de um broker MQTT e repassar aos motores em tempo real.

- Desenvolvimento de software web em Angular para controlar o robô remotamente de algum dispositivo, em qualquer lugar aonde se tenha uma conexão com a internet.

- Configuração e utilização de broker MQTT grátis para protocolar a comunicação entre sistema web de controle e o hardware do rôbo.

# Referências

### Controle de led e configuração da IDE arduino com o nodemcu

https://www.robocore.net/tutoriais/como-programar-nodemcu-arduino-ide

### Ponte H para controlar os motores

https://blog.eletrogate.com/guia-definitivo-de-uso-da-ponte-h-l298n/

### Montagem do circuito para 2 motores com alimentação única

https://www.instructables.com/WiFi-Controlled-Robot-With-NodeMCU/

### Protocolo de comunicação MQTT e como configurar

https://www.hivemq.com/

https://www.hivemq.com/article/mqtt-on-arduino-nodemcu-esp8266-hivemq-cloud/

https://www.hivemq.com/article/ultimate-guide-on-how-to-use-mqtt-with-node-js/

https://github.com/hivemq-cloud/mqtt.js-client-example
