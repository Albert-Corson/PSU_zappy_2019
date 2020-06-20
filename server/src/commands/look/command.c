/*
** EPITECH PROJECT, 2020
** PSU_zappy_2019
** File description:
** callback
*/

#include <stdlib.h>

#include <game.h>

static void readjust_pos(vector_t *pos)
{
    if (pos->x >= GAME.width)
        pos->x -= GAME.width;
    else if (pos->x < 0)
        pos->x += GAME.width;
    if (pos->y >= GAME.height)
        pos->y -= GAME.height;
    else if (pos->y < 0)
        pos->y += GAME.height;
}

static void get_tile_pos(player_t *player, const vector_t *off, vector_t *pos)
{
    pos->x = player->pos.x;
    pos->y = player->pos.y;
    if (player->dir == NORTH) {
        pos->x += off->x;
        pos->y += off->y;
    }
    if (player->dir == SOUTH) {
        pos->x += off->x * -1;
        pos->y += off->y * -1;
    }
    if (player->dir == WEST) {
        pos->x += off->y;
        pos->y += off->x;
    }
    if (player->dir == EAST) {
        pos->x += off->y * -1;
        pos->y += off->x;
    }
    readjust_pos(pos);
}

static bool dump_tile(sbuffer_t *buf, vector_t *pos)
{
    const tile_t *tile = &GAME.map[pos->y][pos->x];
    const size_t size = sizeof(tile->inventory) / sizeof(*tile->inventory);
    bool good = true;
    player_t *it = SLIST_FIRST(&GAME.players);

    for (size_t idx = 0; good && idx < size; ++idx) {
        for (size_t n = 0; good && n < tile->inventory[idx].amount; ++n)
            good = sbuffer_printf(buf, "%s ", tile->inventory[idx].name);
    }
    while (good && it) {
        if (it->pos.x == pos->x && it->pos.y == pos->y)
            good = sbuffer_write(buf, "player ");
        it = SLIST_NEXT(it, next);
    }
    return (good);
}

static bool dump_row(sbuffer_t *buf, player_t *player, int lvl, int off_y)
{
    bool good = true;
    vector_t pos = { 0, 0 };
    vector_t off = {
        .x = 0,
        .y = off_y
    };

    for (off.x = lvl * -1; good && off.x <= lvl; ++off.x) {
        get_tile_pos(player, &off, &pos);
        good = dump_tile(buf, &pos);
        if (good && (off.x + 1 <= lvl || lvl != player->level))
            good = sbuffer_write(buf, ", ");
    }
    return (good);
}

bool exec_look(player_t *player, char *data)
{
    sbuffer_t buf;
    bool good = true;
    int off_y = 0;

    sbuffer_init(&buf);
    good = sbuffer_write(&buf, "[");
    for (int lvl = 0; good && lvl <= player->level; ++lvl) {
        good = dump_row(&buf, player, lvl, off_y);
        --off_y;
    }
    if (!good || !sbuffer_write(&buf, "]\n"))
        exit(84);
    send_str(player->sockd, buf.buffer);
    sbuffer_destroy(&buf);
    return (true);
}
