import {Model} from './wrappers/Model.js'

export class Bloc extends Model {
    constructor(idx, copy = null) {
        super(copy);

        this.idx = idx;
        this.gems = {
            'LINEMATE': 0,
            'DERAUMERE': 0,
            'SIBUR': 0,
            'MENDIANE': 0,
            'PHIRAS': 0,
            'THYSTAME': 0
        };
    }

    getControlPanelInfo() {
        let list = document.getElementById('gems');
        let info = document.getElementById('info');

        let tmp = `<p>Tile: bloc <i>${this.idx}</i></p>`;
        tmp += `<p>Gems on this tile:</i></p>`;

        info.innerHTML = tmp;

        list.innerHTML = '';
        Object.keys(this.gems).map(e => {
            list.innerHTML += `<li>${e.toLowerCase()}: ${this.gems[e] ? this.gems[e].toString() : 0}</li>`
        });
    }

    initRaycaster() {
        this.getMesh().children[0].name = this.getControlPanelInfo.bind(this);
    }

    putGemOnBlock(type) {
        this.gems[type]++;
    }

    subGemOnBlock(type) {
        this.gems[type] = this.gems[type] <= 1 ? 0 : this.gems[type] - 1;
    }
}