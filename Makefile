#gcc cmd
GCC = gcc -o3 -std=c99 -Wall -Wshadow -Wvla -pedantic

run-a-%: gcc
	@echo "executing pa1 array $*..."
	@./build/pa1 -a examples/$*.b outputs/$*.b
	@echo "done"

run-l-%: gcc
	@echo "executing pa1 list $*..."
	@./build/pa1 -l examples/$*.b outputs/$*_ll.b
	@echo "done"

test-%: run-a-% run-l-%
	@echo "diffing $*..."
	@diff outputs/$*.b outputs/$*_ll.b
	@echo "$* OK"

test_all: \
	test-15 \
	test-1K \
	test-10K \
	test-100K #\
      #test-1M

.PHONY: gcc
gcc: *.c *.h
	@echo "compiling C files..."
	@$(GCC) *.c *.h -o build/pa1
	@echo "done"

%: %.c %.h
	@echo "compiling $*..."
	@$(GCC)  $*.c $*.h -o build/$*.o
	@echo "done"

clean:
	@rm -rf build/* outputs/*
