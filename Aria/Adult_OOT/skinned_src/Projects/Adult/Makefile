PROGRAM = ../../tunic
OVLOUT = actor.zovl
ADDRESS = 0x80800000
OBJDUMP = mips-n64-objdump
PARTS = $(PROGRAM).o

CC   = mips-n64-gcc
LD   = mips-n64-ld
NOVL = novl

CFLAGS = -G 0 -O2 --std=gnu99 -mtune=vr4300 -mabi=32 -mips3 -mno-explicit-relocs -mno-memcpy -Wall -Wno-unused-function -Wno-strict-aliasing
LDFLAGS = -L$(Z64OVL_LD) -T z64ovl.ld --emit-relocs
NOVLFLAGS = -v -c -A $(ADDRESS) -o $(OVLOUT)

default: clean entry $(PROGRAM).ovl symbols

$(PROGRAM).ovl: $(PARTS)
	$(LD) -o $(PROGRAM).elf $(PARTS) $(LDFLAGS)
	$(NOVL) $(NOVLFLAGS) $(PROGRAM).elf

entry:
	@echo -n "ENTRY_POINT = "$(ADDRESS) > entry.ld
	@echo ";" >> entry.ld

symbols:
	@$(OBJDUMP) -t $(PROGRAM).elf > symbols.txt

clean:
	rm -fv $(PROGRAM).elf $(OVLOUT) $(PARTS) entry.ld symbols.txt conf.txt