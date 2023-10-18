import { Injectable } from '@angular/core';
import * as Paho from 'paho-mqtt';
import { HttpClient } from '@angular/common/http';

@Injectable({
  providedIn: 'root',
})
export class BrokerService {
  private client: Paho.Client | null = null;

  constructor(private http: HttpClient) {}

  async connectToBroker() {
    const hostname = 'b5591e2e960d4011a3027e9973460de5.s1.eu.hivemq.cloud'; // Remova 'mqtts://'
    const port = 8884;
    const clientId = 'controlerWeb1';
    const username = ''; // colocar pela tela 
    const password = ''; // colocar pela tela
  
    const options: Paho.ConnectionOptions = {
      useSSL: true, // Mantenha isso como verdadeiro para usar TLS
      onSuccess: this.onConnect.bind(this),
      onFailure: this.onFailure.bind(this),
      userName: username,
      password: password,
    };
  
    this.client = new Paho.Client(hostname, port, clientId);
  
    // Set callback handlers
    this.client.onConnectionLost = this.onConnectionLost.bind(this);
    this.client.onMessageArrived = this.onMessageArrived.bind(this);
  
    // Connect the client
    this.client.connect(options);
  }
  

  onConnect() {
    console.log('Conexão MQTT estabelecida com sucesso no broker.');
    this.subscribeToTopic('led_state');

    this.publishMessage('robotMessages','Olá mundo, sou o controle Angular ficando online para controlar o led  '+
    new Date().toLocaleDateString()+' - '+new Date().toLocaleTimeString());
  }

  onFailure(error: any) {
    console.error('Erro na conexão MQTT:', error.errorMessage);
  }

  onConnectionLost(responseObject: any) {
    if (responseObject.errorCode !== 0) {
      console.log('Conexão MQTT perdida: ' + responseObject.errorMessage);
    }
  }

  onMessageArrived(message: Paho.Message) {
    console.log(`Received message on topic: ${message.destinationName}: ${message.payloadString}`);
  }

  subscribeToTopic(topic: string) {
    if (this.client && this.client.isConnected()) {
      this.client.subscribe(topic, { qos: 0 });
      console.log('topico inscrito: ', topic);
    } else {
      console.warn('Conexão MQTT não está ativa. Não é possível se inscrever no tópico.');
    }
  }

  publishMessage(topic: string, message: string) {
    if (this.client && this.client.isConnected()) {
      const mqttMessage = new Paho.Message(message);
      mqttMessage.destinationName = topic;
      this.client.send(mqttMessage);
      console.log(`Mensagem publicada em ${topic}: ${message}`);
    } else {
      console.warn('Conexão MQTT não está ativa. Não é possível publicar mensagens.');
    }
  }
}
