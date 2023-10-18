import { Component, OnDestroy } from '@angular/core';

import { BrokerService } from './service/broker.service';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss']
})
export class AppComponent implements OnDestroy {
  title = 'Aplicativo Web para controle de robô FPV';
  led_state: 0 | 1 = 0;


  loginForm!: FormGroup;

  constructor(public brokerService: BrokerService, private fb: FormBuilder) {
    this.loginForm = fb.group({
      username: ['', Validators.required],
      password: [
        '',
        Validators.compose([
          Validators.required,
          Validators.minLength(6), // Define um comprimento mínimo da senha
          Validators.pattern(/^(?=.*[a-z])(?=.*[A-Z])(?=.*\d).+$/), // Verifica se a senha tem letras maiúsculas, minúsculas e dígitos
        ]),
      ],
    });
  }
  ngOnDestroy(): void {
    this.brokerService.disconnectFromBroker();
  }

  connectToBroker() {
    if (this.loginForm.valid) {
      const username = this.loginForm.value?.username;
      const password = this.loginForm.value?.password;
      this.brokerService.connectToBroker(username, password);
    }

  }



  mudarLed() {
    this.led_state = this.led_state === 1 ? 0 : 1;
    this.brokerService.publishMessage('led_state', this.led_state.toString());
  }
}
