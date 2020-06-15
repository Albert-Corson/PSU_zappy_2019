import * as THREE from "../THREE/three.module.js"
import { Scene } from './wrappers/Scene.js';
import { Model } from './wrappers/Model.js';
import { Gem } from './Gem.js';
import { Player } from './Player.js';
import { Map } from './Map.js';

export class Core {
    constructor(opt = {}) {
        this.sceneWrapper = new Scene('white');
        this.map = new Map({ x: 10, y: 10});

        (async () => await Gem.init(this.sceneWrapper))();

        (async () => {
            await Player.init(this.sceneWrapper)
            let player1 = new Player('ROBOT', this.sceneWrapper, {coordinates: { x: 0, y: 1 }})
        })();

        this.sceneWrapper.addLight(new THREE.HemisphereLight(0xffffff, 0xffffff, 1.5), {x: 0, y: 40, z: 0});
        this.sceneWrapper.addLight(new THREE.PointLight(0xebe3ce, 1.5, 50), {x: 10, y: 10, z: 10});


        (async () => await this.map.generate(this.sceneWrapper))();


        this.sceneWrapper.launch();
    }

    async generatePlayer() {
        let robot = new Model;

        await robot.load('../models/robot.glb', this.sceneWrapper, true);
        robot.setAnimationIndex(2);
        robot.getMesh().scale.set(0.3, 0.3, 0.3);

        let pos = this.map.getPositionFromCoord(10, 0);

        if (pos) {
            robot.getMesh().position.set(pos.x, pos.y, pos.z);
        } else {
            console.error('Invalid coordinates')
        }
    }
}