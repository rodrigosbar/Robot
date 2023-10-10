import { Injectable } from '@angular/core';
import { environment } from 'src/environments/environment';

@Injectable({
  providedIn: 'root'
})
export class BrokerConnectionService {
  brokerConnected: boolean = false;

  constructor() {
    if (!environment.production) {
      console.log('Estamos em um ambiente de desenvolvimento.');
    }else{
      console.log('Estamos em um ambiente de produção.');

    }
   }
}
