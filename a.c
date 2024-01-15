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
                                                    //!< \note it is fine to declare it globally, since k/simple runs on a single thread.

f(si,sprintf(b,"%d ",(int)(128>x?x:x-256));b)       //!< (s)tring from (i)nteger: format a given atom x as decimal into buffer b using sprintf(3):
                                                    //!< if x is in 0..127 print it as is, otherwise offset it by 256 into the negative range.
f(wi,w(si(x)))                                      //!< (w)rite (i)nteger: format x and (w)rite it to stdout.
f(w_,$(ax,wi(x))i(nx,wi(xi))w(10))                  //!< (w)rite to repl: if x is an atom, format and print it, otherwise print all items of vector x,
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
//F(Add,ax?af?(c)(f+x):Add(x,f):                    //!< dyadic x+y is add. operands can be both atoms and verbs, ie. a+a, a+v, v+a, v+v are all valid.
// af?_(i(nx,sx[i]+=f)x):nx-nf?Ql():r(nx,xi+fi))    //!< \note that in case of v+v addition of elements is pairwise, so vectors must be of same length.
                                                    //!< in Add() we encounter what is infomally known as "ternary cascade", which takes time to get used to,
                                                    //!< so let's reformat the function body to make the control flow a bit easier to follow:
F(Add,ax?af?(c)(f+x)                                //!< case a+a: if (f,x) are atoms, compute their sum and handle possible overflows by downcasting it to c.
           :Add(x,f)                                //!< case v+a: if f is a vector and x is an atom, make a recursive call with operands swapped, i.e. a+v.
        :af?_(i(nx,sx[i]+=f)x)                      //!< case a+v: if f is an atom, modify vector x in place by adding f to its every element and return x.
           :nx-nf?Ql()                              //!< case v+v: if (f,x) are vectors, first make sure they are of the same length, throw length error if not.
                 :r(nx,xi+fi))                      //!<           if lengths are the same, return a new vector holding their pairwise sum.
                                                    //!<           \note the inequality test is nx-nf instead of nx!=nf, which is a staple convention in atwc.

F(Sub,Add(f,sub(x)))                                //!< dyadic x-y is subtract. since we already have Add() and sub(), we get Sub() for free by negating x.
F(Ind,Qr(!f)r(nx,xi%f))
F(Cnt,Qr(!af)r(f,ax?x:xi))
F(Cat,f=af?cat(f):f;x=ax?cat(x):x;u r=a(nf+nx);m(nx,r+nf,x);m(nf,r,f))
F(At,Qr(af)ax?sf[x]:r(nx,sf[xi]))
f(at,At(x,0))

//!verb dispatch
char*V=" +-!#,@";                                    //!< V is a string which holds tokens of all supported k verbs. 0'th item (space) is nop.
u(*f[])(u  )={0,foo,sub,ind,cnt,cat,at},             //!< f[] is an array of pointers to c functions which implement monadic versions of k verbs listed in V.
 (*F[])(u,u)={0,Add,Sub,Ind,Cnt,Cat,At},             //!< F[] is ditto for dyadic versions of verbs listed in V.
 U[26];                                              //!< array of global variables abc..xyz \todo

                                                     //!< transposition of V, f[] and F[] gives the following matrix:

                                                     //!<    verb   monadic    dyadic     semantics
                                                     //!<           0          0          nop   nop
                                                     //!<       +   foo        Add        nyi   add
                                                     //!<       -   sub        Sub        neg   sub
                                                     //!<       !   ind        Ind        til
                                                     //!<       #   cnt        Cnt        cnt
                                                     //!<       ,   cat        Cat        enl   cat
                                                     //!<       @   at         At         fst

f(v,(strchr(V,x)?:V)-V)                              //!< is x a valid verb from V? if so, return its index, otherwise return 0.
f(n,10>x-48?x-48:U[x-97])                            //!< is x a noun?  valid nouns are digits 0..9 and lowercase ascii abc..xyz.   \todo

//!\todo
us(e,u i=*s++;
    v(i)?x(e(s),Q(x)f[v(i)](x))
        :x(n(i),*s?y(e(s+1),Q(y)F[v(*s)](x,y)):x))
int main(){char s[99];w((u)"k/simple (c) 2024 atw/kpc\n");while(1)if(w(32),s[read(0,s,99)-1]=0,*s)w_(e(s));}

//:~
