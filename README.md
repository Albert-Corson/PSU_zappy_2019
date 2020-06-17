# ZAPPY ![C/C++ CI](https://github.com/Albert-Corson/PSU_zappy_2019/workflows/C/C++%20CI/badge.svg?branch=master)

made by:
Adrien Lucbert
Albert Corson
Louis Viot
Mathias Vigier
Alexis Delebecque
Fahad Assoumani

_________

## UI/Server communication protocol:
To communicate with the server, a graphical client has to follow this communication protocol.  
Note that apart from the initial "-spectator" message, all requests from the graphical clients will be ignored.

### Initiating the connection

After receiving the `WELCOME` message, the UI-client need to respond by `-spectator` to register as a spectator. The UI-client will next receive the height and width of the map.

    --> WELCOME
    <-- -spectator
    --> height width

> **\/!\\** After the connection's initialization, the server will send a first batch of [notifications](###-Game-updates) so that the UI-client can catch up on the ongoing game.

### Game updates
During a game, the UI-client may receive different types of updates (notifications) about the course of the match. Theses notifications will end by a single new-line character (\\n)

**NB:** `<dir>` is a numeral representation of the orientation of a player:
* NORTH = 0
* WEST = 1
* SOUTH = 2
* EAST = 3

```xml
new_item <item_name> <y> <x>
```
> A new item has spawned on the map

```xml
new_team <max_players> <name>
```
> A new team was created. Be aware that the team's `name` can be composed of multiple words

```xml
new_player <player_id> <team_name> <dir> <y> <x>
```
> A new player has spawned

```xml
inventory <player_uui> [<item_name> <amount>]...
```
> An update of a player's inventory

```xml
new_egg <egg_id> <player_id> <y> <x>
```
> An egg has been layed by `player_id` at [`y`, `x`]

```xml
hatched <egg_id>
```
> An egg has hatched, creating a new slot in it's team for a player to join

```xml
eat <player_id>
```
> A player has eaten one unit of the "food" item

```xml
died <player_id>
```
> A player has died, leaving a slot in his team vacant

```xml
win <team_name>
```
> A team has won and the game has ended. The server will shortly close after this message

```xml
elevation_start [<player_id>]...
```
> An elevation has started. The players involved in it is a list of player-IDs

```xml
elevation_failed [<player_id>]...
```
> An elevation has failed.

```xml
elevation_end [<player_id>]...
```
> An elevation has ended successfully. Players involved in it

```xml
drop <player_id> <object_name>
```
> A player dropped an item from his inventory onto the ground

```xml
take <player_id> <object_name>
```
> A player picked-up an item

```xml
broadcast <player_id> <message>
```
> A player is broadcasting a message

```xml
eject <player_id>
```
> A player has pushed the other players from his tile to the next one in the direction he is facing

```xml
move <player_id> <dir> <y> <x>
```
> Moved a player to [`y`, `x`] and updated his orientation

```xml
forward <player_id>
```
> A player has moved forward

```xml
left <player_id>
```
> A player has turned his orientation to the left

```xml
right <player_id>
```
> A player has turned his orientation to the right
