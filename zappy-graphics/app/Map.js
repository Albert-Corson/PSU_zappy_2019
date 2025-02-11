import { Item } from '@/app/Item';
import { Bloc } from '@/app/Bloc';

export class Map {
    constructor() {
        this.blocks = [];
        this.rootBlock = null;
    }

    loadBlock(sceneWrapper) {
        this.rootBlock = new Bloc(0);
        return this.rootBlock.load('static/assets/models/ground.glb', sceneWrapper, true);
    }

    generate({ x, z }, sceneWrapper) {
        this.size_x = x;
        this.size_z = z;

        this.itemSlots = new Array(this.size_x * this.size_z).fill({});
        this.itemSlots = this.itemSlots.map(_ => {
            return {
                freeIndexes: new Array(16).fill(0).map((a, i) => i),
                playerFreeIndexes: new Array(9).fill(0).map((a, i) => i),
                items: {}
            }
        });


        let first = true;

        this.rootBlock.initRaycaster();

        this.blocks.push(this.rootBlock);

        this.modelSize = this.rootBlock.getSize();

        let rangeZ = Array(this.size_z).fill(0).map((a, i) => i);
        let rangeX = Array(this.size_x).fill(0).map((a, i) => i);

        for (let j of rangeZ) {
            for (let i of rangeX) {
                let copy;
                if (first) {
                    this.rootBlock.getMesh().position.set(Number(i) * this.modelSize.x, -this.modelSize.y / 2, Number(j) * this.modelSize.z);
                } else {
                    copy = new Bloc(this.size_x * Number(j) + Number(i), {scene: sceneWrapper, mesh: this.rootBlock.getMesh()});
                    copy.getMesh().position.set(Number(i) * this.modelSize.x, -this.modelSize.y / 2, Number(j) * this.modelSize.z);
                    copy.initRaycaster();
                    this.blocks.push(copy);
                }
                first = false;
            }
        }

        this.initCamera(sceneWrapper, 35);
        return Promise.resolve();
    }

    initCamera(sceneWrapper, angle) {
        sceneWrapper.controls.target.set(
            this.size_x * this.modelSize.x / 2,
            0,
            this.size_z * this.modelSize.z / 2,
        );
        let distance_x = this.size_x * this.modelSize.x
        let distance_z = this.size_z * this.modelSize.z

        let cam_x = distance_x + distance_x / 4
        let cam_z = distance_z + distance_z / 4
        let cam_y = Math.tan(angle) * Math.sqrt(Math.pow(distance_x / 4, 2) + Math.pow(distance_z / 4, 2))

        sceneWrapper.camera.position.set(
            cam_x,
            cam_y,
            cam_z,
        );
        sceneWrapper.controls.update();
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

    addItem({ x, z }, type, sceneWrapper) {
        if (z == undefined || x == undefined || isNaN(z) || isNaN(x) || x > this.size_x - 1 || z > this.size_z - 1)
            return;

        let block = this.itemSlots[this.size_x * z + x];

        if (!block)
         console.warn( { x, z, index: this.size_x * z + x, width: this.size_x, height: this.size_z });

        if (!block.items[type]) {
            let index = block.freeIndexes[~~(Math.random() * block.freeIndexes.length)];

            block.freeIndexes.splice(block.freeIndexes.indexOf(index), 1);

            block.items[type] = {nb: 1, index, model: new Item(type, sceneWrapper)};

            block.items[type].model.getMesh().rotation.y = Math.PI / 180 * ~~(Math.random() * 360);

            let pos = this.getPositionFromCoord({x, y: z}, false);
            pos.x = pos.x - this.modelSize.x / 2 + (index % 4 * this.modelSize.x / 4) + this.modelSize.x / 8;
            pos.z = pos.z - this.modelSize.z / 2 + (Math.floor(index / 4) * this.modelSize.z / 4)  + this.modelSize.x / 8;

            block.items[type].model.getMesh().position.set(pos.x, pos.y, pos.z);
        } else {
            block.items[type].nb++;
        }

        this.blocks[this.size_x * z + x].putItemOnBlock(type);
        this.blocks[this.size_x * z + x].getControlPanelInfo();
    }

    getItem({ x, z }, type) {
        if (z == undefined || x == undefined || x > this.size_x - 1 || z > this.size_z - 1)
            return null;

        if (this.itemSlots[this.size_x * z + x])
            return this.itemSlots[this.size_x * z + x].items[type];
        return null;
    }

    getPlayerPositionFromCord(coordinates) {
        let pos = this.getPositionFromCoord(coordinates);
        let block = this.itemSlots[this.size_x * coordinates.y + coordinates.x];
        let Place = block.playerFreeIndexes.length !== 0;
        let index = block.playerFreeIndexes[~~(Math.random() * block.playerFreeIndexes.length)];

        block.playerFreeIndexes.splice(block.playerFreeIndexes.indexOf(index), 1);

        if (Place) {
            pos.x = pos.x - this.modelSize.x / 2 + (index % 3 * this.modelSize.x / 3) + this.modelSize.x / 6;
            pos.z = pos.z - this.modelSize.z / 2 + (Math.floor(index / 3) * this.modelSize.z / 3)  + this.modelSize.x / 6;
        } else {
            pos.x = pos.x - this.modelSize.x / 3 + (Math.random() * this.modelSize.x * 0.6);
            pos.z = pos.z - this.modelSize.z / 3 + (Math.random() * this.modelSize.z * 0.6);
        }

        return { x: pos.x * this.modelSize.x, y: 0, z: this.modelSize.z * pos.z };
    }

    deleteItem({ x, z }, type, sceneWrapper) {
        if (z == undefined || x == undefined || x > this.size_x - 1 || z > this.size_z - 1)
            return false;

        let block = this.itemSlots[this.size_x * z + x];

        if (!block.items[type])
            return false;

        block.items[type].nb--;
        this.blocks[this.size_x * z + x].subItemOnBlock(type);
        this.blocks[this.size_x * z + x].getControlPanelInfo();


        if (block.items[type].nb <= 0) {
            sceneWrapper.getScene().remove(block.items[type].model.getMesh());
            block.freeIndexes.push(block.items[type].index);
            block.items[type] = undefined;
        }
        return true;
    }
}