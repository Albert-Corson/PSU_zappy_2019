import * as THREE from "../libs/three/three.module.js"
import { Scene } from './wrappers/Scene.js';
import { Gem } from './Gem.js';
import { Player } from './Player.js';
import { Map } from './Map.js';
import { Manager, SoundRef } from './sound/SoundManager.js';

export class Core {
    constructor(opt = {}) {
        this.sceneWrapper = new Scene('white');
        this.map = new Map({ x: 10, y: 10});
        this.players = [];

        let muteToggle = document.getElementById('mute');

        window.addEventListener('click', this.onDocumentMouseDown.bind(this), false);
        window.addEventListener('mousemove', this.onDocumentMouseMove.bind(this), false);

        muteToggle.addEventListener('click', () => {
            let icon = muteToggle.className.split(' ')[1];

            muteToggle.classList.remove(icon);

            let state = icon.split('-');
            let oldState = state.pop();
            state.push(oldState === 'up' ? 'off' : 'up');

            let className = state.join('-');
            muteToggle.classList.add(className);

            Manager.muted = oldState === 'up';
        });

        Manager.register(
            'ambient',
            new SoundRef('../sounds/ambient.mp3', { loop: true, fadeIn: true, volume: .2 }),
            e => e.src === '../sounds/ambient.mp3' ? Manager.play('ambient') : null
        );

        Manager.register(
            'click',
            new SoundRef(['../sounds/click.ogg', '../sounds/click2.ogg'], { random: true, streamsLimit: 2 })
        );


        this.sceneWrapper.addLight(new THREE.HemisphereLight(0xffffff, 0x000000, 3), {x: 0, y: -30, z: 0});
        this.sceneWrapper.addLight(new THREE.PointLight(0xffffff, 1.7, 50), {x: 4, y: 20, z: 5});

        (async () => {
            await this.map.generate(this.sceneWrapper);

            await Gem.init(this.sceneWrapper);
            let player = await this.addPlayer({ x: 0, y: 0 });
            player.getMesh().callback = player.getControlPanelInfo.bind(player);

            this.map.addGem({x: 0, z: 0}, 'MENDIANE', this.sceneWrapper);
            this.map.addGem({x: 0, z: 0}, 'MENDIANE', this.sceneWrapper);
            this.map.addGem({x: 0, z: 0}, 'MENDIANE', this.sceneWrapper);
            this.map.addGem({x: 0, z: 0}, 'SIBUR', this.sceneWrapper);
            this.map.addGem({x: 0, z: 0}, 'PHIRAS', this.sceneWrapper);
            this.map.addGem({x: 0, z: 0}, 'PHIRAS', this.sceneWrapper);
            this.map.addGem({x: 0, z: 0}, 'PHIRAS', this.sceneWrapper);
            this.map.addGem({x: 0, z: 0}, 'LINEMATE', this.sceneWrapper);
            this.map.addGem({x: 0, z: 0}, 'THYSTAME', this.sceneWrapper);
            this.map.addGem({x: 0, z: 0}, 'THYSTAME', this.sceneWrapper);
            this.map.addGem({x: 0, z: 0}, 'DERAUMERE', this.sceneWrapper);
            player.pickGem('LINEMATE', this.sceneWrapper);
            player.pickGem('SIBUR', this.sceneWrapper);
            player.pickGem('MENDIANE', this.sceneWrapper);
            player.pickGem('MENDIANE', this.sceneWrapper);
            player.pickGem('MENDIANE', this.sceneWrapper);
            player.pickGem('DERAUMERE', this.sceneWrapper);
            player.pickGem('PHIRAS', this.sceneWrapper);

            this.players.push(player);
        })();


        this.sceneWrapper.launch();
    }

    async addPlayer(coordinates) {
        let robot = new Player(this.map, { coordinates });

        await robot.load('../models/players/robot.glb', this.sceneWrapper, true);
        robot.updatePosition();
        robot.setAnimationIndex(2);
        robot.getMesh().scale.set(0.3, 0.3, 0.3);
        return robot;
    }

    onDocumentMouseDown(event) {
        let raycaster = new THREE.Raycaster();
        let mouse = new THREE.Vector2();

        event.preventDefault();
        mouse.x = (event.clientX / this.sceneWrapper.renderer.domElement.clientWidth) * 2 - 1;
        mouse.y = -(event.clientY / this.sceneWrapper.renderer.domElement.clientHeight) * 2 + 1;
        raycaster.setFromCamera(mouse, this.sceneWrapper.camera);

        let intersects = raycaster.intersectObjects([
            ...this.map.blocks.map(model => model.mesh.children[0]),
            ...this.sceneWrapper.getScene().children
        ]);

        if (intersects.length > 0) {
            if (typeof intersects[0].object.name === "function")
                intersects[0].object.name();
            else if (intersects[0].object.root && intersects[0].object.root.callback)
                intersects[0].object.root.callback();
        } else {
            document.getElementById('gems').innerHTML = '';
            document.getElementById('info').innerHTML = '';
        }
    }

    onDocumentMouseMove(event) {
        let raycaster = new THREE.Raycaster();
        let mouse = new THREE.Vector2();

        event.preventDefault();
        mouse.x = (event.clientX / this.sceneWrapper.renderer.domElement.clientWidth) * 2 - 1;
        mouse.y = -(event.clientY / this.sceneWrapper.renderer.domElement.clientHeight) * 2 + 1;
        raycaster.setFromCamera(mouse, this.sceneWrapper.camera);

        let intersects = raycaster.intersectObjects(this.map.blocks.map(model => model.mesh.children[0]));

        if (intersects.length === 0 || intersects[0].object.twin)
            return;

        if (typeof intersects[0].object.name === "function")
            intersects[0].object.name();

        intersects[0].object.twin = true;
        new createjs.Tween.get(intersects[0].object.scale).to({
            x: 0.009,
            y: 0.009,
        }, 200).call(() => {
            new createjs.Tween.get(intersects[0].object.scale).to({
                x: 0.01,
                y: 0.01,
            }, 200).call(() => {
                intersects[0].object.twin = false;
            });
        });
    }
}