import { NgModule } from '@angular/core';
import { RouterModule } from '@angular/router';
import { FormsModule } from '@angular/forms';
import { UniversalModule } from 'angular2-universal';

import { BrowserModule } from '@angular/platform-browser';

import { Auth } from './services/auth/auth.service';
import { ModelsService } from './services/models/models.service';
import { AUTH_PROVIDERS } from 'angular2-jwt';

import { AppComponent } from './components/app/app.component';
import { AppRoutingModule } from './modules/app-routing.module';
import { CadModule } from './modules/cad/cad.module';

console.log(FormsModule);
console.log(BrowserModule);

@NgModule({
    imports: [
        UniversalModule, // Must be first import. This automatically imports BrowserModule, HttpModule, and JsonpModule too.
        FormsModule,
        AppRoutingModule,
        CadModule,
    ],
    bootstrap: [
        AppComponent
    ],
    declarations: [
        AppComponent,
    ],
    providers: [
        AUTH_PROVIDERS,
        Auth,
        ModelsService
    ]
})
export class AppModule {
}
