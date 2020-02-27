# If you don't have devkitARM binaries in your path, uncomment and adapt below line
#export PATH=/d/Libraries/devkitPro/devkitARM/bin:$PATH

arm-none-eabi-gcc -c main.c -mthumb-interwork -mthumb -O2 -o main.o
arm-none-eabi-gcc main.o -mthumb-interwork -mthumb -specs=gba.specs -o gba-frame-test.elf
arm-none-eabi-objcopy -v -O binary gba-frame-test.elf gba-frame-test.gba
