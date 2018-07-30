import { Component, OnInit, ElementRef, Input, OnChanges, SimpleChanges } from '@angular/core';
import { ModelsService } from '../../services/models/models.service';

@Component({
    selector: 'workspace',
    template: require('./workspace.component.html'),
    styles: [require('./workspace.component.scss')]
})
export class WorkspaceComponent implements OnInit {

    @Input() public showInfo: boolean;

    constructor(private myElement: ElementRef, public model: ModelsService) {
    }

    ngOnInit() {
        let elem = (<HTMLCollection>this.myElement.nativeElement.children).namedItem('workspace');

        let width = elem.scrollWidth;
        let height = elem.scrollHeight;

        this.model.setResolution(width, height);

        document.querySelector('workspace div.workspace').appendChild(this.model.element);
    }
}
