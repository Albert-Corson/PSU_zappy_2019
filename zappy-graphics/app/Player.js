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
        this.playerId = opt.id;
        this.direction = opt.dir;
        this.coordinates = opt.coordinates;
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

    updateInventory(list) {
        let keys = [];
        let properties = [];

        list.map((word, i) => {
            if ((i % 2) === 0)
                keys.push(word);
            else
                properties.push(word);
        });

        keys.map((key, i) => {
            let nb = parseInt(properties[i]);
            if (key.toUpperCase() === 'FOOD')
                this.food = nb;
            else
                this.gems[key.toUpperCase()] = nb;
        });

        this.getControlPanelInfo();
    }

    updatePosition() {
        let pos = this.map.getPlayerPositionFromCord(this.coordinates);

        this.getMesh().position.set(pos.x, pos.y, pos.z);
        this.getMesh().rotation.y = (this.direction - DIR.S) * Math.PI / 2;
    }

    move(coordinates, direction) {
        let pos =  this.map.getPlayerPositionFromCord(coordinates);

        this.direction = direction;
        this.getMesh().rotation.y = (direction - DIR.S) * Math.PI / 2;
        this.playAnimationOnce(3);
        createjs.Tween
            .get(this.getMesh().position, {override : true})
            .to({
                x: pos.x,
                y: pos.y,
                z: pos.z
            }, 150)
    }

    rotateLeft() {
        this.direction = (this.direction === 0 ? 3 : this.direction - 1);
        this.getMesh().rotation.y += Math.PI / 2;
    }

    rotateRight() {
        this.direction++;
        this.direction = this.direction % 4;
        this.getMesh().rotation.y -= Math.PI / 2;
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
                break;
        }
        if (this.isFPV)
            document.getElementById('first-person').dispatchEvent(new CustomEvent('update'));
    }

    ejectAnimation() {
        this.playAnimationOnce(5);
        // TODO: Animation ejecting another player, like "dégage sale cake"
    }

    dropItem(type, scene) {
        //this.playAnimationOnce(1);

        if (this.map.addItem({ x: this.coordinates.x, z: this.coordinates.y }, type, scene)) {
            if (type !== 'FOOD')
                this.gems[type] = this.gems[type] === undefined ? 0 : this.gems[type] - 1
            else
                this.food -= 1
        }
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

    elevationStart() {
        this.setAnimationIndex(0);
    }

    elevationFinish() {
        this.setAnimationIndex(2);
        this.level++;
        this.getControlPanelInfo();
    }

    died() {
        this.playAnimationOnce(1);
        this.getControlPanelInfo(true);
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
        let objectGeometry = new THREE.TorusBufferGeometry( .5, 0.01, 6, 28 );
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

        this.scene.getScene().add( mesh );
    }

    getControlPanelInfo(clear = false) {
        let list = document.getElementById('items');
        let info = document.getElementById('info');
        let fpv = document.getElementById('first-person');

        if (clear) {
            info.innerText = 'No item selected';
            list.innerHTML = '';
            fpv.style.display = 'none';
            return;
        }

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