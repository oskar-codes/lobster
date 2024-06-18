.SILENT:

CC         = gcc
ASAN_FLAGS = -fsanitize=address -fno-omit-frame-pointer -Wno-format-security
ASAN_LIBS  = -static-libasan
CFLAGS    := -Wall -Werror --std=gnu99 -g3
LDFLAGS   += -lpthread


SRCS = $(wildcard *.c)
OBJS=$(subst .c,.o,$(SRCS))
TARGETS = main

main: ${OBJS} main.o
	$(CC) -o $@ $(CFLAGS) $(ASAN_FLAGS) $(CURL_CFLAGS) $^ $(LDFLAGS) $(CURL_LIBS) $(ASAN_LIBS)
all: ${TARGETS}

style:
	astyle -n -o -A14 -s2 -xt0 *.[ch]
clean::
	-@/bin/rm -f *.o *~  .depend $(TARGETS)

