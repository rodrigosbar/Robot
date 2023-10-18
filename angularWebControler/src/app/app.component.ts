import { Component } from '@angular/core';

import { BrokerService } from './service/broker.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss']
})
export class AppComponent {
  title = 'Aplicativo Web para controle de robô FPV';
  led_state: 0 | 1 = 0;
  constructor(private brokerService: BrokerService) {

  }
  connectToBroker() {
    console.log('tentando conectar ao broker');
    this.brokerService.connectToBroker();
  }

  mudarLed() {
    this.led_state = this.led_state === 1 ? 0 : 1;
    this.brokerService.publishMessage('led_state', this.led_state.toString());
  }
}
