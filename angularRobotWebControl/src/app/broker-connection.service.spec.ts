import { TestBed } from '@angular/core/testing';

import { BrokerConnectionService } from './broker-connection.service';

describe('BrokerConnectionService', () => {
  let service: BrokerConnectionService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(BrokerConnectionService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
