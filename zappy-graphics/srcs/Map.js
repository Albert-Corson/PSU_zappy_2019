import { Gem } from './Gem.js'
import { Bloc } from './Bloc.js'
export class Map {
    constructor(opt = {}) {
        this.size_x = opt.x || 10;
        this.size_z = opt.z || 10;
        this.gemSlots = new Array(this.size_x * this.size_z).fill({});
        this.gemSlots = this.gemSlots.map(_ => {
            return {
                freeIndexes: new Array(9).fill(0).map((a, i) => i),
                gems: {}
            }
        });
        this.blocks = [];
    }

    async generate(sceneWrapper) {
        noise.seed(Math.random());

        let first = true;

        let block = new Bloc(0);
        await block.load('../models/ground.glb', sceneWrapper, true);
        block.initRaycaster();

        this.blocks.push(block);

        this.modelSize = block.getSize();

        let rangeZ = Array(this.size_z).fill(0).map((a, i) => i);
        let rangeX = Array(this.size_x).fill(0).map((a, i) => i);

        for (let j of rangeZ) {
            for (let i of rangeX) {
                let copy;
                if (first) {
                    block.getMesh().position.set(Number(i) * this.modelSize.x, -this.modelSize.y / 2, Number(j) * this.modelSize.z);
                } else {
                    copy = new Bloc(this.size_x * Number(j) + Number(i), {scene: sceneWrapper, mesh: block.getMesh()});
                    copy.getMesh().position.set(Number(i) * this.modelSize.x, -this.modelSize.y / 2, Number(j) * this.modelSize.z);
                    copy.initRaycaster();
                    this.blocks.push(copy);
                }
                first = false;
            }
        }
    }

    getPositionFromCoord(coordinates, modifySource = true) {
        if (!this.modelSize)
            return null;

        if (modifySource) {
            coordinates.x = coordinates.x < 0 ? this.size_x - 1 : coordinates.x % this.size_x;
            coordinates.y = coordinates.y < 0 ? this.size_z - 1 : coordinates.y % this.size_z;
        }
        return { x: coordinates.x * this.modelSize.x, y: 0, z: this.modelSize.z * coordinates.y };
    }

    addGem({ x, z }, type, sceneWrapper) {
        if (z == undefined || x == undefined || x > this.size_x - 1 || z > this.size_z - 1)
            return;

        let block = this.gemSlots[this.size_x * z + x];

        if (!block.gems[type]) {
            let index = block.freeIndexes[~~(Math.random() * block.freeIndexes.length)];

            block.freeIndexes.splice(block.freeIndexes.indexOf(index), 1);

            block.gems[type] = {nb: 1, index, model: new Gem(type, sceneWrapper)};

            let pos = this.getPositionFromCoord({x, y: z}, false);
            pos.x = pos.x - this.modelSize.x / 3 + (index % 3 * this.modelSize.x / 3);
            pos.z = pos.z - this.modelSize.z / 3 + (Math.floor(index / 3) * this.modelSize.z / 3);

            block.gems[type].model.getMesh().position.set(pos.x, pos.y, pos.z);
        } else {
            block.gems[type].nb++;
        }

        this.blocks[this.size_x * z + x].putGemOnBlock(type);
    }

    deleteGem({ x, z }, type, sceneWrapper) {
        if (z == undefined || x == undefined || x > this.size_x - 1 || z > this.size_z - 1)
            return false;

        let block = this.gemSlots[this.size_x * z + x];

        if (!block.gems[type])
            return false;

        block.gems[type].nb--;
        this.blocks[this.size_x * z + x].subGemOnBlock(type);


        if (block.gems[type].nb <= 0) {
            sceneWrapper.getScene().remove(block.gems[type].model.getMesh());
            block.freeIndexes.push(block.gems[type].index);
            block.gems[type] = undefined;
        }
        return true;
    }
}