![](https://raw.githubusercontent.com/hwoy/slider/master/res/pic.png?raw=true)

# Slider
- Slider is a sliding puzzle game aim to maximum cross platform.
- Written in ansi-C.
- No special lib, standard lib only.

### Features
1. In-house random number generator [prng](https://github.com/hwoy/prng) , avoid difference value if you use rand() in stdlib.h in differnece C standard lib
2. Set seed by -s:[SEED number] parameter
3. Set blank by -b:[blank charecter] parameter
4. Portable game core (slider.c,lcg.c,minstd.c)
5. Easy for porting , **No special lib**, **No file io**, **No memory alloc**
6. [slider.gba](https://github.com/hwoy/slider.gba) ported to GameBoy Advance uses this core function (slider.c,lcg.c,minstd.c)

### How to build

```sh
$ make
```
- For 3x3 ABC

```sh
$ make -f Makefile.3
```

- For 4x4 ABC

```sh
$ make -f Makefile.4
```

- For 5x5 ABC

```sh
$ make -f Makefile.5
```

- For All

```sh
$ ls Make* | xargs -I{} make -f {}
```


### How to play
```sh
- w  == moves down block
- s  == moves up block
- a  == moves left block to right
- d  == moves right block to left
- -  == quit
- +  == reset a board

```




### Contact me
- Web: https://github.com/hwoy 
- Email: zaintcorp@yahoo.com 
- Facebook: http://www.facebook.com/dead-root
