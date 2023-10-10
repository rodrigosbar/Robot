import { Component } from '@angular/core';
import { BrokerConnectionService } from '../broker-connection.service';
import { FormBuilder, FormControl, FormGroup, Validators } from '@angular/forms';

@Component({
  selector: 'app-connection-panel',
  templateUrl: './connection-panel.component.html',
  styleUrls: ['./connection-panel.component.scss']
})
export class ConnectionPanelComponent {
  loading: boolean = false;
  loginForm!: FormGroup;

  constructor(public service: BrokerConnectionService,
    private fb: FormBuilder) {
    this.initForm();
  }

  initForm() {
    this.loginForm = this.fb.group({
      user: new FormControl('', [Validators.required, Validators.minLength(4)]),
      password: new FormControl('', [Validators.required, Validators.minLength(4)])
    });
  }
}
