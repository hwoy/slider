![](https://raw.githubusercontent.com/hwoy/slider/master/res/pic.png?raw=true)

# Slider
- Slider is a sliding puzzle game aim to maximum cross platform.
- Written in ansi-C.
- No special lib, standard lib only.



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
- -  == exit
- +  == reset

```




### Cntact me
- Email: booskillerz@gmail.com
- FB: facebook.com/watt.duean
