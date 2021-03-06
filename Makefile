SRCS =  mutex.c mypthread_queue.c mypthread.c mypthread_utilities.c mypthread_wrapper.c warrior.c battlefield.c kbhit.c deck.c
INC = mutex.h  mutex_inline.h  mutex_assam.h  mypthread.h  mypthread_queue.h kbhit.h warrior.h
OBJS = $(SRCS:.c=.o)
TEST_SRCS = ejemplo.c
TEST_OBJS = $(TEST_SRCS:.c=.o)
#DEBUG=0

CFLAGS = -Wall -Werror -I. -g
LDFLAGS = -L.
LIB = libmythread.a

AR = /usr/bin/ar
CC = gcc

#ifeq ($(DEBUG),1)
#EXTRA_CFLAGS += -DDEBUG
#endif

.PHONY: all lib clean tags test a5
a5:  all
all: lib test

lib: $(LIB)

libmythread.a: $(OBJS) $(INC)
	$(AR) rcs $(LIB) $(OBJS)

%.o: %.c $(INC)
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TEST_OBJS) $(LIB) *~ tec-royale

tags:
	find . -name "*.[cChH]" | xargs ctags
	find . -name "*.[cChH]" | etags -

test:	$(TEST_OBJS) $(INC) lib
	$(CC) -o tec-royale $(CFLAGS) $(EXTRA_CFLAGS) $(TEST_OBJS) $(LIB)
