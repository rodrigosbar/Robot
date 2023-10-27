import { Component, OnInit, ViewChild } from '@angular/core';

import { JoystickEvent, NgxJoystickComponent } from 'ngx-joystick';
import { JoystickManagerOptions, JoystickOutputData } from 'nipplejs';

@Component({
  selector: 'app-joystick',
  templateUrl: './joystick.component.html',
  styleUrls: ['./joystick.component.scss']
})
export class JoystickComponent implements OnInit {

  @ViewChild('staticJoystic') staticJoystick!: NgxJoystickComponent;
  staticOptions: JoystickManagerOptions = {
    mode: 'static',
    position: { left: '50%', top: '50%' },
    color: 'blue',
  };

  staticOutputData!: JoystickOutputData;
  directionStatic!: string;
  interactingStatic!: boolean;


  constructor() { }

  ngOnInit(): void {
  }
  
  onStartStatic(event: JoystickEvent) {
    this.interactingStatic = true;
  }

  onEndStatic(event: JoystickEvent) {
    this.interactingStatic = false;
  }

  onMoveStatic(event: JoystickEvent) {
    this.staticOutputData = event.data;
  }

  onPlainUpStatic(event: JoystickEvent) {
    this.directionStatic = 'UP';
  }

  onPlainDownStatic(event: JoystickEvent) {
    this.directionStatic = 'DOWN';
  }

  onPlainLeftStatic(event: JoystickEvent) {
    this.directionStatic = 'LEFT';
  }

  onPlainRightStatic(event: JoystickEvent) {
    this.directionStatic = 'RIGHT';
  }

  

}
