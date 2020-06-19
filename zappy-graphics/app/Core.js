import * as THREE from 'three';
import { Scene } from '@/app/wrappers/Scene';
import { Item } from '@/app/Item';
import { Map } from '@/app/Map';
import { DIR } from '@/app/constants';
import { Manager, SoundRef } from '@/app/sound/SoundManager';
import { PlayerManager } from '@/app/PlayerManager';
import { Queue } from '@/app/wrappers/Queue'
import { Server } from '@/app/server/index'
import { Sky } from 'three/examples/jsm/objects/Sky';

export class Core {
    constructor(opt = {}) {
        this.sceneWrapper = new Scene('white');
        this.map = new Map(opt.mapSize || {x: 20, z: 20});
        this.playerManager = new PlayerManager;
        this.messageQueue = new Queue;


        Server.on('message', (message) => this.messageQueue.enqueue(message));

        window.addEventListener('click', this.onDocumentMouseDown.bind(this), false);

        document.getElementById('mute').addEventListener('click', this.toggleSound.bind(this));
        document.getElementById('first-person').addEventListener('click', this.setFirstPersonView.bind(this));
        document.getElementById('first-person').addEventListener('update', this.setFirstPersonView.bind(this));

        this.playerManager.addTeam('la cité en i', 5);
        this.playerManager.addTeam('ah', 5);
        // Manager.register(
        //     'ambient',
        //     new SoundRef('static/assets/audio/ambient.mp3', { loop: true, fadeIn: true, volume: .2 }),
        //     e => e.src === 'static/assets/audio/ambient.mp3' ? Manager.play('ambient') : null
        // );

        Manager.register(
            'click',
            new SoundRef(['static/assets/audio/click.ogg', 'static/assets/audio/click2.ogg'], { random: true, streamsLimit: 2 })
        );

        (async () => {
            await this.map.generate(this.sceneWrapper);

            await Item.init(this.sceneWrapper);

            await this.playerManager.addPlayerInTeam({coordinates: { x: 0, y: 0 }, id: 1}, 'ah', this.sceneWrapper, this.map);
            let player2 = await this.playerManager.addPlayerInTeam({coordinates: { x: 1, y: 0 }, id: 2}, 'ah', this.sceneWrapper, this.map);

            let player1 = this.playerManager.getPlayerById(1);

            //console.log(this.playerManager.getPlayerById(1))


            this.map.addItem({x: 0, z: 0}, 'MENDIANE', this.sceneWrapper);
            this.map.addItem({x: 0, z: 0}, 'MENDIANE', this.sceneWrapper);
            this.map.addItem({x: 0, z: 0}, 'MENDIANE', this.sceneWrapper);
            this.map.addItem({x: 0, z: 0}, 'SIBUR', this.sceneWrapper);
            this.map.addItem({x: 0, z: 0}, 'PHIRAS', this.sceneWrapper);
            this.map.addItem({x: 0, z: 0}, 'PHIRAS', this.sceneWrapper);
            this.map.addItem({x: 0, z: 0}, 'PHIRAS', this.sceneWrapper);
            this.map.addItem({x: 0, z: 0}, 'LINEMATE', this.sceneWrapper);
            this.map.addItem({x: 0, z: 0}, 'THYSTAME', this.sceneWrapper);
            this.map.addItem({x: 0, z: 0}, 'THYSTAME', this.sceneWrapper);
            this.map.addItem({x: 0, z: 0}, 'DERAUMERE', this.sceneWrapper);
            this.map.addItem({x: 0, z: 0}, 'FOOD', this.sceneWrapper);
            this.map.addItem({x: 0, z: 0}, 'FOOD', this.sceneWrapper);
            this.map.addItem({x: 0, z: 0}, 'FOOD', this.sceneWrapper);
            this.map.addItem({x: 3, z: 3}, 'FOOD', this.sceneWrapper);

            player1.pickItem('LINEMATE', this.sceneWrapper);
            player1.pickItem('SIBUR', this.sceneWrapper);
            player1.pickItem('MENDIANE', this.sceneWrapper);
            player1.pickItem('MENDIANE', this.sceneWrapper);
            player1.pickItem('MENDIANE', this.sceneWrapper);
            player1.pickItem('DERAUMERE', this.sceneWrapper);
            player1.pickItem('PHIRAS', this.sceneWrapper);

            player1.dropEgg(this.sceneWrapper);
        })();

        this.initSky();
        this.sceneWrapper.launch();
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
        let player = this.playerManager.getPlayerById(parseInt(e.target.getAttribute('name')));

        console.log(player)
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

        cam.position.set(pos.x, pos.y + .3, pos.z);


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

        let isFPV = this.playerManager.getAllPlayers().filter(player => player.isFPV).length > 0;

        if (intersects.length > 0 && !isFPV) {
            if (typeof intersects[0].object.name === "function")
                intersects[0].object.name();
            else if (intersects[0].object.root && intersects[0].object.root.callback)
                intersects[0].object.root.callback();
        } else {
            //document.getElementById('items').innerHTML = '';
            //document.getElementById('info').innerHTML = '';
            //document.getElementById('fpv').style.display = 'none';
        }
    }

    initSky() {
        let sky = new Sky();

        sky.scale.setScalar(450000);

        let uniforms = sky.material.uniforms;

        uniforms["turbidity"].value = 10;
        uniforms["rayleigh"].value = 2;
        uniforms["mieCoefficient"].value = 0.005;
        uniforms["mieDirectionalG"].value = 0.8;
        uniforms["luminance"].value = 1;

        let theta = Math.PI * ( 0.2256 - 0.5 );
        let phi = 2 * Math.PI * ( 0.2472 - 0.5 );
        let position = {}

        position.x = 400000 * Math.cos( phi );
        position.y = 400000 * Math.sin( phi ) * Math.sin( theta );
        position.z = 400000 * Math.sin( phi ) * Math.cos( theta );

        uniforms["sunPosition"].value.copy( position );

        this.sceneWrapper.getScene().add(sky);
    }
}

