import * as THREE from "../Libs/Three/three.module.js"
import { Scene } from './wrappers/Scene.js';
import { Model } from './wrappers/Model.js';
import { Gem } from './Gem.js';
import { Player } from './Player.js';
import { Map } from './Map.js';

import { GEM_TYPE, PLAYER_TYPE } from "./constants.js";

export class Core {
    constructor(opt = {}) {
        this.sceneWrapper = new Scene('white');
        this.map = new Map({ x: 10, y: 10});

        (async () => {
            await Gem.init(this.sceneWrapper)
            let gem = new Gem('LINEMATE', this.sceneWrapper);
        })();

       /* (async () => {
            await Player.init(this.sceneWrapper)
 /!*           let player1 = new Player('ROBOT', this.sceneWrapper);
 *!/           /!*let player1 = new Player('ROBOT', this.sceneWrapper, {coordinates: { x: 0, y: 1 }})*!/
        })();
*/
        this.sceneWrapper.addLight(new THREE.HemisphereLight(0xffffff, 0xffffff, 1.5), {x: 0, y: 40, z: 0});
        this.sceneWrapper.addLight(new THREE.PointLight(0xebe3ce, 1.5, 50), {x: 10, y: 10, z: 10});

        (async () => await this.map.generate(this.sceneWrapper))();

        this.sceneWrapper.launch();
        this.generatePlayer();
    }

    async generatePlayer() {
        let robot = new Player(this.map.getPositionFromCoord.bind(this.map));

        await robot.load('../models/players/robot.glb', this.sceneWrapper, true);
        robot.setAnimationIndex(2);
        robot.getMesh().scale.set(0.3, 0.3, 0.3);
/*
        let pos = this.map.getPositionFromCoord(10, 0);

        if (pos) {
            robot.getMesh().position.set(pos.x, pos.y, pos.z);
        } else {
            console.error('Invalid coordinates')
        }
    */}
}