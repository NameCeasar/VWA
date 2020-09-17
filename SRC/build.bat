@echo off
set CPP_FLAGS=-mfloat-abi=hard -mfpu=vfp -O2 -march=armv6zk -mtune=arm1176jzf-s
set AS_FLAGS=-mfloat-abi=hard -mfpu=vfp -march=armv6zk

set BUILD=build\
set OUTPUT=R:\

arm-none-eabi-c++ -c -o %BUILD%Main.o Main.cpp %CPP_FLAGS%
arm-none-eabi-as -c -o %BUILD%bootloader.o boot\bootloader.s %AS_FLAGS%
arm-none-eabi-ld -o %BUILD%kernel.elf %BUILD%Main.o %BUILD%bootloader.o
arm-none-eabi-objcopy %BUILD%kernel.elf -O binary %OUTPUT%kernel.img

pause