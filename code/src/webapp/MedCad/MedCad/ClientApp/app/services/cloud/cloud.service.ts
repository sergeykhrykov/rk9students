import { Injectable } from '@angular/core';

@Injectable()
export class CloudService {

    public models: any = [];

    constructor() {
        var blah = localStorage.getItem('models')
        if (blah) {
            this.models = JSON.parse(blah);
        }
        else
            this.models = [];
    }

    public saveModel(name: string, json: string) {
        this.models.push({ name: name, value: json });
        localStorage.setItem('models', JSON.stringify(this.models));
    }
}