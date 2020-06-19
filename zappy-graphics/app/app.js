import '@babel/polyfill';
import { Core } from '@/app/Core';
import { Server } from '@/app/server/index'
import { ConnectionManager } from "@/app/ConnectionManager";

const connectionManager = new ConnectionManager;

// TODO: handling connection
//Server.on('connect', () => {
    console.log('pute pute pute')
    //const core = new Core();
//});
