import { NgModule } from '@angular/core';
import { RouterModule } from '@angular/router';

import { AppComponent } from '../components/app/app.component'

@NgModule({
    imports: [
        RouterModule.forRoot([
            { path: '', redirectTo: 'cad', pathMatch: 'full' },
            { path: '**', redirectTo: 'cad' }
        ])
    ],
    exports: [
        RouterModule
    ]
})

export class AppRoutingModule { }