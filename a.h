//!\file a.h \brief less is more \copyright (c) 2024 arthur whitney and the regents of kparc \license public domain

//!headers for syscalls and stdlib functions
#include<unistd.h> //write(2)
#include<string.h> //strlen memcpy strchr
#include<stdlib.h> //malloc
#include<stdio.h>  //sprintf

//!minimal type system
typedef unsigned char c;typedef unsigned long long u;    //!< type c is just a shorthand for byte, but type u requires more words:
                                                         //!< although u is formally defined as ull (an unsigned 64bit integer),
                                                         //!< it is in fact an *opaque type*, i.e. k/simple uses it for everything,
                                                         //!< e.g. u can be: an atom (0..255), a vector pointer or a function pointer.
                                                         //!< since k/simple only supports a single atom type (8bit integer),
                                                         //!< atoms are expensive, since 7 out of 8 bytes of u are wasted. however,
                                                         //!< vectors of atoms do not incur this tax, because they are allocated with
                                                         //!< one extra leading byte which holds its length in bytes:

                                                         //!< k/simple memory layout for vectors:
                                                         //!<  vector x: |n|aaaaaaaaaaa....
                                                         //!<             ^ ^
                                                         //!<             | pointer to x points to its 0'th item, all a's are 8bit wide
                                                         //!<             byte prior to 0'th item of x holds the length of x (max 255 items)

                                                         //!< \note it would make sense to redefine u as an alias for uintptr_t to reduce
                                                         //!< pressure on 32bit targets, e.g. for wasm32 there is no reason for u to
                                                         //!< be 8 bytes wide. uintptr_t is basically sizeof(void*) and requires <stdint.h>.
                                                         //!< for simplicity, we keep u as ull for now.

//!minimal atwc
#define R return                                         //!< unclutter
#define $(a,b) if(a)b;else                               //!< handy shorthand for if-then-else. beware of dangling else!
#define i(n,e) {int $n=n;int i=0;for(;i<$n;++i){e;}}     //!< execute expression e n times, loop counter i is accessible from e

#define _(e) ({e;})                                      //!< isolate expression e in its own lexical scope and clamp it with ;
                                                         //!< note the outer parens, which is a very powerful c trick: they turn _(e) into a so called
                                                         //!< r-value, which basically means we can do x=_(e) for as long as e evaluates to or returns
                                                         //!< at least anything at all, i.e. not void. this macro is fundamental to k/simple implementation.
                                                         //!< l-/r-values are fundamental to c, good mnemonic is (l)eft/(r)ight although not 100% precise.

//!functions
#define _u(f,e,x...) u f(x){R(u)_(e);}                   //!< generic function definition template: f name, x args, e body, all functions return some u
#define f(g,e) _u(g,e,u x)                               //!< define a monadic function g: takes arg x of type u and returns some u, e is body
#define F(g,e) _u(g,e,u f,u x)                           //!< define a dyadic function g: takes args f and x of type u, returns some u, or:
                                                         //!< define an adverb g: takes function pointer f to some verb and its only arg x (nyi)
#define G(g,e) _u(g,e,u f,u x,u y)                       //!< define an adverb g: takes function pointer f, x and y are the args, returns some u (nyi)
#define us(f,e) _u(f,e,c*s)                              //!< define a function f which takes a string s as its only argument, e is body

//!accessors for x
#define ax (256>x)                                       //!< is x an atom? (atoms are 0..255, x presumed to be of type u)
#define sx ((c*)x)                                       //!< reinterpret x as char pointer (ie as string or byte vector)
#define xi (nx>i?sx[i]:0)                                //!< return i'th element of vector x or 0 if i is out of bounds
#define nx sx[-1]                                        //!< length of vector x (stored in the byte preceding the actual data \see typedef u)
#define x(a,e) _(u x=a;e)                                //!< whatever a is, call it x and then execute some expression e in a separate lexical scope
#define y(a,e) _(u y=a;e)                                //!< (ditto for y) idea of x()/y() is to make use of standard accessors eg ax xi etc

//!accessors for r
#define sr x(r,sx)                                       //!< reinterpret r as char pointer (ie as string or byte vector) \see sx
#define nr x(r,nx)                                       //!< length of vector r
#define ri sr[i]                                         //!< get i'th element of vector r

//!accessors for f
#define af x(f,ax)                                       //!< is f an atom?
#define nf x(f,nx)                                       //!< length of vector f
#define sf x(f,sx)                                       //!< reinterpret r as char pointer (ie as string or byte vector)
#define fi x(f,xi)                                       //!< return i'th element of vector f or 0 if i is out of bounds

//!error handling
u Q=96;                                                  //!< Q is magic number for error (ascii for `backtick)
#define Q(e)  if(Q==(e))R Q;                             //!< if some e evaluates to Q, return error
#define Qr(e) if(e){R err((u)__func__,(u)"rank");}       //!< if some e evaluates to true, throw rank error
#define Qz(e) if(e){R err((u)__func__,(u)"nyi");}        //!< ditto for not yet implemented
#define Ql()          err((u)__func__,(u)"length")       //!< throw length error unconditionally

//!all of the above coming together:
#define r(n,e) _(u r=a(n);i(n,ri=e)r)                    //!< (r)esult macro is the foundation of k/simple and is ubiqutous in a.c. it reads:
                                                         //!< (a)llocate a new vector r of size n, then apply some (e)xpression to it, then return r.

                                                         //!< here are few basic examples to illustrate what "apply" means:

                                                         //!< u x=r(8,2*i);        //!< x is (0,2,4,6,8,10,12,14)
                                                         //!< u f=r(8,pow(2,i));   //!< f is (1,2,4,8,16,32,64,128,256)
                                                         //!< u y=r(8,xi==fi);     //!< y is (0,1,1,0,0,0,0,0)

//:~
