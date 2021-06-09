# sys

ARCH: RISCV

LIB: riscv-glibc

![syscall](https://github.com/H-Y-B/sys/blob/main/images/sys.jpeg)



# [strace tools](https://strace.io/)

```
./configure --host=arm-linux CC=riscv64-unknown-linux-gnu --prefix=/.../
make CFLAGS="-static"
```



# problemm

autoreconf: not found

```
sudo apt-get install autoconf
```

