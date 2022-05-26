SRCDIR=src/
OBJDIR=obj/
SRCTESTDIR=test/src/
OBJTESTDIR=test/obj/

TARGET=exe

.PHONY: all

all: $(TARGET)

exe: object
	make -C $(OBJDIR)

object:
	make -C $(SRCDIR)

debug: debug_object
	make -C $(OBJDIR)

debug_object:
	make -C $(SRCDIR) debug

test: test_object
	make -C $(OBJTESTDIR)

test_object:
	make -C $(SRCTESTDIR)

clean:
	rm -rf obj/*.o test/obj/*.o

mrproper: clean
	rm -rf bin/* test/bin/*
