import * as THREE from '../build/three.module.js';

export class Scene {
    constructor(color, width, height) {
        this.scene = new THREE.Scene();
        this.camera = new THREE.PerspectiveCamera(75, width / height, 0.1, 1000);
        this.renderer = new THREE.WebGLRenderer();

        this.scene.background = new THREE.Color(color);

        this.renderer.setSize(width, height);
        document.body.appendChild(this.renderer.domElement);
    }

    add(elem) {
        this.scene.add(elem);
    }

    render() {
        this.renderer.render(this.scene, this.camera);
    }
}