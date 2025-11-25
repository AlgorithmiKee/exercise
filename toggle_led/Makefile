CC := gcc
CFLAGS := -Wall -Wextra -std=c11 -D__SIMULATOR__ -I.

all: sil_test

sil_test: app.o sim_gpio.o sil_test.o
	$(CC) $(CFLAGS) -o sil_test app.o sim_gpio.o sil_test.o

app.o: app.c gpio_if.h
	$(CC) $(CFLAGS) -c app.c

sim_gpio.o: sim_gpio.c gpio_if.h
	$(CC) $(CFLAGS) -c sim_gpio.c

sil_test.o: sil_test.c gpio_if.h
	$(CC) $(CFLAGS) -c sil_test.c

clean:
	rm -f *.o sil_test
