# SBreakout

Simple breakout game with allegro5.

## Compilation and running

These commands should do the trick.

```
$ cc src/*/*.c src/game.c -Iinclude -O3 -o game $(pkg-config allegro-5 allegro_font-5 allegro_primitives-5 --libs --cflags)
$ ./game
```

## Grab a release

- [v2.0.0](https://github.com/swajeet01/sbreakout/releases/tag/v2.0.0)
