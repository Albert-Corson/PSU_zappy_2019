import * as THREE from 'three';

class TeamManager {
    constructor() {
    }
}

class Team {
    constructor(name, size) {
        this.name = name;
        this.size = size;
        this.playersId = []
    }

    expendTeam() {
        this.size++;
    }

    getSize() {
        return this.size;
    }

    getName() {
        return this.name;
    }

    addPlayer(playerId) {
        if (this.playersId.indexOf(playerId) === -1) {
            this.playersId.push(playerId);
            return true;
        }
        return false;
    }

    removePlayer(playerId) {
        let index = this.playersId.indexOf(playerId);

        if (index !== -1) {
            this.playersId.splice(index, 1);
            return true;
        }
        return false;
    }


}

export { TeamManager, Team };