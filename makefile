CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = train_booking
OBJECTS = main.o train.o file.o booking.o login.o

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

main.o: main.c train.h
	$(CC) $(CFLAGS) -c main.c

train.o: train.c train.h
	$(CC) $(CFLAGS) -c train.c

file.o: file.c train.h
	$(CC) $(CFLAGS) -c file.c

booking.o: booking.c train.h
	$(CC) $(CFLAGS) -c booking.c

login.o: login.c train.h
	$(CC) $(CFLAGS) -c login.c

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: clean
