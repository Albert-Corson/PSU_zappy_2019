import * as THREE from 'three';
import { Scene } from '@/app/wrappers/Scene';
import { Item } from '@/app/Item';
import { Player } from '@/app/Player';
import { Map } from '@/app/Map';
import { DIR } from '@/app/constants';
import { Manager, SoundRef } from '@/app/sound/SoundManager';
import { TeamManager, Team } from '@/app/Team';

import { Sky } from 'three/examples/jsm/objects/Sky';

export class Core {
    constructor(opt = {}) {
        this.sceneWrapper = new Scene('white');
        this.map = new Map({ x: 10, y: 10});
        this.teamManager = new TeamManager;

        window.addEventListener('click', this.onDocumentMouseDown.bind(this), false);

        document.getElementById('mute').addEventListener('click', this.toggleSound.bind(this));
        document.getElementById('first-person').addEventListener('click', this.setFirstPersonView.bind(this));
        document.getElementById('first-person').addEventListener('update', this.setFirstPersonView.bind(this));

        this.teamManager.addTeam('la cité en i', 5);
        this.teamManager.addTeam('ah', 5);
        // Manager.register(
        //     'ambient',
        //     new SoundRef('static/assets/audio/ambient.mp3', { loop: true, fadeIn: true, volume: .2 }),
        //     e => e.src === 'static/assets/audio/ambient.mp3' ? Manager.play('ambient') : null
        // );


        Manager.register(
            'click',
            new SoundRef(['static/assets/audio/click.ogg', 'static/assets/audio/click2.ogg'], { random: true, streamsLimit: 2 })
        );

        let hemiLight = new THREE.HemisphereLight(0xffffff, 0xffffff, 1);//, {x: 0, y: -30, z: 0});
        hemiLight.color.setHSL( 0.6, 1, 0.6 );
        hemiLight.groundColor.setHSL( 0.095, 1, 0.75 );
        hemiLight.position.set( 0, 50, 0 );
        this.sceneWrapper.getScene().add( hemiLight );

        let dirLight = new THREE.DirectionalLight( 0xffffff, 1.6);//0.8 );
        dirLight.color.setHSL( 0.1, 1, 0.95 );
        dirLight.position.set( - 1, 1.75, 1 );
        dirLight.position.multiplyScalar( 30 );
        this.sceneWrapper.getScene().add( dirLight );

/*
        let groundGeo = new THREE.PlaneBufferGeometry( 10000, 10000 );
        let groundMat = new THREE.MeshLambertMaterial( { color: 0xffffff } );
        groundMat.color.setHSL( 0.095, 1, 0.75 );

        let ground = new THREE.Mesh( groundGeo, groundMat );
        ground.position.y = - 33;
        ground.rotation.x = - Math.PI / 2;
        ground.receiveShadow = true;
        this.sceneWrapper.getScene().add( ground );
*/

        /*
        this.sceneWrapper.addLight(new THREE.PointLight(0xffffff, 1.7, 50), {x: 4, y: 20, z: 5});
        */

        (async () => {
            await this.map.generate(this.sceneWrapper);

            await Item.init(this.sceneWrapper);

             await this.teamManager.addPlayerInTeam({coordinates: { x: 0, y: 0 }, id: 1}, 'ah', this.sceneWrapper, this.map);
            let player2 = await this.teamManager.addPlayerInTeam({coordinates: { x: 1, y: 0 }, id: 1}, 'ah', this.sceneWrapper, this.map);

            let player1 = this.teamManager.getPlayerById(1);

            //console.log(this.teamManager.getPlayerById(1))


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

            this.map.addItem({x: 3, z: 3}, 'FOOD', this.sceneWrapper);

            player1.pickItem('LINEMATE', this.sceneWrapper);
            player1.pickItem('SIBUR', this.sceneWrapper);
            player1.pickItem('MENDIANE', this.sceneWrapper);
            player1.pickItem('MENDIANE', this.sceneWrapper);
            player1.pickItem('MENDIANE', this.sceneWrapper);
            player1.pickItem('DERAUMERE', this.sceneWrapper);
            player1.pickItem('PHIRAS', this.sceneWrapper);

            player1.pickItem('FOOD', this.sceneWrapper);
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

        let isFPV = this.teamManager.getAllPlayers().filter(player => player.isFPV).length > 0;

        console.log(isFPV);

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

