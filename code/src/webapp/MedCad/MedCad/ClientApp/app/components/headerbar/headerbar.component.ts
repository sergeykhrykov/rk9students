import { Component, Input } from '@angular/core';
import { Auth } from '../../services/auth/auth.service';
import { ModelsService } from '../../services/models/models.service';

@Component({
    selector: 'headerbar',
    template: require('./headerbar.component.html'),
    styles: [require('./headerbar.component.scss')],
})

export class HeaderbarComponent {

    @Input() public showInfo: boolean;

    constructor(public auth: Auth, public model: ModelsService ) {
        console.log(auth.userProfile);
    }

    public openFileContextClickHandler() {
        document.getElementById('open-file-dlg').click();
    }

    public addFileContextClickHandler() {
        document.getElementById('add-file-dlg').click();
    }

    public openCloudContextClickHandler() {
        document.getElementById('load-cloud').click();
    }

    public addCloudContextClickHandler() {
        document.getElementById('import-cloud').click();
    }

    public saveCloudContextClickHandler() {
        document.getElementById('save-cloud').click();
    }

    public toggleInfo() {
        document.getElementById('show-info').click();
    }

    public clearSceen() {
        this.model.clear();
    }
}
