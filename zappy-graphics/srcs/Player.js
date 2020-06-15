import * as THREE from '../THREE/three.module.js'
import { Model } from './wrappers/Model.js'
import { DIR } from './constants.js'
import { PLAYER_TYPE} from "./constants.js";

export class Player extends Model {
    constructor(type, scene, opt = {}) {
        super({ scene, mesh: PLAYER_TYPE[type].mesh });

        this.teamId = opt.teamId || 1;
        this.playerName = opt.name || "bob";
        this.direction = opt.dir || DIR.N;
        this.coordinates = opt.coordinates || new THREE.Vector2(0, 0);
        this.level = 1;
    }

    static init(sceneWrapper) {
        return new Promise((async (resolve, reject) => {

            let promises = Object.keys(PLAYER_TYPE).map(async key => {
                let model = new Model();

                await model.load(`../models/players/${PLAYER_TYPE[key].name}.glb`, sceneWrapper, false);
                PLAYER_TYPE[key].mesh = model.getMesh();
            });

            await Promise.all(promises);
            resolve();
        }));
    }

    rotateLeft() {
        this.direction = (this.direction === 0 ? 3 : this.direction - 1);
    }

    rotateRight() {
        this.direction++;
        this.direction = this.direction % 4;
    }

    moveForward() {
        switch (this.direction) {
            case DIR.N:
                this.position.setY(this.position.y + 1);
                break;
            case DIR.E:
                this.position.setX(this.position.x + 1);
                break;
            case DIR.S:
                this.position.setY(this.position.y - 1);
                break;
            case DIR.W:
                this.position.setX(this.position.x - 1);
                break;
        }
    }

    forkAnimation() {
        // TODO: Animation on fork, like "chie un oeuf'
    }

    ejectAnimation() {
        // TODO: Animation ejecting another player, like "dégage sale cake"
    }

    pickGem() {
        // TODO: Animation pick up a gem on ground
    }

    levelUp() {
        this.level++;
        // TODO: Animation on level up
    }
}