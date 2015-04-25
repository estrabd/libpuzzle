#!/bin/sh

cd src
gcc -DHAVE_CONFIG_H -I. -I..    -D_GNU_SOURCE=1 -I/usr/local/include  -g -O2 -c puzzle-sig.c
/bin/sh ../libtool --tag=CC    --mode=link gcc  -g -O2   -L/usr/local/lib -fstack-protector -L/usr/local/lib -o puzzle-sig puzzle-sig.o libpuzzle.la -lgd
cd ..
