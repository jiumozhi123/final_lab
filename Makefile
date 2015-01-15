#
# Makefile for final_lab
#

all: server.o client.o server client MD5.o MD5test.o md5 fclean.o fclean fcreate.o fcreate

server:server.o
	gcc -o server server.o

client:client.o
	gcc -o client client.o

md5:MD5.o MD5test.o
	gcc -o md5 MD5.o MD5test.o

fcreate:fcreate.o
	gcc -o fcreate fcreate.o

fclean:fclean.o
	gcc -o fclean fclean.o

server.o:server.c common.h
	gcc -c server.c

client.o:client.c common.h
	gcc -c client.c

MD5.o:MD5.c MD5.h
	gcc -c MD5.c

MD5test.o:MD5test.c MD5.h
	gcc -c MD5test.c

fcreate.o:fcreate.c
	gcc -c fcreate.c

fclean.o:fclean.c
	gcc -c fclean.c

clean:
	rm -f server client server.o client.o md5 MD5.o MD5test.o fcreate fcreate.o fclean.o fclean
