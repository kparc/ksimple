//!\file k.c \brief bare minimum atw-style k interpreter for learning purposes \copyright (c) 2024 arthur whitney and the regents of kparc \license mit

#include"a.h"                                       //fF[+-!#,@] atom/vector 1byteint 1bytetoken  no(memmanage parser tokens ..) cc -Os -oa a.c -w

                                                    //! above is a brief description of k/simple system by atw:
                                                    //! he says:       he means:
                                                    //! fF[+-!#,@]     we have 6 verbs [+ - ! # , @] in both monadic and dyadic contexts, total of 12
                                                    //!                (since monadic plus is nyi, we actually have 11, feel free to implement f[+])
                                                    //! atom/vector    k/simple sports atoms and vectors!
                                                    //! 1byteint       the only supported atom/vector type is 8bit integer, so beware of overflows
                                                    //! 1bytetoken     input tokenizer is spartan: a token can't be longer than one char
                                                    //! no(...)        no memory management, no parser and no tokenizer are implemented
                                                    //! cc -w ..       minimal build instructions (which are much more stringent in provided makefile)

//!printing facilities
f(w,write(1,ax?(c*)&x:sx,ax?1:strlen(sx)))          //!< (w)rite to stdout: if x is an atom, print its decimal value, otherwise print x as ascii string.
c b[12];                                            //!< temporary string (b)uffer for storing a formatted vector item.
                                                    //!< \note it is fine to declare b globally, since k/simple runs on a single thread.

f(si,sprintf(b,"%d ",(int)(128>x?x:x-256));b)       //!< (s)tring from (i)nteger: format a given atom x as decimal into buffer b using sprintf(3):
                                                    //!< if x is in 0..127 print it as is, otherwise offset it by 256 into the negative range.
f(wi,w(si(x)))                                      //!< (w)rite (i)nteger: format x and (w)rite it to stdout.
f(w_,Q(x)$(ax,wi(x))i(nx,wi(xi))w(10))              //!< (w)rite to repl: if x is an atom, format and print it, otherwise print all items of vector x,
                                                    //!< separated by space. terminate output by a newline aka ascii 10.
F(err,w(f);w(58);w(x);w(10);Q)                      //!< throw error: print the name of the (f)unction where error occured, followed by colon(58),
                                                    //!< followed by error message x (eg "rank"/"nyi"), terminated by a newline. \return Q aka error code.

//!memory management
G(m,(u)memcpy((void*)x,(void*)y,f))                 //!< (m)ove: x and y are pointers to source and destination, f is number of bytes to be copied from x to y.
                                                    //!< \note memcpy(3) assumes that x/y don't overlap in ram, which in k/simple they can't, but \see memmove(3)
f(a,c*s=malloc(x+1);*s++=x;(u)s)                    //!< (a)llocate x bytes of memory for a vector of length x plus one extra preamble byte, store the length
                                                    //!< in the preamble, and return pointer to the 0'th element of a new vector \see a.h type system

//!monadic verbs
f(foo,Qz(1)Q)                                       //!< (foo)bar is a dummy monadic verb: for any x, throw nyi error and return error code Q.

f(sub,ax?(c)-x:r(nx,-xi))                           //!< monadic (sub)tract is also known as (neg)ation, or -x: if x is atom, return its additive inverse.
                                                    //!< if x is a vector, return a new vector same as x only with sign of its every element flipped.

f(ind,Qr(!ax)r(x,i))                                //!< monadic (ind)ex is her majesty apl iota aka til aka !x. for a given atom x, it returns a vector
                                                    //!< of x integers from 0 to x-1. if x is not an atom, til throws a rank error.

f(cnt,Qr(ax)nx)                                     //!< monadic (c)ou(nt) is #x. it returns the length of a given vector and throws rank error for atoms.

f(cat,Qr(!ax)r(1,x))                                //!< monadic (cat)enate is (enl)ist, or comma-x: wraps a given atom x into a new vector of length 1 whose
                                                    //!< only item holds the value of that atom. if x is a vector, enlist will throw a rank error.

//!dyadic verbs 
F(Add,                                              //!< dyadic f+y is add. operands can be both atoms and verbs, ie. a+a, a+v, v+a, v+v are all valid.
  ax?af?(c)(f+x)                                    //!< case a+a: if (f,x) are atoms, compute their sum and handle possible overflows by downcasting it to c.
       :Add(x,f)                                    //!< case v+a: if f is a vector and x is an atom, make a recursive call with operands swapped, i.e. a+v.
    :af?_(i(nx,sx[i]+=f)x)                          //!< case a+v: if f is an atom, modify vector x in place by adding f to its every element and return x.
       :nx-nf?Ql()                                  //!< case v+v: if (f,x) are vectors, first make sure they are of the same length, throw length error if not.
             :r(nx,xi+fi))                          //!<           if lengths are the same, return a new vector holding their pairwise sum.
                                                    //!< \note by convention, atwc uses x-y for inequality test, which has the same effect as nx!=nf.

