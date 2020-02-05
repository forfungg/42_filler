# 42_filler
42 cursus project filler

## Description
The aim of this project was to code an algorithmic program that could play a game of filler.
The goal of the game is to place more tokens than the opponent. The tokens are random and distributed
by the "referee" program called filler_vm. The given token can be placed only so it's attached to player's
already existing shape in such manner that one and only one tile is shared (palced over). If either
player cannot place the given token, the game ends.

The repository includes folder called resources where the referee program, maps and other players can be found.

## Installation
Requires ecole-42 made graphic library [minilibx](https://github.com/gcamerli/minilibx)

Download repo and make.
```
git clone https://github.com/forfungg/42_filler.git; cd 42_filler; make;
```

The game command syntax
```
./filler_vm -f <map> -p1 <player1> -p2 <player2>

#optional flag -t <timeout>
```

I would recommend not to use the original players given during the assignment, since they are a bit buggy.
Rather use one of the 2 created by other 42 students. Or find yourself some other player on github :)

Try these out:

[ikozlov](https://github.com/IvanKozlov95/filler) on map02
```
./resources/filler_vm -f resources/maps/map02 -p1 resources/players/ikozlov.filler -p2 ./jnovotny.filler
```

[mtan](https://github.com/mgia/fillerBot) on map02
```
./resources/filler_vm -f resources/maps/map02 -p1 resources/players/mtan.filler -p2 ./jnovotny.filler
```
