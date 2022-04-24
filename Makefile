SRCDIR=src/
OBJDIR=obj/
SRCTESTDIR=test/src/
OBJTESTDIR=test/obj/

TARGET=brownian_path


all: $(TARGET)

brownian_path: object
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
	rm -rf bin/*.exe test/bin/*.exe
