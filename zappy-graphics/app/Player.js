import * as THREE from 'three';
import { Model } from '@/app/wrappers/Model';
import { Egg } from '@/app/Egg';
import { DIR } from '@/app/constants';
import { Manager } from '@/app/sound/SoundManager';

export class Player extends Model {
    constructor(map, sceneWrapper, opt = {}) {
        super();

        this.scene = sceneWrapper;
        this.teamName = opt.teamName;
        this.playerId = opt.id || 0;
        this.direction = opt.dir || DIR.S;
        this.coordinates = opt.coordinates || new THREE.Vector2(0, 0);
        this.level = 1;
        this.map = map;
        this.gems = {};
        this.eggs = [];
        this.food = 0;
        this.isFPV = false;

        document.addEventListener("keydown", this.setDirection.bind(this), false, this);
    }

    async initInstance(sceneWrapper) {
        await this.load('static/assets/models/players/robot.glb', sceneWrapper, true);

        this.updatePosition();
        this.setAnimationIndex(2);
        this.getMesh().scale.set(.08, .08, .08);
        this.getMesh().callback = this.getControlPanelInfo.bind(this);
        return this;
    }

    updatePosition() {
        let pos = this.map.getPlayerPositionFromCord(this.coordinates);

        this.getMesh().position.set(pos.x, pos.y, pos.z);
    }

    rotateLeft() {
        this.direction = (this.direction === 0 ? 3 : this.direction - 1);
        this.getMesh().rotation.y -= Math.PI / 2;
    }

    rotateRight() {
        this.direction++;
        this.direction = this.direction % 4;
        this.getMesh().rotation.y += Math.PI / 2;
    }

    moveForward() {
        switch (this.direction) {
            case DIR.N:
                this.coordinates.y -= 1;
                break;
            case DIR.E:
                this.coordinates.x -= 1;
                break;
            case DIR.S:
                this.coordinates.y += 1;
                break;
            case DIR.W:
                this.coordinates.x += 1;
                break;
        }

        Manager.play('click');
        let vec = this.map.getPlayerPositionFromCord(this.coordinates);

        if (this.isFPV) {
            this.getMesh().position.set(vec.x, vec.y, vec.z)
        } else {
            this.setAnimationIndex(10);
            createjs.Tween
                .get(this.getMesh().position, {override : true})
                .to({
                    x: vec.x,
                    y: vec.y,
                    z: vec.z
                }, 150)
                .call(() => this.setAnimationIndex(2));
        }
    }

    setDirection(event) {
        let keyCode = event.which || event.keyCode || event.charCode;

        switch (keyCode) {
            case 68:
                this.rotateLeft();
                break;
            case 81:
                this.rotateRight();
                break;
            case 90:
                this.moveForward();
                break;
            case 67:
                this.ejectAnimation();
                break;
            case 89:
                this.levelUp();
                this.speak();
                break;
        }
        if (this.isFPV)
            document.getElementById('first-person').dispatchEvent(new CustomEvent('update'));
    }

    dropEgg(eggID, scene) {
        let coordinates = { x: this.coordinates.x, z: this.coordinates.y };
        this.playAnimationOnce(9);

        //this.map.addItem(coordinates, 'EGG', scene);
        //this.eggs.push({ eggID, coordinates: this.coordinates });
        // TODO: Animation on fork, like "chie un oeuf'
    }

    ejectAnimation() {
        this.playAnimationOnce(5);
        // TODO: Animation ejecting another player, like "dégage sale cake"
    }

    pickItem(type, scene) {
        //this.playAnimationOnce(1);

        if (this.map.deleteItem({ x: this.coordinates.x, z: this.coordinates.y }, type, scene)) {
            if (type !== 'FOOD')
                this.gems[type] = this.gems[type] === undefined ? 1 : this.gems[type] + 1
            else
                this.food += 1
        }
    }

    levelUp() {
        this.playAnimationOnce(3);
        this.level++;
        // TODO: Animation on level up
    }

    speak() {
        let planeGeometry1 = new THREE.Plane( new THREE.Vector3( -1, 0, 0 ), this.map.modelSize.x * (this.map.size_x - 0.5) );
        let planeGeometry2 = new THREE.Plane( new THREE.Vector3( 1, 0, 0 ), 0.5);
        let planeGeometry3 = new THREE.Plane( new THREE.Vector3( 0, 0, -1 ), this.map.modelSize.z * (this.map.size_z - 0.5) );
        let planeGeometry4 = new THREE.Plane( new THREE.Vector3( 0, 0, 1 ), 0.5);
        let groundMaterial = new THREE.MeshStandardMaterial( {
            color: 0xffffff,
            clippingPlanes: [ planeGeometry1, planeGeometry2, planeGeometry3, planeGeometry4 ],
        } );
        let objectGeometry = new THREE.TorusBufferGeometry( 1, 0.01, 6, 28 );
        objectGeometry.rotateX(Math.PI / 2);
        let mesh = new THREE.Mesh( objectGeometry, groundMaterial );

        mesh.position.set( this.getMesh().position.x, this.getMesh().position.y, this.getMesh().position.z);
        createjs.Tween
            .get(mesh.scale, {override : true})
            .to({
                x: this.map.size_x * this.map.size_z * .15,
                y: 5,
                z: this.map.size_x * this.map.size_z * .15,
            }, this.map.size_x * this.map.size_z * 13)
            .call(() => {
                mesh.geometry.dispose();
                mesh.material.dispose();
                this.scene.getScene().remove(mesh);
            });

        console.log("je suis un pute");
        this.scene.getScene().add( mesh );
    }

    getControlPanelInfo() {
        let list = document.getElementById('items');
        let info = document.getElementById('info');
        let fpv = document.getElementById('first-person');

        let tmp = `<p>ID: <i>${ this.playerId }</i></p>`;
        tmp += `<p>Team: <i>${ this.teamName }</i></p>`;
        tmp += `<p>Level: <i>${ this.level }</i></p>`;
        tmp += `<p>Food: <i>${ this.food }</i></p>`;
        tmp += `<p>Inventory:</p>`;

        info.innerHTML = tmp;

        list.innerHTML = '';
        Object.keys(this.gems).map(e => {
            list.innerHTML += `<li>${e.toLowerCase()}: ${this.gems[e].toString()}</li>`
        });

        fpv.style.display = 'block';
        fpv.setAttribute('name', this.playerId);
    }
}