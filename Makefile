#
# Makefile for project4 csc421.241
# last-update:
# 	13 nov 2022 -bjr:
# 	 5 nov 2023 -bjr:
#

V=
# comment out for not verbose
V= -vv 

RED= \033[0;31m
GREEN= \033[0;32m
NC= \033[0m

F= fat-reduced
G= fat-reduced-util

$F: $F.c $G.o $F.h
	cc -o $@ $< $G.o
	
$G.o: $G.c $F.h
	cc -c $< 

run: $F
	./$< $V

test:
	make clean
	make $F
	@echo "${RED}testing ... ${NC}"
	cat test1.run | ./$F > test.out
	diff test1.ref test.out
	@echo "*** ${GREEN}PASSED the test ${NC}***"

clean:
	-rm $F $G.o test.out
