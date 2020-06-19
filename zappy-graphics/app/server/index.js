/**
 * Communication with Zappy server
 */

if (WebTCP == undefined) {
    throw new Error('WebTCP is undefined. Please import webtcp library.')
}

import * as EventEmitter from 'events'

export class Server {
    /**
     * Establish a connection with a bridge server running on localhost
     * See bridge/README.md
     * @type {WebTCP}
     * @private
     */
    static _net = new WebTCP('localhost', 9999)

    /**
     * Socket connected to a remote Zappy server
     * @type {Boolean}
     * @private
     */
    static _socket = null

    /**
     * Connection state (opened or closed)
     * @type {Boolean}
     * @private
     */
    static _isOpen = false

    /**
     * Event emitter used to listen/emit server events
     * @type {EventEmitter}
     * @private
     */
    static _emitter = new EventEmitter()

    /**
     * Connect to a remote server
     * 
     * @param {String} host server host
     * @param {Number} port server port
     */
    static connect(host, port) {
        if (this._socket !== null) {
            this.close()
        }
        this._socket = this._net.createSocket(host, port, {
            encoding: "utf-8",
            timeout: 0,
            noDelay: true,
            keepAlive: false,
            initialDelay: 0
        });
        this._net.onclose = ()=>{console.log('close')}
        this._socket.on('connect', () => {
            this._isOpen = true
            this._emitter.emit('connect')
        })
        this._socket.on('end', () => {
            this._isOpen = false
            this._emitter.emit('disconnect')
        })
        this._socket.on('data', data => {
            const messages = data.split('\n')
            for (let message of messages) {
                this._emitter.emit('message', message)
            }
        })
    }

    /**
     * Returns the state of the connection to a remote server (opened or closed)
     */
    static isOpen() {
        return this._isOpen
    }

    /**
     * Close the connection to a remote server
     */
    static disconnect() {
        if (this._socket !== null) {
            this._socket.close()
            this._socket = null;
        }
    }

    /**
     * Bind an event listener among the following types:
     * - **connect**: the connection with the Zappy server is established
     * - **disconnect**: the connection with the Zappy server is closed
     * - **message**: a message was received from the Zappy server
     * @param {String} event event type
     * @param {Function} listener event listener
     */
    static on(event, listener) {
        if (this._socket === null) {
            throw new Error('Connection with the server is not established. Cannot bind event listeners.')
        }
        this._emitter.on(event, listener)
    }

    /**
     * Send a message to the Zappy server
     * 
     * @param {String} payload message content
     */
    static send(payload) {
        if (this._socket === null) {
            throw new Error('Connection with the server is not established. Cannot send message.')
        }
        this._socket.write(payload)
    }
}

export default Server