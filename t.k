/basic smoke test
-1
-0
0-0
1-2

/basic vector ops
a:!9
a+1
1+1
a+a
a-a+a
a
b:-a
b
c:2!a
c
c:c,c
c
#c
\w
\v

/ws should be zero
a:b:c:0
\w
\v

/enlist
x:,2
x:x,x,x,x
x
\w
@x
x@1
x:0
\w

/scan
+/!9
-/!9

/over
+\|!5
*\1+!5

\w
\\

/:~
