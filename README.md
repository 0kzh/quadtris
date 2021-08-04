## Quadris

![Screenshot](https://puu.sh/I1k9F/197560d525.png)

### Dependencies

- C++ 17
- X11

### Building

To build Quadris,

```
make all
./quadris <optional flags>
```

The following flags are supported:

- `-text` to run in text-only mode
- `-gui` to run in GUI-only mode (adds keyboard controls!)
- `-seed xxx` specify a random seed
- `-startlevel n` start at level `n`

### Bonus Features:

- All memory management done via STD Containers and smart pointers
- Extra CLI command: `-gui` that allows for a GUI only mode
- Extra GUI features such as arrows and keys that allow for full functionality on its own

### Hint Implementation

Hints were implemented using four different criteria:

1. **Aggregate Height**: the sum of heights of all columns
2. **Complete Lines**: the number of lines that can be cleared
3. **Holes**: a hole is defined as an empty space such that there is >= 1 tile above it
4. **Bumpiness**: sum of absolute differences between adjacent columns

These factors were added together with different weights for each to produce a final "fitness" score for how clean the grid is. The weights are taken from [this blog post](https://codemyroad.wordpress.com/2013/04/14/tetris-ai-the-near-perfect-player/), where the author trained a genetic algorithm to find the ideal weights.

When a hint is requested, the program tries all block rotations and positions by "fake dropping" at each point. This, however, does not take into consideration actions like T-Spins.
