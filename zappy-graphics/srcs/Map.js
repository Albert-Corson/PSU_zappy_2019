import * as THREE from '../Libs/Three/three.module.js'
import { Model } from './wrappers/Model.js'

export class Map {
    constructor(opt = {}) {
        this.x = opt.x || 10;
        this.z = opt.z || 10;
    }

    async generate(sceneWrapper) {
        noise.seed(Math.random());

        let first = true;

        let block = new Model;
        await block.load('../models/block_grass.glb', sceneWrapper, true);

        this.modelSize = block.getSize();

        let rangeZ = Array(this.z).fill(0).map((a, i) => i);
        let rangeX = Array(this.x).fill(0).map((a, i) => i);

        for (let j of rangeZ) {
            for (let i of rangeX) {
                if (first) {
                    block.getMesh().position.set(Number(i) * this.modelSize.x, -this.modelSize.y, Number(j) * this.modelSize.z);
                } else {
                    let copy = new Model({scene: sceneWrapper, mesh: block.getMesh()});
                    copy.getMesh().position.set(Number(i) * this.modelSize.x, -this.modelSize.y, Number(j) * this.modelSize.z);
                }
                first = false;
            }
        }
    }

    getPositionFromCoord(coordinates) {
        if (!this.modelSize)
            return null;
        coordinates.x = coordinates.x < 0 ? this.x - 1 : coordinates.x % this.x;
        coordinates.y = coordinates.y < 0 ? this.z - 1 : coordinates.y % this.z;
        return { x: coordinates.x * this.modelSize.x, y: 0, z: this.modelSize.z * coordinates.y };
    }
}