all:
	@cc -Os -oa a.c -Werror -Wno-pointer-sign
	@./a
