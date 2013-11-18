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

objs = main.o AVL.o
source = main.c AVL.h AVL.c

CFLAGS = -g -O2 -march=native



all : source
	cc $(objs) -o main $(CFLAGS)


main.o : main.c AVL.h
	cc -c main,c $(CFLAGS)

AVL.o : AVL.c AVL.h
	cc -c AVL.c $(CFLAGS)




run : main.o
		@./main

commit :
		@git commit -a && git push

zip :
		@zip alg1 $(source) makefile

clean :
		@rm main $(objs) *~ alg1.zip
