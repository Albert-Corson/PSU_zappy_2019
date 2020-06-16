import * as THREE from "../Libs/Three/three.module.js"
import { Scene } from './wrappers/Scene.js';
import { Gem } from './Gem.js';
import { Player } from './Player.js';
import { Map } from './Map.js';
import { Manager, SoundRef } from './sound/SoundManager.js';
import { GEM_TYPE, PLAYER_TYPE } from "./constants.js";

export class Core {
    constructor(opt = {}) {
        this.sceneWrapper = new Scene('white');
        this.map = new Map({ x: 10, y: 10});

        (async () => {
            await Gem.init(this.sceneWrapper)
            let gem = new Gem('LINEMATE', this.sceneWrapper);
        })();

        Manager.register(
            'ambient',
            new SoundRef('../sounds/ambient.mp3', { loop: true, fadeIn: true, volume: .2 }),
            e => e.src === '../sounds/ambient.mp3' ? Manager.play('ambient') : null
        );

        Manager.register(
            'click',
            new SoundRef(['../sounds/click.ogg', '../sounds/click2.ogg'], { random: true })
        );


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
    }
}