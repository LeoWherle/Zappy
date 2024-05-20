# MyTeams
- **Contributors:**
  - [Léo Wehrle - Rentmeister](https://github.com/leoWherle)
  - [Théodore Magna](https://github.com/TheodoreEpitech)
  - [Raphaël Castres](https://github.com/castres-raphael)

## Description
The goal of this project is to create a network game where several teams confront on a tiles map
containing resources.
The winning team is the first one where at least 6 players who reach the maximum elevation.



## Install
```sh
binary-names : zappy_server, zappy_ai, zappy_gui
language : C, C++, (free choice for AI)
compilation : via Makefile, including re, clean and fclean rules
```

## Documentation
- [Protocol](./doc/Protocol.txt)

## Usage
```bash
./zappy_server -help
USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq
  option description
  -p port port number
  -x width width of the world
  -y height height of the world
  -n name1 name2 .. . name of the team
  -c clientsNb number of authorized clients per team
  -f freq reciprocal of time unit for execution of actions

```
  ```bash
./zappy_gui -help
USAGE: ./zappy_gui -p port -h machine
  option description
  -p port port number
  -h machine name of the machine
```
```bash
./zappy_ai -help
USAGE: ./zappy_ai -p port -n name -h machine
  option description
  -p port port number
  -n name name of the team
  -h machine name of the machine; localhost by default
```

## BONUSES

- .env file support

