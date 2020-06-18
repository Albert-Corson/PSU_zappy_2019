import * as THREE from 'three';

class TeamManager {
    constructor() {
        this.nbTeam = 0;
        this.teams = [];
    }

    addTeam(team) {
        if (this.teams.indexOf(team) !== -1)
            return false;
        this.teams.push(team);
        this.nbTeam++;
        this.updateTeamPanel();
        return true;
    }

    removeTeam(teamName) {
        let arr = this.teams.filter(team => team.name === teamName);
        let team = arr.length ? arr[0] : null;

        if (!team)
            return false;
        this.teams.splice(this.teams.indexOf(team), 1);
        return true;
    }

    updateTeamPanel() {
        let teams = document.getElementById('teams');
        let tmp = '';

        this.teams.map(team => {
            tmp += `<li>${team.name}: ${team.playersId.length}/${team.getSize()}</li>`
        });

        teams.innerHTML = tmp;
    }
}

class Team {
    constructor(name, size = 1) {
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