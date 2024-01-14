//!\file k.c \brief bare minimum atw-style interpreter for learning purposes
//!\copyright 2024 atw & regents of kparc \license mit

#include"a.h"                                       //fF[+-!#,@] atom/vector 1byteint 1bytetoken  no(memmanage parser tokens ..) cc -Os -oa a.c -w

                                                    //! this is a brief description of k/simple from atw:
                                                    //! he says:       he means:
                                                    //! fF[+-!#,@]     we have 6 verbs [+ - ! # , @] in both monadic and dyadic contexts, total of 12
                                                    //!                (since monadic plus is nyi, we actually have 11, so roll your own f[+])
                                                    //! atom/vector    k/simple sports atoms and vectors
                                                    //! 1byteint       only supported atom/vector type is 8bit integer
                                                    //! 1bytetoken     input tokenizer is spartan: a token can't be longer than one char
                                                    //! no(...)        no memory management, no parser and no tokenizer are implemented
                                                    //! cc -w ..       build it like so

//!printing facilities
f(w,write(1,ax?(u)&x:x,ax?1:strlen(x)))             //!< (w)rite to stdout: if x is an atom, print its decimal value, otherwise print x as ascii string.
c b[12];                                            //!< temporary string (b)uffer for storing a formatted vector item.
                                                    //!< \note it is fine to declare it globally, since k/simple runs on a single thread.

f(si,sprintf(b,"%d ",128>x?x:x-256);b)              //!< (s)tring from (i)nteger: format a given atom x as decimal into buffer b using sprintf(3):
                                                    //!< if x is in 0..127 print it as is, otherwise offset it by 256 into the negative range.
f(wi,w(si(x)))                                      //!< (w)rite (i)nteger: format x and (w)rite it to stdout.
f(w_,$(ax,wi(x))i(nx,wi(xi))w(10))                  //!< (w)rite to repl: if x is an atom, format and print it, otherwise do the same for all items of x,
                                                    //!< i.e. print vector items separated by space. output is terminated by a newline aka ascii 10.
F(err,w(f);w(58);w(x);w(10);Q)                      //!< throw error: print the name of the (f)unction where error occured, followed by colon(58),
                                                    //!< followed by error message x (eg "rank"/"nyi"), terminated by a newline. \return Q aka error code.

//!memory management
G(m,(u)memcpy((void*)x,(void*)y,f))                 //!< (m)ove: x and y are pointers to source and destination, f is number of bytes to be copied from x to y.
                                                    //!< \note memcpy(3) assumes that x/y don't overlap in ram, which in k/simple they can't. \see memmove(3)
f(a,c*s=malloc(x+1);*s++=x;(u)s)                    //!< (a)llocate: allocate x bytes of memory for a vector of size x plus one extra preamble byte,
                                                    //!< store the size x in the preamble and return pointer to the 0'th element \see a.h type system

//!monadic verbs
f(foo,Qz(1)0)                                       //!< (foo)bar is a dummy monadic verb: for any x, it just throws nyi and returns 0.

f(sub,ax?(c)-x:r(nx,-xi))                           //!< monadic (sub)tract is also known as (inv)erse, or -x: if x is atom, return its additive inverse,
                                                    //!< if x is a vector, reverse the sign of its every element in-place. in either case, return x.

f(ind,Qr(!ax)r(x,i))                                //!< monadic (ind)ex is her majesty til aka apl iota aka !x. for a given atom x, it returns a vector
                                                    //!< of x integers from 0 to x-1. if x is not an atom, til throws a rank error.

f(cnt,Qr(ax)nx)                                     //!< monadic (c)ou(nt) is #x. it returns the length of a given vector and throws rank error for atoms.

f(cat,Qr(!ax)r(1,x))                                //!< monadic (cat)enate is enlist, or comma-x: it wraps a given atom x into a new vector of length 1 which
                                                    //!< only item holds the value that atom. if x is a vector, enlist will throw a rank error.

//!dyadic verbs \todo
F(Add,ax?af?f+x:Add(x,f):r(nx,(af?f:fi)+xi))
F(Sub,Add(f,sub(x)))
F(Ind,Qr(!f)r(nx,xi%f))
F(Cnt,Qr(!af)r(f,ax?x:xi))
F(Cat,f=af?cat(f):f;x=ax?cat(x):x;u r=a(nf+nx);m(nx,r+nf,x);m(nf,r,f))
F(At,Qr(af)ax?sf[x]:r(nx,sf[xi]))f(at,At(x,0))

//!verb dispatch
char*V=" +-!#,@";                                    //!< string which holds interpretable k verbs. 0'th item (space) is nop.
u(*f[])()={0,foo,sub,ind,cnt,cat,at},                //!< f is an array of pointers to c functions which implement monadic versions of k verbs listed in V.
 (*F[])()={0,Add,Sub,Ind,Cnt,Cat,At},                //!< ditto for dyadic versions of verbs listed in V.
 U[26];                                              //!< array of global variables abcd..xyz (nyi, warrants a separate discussion)

//!combination of V, f[] and F[] translates to the following matrix:

//!    verb   monadic    dyadic     semantics
//!           0          0          nop     nop
//!       +   foo        Add        nyi     add
//!       -   sub        Sub        inverse subtract
//!       !   ind        Ind        til
//!       #   cnt        Cnt        count
//!       ,   cat        Cat        enlist  catenate
//!       @   at         At

//!\todo
f(v,(strchr(V,x)?:V)-V)
f(n,10>x-48?x-48:U[x-97])
us(e,u i=*s++;v(i)?x(e(s),Q(x)f[v(i)](x)):x(n(i),*s?y(e(s+1),Q(y)F[v(*s)](x,y)):x))
int main(){w("k/simple (c) 2024 atw/kpc"),w(10);char s[99];while(1)if(w(32),s[read(0,s,99)-1]=0,*s)w_(e(s));}

//:~
