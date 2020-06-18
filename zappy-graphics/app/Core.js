import * as THREE from 'three';
import { Scene } from '@/app/wrappers/Scene';
import { Gem } from '@/app/Gem';
import { Player } from '@/app/Player';
import { Map } from '@/app/Map';
import { DIR } from '@/app/constants';
import { Manager, SoundRef } from '@/app/sound/SoundManager';

export class Core {
    constructor(opt = {}) {
        this.sceneWrapper = new Scene('white');
        this.map = new Map({ x: 10, y: 10});
        this.players = [];


        window.addEventListener('click', this.onDocumentMouseDown.bind(this), false);
        window.addEventListener('mousemove', this.onDocumentMouseMove.bind(this), false);

        document.getElementById('mute').addEventListener('click', this.toggleSound.bind(this));
        document.getElementById('first-person').addEventListener('click', this.setFirstPersonView.bind(this));
        document.getElementById('first-person').addEventListener('update', this.setFirstPersonView.bind(this));

        // Manager.register(
        //     'ambient',
        //     new SoundRef('static/assets/audio/ambient.mp3', { loop: true, fadeIn: true, volume: .2 }),
        //     e => e.src === 'static/assets/audio/ambient.mp3' ? Manager.play('ambient') : null
        // );

        Manager.register(
            'click',
            new SoundRef(['static/assets/audio/click.ogg', 'static/assets/audio/click2.ogg'], { random: true, streamsLimit: 2 })
        );


        this.sceneWrapper.addLight(new THREE.HemisphereLight(0xffffff, 0x000000, 3), {x: 0, y: -30, z: 0});
        this.sceneWrapper.addLight(new THREE.PointLight(0xffffff, 1.7, 50), {x: 4, y: 20, z: 5});

        (async () => {
            await this.map.generate(this.sceneWrapper);

            await Gem.init(this.sceneWrapper);

            let player1 = await this.addPlayer({ x: 0, y: 0 }, 1);
            player1.getMesh().callback = player1.getControlPanelInfo.bind(player1);
            let player2 = await this.addPlayer({ x: 0, y: 1 }, 2);
            player2.getMesh().callback = player2.getControlPanelInfo.bind(player2);

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
            player1.pickGem('LINEMATE', this.sceneWrapper);
            player1.pickGem('SIBUR', this.sceneWrapper);
            player1.pickGem('MENDIANE', this.sceneWrapper);
            player1.pickGem('MENDIANE', this.sceneWrapper);
            player1.pickGem('MENDIANE', this.sceneWrapper);
            player1.pickGem('DERAUMERE', this.sceneWrapper);
            player1.pickGem('PHIRAS', this.sceneWrapper);

            this.players.push(player1);
            this.players.push(player2);
        })();


        this.sceneWrapper.launch();
    }

    async addPlayer(coordinates, id) {
        let robot = new Player(this.map, { coordinates, id });

        await robot.load('static/assets/models/players/robot.glb', this.sceneWrapper, true);
        robot.updatePosition();
        robot.setAnimationIndex(2);
        robot.getMesh().scale.set(0.3, 0.3, 0.3);
        return robot;
    }

    toggleSound(e) {
        let muteToggle = e.target;
        let icon = muteToggle.className.split(' ')[1];

        muteToggle.classList.remove(icon);

        let state = icon.split('-');
        let oldState = state.pop();
        state.push(oldState === 'up' ? 'off' : 'up');

        let className = state.join('-');
        muteToggle.classList.add(className);

        Manager.muted = oldState === 'up';
    }

    setFirstPersonView(e) {
        let player = this.getPlayerById(e.target.getAttribute('name'));

        if (!player)
            return;

        let cam = this.sceneWrapper.camera;

        if (player.isFPV && e.type === 'click') {
            let old = this.oldCameraSettings;

            player.isFPV = false;

            cam.rotation.set(old.rotation.x, old.rotation.y, old.rotation.z);
            cam.position.set(old.position.x, old.position.y, old.position.z);
            cam.updateProjectionMatrix();

            this.sceneWrapper.controls.enabled = true;
            this.sceneWrapper.launch();
            return;
        }

        if (!player.isFPV) {
            this.oldCameraSettings = {
                rotation: {...this.sceneWrapper.camera.rotation},
                position: {...this.sceneWrapper.camera.position}
            };
        }

        player.isFPV = true;
        this.sceneWrapper.controls.enabled = false;



        let pos = player.getMesh().position;
        let rotation = player.getMesh().rotation;

        cam.position.set(pos.x, pos.y + .7, pos.z);


        if (player.direction === DIR.N || player.direction === DIR.S)
            cam.position.z =  cam.position.z + (player.direction === DIR.N ? -.30 : .30);
        else
            cam.position.x =  cam.position.x + (player.direction === DIR.E ? -.30 : .30);

        cam.rotation.set(rotation.x, rotation.y - Math.PI, rotation.z);

        cam.updateProjectionMatrix();
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

        let isFPV = this.players.filter(player => player.isFPV).length > 0;

        console.log(isFPV);

        if (intersects.length > 0 && !isFPV) {
            if (typeof intersects[0].object.name === "function")
                intersects[0].object.name();
            else if (intersects[0].object.root && intersects[0].object.root.callback)
                intersects[0].object.root.callback();
        } else {
            //document.getElementById('gems').innerHTML = '';
            //document.getElementById('info').innerHTML = '';
            //document.getElementById('fpv').style.display = 'none';
        }
    }

    getPlayerById(id) {
        let arr = this.players.filter(player => {
            return player.playerId === parseInt(id);
        });

        return arr.length ? arr[0] : null;
    }

    onDocumentMouseMove(event) {
        let raycaster = new THREE.Raycaster();
        let mouse = new THREE.Vector2();

        event.preventDefault();
        mouse.x = (event.clientX / this.sceneWrapper.renderer.domElement.clientWidth) * 2 - 1;
        mouse.y = -(event.clientY / this.sceneWrapper.renderer.domElement.clientHeight) * 2 + 1;
        raycaster.setFromCamera(mouse, this.sceneWrapper.camera);

        let intersects = raycaster.intersectObjects(this.map.blocks.map(model => model.mesh.children[0]));


        let isFPV = this.players.filter(player => player.isFPV).length > 0;

        if (intersects.length === 0 || intersects[0].object.twin || isFPV)
            return;

        //if (typeof intersects[0].object.name === "function")
        //intersects[0].object.name();

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