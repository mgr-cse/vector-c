OBJS = vec_test.o libvec.a
HEADERS = vec.h

CFLAGS = -g -Wall -Wextra -Werror -pedantic \
		 -fno-sanitize-recover -fsanitize=undefined \
		 -fsanitize=address -fstack-protector-strong

LIBS =

vec_test.bin: $(OBJS)
	cc $(CFLAGS) -o $@ $^ $(LIBS) 

libvec.a: vec.o
	ar rcs $@ $<

%.o: %.c $(HEADERS)
	cc -c $(CFLAGS) -o $@ $<

str_test.bin: str_test.o
	cc $(CFLAGS) -o $@ $^ $(LIBS)

perf_test.bin: perf_test.o
	cc $(CFLAGS) -o $@ $^ $(LIBS)

.PHONY: clean

clean:
	rm *.o *.bin *.a

