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
f(W,Q(x)$(ax,wi(x))i(nx,wi(xi))w(10))               //!<  pretty print x: if x is an atom, format and print it, otherwise print all items of vector x,
                                                    //!< separated by space. terminate output by a newline aka ascii 10.
G(err,w(f);w(58);wi(x);w(y);w(10);Q)                //!< (err)or: print name of the c (f)unction where error occured, line number and error msg, return Q.

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
                                                    //!< \note rarely seen ternary form x?:y, which is just a shortcut for x?x:y in c.
f(n,10>x-48                                         //!< is x a (n)oun? valid nouns are digits 0..9 and lowercase varnames a..z.
           ?x-48                                    //!< if x is a digit, e.g. '7', n() returns its decimal value.
           :g(x)?U[x-97]                            //!< if x is a varname, e.g. 'a', n() returns its value from U[26].
                :Q)                                 //!< ..anything else is an error.

us(e,                                               //!< (e)val: recursively tokenize and evaluate input tape s, and return the final result:
   c*t=s;c i=*t++;                                  //!< t is a temporary pointer to s. read the current token into i and advance temporary tape pointer.
   !*t?x(n(i),Qp()x)                                //!< if next token after i is null (ie end of tape): final token must be a noun, so return it, otherwise:
      :v(i)?x(                                      //!< in case if i is a valid verb:
              e(t),Q(x)                             //!<   recursively evaluate next token after i and put resulting noun into x. bail out on error.
              f[v(i)](x))                           //!<   apply monadic verb i to the operand x and return the result, which can be either nounmn or error.
           :y(                                      //!< in case if i is not a verb, it must be a valid noun, and the next token after a noun should be a verb,
              e(t+1),Q(y)                           //!<   recursively evaluate next token to the right of the verb and put result into y. bail out on error.
              58==*t                                //!<   special case: if y is preceded by a colon instead of a verb, it is an inline assignment (eg 1+a:1),
                    ?x(g(i),Qp()U[i-97]=y)          //!<   so i should be a valid (g)lobal a..z. if so, store y in U[26] and return it. if not, throw parse error.
                    :x(n(i),Qp()                    //!<   x is a noun to the left of the verb. throw parse error if it is invalid.
                         c f=v(*t);Qd(!f)           //!<   f is the index of the verb to the left of noun y. if it's not a valid verb, throw domain error.
                         F[f](x,y))))               //!< apply dyadic verb f to nouns x and y (e.g. 2+3) and return result (noun or error).
 
//!repl
int main(){c b[99];w(ba);                           //!< entry point. print benner, buffer b will hold user input up to 99 chars.
  while(1)                                          //!< enter infinite read-eval-print loop until ctrl+c is pressed or segfault is caught.
   if(w(32),b[read(0,b,99)-1]=0,*b)                 //!< write prompt (single space), then wait for input from stdin which is read into t.
    x(e(b),                                         //!< evaluate buffer t and put result into x, otherwise:
      58==b[1]?x                                    //!<   if b starts with a global assignment e.g. a:7, suppress output and cycle repl.
              :W(x));                               //!<     otherwise, pretty print evaluation result to stdout, then cycle repl.
  R 0;}                                             //!< in c, return value of main() is the exit code of the process, 0 is success.

//:~
