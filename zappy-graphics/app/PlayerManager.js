import * as THREE from 'three';
import { Player } from '@/app/Player';

class PlayerManager {
    constructor() {
        this.teams = [];
        this.eggs = [];
    }

    addTeam(teamName, size) {
        this.teams.push({ teamName, size, players: [] });
        this.updateTeamPanel();
    }

    getTeamsCount() {
        return this.teams.length
    }

    async addPlayerInTeam(playerOpt, teamName, scene, map) {
        let teamId = this.teams.map(team => team.teamName).indexOf(teamName);
        let team = this.teams[teamId];

        if (team === -1)
            return;
        let player = new Player(map, scene, { ...playerOpt, teamName });

        await player.initInstance(scene);
        team.players.push(player);
        this.updateTeamPanel();
        return player;
    }

    deletePlayerInTeam(playerId, scene) {
        for (let team of this.teams) {
            let index = team.players.map(player => player.playerId).indexOf(playerId);

            if (index !== -1) {
                team.players[index].addEventListener('animation-end', _ => {
                    scene.getScene().remove(team.players[index].getMesh());
                    team.players.splice(index, 1);
                    this.updateTeamPanel();
                });
                team.players[index].died();
                return;
            }
        }
    }

    playerDropEgg(coordinates, egg_id, map, scene, player_id) {
        let player = this.getPlayerById(player_id);
        let team = this.getTeamByPlayerId(player_id);

        if (player)
            player.playAnimationOnce(9);
        if (team)
            this.eggs.push({ egg_id, team, coordinates });
        map.addItem(coordinates, 'EGG', scene);
    }

    hatchEgg(egg_id, map, scene) {
        let index = this.eggs.map(elem => elem.egg_id).indexOf(egg_id);

        if (index === -1)
            return;

        this.eggs[index].team.size++;

        let model = map.getItemModel(this.eggs[index].coordinates, 'EGG');

        if (!model)
            return;

        new createjs.Tween.get(model.position).to({
            y: 2
        }, 1000).call(() => {
            this.updateTeamPanel();
            map.deleteItem(this.eggs[index].coordinates, 'EGG', scene);
        })
    }

    getTeamByPlayerId(playerId) {
        for (let team of this.teams) {
            let index = team.players.map(player => player.playerId).indexOf(playerId);

            if (index !== -1) {
                return team;
            }
        }
        return null;
    }

    getPlayerById(playerId) {
        for (let team of this.teams) {
            let index = team.players.map(player => player.playerId).indexOf(playerId);

            if (index !== -1) {
                return team.players[index];
            }
        }
        return null;
    }

    getAllPlayers() {
        let ret = [];

        this.teams.map(team => team.players.map(player => ret.push(player)));
        return ret;
    }

    updateTeamPanel() {
        let teams = document.getElementById('teams');
        let teamsHdr = document.getElementById('teams-header');
        let tmp = '';

        if (this.teams.length === 0) {
            teamsHdr.innerHTML = 'No team registered';
            teams.innerHTML = '';
            return;
        }

        teamsHdr.innerHTML = 'Teams:';

        this.teams.map(team => {
            tmp += `<li>${team.teamName}: ${team.players.length}/${team.size}</li>`
        });

        teams.innerHTML = tmp;
    }
}

export { PlayerManager };