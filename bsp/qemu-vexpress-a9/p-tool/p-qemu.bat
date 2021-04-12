@echo off
if exist sd.bin goto run
qemu-img create -f raw sd.bin 64M

:run
qemu-system-arm -nographic -M vexpress-a9 -smp cpus=2 -kernel rtthread.bin    -chardev stdio,mux=on,id=char0    -mon chardev=char0,mode=readline    -serial chardev:char0    -sd sd.bin -s
