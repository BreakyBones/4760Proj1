CC	= gcc -g3
CFLAGS  = -g3
TARGET1 = child
TARGET2 = parent 

OBJS1	= oss.c
OBJS2	= user.c

all:	$(TARGET1) $(TARGET2)

$(TARGET1):	$(OBJS1)
	$(CC) -o $(TARGET1) $(OBJS1)

$(TARGET2):	$(OBJS2)
	$(CC) -o $(TARGET2) $(OBJS2)

child.o:	child.c
	$(CC) $(CFLAGS) -c child.c 

parent.o:	parent.c
	$(CC) $(CFLAGS) -c parent.c

clean:
	/bin/rm -f *.o $(TARGET1) $(TARGET2)
