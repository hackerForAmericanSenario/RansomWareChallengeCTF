NAME = RansomWare
OBJS = main.o          \
       file_interact.o \
       get_key.o

all: $(OBJS)
	gcc -o $(NAME) $(OBJS)

clean:
	rm -rf $(NAME) $(OBJS)

main.o: srcs/main.c includes/include.h
	gcc -c srcs/main.c
file_interact.o: srcs/file_interact.c includes/file_interact.h
	gcc -c srcs/file_interact.c
get_key.o: srcs/get_key.c includes/get_key.h
	gcc -c srcs/get_key.c