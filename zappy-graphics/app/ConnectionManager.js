import { Server } from '@/app/server/index'
import { Core } from '@/app/Core'

export class ConnectionManager {
    constructor() {
        this.ip = document.getElementById('ip').getAttribute('value');
        this.port = document.getElementById('port').getAttribute('value');

        let submitForm = document.getElementById('submit');

        document.getElementById('ip').addEventListener('change', e => this.ip = e.target.value);
        document.getElementById('port').addEventListener('change', e => this.port = e.target.value);

        submitForm.addEventListener('click', () => {
            console.log(this.ip, this.port);
            Server.connect(this.ip, parseInt(this.port));
            Server.send("-spectator");
            Server.on('connect', () => {
                console.info('waiting for initialization...');
                let core = new Core;
                document.getElementById('connection').style.display = 'none';
            });
        });
        this.displayConnectionForm();
    }

    displayConnectionForm() {
        document.getElementById('connection').style.display = 'block';
    }
}