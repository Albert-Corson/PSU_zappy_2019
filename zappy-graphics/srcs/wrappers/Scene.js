import * as THREE from '../../libs/three.module.js'
import { OrbitControls } from "../../libs/OrbitControls.js";

export class Scene {
    constructor(color = 'black', width = window.innerWidth, height = window.innerHeight) {
        this.scene = new THREE.Scene();
        this.renderer = new THREE.WebGLRenderer({ antialias: true });
        this.camera = new THREE.PerspectiveCamera(75, width / height, 0.1, 1000);
        this.controls = new OrbitControls(this.camera, this.renderer.domElement);
        this.clock = new THREE.Clock();
        this.lights = [];
        this.mixers = [];

        this.camera.position.set(8, 10, 20);
        this.controls.update();

        this.scene.background = new THREE.Color(color);

        this.renderer.setSize(width, height);
        document.body.appendChild(this.renderer.domElement);

        window.addEventListener( 'resize', () => {
            this.camera.aspect = window.innerWidth / window.innerHeight;
            this.camera.updateProjectionMatrix();

            this.renderer.setSize(window.innerWidth, window.innerHeight);
        });
    }

    getScene() {
        return this.scene;
    }

    launch() {
        const animate = () => {
            requestAnimationFrame(animate);

            if (this.controls.enabled)
                this.controls.update();
            let mixerUpdateDelta = this.clock.getDelta();

            // Update the animation mixer, the stats panel, and render this frame
            for (let mixer of this.mixers) {
                mixer.update(mixerUpdateDelta);
            }
            this.renderer.render(this.scene, this.camera);
        };
        animate();
    }

    addLight(light, position = {x: 0, y: 0, z: 0}) {
        light.position.set(position.x, position.y, position.z);

        this.scene.add(light);
        this.lights.push(light);
    }

    addMixer(mixer) {
        this.mixers.push(mixer);
    }
}