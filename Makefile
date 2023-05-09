build:
	gcc Question1.c -o Question1.out
	gcc Question2.c -o Question2.out

clean:
	rm -f *.exe

all: clean build

run:
	./Question1.out
	./Question2.out

