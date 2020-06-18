import { Model } from '@/app/wrappers/Model';
import { ITEM_TYPE }  from '@/app/constants';

export class Item extends Model {
    constructor(type, scene) {
        super({ scene, mesh: ITEM_TYPE[type].mesh });

        this.type = type;
        this.mesh.scale.set(0.3, 0.3, 0.3)
    }

    static init(sceneWrapper) {
        return new Promise((async (resolve, reject) => {

            let promises = Object.keys(ITEM_TYPE).map(async key => {
                let model = new Model();

                await model.load(`static/assets/models/items/${ITEM_TYPE[key].name}.glb`, sceneWrapper, false);
                ITEM_TYPE[key].mesh = model.getMesh();
                /*console.log(ITEM_TYPE[key].mesh);*/
            });

            await Promise.all(promises);
            resolve();
        }));
    }
}