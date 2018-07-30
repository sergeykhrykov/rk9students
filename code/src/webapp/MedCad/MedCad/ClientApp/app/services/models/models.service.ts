import { Injectable } from '@angular/core';
var THREE = require("three-js")();
var STLLoader = require('three-stl-loader')(THREE);
require('three-editor-controls')(THREE);

@Injectable()
export class ModelsService {

    private meshClass: any;
    private lightClass: any;
    private additionalLightDistance = 10;

    private loader: any;
    private exporter: any;

    private scene: any;
    private camera: any;
    private renderer: any;
    private controls: any;
    private light: any;

    private needResize: any[] = [];

    public objects: number = 0;
    public vertices: number = 0;
    public triangles: number = 0;

    public get element(): any {
        return this.renderer.domElement;
    }

    constructor() {
        this.lightClass = THREE.Light;
        this.meshClass = THREE.Mesh;

        this.loader = new STLLoader();
        this.exporter = new THREE.ObjectLoader();

        let width = 1;
        let height = 1;


        this.camera = new THREE.PerspectiveCamera(45, width / height, 0.1, 1000);
        this.camera.position.x = 5;
        this.camera.position.y = 5;
        this.camera.position.z = 5;
        this.camera.lookAt(new THREE.Vector3(0, 0, 0));

        this.renderer = new THREE.WebGLRenderer();
        this.renderer.setClearColor(0x3b3b3b);
        this.renderer.setSize(width, height);

        this.light = new THREE.SpotLight(0xFFFFFF);
        this.setLightPosition();

        this.scene = new THREE.Scene();
        this.scene.add(this.light);

        this.render();
    }

    public setResolution(width: number, height: number): void {
        var newCam = new THREE.PerspectiveCamera(45, width / height, 0.1, 1000);
        newCam.position.x = this.camera.position.x;
        newCam.position.y = this.camera.position.y;
        newCam.position.z = this.camera.position.z;
        newCam.lookAt(this.scene.position);
        this.camera = newCam;
        this.renderer.setSize(width, height);
        this.controls = new THREE.EditorControls(this.camera, this.renderer.domElement);
        console.log(this.controls);
    }

    public clear(): void {
        this.scene = new THREE.Scene();
        this.scene.add(this.light);
        this.needResize.length = 0;
        this.calculateTrianglesAndVertices();
    }

    public openFile(file: any) {
        let reader = new FileReader();
        let _self = this;
        reader.onload = function () {
            var geometry = _self.loader.parse(reader.result);
            geometry.sourceType = "stl";
            geometry.sourceFile = file.name;

            var color = 0x00ABE7;
            var material = new THREE.MeshLambertMaterial({ color: color, emissive: color });

            var mesh = new THREE.Mesh(geometry, material);
            mesh.name = file.name;

            _self.clear();
            _self.scene.add(mesh);

            _self.calculateTrianglesAndVertices();

            _self.needResize.push(mesh);
        };

        if (reader.readAsBinaryString !== undefined) {
            reader.readAsBinaryString(file);
        } else {
            reader.readAsArrayBuffer(file);
        }
    }

    public saveModels(): string {
        return JSON.stringify(this.scene.toJSON());
    }

    public addFile(file: any) {
        let reader = new FileReader();
        let _self = this;
        reader.onload = function () {
            var geometry = _self.loader.parse(reader.result);
            geometry.sourceType = "stl";
            geometry.sourceFile = file.name;

            var color = 0x00ABE7;
            var material = new THREE.MeshLambertMaterial({ color: color, emissive: color });

            var mesh = new THREE.Mesh(geometry, material);
            mesh.name = file.name;

            _self.scene.add(mesh);

            _self.calculateTrianglesAndVertices();

            _self.needResize.push(mesh);
        };

        if (reader.readAsBinaryString !== undefined) {
            reader.readAsBinaryString(file);
        } else {
            reader.readAsArrayBuffer(file);
        }
    }

    public openJSON(json: string) {
        var result = this.exporter.parse(JSON.parse(json));

        this.clear();
        result.children
            .filter(c => c instanceof this.meshClass)
            .forEach(c => {
                this.scene.add(c);
                this.needResize.push(c);
            });

        this.calculateTrianglesAndVertices();
    }

    public addJSON(json: string) {
        var result = this.exporter.parse(JSON.parse(json));

        result.children
            .filter(c => c instanceof this.meshClass)
            .forEach(c => {
                this.scene.add(c);
                this.needResize.push(c);
            });

        this.calculateTrianglesAndVertices()
    }

    public setView(view: number) {
        var x = 0, y = 0, z = 0;
        switch (view) {
            case 1:
                x = 1;
                break;
            case 2:
                x = -1;
                break;
            case 3:
                z = 1;
                break;
            case 4:
                z = -1;
                break;
            case 5:
                y = 1;
                break;
            case 6:
                y = -1;
                break;
        }

        this.camera.position.x = x;
        this.camera.position.y = y;
        this.camera.position.z = z;
        this.camera.lookAt(new THREE.Vector3(0, 0, 0));

        this.needResize.length = 0;
        this.scene.children
            .filter(c => c instanceof this.meshClass)
            .forEach(c => this.needResize.push(c));
    }

    private recalculateCamera(viewSphere: any) {
        var offsetRadius = Math.sqrt(
            Math.pow(viewSphere.center.x, 2) +
            Math.pow(viewSphere.center.y, 2) +
            Math.pow(viewSphere.center.z, 2));
        var cameraRadius = Math.sqrt(
            Math.pow(this.camera.position.x, 2) +
            Math.pow(this.camera.position.y, 2) +
            Math.pow(this.camera.position.z, 2));
        if (cameraRadius < (viewSphere.radius + offsetRadius)) {
            let coef = 2*((viewSphere.radius + offsetRadius) / cameraRadius);
            this.camera.position.x *= coef;
            this.camera.position.y *= coef;
            this.camera.position.z *= coef;
        }
    }

    private processNewGeometry() {
        var forRecalc = this.needResize.filter(e => !!e.geometry.boundingSphere);
        this.needResize = this.needResize.filter(e => !e.geometry.boundingSphere);
        forRecalc.forEach(m => this.recalculateCamera(m.geometry.boundingSphere));
    }

    private setLightPosition() {
        var prop = Math.sqrt(Math.pow(this.camera.position.x, 2) + Math.pow(this.camera.position.y, 2) + Math.pow(this.camera.position.z, 2));
        var coef = prop == 0 ? 1 : (1 + this.additionalLightDistance / prop)
        this.light.position.set(
            (this.camera.position.x + 0) * coef + 100,
            (this.camera.position.y + 0) * coef + 100,
            (this.camera.position.z + 0) * coef - 100);
    }

    private calculateTrianglesAndVertices(): void {
        this.objects = 0;
        this.vertices = 0;
        this.triangles = 0;

        this.scene.children
            .filter(c => c instanceof this.meshClass)
            .forEach(c => {
                let geometry = c.geometry;
                this.objects++;
                if (geometry.index !== null) {
                    this.vertices += geometry.index.count * 3;
                    this.triangles += geometry.index.count;

                } else {
                    this.vertices += geometry.attributes.position.count;
                    this.triangles += geometry.attributes.position.count / 3;
                }
            })
    }

    private render() {
        this.processNewGeometry();
        this.setLightPosition()
        this.renderer.render(this.scene, this.camera);
        requestAnimationFrame(() => this.render());
    }
}