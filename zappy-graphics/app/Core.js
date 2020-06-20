import * as THREE from 'three';
import { Scene } from '@/app/wrappers/Scene';
import { Item } from '@/app/Item';
import { Map } from '@/app/Map';
import { DIR, FOCUS_ON } from '@/app/constants';
import { Manager, SoundRef } from '@/app/sound/SoundManager';
import { PlayerManager } from '@/app/PlayerManager';
import { Queue } from '@/app/wrappers/Queue'
import { Server } from '@/app/server/index'
import { Sky } from 'three/examples/jsm/objects/Sky';
import {EventDispatcher} from "three";

export class Core extends EventDispatcher {
    constructor(opt = {}) {
        super();
        this.sceneWrapper = new Scene('white');
        this.playerManager = new PlayerManager;
        this.broadcastMessages = [];
        this.map = new Map;

        this.initCommandQueue();
        this.initEventListeners();
        this.initControlPanel();
        this.initSoundManager();
        this.initSky();

        this.sceneWrapper.launch();
    }

    initSoundManager() {
        /*
        Manager.register(
            'ambient',
            new SoundRef('static/assets/audio/ambient.mp3', { loop: true, fadeIn: true, volume: .2 }),
            e => e.src === 'static/assets/audio/ambient.mp3' ? Manager.play('ambient') : null
        );
         */

        Manager.register(
            'click',
            new SoundRef(['static/assets/audio/click.ogg', 'static/assets/audio/click2.ogg'], { random: true, streamsLimit: 2 })
        );
    }

    initControlPanel() {
        document.getElementById('info').innerText = 'No item selected';
        document.getElementById('settings-content').style.display = 'block';
    }

    initCommandQueue() {
        this.messageQueue = new Queue;
        this.mapCommand = this.getMapCommand();

        this.messageQueue.enqueue({ promise: async () => this.map.loadBlock(this.sceneWrapper), args: null });
        this.messageQueue.enqueue({ promise: async () => Item.init(this.sceneWrapper), args: null });

        Server.on('message',  (message) => {
            let cmd = message.split(' ');

            if (cmd && this.mapCommand[cmd[0]])
                this.messageQueue.enqueue({ promise: this.mapCommand[cmd[0]], args: cmd.slice(1) });
        });
    }

    initEventListeners() {
        window.addEventListener('click', this.onDocumentMouseDown.bind(this), false);
        document.getElementById('mute').addEventListener('click', this.toggleSound.bind(this));
        document.getElementById('volume').addEventListener('change', this.changeVolume.bind(this));
        document.getElementById('first-person').addEventListener('click', this.setFirstPersonView.bind(this));
        document.getElementById('first-person').addEventListener('update', this.setFirstPersonView.bind(this));
    }

    changeVolume(e) {
        Manager.globalVolume = e.target.value;
    }

    toggleSound(e) {
        let muteToggle = e.target;
        let slider = document.getElementById('volume');
        let icon = muteToggle.className.split(' ')[1];

        muteToggle.classList.remove(icon);

        let state = icon.split('-');
        let oldState = state.pop();
        state.push(oldState === 'up' ? 'off' : 'up');

        let className = state.join('-');
        muteToggle.classList.add(className);

        Manager.muted = oldState === 'up';

        if (Manager.muted)
            slider.setAttribute('disabled', '');
        else
            slider.removeAttribute('disabled')
    }

    resetFPVMode(player) {
        let cam = this.sceneWrapper.camera;
        let old = this.oldCameraSettings;

        player.isFPV = false;

        cam.rotation.set(old.rotation.x, old.rotation.y, old.rotation.z);
        cam.position.set(old.position.x, old.position.y, old.position.z);
        cam.updateProjectionMatrix();

        this.sceneWrapper.controls.enabled = true;
        this.sceneWrapper.launch();
    }

