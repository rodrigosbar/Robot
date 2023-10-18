import { Component } from '@angular/core';
import * as mqtt from "mqtt"; // import everything inside the mqtt module and give it the namespace "mqtt"

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss']
})
export class AppComponent {
  title = 'Aplicativo Web para controle de robô FPV';


  connectToBroker() {
    console.log('tentando conectar ao broker');
  }
}
