@echo off
set FILES=boot\bootloader.s Main.cpp

set BUILD=build\
set OUTPUT=R:\

arm-none-eabi-g++ -Wwrite-strings -nostartfiles -specs=nosys.specs -mfloat-abi=hard -mfpu=vfp -O0 -march=armv6zk -mtune=arm1176jzf-s -o %BUILD%kernel.elf %FILES%
arm-none-eabi-objdump %BUILD%kernel.elf -D > %BUILD%kernel.dump
arm-none-eabi-objcopy %BUILD%kernel.elf -O binary %OUTPUT%kernel.img

pause