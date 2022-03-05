# Compiler flags
CFLAGS=-Wall -std=gnu11 -Werror -g -Wextra -Wpedantic -Wmissing-declarations -Wmissing-prototypes -Wold-style-definition

# Force remove
RM=rm -f

# Main program compilation linking with child and commands modul.
main: mexec.o commands.o child.o
	gcc $(CFLAGS) mexec.o commands.o child.o -o mexec

# Separate file compilation for the command modul
commands: commands.c commands.h
	gcc $(CFLAGS) -c commands.c -o commands.o

# Separate file compilation for the child modul
child: child.c child.h
	gcc $(CFLAGS) -c child.c -o child.o

# Clean workspace
clean:
	$(RM) main *.o
