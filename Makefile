CC=gcc -g -Wall

errchk.o: errchk.c errchk.h
	$(CC) -c errchk.c

test_errchk: errchk.o test_errchk.c
	$(CC) -o test_errchk test_errchk.c errchk.o

clean:
	rm -f errchk.o test_errchk
