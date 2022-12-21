# SBreakout

Simple breakout game with allegro5.

Preview-

![Game Preview](img/sbreakout.webp)

## Compilation and running

This command should do the trick.

```
$ cc src/*.c -O3 -o game $(pkg-config allegro-5 allegro_font-5 allegro_image-5 allegro_primitives-5 --libs --cflags)
$ ./game
```

## TODO

- [ ] Complete game.
- [ ] Automate installtion.
- [ ] Cross platform implementation.
- [ ] Improve README.md.

