FN = main.c
BIN = bin
CFLAGS = -Wall -Wextra -Wpedantic
CVER = 11
OPTLVL = 0
.PHONY: run build ${BIN} remove

run:build
	./${BIN}

build:${BIN}

${BIN}:${FN}
	clang -std=c${CVER} ${FN} -O${OPTLVL} -o ${BIN} ${CFLAGS}

remove:
	rm compile_flags.txt
	rm Makefile
	rm ${FN}
	rm ${BIN}