F(Sub,Add(f,sub(x)))                                //!< dyadic f-x is subtract. since we already have Add() and sub(), we get Sub() for free by negating x.
F(Ind,Qr(!f||!af)ax?x%f:r(nx,xi%f))                 //!< dyadic f!x is x (mod)ulo f, aka remainder operation. f must be an non-zero atom, x can be anything.
F(Cnt,Qr(!af)r(f,ax?x:sx[i%nx]))                    //!< dyadic f#x is (tak)e, which has two variants based on the type of right opearnd (left must be atom):
                                                    //!<  if x is a vector, return first f items of x. if f exceeds the size of x, wrap around from the start.
                                                    //!<  if x is an atom, return a vector of length f filled with x.

F(Cat,                                              //!< dyadic f,x is (cat)enate: a) join two vectors b) join an atom to vector c) make a vector from two atoms.
  f=af?cat(f):f;                                    //!< if f is an atom, enlist it \see cat()
  x=ax?cat(x):x;                                    //!< ditto for x
  u r=a(nf+nx);                                     //!< (a)llocate array r long enough to hold f and x.
  m(nx,r+nf,x);m(nf,r,f))                           //!< (m)ove (or more precisely, copy) contents of f and x to r, one after another, and return pointer to r.

F(At,Qr(af)                                         //!< dyadic f@x is "needle at x in the haystack f" and has two modes based on the type of x (f must be a vector):
  ax?x>nf?Ql():sf[x]                                //!<  if x is an atom, return the x'th item of f.
    :r(nx,sf[xi]))                                  //!<  if x is a vector, return a vector containg items from f at indices listed in x.
                                                    //!< \note that the second mode currently doesn't perform the boundary check, fell free to implement it!

f(at,At(x,0))                                       //!< monadic @x is simply (f)ir(st): return the head element of x, or throw a rank error if x is an atom.

//!verb dispatch
char*V=" +-!#,@";                                   //!< V is an array of tokens of all supported k verbs. 0'th item (space) is nop.
u(*f[])(u  )={0,foo,sub,ind,cnt,cat,at},            //!< f[] is an array of pointers to c functions which implement monadic versions of k verbs listed in V.
 (*F[])(u,u)={0,Add,Sub,Ind,Cnt,Cat,At},            //!< F[] is ditto for dyadic versions of verbs listed in V.
 U[26];                                             //!< global namespace: array of values of variables abc..xyz. in c, global arrays are initialized with zeroes.

                                                    //!< transposition of V, f[] and F[] gives the following matrix:

                                                    //!<  verb   monadic  dyadic  semantics
                                                    //!<     +   foo      Add     nyi   add
                                                    //!<     -   sub      Sub     neg   sub
                                                    //!<     !   ind      Ind     til   mod
                                                    //!<     #   cnt      Cnt     cnt   tak
                                                    //!<     ,   cat      Cat     enl   cat
                                                    //!<     @   at       At      fst   at

//!globals, verbs, nouns
f(g,x>='a'&&x<='z')                                 //!< is x a valid (g)lobal variable identifier?
f(v,(strchr(V,x)?:V)-V)                             //!< is x a valid (v)erb from V? if so, return its index, otherwise return 0.
                                                    //!< \note a rarely seen ternary form x?:y, which is just a shortcut for x?x:y in c.
f(n,10>x-48?x-48:g(x)?U[x-97]:Q)                    //!< is x a (n)oun? valid nouns are digits 0..9 and lowercase ascii chars abc..xyz.
                                                    //!< if i is a digit, e.g. '7', n() returns its decimal value.
                                                    //!< if i is a varname, e.g. 'a', n() returns its value U[26].

//!eval
us(e,                                               //!< (e)val: recursively tokenize and evaluate input tape s, and return the final result:
    u i=*s++;                                       //!< read the current token into i and advance tape.
    v(i)?x(                                         //!< in case if i is a valid verb:
          e(s),Q(x)                                 //!<   recursively evaluate next token after i and put result into x. bail out on error.
          f[v(i)](x))                               //!<   apply monadic verb i to the operand x and return the result, which can be either noun or error.
        :x(n(i),Qp(Q==x)                            //!< in case if i is not a verb, it must be a valid noun, and we assign its value to x.
           Qp(*s&&!v(*s))                           //!<   if there are more tokens on tape, the next token after a noun can only be a verb.
           *s?y(e(s+1),Q(y)                         //!<   recursively evaluate the token to the right of the verb and put result into y. bail out on error.
                F[v(*s)](x,y))                      //!<   apply dyadic verb at *s to nouns x and y. return value can be noun or error.
             :x))                                   //!<   end of tape: return the noun in x (last token can only be a noun).

//!repl
int main(){c s[99];w(ba);                           //!< entry point. print banner, buffer s will hold repl input up to 99 chars.
  while(1)                                          //!< enter infinite read-eval-print loop until ctrl+c is pressed or segfault is caught.
   if(w(32),s[read(0,s,99)-1]=0,*s)                 //!< write prompt (single space), then wait for input from stdin which is read into s.
     x(*s,x=g(x)&&s[1]==':'?x:0;                    //!< if input starts with global assignment e.g. a:7, retain variable name in x.
       y(e(s+2*!!x),                                //!< (e)valuate input string, optionally skipping first two tokens in case of assignment.
        $(x&&y-Q,U[x-97]=y)                         //!< if assignment is pending and eval was successful, store result in U[] and suppress output,
         w_(y)));                                   //!< otherwise, pretty-print evaluation result to stdout and cycle repl.
  R 0;}                                             //!< in c, main() must return an exit code of the process (by convention, 0 is 'success').

//:~
