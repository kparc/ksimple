all:
	@cc -O0 -g -oa a.c -Werror -Wno-pointer-sign
	@./a
