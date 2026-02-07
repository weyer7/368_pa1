compile: *.c *.h
	echo "compiling C files..."
	@gcc *.c *.h
	echo "done"