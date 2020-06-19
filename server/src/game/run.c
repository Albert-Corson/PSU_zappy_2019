/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** run
*/

#include <stdio.h>

#include <utils/randbetween.h>
#include <utils/getelapsedms.h>
#include <game.h>

static void game_process_map(struct timeval *now)
{
    struct timeval new = { 0 };
    vector_t pos = { 0 };
    element_e elem = E_UNKNOWN;
    const double lim = (RESPAWN / GAME.freq) * 1000;
    double elapsed = getelapsedms(&GAME.respawn, now);

    while (elapsed >= lim) {
        elapsed -= lim;
        new.tv_usec = lim * 1000;
        timeradd(&GAME.respawn, &new, &GAME.respawn);
        pos.x = randbetween(0, GAME.width - 1);
        pos.y = randbetween(0, GAME.height - 1);
        elem = randbetween(E_FOOD, E_THYSTAME);
        GAME.map[pos.y][pos.x].inventory[elem].amount += 1;
        spectators_send_new_item(&GAME.map[pos.y][pos.x].inventory[elem], &pos);
    }
}

static bool game_process_team_win(team_t *team)
{
    player_t *it = NULL;
    size_t max_lvl = 0;

    SLIST_FOREACH(it, &GAME.players, next) {
        if (it->team == team && it->level == 8)
            max_lvl++;
    }
    return (max_lvl >= 6);
}

void game_run(void)
{
    team_t *it = NULL;
    struct timeval now = { 0 };

    gettimeofday(&now, NULL);
    game_process_players(&now);
    game_process_eggs(&now);
    game_process_map(&now);
    SLIST_FOREACH(it, &GAME.teams, next) {
        if (game_process_team_win(it)) {
            GAME.running = false;
            break;
        }
    }
    if (!GAME.running && it) {
        spectators_send_win(it);
        printf("Team '%s' won!\n", it->name);
    }
}
