a.out : main.o FPBST.o FPBSTHelper.o
	gcc main.o FPBST.o FPBSTHelper.o

main.o: main.c FPBST.h
	gcc -c main.c

FPBST.o : FPBST.c FPBST.h FPBSTHelper.h
	gcc -c FPBST.c

FPBSTHelper.o : FPBSTHelper.c FPBSTHelper.h
	gcc -c FPBSTHelper.c
