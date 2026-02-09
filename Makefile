run: gcc
	@echo "executing pa1..."
	@./build/pa1
	@echo "done"

gcc: *.c *.h
	@echo "compiling C files..."
	@gcc -o3 -Wall -pedantic *.c *.h -o build/pa1
	@echo "done"

%: %.c %.h
	@echo "compiling $*..."
	@gcc -Wall -pedantic $*.c $*.h -o build/$*.o
	@echo "done"

clean:
	@rm -rf build/* outputs/*