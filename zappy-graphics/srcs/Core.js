import * as THREE from "../THREE/three.module.js"
import { Scene } from './Wrappers/Scene.js';
import { Model } from './Wrappers/Model.js';

export class Core {
    constructor() {
        this.sceneWrapper = new Scene('white');

        this.sceneWrapper.addLight(new THREE.PointLight(0xebe3ce, 5, 50), {x: 10, y: 10, z: 10});

        this.sceneWrapper.launch();

        this.generateMap({x: 10, y: 10});

        this.generatePlayer();
    }

    async generateMap(coordinates) {
        let { x, y } = coordinates;
        let first = true;

        let block = new Model;
        await block.load('../models/block.glb', this.sceneWrapper);

        let modelSize = block.getSize();

        let rangeY = Array(y).fill(0).map((a, i) => i - y / 2);
        let rangeX = Array(x).fill(0).map((a, i) => i - x / 2);

        for (let j of rangeY) {
            for (let i of rangeX) {
                if (first) {
                    block.getMesh().position.set(Number(i) * (modelSize.x + 0.1), -modelSize.z, Number(j) * (modelSize.y + 0.1));
                } else {
                    let copy = new Model({scene: this.sceneWrapper, mesh: block.getMesh()});
                    copy.getMesh().position.set(Number(i) * (modelSize.x + 0.1), -modelSize.z, Number(j) * (modelSize.y + 0.1));
                }
                first = false;
            }
        }
    }

    async generatePlayer() {
        let robot = new Model;

        await robot.load('../models/robot.glb', this.sceneWrapper);
        robot.setAnimationIndex(0);
        robot.getMesh().scale.set(0.3, 0.3, 0.3);
        robot.getMesh().translateY(-0.07);
    }
}