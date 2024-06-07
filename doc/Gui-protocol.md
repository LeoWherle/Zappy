
## ZAPPY - GUI PROTOCOL

### Syntax

| Symbol | Meaning                         | Symbol | Meaning                             |
| :----- | :------------------------------ | :----- | :---------------------------------- |
| X      | width or horizontal position    | n      | player number                       |
| Y      | height or vertical position     | O      | orientation: 1(N), 2(E), 3(S), 4(W) |
| q0     | resource 0 (food) quantity      | L      | player or incantation level         |
| q1     | resource 1 (linemate) quantity  | e      | egg number                          |
| q2     | resource 2 (deraumere) quantity | T      | time unit                           |
| q3     | resource 3 (sibur) quantity     | N      | name of the team                    |
| q4     | resource 4 (mendiane) quantity  | R      | incantation result                  |
| q5     | resource 5 (phiras) quantity    | M      | message                             |
| q6     | resource 6 (thystame) quantity  | i      | resource number                     |


### Commands
These commands are part of the protocol and are required to be implemented by the server and the client for the GUI & server to work together.

| Server                                     |    Client | Details                                       |
| :----------------------------------------- | --------: | :-------------------------------------------- |
| msz X Y\n                                  |     msz\n | map size                                      |
| bct X Y q0 q1 q2 q3 q4 q5 q6\n             | bct X Y\n | content of a tile                             |
| bct X Y q0 q1 q2 q3 q4 q5 q6\n * nbr_tiles |     mct\n | content of the map (all the tiles)            |
| tna N\n * nbr_teams                        |     tna\n | name of all the teams                         |
| pnw #n X Y O L N\n                         |           | connection of a new player                    |
| ppo #n X Y O\n                             |  ppo #n\n | player’s position                             |
| plv #n L\n                                 |  plv #n\n | player’s level                                |
| pin #n X Y q0 q1 q2 q3 q4 q5 q6\n          |  pin #n\n | player’s inventory                            |
| pex #n\n                                   |           | expulsion                                     |
| pbc #n M\n                                 |           | broadcast                                     |
| pic X Y L #n #n . . . \n                   |           | start of an incantation (by the first player) |
| pie X Y R\n                                |           | end of an incantation                         |
| pfk #n\n                                   |           | egg laying by the player                      |
| pdr #n i\n                                 |           | resource dropping                             |
| pgt #n i\n                                 |           | resource collecting                           |
| pdi #n\n                                   |           | death of a player                             |
| enw #e #n X Y\n                            |           | an egg was laid by a player                   |
| ebo #e\n                                   |           | player connection for an egg                  |
| edi #e\n                                   |           | death of an egg                               |
| sgt T\n                                    |     sgt\n | time unit request                             |
| sst T\n                                    |   sst T\n | time unit modification                        |
| seg N\n                                    |           | end of game                                   |
| smg M\n                                    |           | message from the server                       |
| suc\n                                      |           | unknown command                               |
| sbp\n                                      |           | command parameter                             |

### Custom Commands
These commands are not part of the protocol, but can be used in the GUI to interact with the server.
They are NOT required to be implemented by the server or the client for it to work.

| Server       | Client | Details                                                       |
| :----------- | -----: | :------------------------------------------------------------ |
| pm #n\n      |        | player start moving                                               |
| ptr #n\n     |        | player start turn right                                           |
| ptl #n\n     |        | player start turn left                                            |
| pla #n\n     |        | player start looking                                              |
| pf #n\n      |        | player start forking                                              |
| pto #n i\n   |        | player start taking object                                        |
| pdo #n i\n   |        | player start dropping object                                      |
| ok\n \| ko\n |  rst\n | Reset the server, disconnect all clients and restart the game |
