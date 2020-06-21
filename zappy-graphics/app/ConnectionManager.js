import { Server } from '@/app/server/index'
import { Core } from '@/app/Core'

export class ConnectionManager {
    constructor() {
        this.ip = document.getElementById('ip').getAttribute('value');
        this.port = document.getElementById('port').getAttribute('value');

        document.getElementById('ip').addEventListener('change', e => this.ip = e.target.value);
        document.getElementById('port').addEventListener('change', e => this.port = e.target.value);

        document.getElementById('submit').addEventListener('click', () => {

            Server.connect(this.ip, parseInt(this.port));
            Server.send("-spectator");
            Server.on('connect', () => {
                console.info('waiting for initialization...');

                const core = new Core;

                this.openInfoOnConnection();
            });
        });

        document.getElementById('disconnect').addEventListener('click', () => {
            Server.disconnect();
        });

        this.displayConnectionForm();
    }

    openInfoOnConnection() {
        let askForConnection = document.getElementsByClassName('ask-for-connection');

        for (let it of askForConnection) {
            it.innerText = '';
        }

        document.getElementById('infos').classList.add('active');
        document.getElementById('infos').classList.add('show');
        document.getElementById('info-tab').classList.add('active');
        document.getElementById('info-tab').setAttribute('aria-selected', 'true');

        document.getElementById('network').classList.remove('active');
        document.getElementById('network').classList.remove('show');
        document.getElementById('network-tab').classList.remove('active');
        document.getElementById('network-tab').setAttribute('aria-selected', 'false');

        document.getElementById('connection').style.display = 'none';
        document.getElementById('disconnect').style.display = 'block';
    }

    displayConnectionForm() {
        document.getElementById('connection').style.display = 'block';
        document.getElementById('disconnect').style.display = 'none';
    }
}