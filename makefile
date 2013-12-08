# # # # # # # # # # # # # # # # # # # # # # # #
#
# ALG1 - Trabalho 2
#
# Alex Frederico Ramos Barboza    Nº7986480
# alex.barbosa@usp.br
#
# Gil Barbosa Reis                Nº8532248
# gil.reis@usp.br
#
# Leonardo Sampaio Ferraz Ribeiro Nº8532300
# leonardo.sampaio.ribeiro@usp.br
#
# # # # # # # # # # # # # # # # # # # # # # # #



# Makefile da geral 2.0!
# Agora melhor, mais compacto e aprimorado!

objs = main.o AVL.o linked_list.o
source = main.c main.h AVL.h AVL.c linked_list.h linked_list.c

CFLAGS = -g -O2 -march=native



all : $(objs)
	cc $(objs) -o main $(CFLAGS)


main.o : main.c AVL.o linked_list.o
	cc -c main.c $(CFLAGS)

AVL.o : AVL.c AVL.h
	cc -c AVL.c $(CFLAGS)

linked_list.o : linked_list.c linked_list.h
	cc -c linked_list.c $(CFLAGS)



run : main.o
		@./main

zip :
		@zip -r alg1 $(source) makefile Doxyfile Readme.dox html main

clean :
		@rm main *.o *~ alg1.zip
