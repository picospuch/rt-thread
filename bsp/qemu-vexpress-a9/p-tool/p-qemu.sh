#!/bin/bash

if [ ! -f "sd.bin" ]; then
dd if=/dev/zero of=sd.bin bs=1024 count=65536
fi

qemu-system-arm \
    -nographic \
    -M vexpress-a9 -smp cpus=2 \
    -kernel rtthread.bin \
    -chardev stdio,mux=on,id=char0 \
    -mon chardev=char0,mode=readline \
    -serial chardev:char0 \
    -sd sd.bin -s
