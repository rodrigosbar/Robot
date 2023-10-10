import { Component } from '@angular/core';
import { BrokerConnectionService } from '../broker-connection.service';

@Component({
  selector: 'app-header',
  templateUrl: './header.component.html',
  styleUrls: ['./header.component.scss']
})
export class HeaderComponent {
  user: string = '';
  password:string ='';


  constructor(private service: BrokerConnectionService) {

  }

}
