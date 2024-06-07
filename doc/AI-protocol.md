
## ZAPPY - AI PROTOCOL

### Syntax
### Commands
These commands are part of the protocol and are required to be implemented by the server and the client for the GUI & server to work together.

| action                       | command        | time limit | response                                |
| ---------------------------- | -------------- | ---------- | --------------------------------------- |
| move up one tile             | Forward        | 7/f        | ok                                      |
| turn 90° right               | Right          | 7/f        | ok                                      |
| turn 90° left                | Left           | 7/f        | ok                                      |
| look around                  | Look           | 7/f        | [tile1, tile2,. .. ]                    |
| inventory                    | Inventory      | 1/f        | [linemate n, sibur n,. .. ]             |
| broadcast text               | Broadcast text | 7/f        | ok                                      |
| number of team unused slots  | Connect_nbr    | -          | value                                   |
| fork a player                | Fork           | 42/f       | ok                                      |
| eject players from this tile | Eject          | 7/f        | ok/ko                                   |
| death of a player            | -              | -          | dead                                    |
| take object                  | Take object    | 7/f        | ok/ko                                   |
| set object down              | Set object     | 7/f        | ok/ko                                   |
| start incantation            | Incantation    | 300/f      | Elevation underway Current level: k /ko |

---
*All commands are transmitted through a character string that ends with a new line.*

*In case of a bad/unknown command, the server must answer "ko".*
