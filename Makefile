OBJS = vec_test.o libvec.a
HEADERS = vec.h

CFLAGS = -g
LIBS =

vec_test: $(OBJS)
	cc $(CFLAGS) -o $@ $^ $(LIBS) 

libvec.a: vec.o
	ar rcs $@ $<

%.o: %.c $(HEADERS)
	cc -c $(CFLAGS) -o $@ $<

.PHONY: clean

clean:
	rm *.o vec_test *.a

