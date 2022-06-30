AS = lwasm

%.bin: %.asm
	$(AS) -o$@ -l$*.lst $<

all: cciodw.bin dwread.bin dwwrite.bin

cciodw.bin: cciodw.asm

dwread.bin: dwread.asm

dwwrite.bin: dwwrite.asm

clean:
	rm -vf *.bin *.lst
