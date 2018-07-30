import { Component } from '@angular/core';
import { Auth } from '../../services/auth/auth.service';
import { ModelsService } from '../../services/models/models.service';
import { CloudService } from '../../services/cloud/cloud.service';

@Component({
    selector: 'cad',
    template: require('./cad.component.html'),
    styles: [require('./cad.component.scss')],
})

export class CadComponent {

    public showInfo: boolean = false;
    public loadCloudRequested: boolean = false;
    public importCloudRequested: boolean = false;
    public saveCloudRequested: boolean = false;

    public cloudName: string = '';

    constructor(private auth: Auth, private model: ModelsService, public cloud: CloudService) {
    }

    public openedFileChanged(fileInput: any) {
        this.model.openFile(fileInput.target.files[0]);
        fileInput.target.value = '';
    }

    public addedFileChanged(fileInput: any) {
        this.model.addFile(fileInput.target.files[0]);
        fileInput.target.value = '';
    }

    public saveModels() {
        var models = this.model.saveModels();
        this.cloud.saveModel(this.cloudName, models);
        this.cloudName = '';
    }

    public loadModel(model: string) {
        if (this.loadCloudRequested)
            this.model.openJSON(model);
        else
            this.model.addJSON(model);
    }
}
