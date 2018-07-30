import { NgModule } from '@angular/core';
import { RouterModule } from '@angular/router';

import { ProfileComponent } from '../../components/profile/profile.component';
import { CadComponent } from '../../components/cad/cad.component';
import { HeaderbarComponent } from '../../components/headerbar/headerbar.component';
import { WorkspaceComponent } from '../../components/workspace/workspace.component';

@NgModule({
    imports: [
        RouterModule.forChild([
            { path: 'cad', component: CadComponent }
        ])
    ],
    exports: [
        RouterModule
    ]
})
export class CadRoutingModule { }