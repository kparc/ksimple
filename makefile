O=-Os -Werror -Wno-pointer-sign
all:
	@cc $O -oa a.c

mm: all
	@cat a.h a.c | python -c "import sys,re;t=sys.stdin.read(); \
		t=re.sub(r';\n', ';', t); \
		t=re.sub(r' {2,}\/\/!.+\n', '\n', t); \
		t=re.sub(r'\n{2,}', '\n', t, flags=re.MULTILINE); \
		t=re.sub(r'\n {2,}', '', t, flags=re.MULTILINE); \
		t=re.sub(r',\n ', ',', t, flags=re.MULTILINE); \
		t=re.sub(r' {2,}', '', t); \
		t=re.sub(r'#include\"a.h\".*\n', '', t); \
		t=re.sub(r'\n\/\/', '\n\n//', t, flags=re.MULTILINE); \
		print(t, end='')" > a.min.c

	@cc $O -omm a.min.c
	@diff a mm

m: mm
	@cat a.min.c | python -c "import sys,re;t=sys.stdin.read(); \
		t=re.sub(r'\n\/\/.+\n', '', t, flags=re.MULTILINE); \
		t=re.sub(r'];\n', '];', t, flags=re.MULTILINE); \
		t=re.sub(r'\";\n', '\";', t, flags=re.MULTILINE); \
		print(t, end='')" > a.m.c

	@cc $O -om a.m.c
	@diff a m
