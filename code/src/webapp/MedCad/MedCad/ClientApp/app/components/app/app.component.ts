import { Component } from '@angular/core';
import { Auth } from '../../services/auth/auth.service';

@Component({
    selector: 'app',
    template: require('./app.component.html'),
    styles: [require('./app.component.scss')],
    providers: [Auth]
})

export class AppComponent {
    constructor(private auth: Auth) {}
}
