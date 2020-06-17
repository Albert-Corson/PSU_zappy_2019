import * as THREE from '../libs/three/three.module.js'
import { Model } from './wrappers/Model.js'
import { DIR } from './constants.js'
import { PLAYER_TYPE} from "./constants.js";
import { Manager } from './sound/SoundManager.js';

export class Player extends Model {
    constructor(map, opt = {}) {
        super();

        this.teamId = opt.teamId || 1;
        this.playerName = opt.name || "bob";
        this.direction = opt.dir || DIR.S;
        this.coordinates = opt.coordinates || new THREE.Vector2(0, 0);
        this.level = 1;
        this.map = map;
        this.gems = {};

        document.addEventListener("keydown", this.setDirection.bind(this), false, this);
    }

    updatePosition() {
        let pos = this.map.getPositionFromCoord(this.coordinates);

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
        let vec = this.map.getPositionFromCoord(this.coordinates);

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
            case 69:
                this.forkAnimation();
                break;
            case 67:
                this.ejectAnimation();
                break;
            case 89:
                this.levelUp();
                break;
        }
    }

    forkAnimation() {
        this.playAnimationOnce(9);

        // TODO: Animation on fork, like "chie un oeuf'
    }

    ejectAnimation() {
        this.playAnimationOnce(5);
        // TODO: Animation ejecting another player, like "dégage sale cake"
    }

    pickGem(type, scene) {
        //this.playAnimationOnce(1);

        if (this.map.deleteGem({ x: this.coordinates.x, z: this.coordinates.y }, type, scene)) {
            this.gems[type] = this.gems[type] == undefined ? 1 : this.gems[type] + 1
        }
    }

    levelUp() {
        this.playAnimationOnce(3);
        this.level++;
        // TODO: Animation on level up
    }

    getControlPanelInfo() {
        let list = document.getElementById('gems');
        let info = document.getElementById('info');

        let tmp = `<p>Name: <i>${ this.playerName }</i></p>`;
        tmp += `<p>Team: <i>${ this.teamId }</i></p>`;
        tmp += `<p>Level: <i>${ this.level }</i></p>`;
        tmp += `<p>Inventory:</p>`;

        info.innerHTML = tmp;


        list.innerHTML = '';
        Object.keys(this.gems).map(e => {
            list.innerHTML += `<li>${e.toLowerCase()}: ${this.gems[e].toString()}</li>`
        });
    }
}