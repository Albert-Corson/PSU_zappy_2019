import { Model } from '@/app/wrappers/Model';
import {FOCUS_ON} from "./constants";

export class Bloc extends Model {
    constructor(idx, copy = null) {
        super(copy);

        this.idx = idx;
        this.items = {
            'LINEMATE': 0,
            'DERAUMERE': 0,
            'SIBUR': 0,
            'MENDIANE': 0,
            'PHIRAS': 0,
            'THYSTAME': 0,
            'FOOD': 0,
            'EGG': 0,
        };
        this.focus = false;
    }

    getControlPanelInfo() {
        let list = document.getElementById('items');
        let info = document.getElementById('info');
        let fpv = document.getElementById('first-person');
        let follow = document.getElementById('follow');

        if (FOCUS_ON.id !== `block${this.idx}`)
            return;

        fpv.style.display = 'none';
        follow.style.display = 'none';

        let tmp = `<p class="font-weight-bold m-0">Tile: <i class="font-weight-normal">bloc ${this.idx}</i></p>`;
        tmp += `<p class="font-weight-bold m-0">Items on this tile:</p>`;

        info.innerHTML = tmp;

        list.innerHTML = '';
        Object.keys(this.items).map(e => {
            list.innerHTML += `<li class="list-group-item">${e.toLowerCase()}: ${this.items[e] ? this.items[e].toString() : 0}</li>`
        });
    }

    initRaycaster() {
        this.getMesh().children[0].name = () => {
            FOCUS_ON.id = `block${this.idx}`;
            this.getControlPanelInfo();
        };
    }

    putItemOnBlock(type) {
        this.items[type]++;
    }

    subItemOnBlock(type) {
        this.items[type] = this.items[type] <= 1 ? 0 : this.items[type] - 1;
    }
}