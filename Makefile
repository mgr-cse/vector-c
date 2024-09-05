OBJS = vec_test.o vec.o
HEADERS =

CFLAGS = -g
LIBS =

vec_test: $(OBJS)
	cc $(CFLAGS) -o $@ $^ $(LIBS) 

%.o: %.c $(HEADERS)
	cc -c $(CFLAGS) -o $@ $<

.PHONY: clean

clean:
	rm *.o vec_test

