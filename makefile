.PHONY	:= all clean
CC		:= gcc
CFLAGS	:= -g -Wall -Wextra -MP -MD

SRC		:= $(wildcard ./*.c)
OBJ		:= $(SRC:%.c=%.o)

all:	bin

bin:	$(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o:	./%.c	
	$(CC) $(CFLAGS) -c $<



clean:
	rm -rf *.dSYM *.o *.d bin

