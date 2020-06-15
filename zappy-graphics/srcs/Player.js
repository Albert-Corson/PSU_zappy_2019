import * as THREE from '../Libs/Three/three.module.js'
import { Model } from './wrappers/Model.js'
import { DIR } from './constants.js'
import { PLAYER_TYPE} from "./constants.js";

export class Player extends Model {
    constructor(ptr, opt = {}) {
        super();

        this.teamId = opt.teamId || 1;
        this.playerName = opt.name || "bob";
        this.direction = opt.dir || DIR.S;
        this.coordinates = opt.coordinates || new THREE.Vector2(0, 0);
        this.level = 1;
        this.ptr = ptr;
        document.addEventListener("keydown", this.setDirection.bind(this), false, this);
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
        let vect = this.ptr(this.coordinates);
        console.log(vect);
        this.setAnimationIndex(10);
        createjs.Tween
            .get(this.getMesh().position, {override : true})
            .to({
                x: vect.x,
                y: vect.y,
                z: vect.z
            }, 600)
            .call(() => this.setAnimationIndex(2));
    }

    setDirection(event) {
        let keyCode = event.which || event.keyCode || event.charCode;

        console.log(keyCode);
        switch (keyCode) {
            case 81:
                this.rotateLeft();
                break;
            case 68:
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
            case 88:
                this.pickGem();
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

    pickGem() {
        this.playAnimationOnce(1);
        // TODO: Animation pick up a gem on ground
    }

    levelUp() {
        this.level++;
        // TODO: Animation on level up
    }
}