    setFirstPersonView(e) {
        let player = this.playerManager.getPlayerById(parseInt(e.target.getAttribute('name')));

        if (!player)
            return;

        let cam = this.sceneWrapper.camera;

        if (player.isFPV && e.type === 'click') {
            this.resetFPVMode(player);
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
            cam.position.z = cam.position.z + (player.direction !== DIR.N ? +.05 : -.05);
        else
            cam.position.x = cam.position.x + (player.direction !== DIR.W ? +.05 : -.05);

        cam.rotation.set(rotation.x, rotation.y - Math.PI, rotation.z);

        cam.updateProjectionMatrix();
    }

    displayUserMessage() {
        let list = document.getElementById('messages-list');

        let tmp = '';

        [...this.broadcastMessages].reverse().map(elem => {
            tmp += `<li class="list-group-item">Player ${elem.playerID} said: ${elem.message}</li>`
        });
        list.innerHTML = tmp;
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
            if (typeof intersects[0].object.name === "function") {
                FOCUS_ON.id = 'block';
                intersects[0].object.name();
            } else if (intersects[0].object.root && intersects[0].object.root.callback) {
                FOCUS_ON.id = intersects[0].object.root.name;
                intersects[0].object.root.callback();
            }
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
        let position = {};

        position.x = 400000 * Math.cos( phi );
        position.y = 400000 * Math.sin( phi ) * Math.sin( theta );
        position.z = 400000 * Math.sin( phi ) * Math.cos( theta );

        uniforms["sunPosition"].value.copy( position );

        this.sceneWrapper.getScene().add(sky);
    }

    getMapCommand() {
        return {
            'map_size': async (list) => {
                if (list.length === 2)
                    return this.map.generate({ x: parseInt(list[1]), z: parseInt(list[0])}, this.sceneWrapper);
            },
            'new_item': async (list) => {
                if (list.length === 3)
                    return this.map.addItem({x: parseInt(list[2]), z: parseInt(list[1])}, list[0].toUpperCase(), this.sceneWrapper)
            },
            'new_team': async (list) => {
                if (list.length === 2)
                    return this.playerManager.addTeam(list[1], parseInt(list[0]))
            },
            'new_player': async (list) => {
                console.log('new player');
                if (list.length !== 5)
                    return;
                let playerOpt = {
                    coordinates: { x: parseInt(list[3]), y: parseInt(list[2]) },
                    id: parseInt(list[0]),
                    dir: parseInt(list[1]),
                };

                console.log(playerOpt.dir);

                return this.playerManager.addPlayerInTeam(playerOpt, list[4], this.sceneWrapper, this.map);
            },
            'new_egg': async (list) => {
                if (list.length === 4)
                    return this.playerManager.playerDropEgg(
                        { x: parseInt(list[2]), z: parseInt(list[1])},
                        parseInt(list[0]),
                        this.map,
                        this.sceneWrapper,
                        parseInt(list[3])
                    );
            },
            'inventory': async (list) => {
                if (list.length >= 1)
                    return this.playerManager.getPlayerById(parseInt(list[0])).updateInventory(list.slice(1))
            },
            'hatched': async (list) => {
                if (list.length === 1)
                    return this.playerManager.hatchEgg(parseInt(list[0]), this.map, this.sceneWrapper)
            },
            'died': async (list) => {
                if (list.length === 1)
                    return this.playerManager.deletePlayerInTeam(parseInt(list[0]), this.sceneWrapper, this.resetFPVMode.bind(this))
            },
            'win': null, //to do paillette de fou furieux
            'elevation_start': async (list) => {
                if (list.length === 1)
                    return this.playerManager.getPlayerById(parseInt(list[0])).elevationStart()
            },
            'elevation_end': async (list) => {
                if (list.length === 1)
                    return this.playerManager.getPlayerById(parseInt(list[0])).elevationFinish()
            },
            'drop': async (list) => {
                if (list.length === 2)
                    return this.playerManager.getPlayerById(parseInt(list[0])).dropItem(list[1].toUpperCase(), this.sceneWrapper)
            }, //do the function
            'take': async (list) => {
                if (list.length === 2)
                    return this.playerManager.getPlayerById(parseInt(list[0])).pickItem(list[1].toUpperCase(), this.sceneWrapper)
            },
            'broadcast': async (list) => {
                if (list.length === 2) {
                    this.broadcastMessages.push({ message: list[1], playerID: parseInt(list[0]) });

                    if (this.broadcastMessages.length > 5)
                        this.broadcastMessages.splice(0, 1);

                    this.displayUserMessage();
                    return this.playerManager.getPlayerById(parseInt(list[0])).speak()
                }
            }, //add text
            'eject': async (list) => {
                if (list.length === 2)
                    return this.playerManager.getPlayerById(parseInt(list[0])).ejectAnimation()
            },
            'move': async (list) => {
                if (list.length === 4)
                    return this.playerManager.getPlayerById(parseInt(list[0])).move({x: parseInt(list[3]), y: parseInt(list[2])}, parseInt(list[1]))
            },
            'forward': async (list) => {
                if (list.length === 1)
                    return this.playerManager.getPlayerById(parseInt(list[0])).moveForward()
            },
            'left': async (list) => {
                if (list.length === 1)
                    return this.playerManager.getPlayerById(parseInt(list[0])).rotateLeft()
            },
            'right': async (list) => {
                if (list.length === 1)
                    return this.playerManager.getPlayerById(parseInt(list[0])).rotateRight()
            },
        };
    }
}

