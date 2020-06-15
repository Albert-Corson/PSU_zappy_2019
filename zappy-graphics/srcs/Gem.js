import { Model } from './wrappers/Model.js'
import * as THREE from '../THREE/three.module.js'
import { GEM_TYPE }  from './constants.js'


export class Gem extends Model {
    constructor(type, scene) {
        super({ scene, mesh: GEM_TYPE[type].mesh });

        this.type = type;
        this.mesh.scale.set(0.3, 0.3, 0.3)
    }

    static init(sceneWrapper) {
        return new Promise((async (resolve, reject) => {

            let promises = Object.keys(GEM_TYPE).map(async key => {
                let model = new Model();

                await model.load(`../models/gems/${GEM_TYPE[key].name}.glb`, sceneWrapper, false);
                GEM_TYPE[key].mesh = model.getMesh();
            });

            await Promise.all(promises);
            resolve();
        }));
    }
}