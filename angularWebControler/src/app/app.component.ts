import { Component, OnDestroy, OnInit, ViewChild } from '@angular/core';
import { FormBuilder, FormGroup, Validators } from '@angular/forms';
import { JoystickEvent, NgxJoystickComponent } from 'ngx-joystick';
import { JoystickManagerOptions, JoystickOutputData } from 'nipplejs';
import { BrokerService } from './service/broker.service';


@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css'],
})
export class AppComponent implements OnInit, OnDestroy {

  title = 'Aplicativo Web para controle de robô FPV';
  ledState: 0 | 1 = 0;
  motorState: 'ahead' | 'back' | 'left' | 'right' | 'aheadLeft' | 'backRight' | 'backLeft' | 'stop' | 'aheadRight' = 'stop'
  loginForm!: FormGroup;

  @ViewChild('staticJoystic') staticJoystick!: NgxJoystickComponent;
  staticOptions: JoystickManagerOptions = {
    mode: 'static',
    position: { left: '50%', top: '50%' },
    color: 'blue',
  };

  staticOutputData!: any;
  directionStatic!: string;
  interactingStatic!: boolean;


  constructor(public brokerService: BrokerService, private fb: FormBuilder) {
    this.loginForm = fb.group({
      username: ['rssoares', Validators.required],
      password: ['',
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

  ngOnInit() {
  }

  onStartStatic(event: JoystickEvent) {
    this.interactingStatic = true;
  }

  onEndStatic(event: JoystickEvent) {
    this.interactingStatic = false;
    this.goMotors('stop');
    this.motorState = 'stop';
  }

  onMoveStatic(event: JoystickEvent) {
    this.staticOutputData = event.data;
    if (this.staticOutputData?.distance > 30) {
      let direction = this.staticOutputData.direction ? this.staticOutputData.direction.angle : '';
      const dg = parseFloat(this.staticOutputData?.angle?.degree?.toFixed(2));

      direction = direction === 'up' ? 'ahead' : direction === 'down' ? 'back' : direction;

      if (dg >= 24 && dg <= 60) {
        direction = 'aheadRight';
      }

      if (dg >= 114 && dg <= 150) {
        direction = 'aheadLeft';
      }

      if (dg >= 151 && dg <= 200) {
        direction = 'left';
      }

      if (dg >= 201 && dg <= 245) {
        direction = 'backLeft';
      }

      if (dg >= 300 && dg <= 340) {
        direction = 'backRight';
      }

      if (this.motorState != direction) {
        this.motorState = direction;
        this.goMotors(this.motorState)
      }

    }

    if(this.staticOutputData?.distance <= 30){
      this.goMotors('stop');
      this.motorState = 'stop';
    }

  }


  connectToBroker() {
    if (this.loginForm.valid) {
      const username = this.loginForm.value?.username;
      const password = this.loginForm.value?.password;
      this.brokerService.connectToBroker(username, password);
    }
  }


  mudarLed() {
    this.ledState = this.ledState === 1 ? 0 : 1;
    this.brokerService.publishMessage('led_state', this.ledState.toString());
  }


  goMotors(moviment: 'ahead' | 'back' | 'left' | 'right' | 'aheadLeft' | 'backRight' | 'backLeft' | 'stop' | 'aheadRight') {
    this.brokerService.publishMessage('motor_state', moviment);
  }


}
