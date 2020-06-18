import * as THREE from 'three';
import { Player } from '@/app/Player';

class Team {
    constructor(name, size = 1) {
        this.name = name;
        this.size = size;
        this.players = []
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

    async addPlayer(coordinates, id, scene, map) {
        let tmp_player = new Player(map, { coordinates, id });

        await tmp_player.initInstance(scene);
        this.players.push(tmp_player);
        return tmp_player;
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

    async addPlayer(coordinates, playerId, teamName, scene, map) {
        let arr = this.teams.filter(team => team.name === teamName);
        let team = arr.length ? arr[0] : null;

        console.log(this.teams);
/*
        console.log(team.addPLayer);
*/
        if (!team)
            return null;
        let tmp_player = new Player(map, { coordinates, playerId });

        await tmp_player.initInstance(scene);
        team.players.push(tmp_player);
        console.log(tmp_player)
        return tmp_player;
        /*return await team.addPLayer(coordinates, playerId, scene, map);*/
    }

    getPlayerById(id) {
        let fetch = null;
        let arr = this.teams.map(team => {
            let tmp = team.players.filter(player => player.playerId === id);
            if (tmp.length)
                fetch = tmp[0];
        });

        return fetch;
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
            tmp += `<li>${team.name}: ${team.players.length}/${team.getSize()}</li>`
        });


        teams.innerHTML = tmp;
    }
}

export { TeamManager, Team };