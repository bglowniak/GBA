# SquareDude

SquareDude is a small scale GameBoy Advance game built for CS 2110 at Georgia Tech. It was built over the course of a week and is designed to emulate the [World's Hardest Game](https://www.coolmath-games.com/0-worlds-hardest-game).

All code was written in C and emulated using the VBA emulator.

All images (characters, levels, and screens) were created in Photoshop and ported to GBA-drawable C using [nin10kit](https://github.com/TricksterGuy/nin10kit).

## Mechanics

As SquareDude, you must navigate through a series of difficult levels for no discernible purpose.

The arrow keys represent their corresponding movements, while SELECT (Backspace) will return you to the start screen.

Each level contains a series of enemies moving in set paths (represented by blue circles). Colliding with one results in a death and a level reset. To beat a level, you must reach a green goal zone at the end. If a level has any pickups (represented by yellow triangles), they must be collected before you reach the goal zone.

Upon reaching 20 deaths, you will receive a Game Over.

There are currently four levels. Three and four are pretty difficult, but are definitely doable. The code is set up very well to easily add new levels, so I may add some periodically because they're pretty fun to design.

## Lore

Nope.
