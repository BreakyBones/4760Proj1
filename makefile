CC	= gcc -g3
CFLAGS  = -g3

all: oss user

oss: oss.c
	$(CC) $(CFLAGS) -o $@ $<

user: user.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f oss user
