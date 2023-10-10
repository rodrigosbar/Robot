import { Injectable } from '@angular/core';
import { MatSnackBar } from '@angular/material/snack-bar';
import { environment } from 'src/environments/environment';

@Injectable({
  providedIn: 'root'
})
export class BrokerConnectionService {

  brokerConnected: boolean = false;
  loading: boolean = false;

  constructor(private _snackBar: MatSnackBar) {
    if (!environment.production) {
      console.log('Estamos em um ambiente de desenvolvimento.');
    } else {
      console.log('Estamos em um ambiente de produção.');

    }
  }


  login(formValue: { user: string, password: string }) {
    this.loading = true;
    if (formValue.password === environment.passWord && formValue.user === environment.userName) {
      this.connectBroker();
    } else {
      setTimeout(() => {
        this._snackBar.open('Usuário ou senha inválidos !', 'ok', {
          duration: 5000
        });
        this.loading = false;
      }, 3000);
    }
  }

  private connectBroker() {

    this._snackBar.open('Conectando ao broker MQTT !', 'ok', {
      duration: 5000
    });
    this.loading = false;
  }
}
