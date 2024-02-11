//!\file k.c \brief bare minimum atw-style k interpreter for learning purposes \copyright (c) 2024 arthur whitney and the regents of kparc \license mit
#include"a.h"                                       //fF[+-!#,@|] atom/vector 1byteint 1bytetoken  no(parser tokens ..) cc -Os -oa a.c -w

                                                    //! above is a brief description of k/simple system by atw:
                                                    //! he says:       he means:
                                                    //! fF[+-!#,@]     we have 6 verbs [+ - ! # , @ |] in both monadic and dyadic contexts, total of 14
                                                    //!                (since monadic + and dyadic | are nyi, we actually have 12, feel free to implement f[+]/F[|])
                                                    //! atom/vector    k/simple sports atoms and vectors!
                                                    //! 1byteint       the only supported atom/vector type is 8bit integer, so beware of overflows
                                                    //! 1bytetoken     input tokenizer is spartan: a token can't be longer than one char
                                                    //! no(...)        no parser and multichar tokenizer are implemented
                                                    //! cc -w ..       minimal build instructions (which are much more stringent in provided makefile)

//!debug
f(wu,O("%lu\n",x))                                  //!< (w)rite (u)ll: print unsigned long long (e.g. total memory allocation), useful for refcount debugging.
void wg(){i(26,x(U[i],$(!ax,O("%c[%d] %d\n",i+97,nx,rx))))} //!< dump global namespace: varname, refcount, length (also useful for refcount debugging).

//!printing facilities
f(w,write(1,ax?(c*)&x:sx,ax?1:strlen(sx)))          //!< (w)rite to stdout: if x is an atom, print its decimal value, otherwise print x as ascii string.
static c pb[12];                                    //!< temporary string (b)uffer for a formatting vector items. ok to declare globally, since we only have one thread.
f(si,sprintf(pb,"%d ",(int)(128>x?x:x-256));pb)     //!< (s)tring from (i)nteger: format a given atom x as decimal in range (-128..127) into buffer b using sprintf(3).
f(wi,w(si(x)))                                      //!< (w)rite (i)nteger: format x and (w)rite it to stdout.
f(W,Q(x)$(ax,wi(x))i(nx,wi(xi))w(10))               //!< pretty print x: if x is an atom, format and print it, otherwise print all items of vector x,
                                                    //!< separated by space. terminate output by a newline aka ascii 10.
G(err,w(f);w(58);wi(x);w(y);w(10);Q)                //!< (err)or: print name of the c (f)unction where error occured, line number and error msg, return Q.

//!malloc
f(a,y(x+2,WS+=x;c*s=malloc(y);*s++=0;*s++=x;s))     //!< (a)llocate x bytes of memory for a vector of length x plus two extra bytes for preamble, set refcount to 0
                                                    //!< and vector length to x in the preamble, and return pointer to the 0'th element of a new vector \see a.h type system
f(_a,WS-=nx;free(sx-2);0)                           //!< release memory allocated for vector x.
G(m,(u)memcpy((c*)x,(c*)y,f))                       //!< (m)ove: x and y are pointers to source and destination, f is number of bytes to be copied from x to y.
                                                    //!< \note memcpy(3) assumes that x/y don't overlap in ram, which in k/simple they can't, but \see memmove(3)
//!memory management
f(r_,ax?x:(++rx,x))                                 //!< increment refcount: if x is an atom, return x. if x is a vector, increment its refcount and return x.
f(_r,ax?x                                           //!< decrement refcount: if x is an atom, return x.
       :rx?(--rx,x)                                 //!<   if x is a vector and its refcount is greater than 0, decrement it and return x.
          :_a(x))                                   //!<   if refcount is 0, release memory occupied by x and return 0.

//!monadic verbs
f(foo,_r(x);Qz(1);Q)F(Foo,_r(x);Qz(1);Q)            //!< (foo)bar is a dummy monadic verb: for any x, throw nyi error and return error code Q.

f(sub,ax?(c)-x:_x(N(nx,-xi)))                       //!< monadic (sub)tract is also known as (neg)ation, or -x: if x is atom, return its additive inverse.
                                                    //!< if x is a vector, return a new vector same as x only with sign of its every element flipped.

f(til,Qr(!ax)(N(x,i)))                              //!< monadic til is !x aka her majesty apl iota. for a given atom x, it returns a vector
                                                    //!< of x integers from 0 to x-1. if x is not an atom, til throws a rank error.

f(cnt,Qr(ax)nx)                                     //!< monadic (c)ou(nt) is #x. it returns the length of a given vector and throws rank error for atoms.

f(cat,Qr(!ax)N(1,x))                                //!< monadic (cat)enate is (enl)ist, or comma-x: wraps a given atom x into a new vector of length 1 whose
                                                    //!< only item holds the value of that atom. if x is a vector, enlist will throw a rank error.

f(rev,Qr(ax)_x(N(nx,sx[nx-i-1])))                   //!< monadic (rev)erse is |x and simply returns a mirror copy of vector x.

//!dyadic verbs
F(Add,                                              //!< dyadic f+y is add. operands can be both atoms and verbs, ie. a+a, a+v, v+a, v+v are all valid.
  ax?af?(c)(f+x)                                    //!< case a+a: if (f,x) are atoms, compute their sum and handle possible overflows by downcasting it to c.
       :Add(x,f)                                    //!< case v+a: if f is a vector and x is an atom, make a recursive call with operands swapped, i.e. a+v.
    :af?_x(N(nx,f+xi))                              //!< case a+v: if f is an atom, return a new vector constructed by adding f to every element of x.
       :nx-nf?(_x(_f(Ql())))                        //!< case v+v: if (f,x) are vectors, first make sure they are of the same length, throw length error if not.
             :_f(_x(N(nx,xi+fi))))                  //!<           if lengths are the same, return a new vector holding their pairwise sum.
                                                    //!< \note by convention, atwc uses x-y for inequality test, which has the same effect as nx!=nf.

F(Sub,Add(f,sub(x)))                                //!< dyadic f-x is subtract. since we already have Add() and sub(), we get Sub() for free by negating x.
F(Mod,Qr(!f||!af)ax?x%f:_x(N(nx,xi%f)))             //!< dyadic f!x is x (mod)ulo f, aka remainder operation. f must be an non-zero atom, x can be anything.
F(Tak,Qr(!af)_f(N(f,ax?x:sx[i%nx])))                //!< dyadic f#x is (tak)e, which has two variants based on the type of right operand (left must be atom):
                                                    //!<  if x is a vector, return first f items of x. if f exceeds the size of x, wrap around from the start.
                                                    //!<  if x is an atom, return a vector of length f filled with x.

F(Cat,                                              //!< dyadic f,x is (cat)enate: a) join two vectors b) join an atom to vector c) make a vector from two atoms.
  f=af?cat(f):f;                                    //!< if f is an atom, enlist it \see cat()
  x=ax?cat(x):x;                                    //!< ditto for x
  u r=a(nf+nx);                                     //!< (a)llocate array r long enough to hold f and x.
  m(nx,r+nf,x);                                     //!< (m)ove contents of x to the end of r.
  m(nf,r,f);_r(x);_r(f);r)                          //!< (m)ove contents of f to the beginning of r, try to release f and x, and return pointer to r.

F(At,Qr(af)                                         //!< dyadic f@x is "needle at x in the haystack f" and has two modes based on the type of x (f must be a vector):
  ax?x>nf?Ql():sf[x]                                //!<  if x is an atom, return the x'th item of f.
    :_x(_f(N(nx,sf[xi]))))                          //!<  if x is a vector, return a vector containg items from f at indices listed in x.
                                                    //!< \note that the second mode currently doesn't perform the boundary check, fell free to implement it!

f(at,At(x,0))                                       //!< monadic @x is simply (f)ir(st): return the head element of x, or throw a rank error if x is an atom.

//! note how Sub() and at() are implemented in terms of other verbs, and especially how Add() cuts corners by calling itself with operands swapped.
//! in fact, Add() serves as a template for generalizing implementation of a whole bunch of other dyadic verbs, provided that they also hold commutative property. in pseudocode:

//! function fn(f,x) implementing a commutative OP:
//!  1. if both operands f and x are atoms, return (f) OP (x)
//!  2. if f is an atom and x is a vector, return fn(x,f)
//!  3. if both operands are vectors, ensure they are the same length.
//!  4. allocate a (r)esult vector of the same length as x, then:
//!  5. depending on type of x, each i'th element of r becomes either:
//!  5.1 (atom x) OP (i'th element of f)
//!  5.2 (i'th element of x) OP (it'h element of f)
//!  6. finally, attempt to release memory of f and x, and return r.

#define op(fn,OP) F(fn,ax?af?(c)(f OP x):fn(x,f):af?_x(N(nx,f OP xi)):_f(_x(nx-nf?Ql():N(nx,sx[i] OP sf[i])))) //!< above pseudocode expressed as a C macro.
op(Eql,==)op(Not,!=)op(And,&)op(Or,|)op(Prd,*)                //!< and we have definitions of dyadic equal, not equal, and, or and product for free.

//!verb dispatch
char*V=" +-!#,@=~&|*";                                        //!< V is an array of tokens of all supported k verbs. 0'th item (space) stands for "not a verb".
u(*f[])(u  )={0,foo,sub,til,cnt,cat,at,foo,foo,foo,rev,foo},  //!< f[] is an array of pointers to c functions which implement monadic versions of k verbs listed in V.
 (*F[])(u,u)={0,Add,Sub,Mod,Tak,Cat,At,Eql,Not,And,Or, Prd};  //!< F[] is ditto for dyadic versions of verbs listed in V.
// V:           +   -   !   #   ,   @  =   ~   &   |   *

//!adverbs
F(Ovr,ax?x:_x(r(*sx,i(nx-1,r=F[f](r,sx[i+1])))))                       //!< adverb over: recursively fold all elements of vector x using dyadic verb f going left to right.
F(Scn,ax?x:_x(r(a(nx),*sr=*sx;i(nx-1,sr[i+1]=F[f](sr[i],sx[i+1])))))   //!< adverb scan: same as over, but produces a vector of intermediate results.

//!adverb dispatch
char*AV=" /\\";u(*D[])(u,u)={0,Ovr,Scn};            //!< AV[]/D[] is the same as V[]/F[], only for adverbs.

//!globals, verbs, nouns, adverbs
f(g,x>='a'&&x<='z')                                 //!< is x a valid (g)lobal variable identifier?
F(ag,y(U[f],!ay?_a(y):x;r_(U[f]=x)))                //!< (a)ssign (g)lobal: release no longer referenced global object at U[f], and replace it with object x.
f(v,(strchr(V,x)?:V)-V)                             //!< is x a valid (v)erb from V? if so, return its index, otherwise return 0.
                                                    //!< \note rarely seen ternary form x?:y, which is just a shortcut for x?x:y in c.
f(d,(strchr(AV,x)?:AV)-AV)                          //!< same as v() for a(d)verbs.
f(n,10>x-48                                         //!< is x a (n)oun? valid nouns are digits 0..9 and lowercase varnames a..z.
           ?x-48                                    //!< if x is a digit, e.g. '7', return its decimal value.
           :g(x)?r_(U[x-97])                        //!< if x is a varname, e.g. 'a', return its value from U[26] and increment its refcount.
                :Q)                                 //!< ..everything else is an error.

//!fio
static char*l;u mx=99;FILE*t;                       //!< l is a line buffer, mx is its max length, t is input stream handle.
us(rl,l=l?:malloc(mx);                              //!< (r)ead(l)ine: reset mx to max line length, allocate buffer l of size mx if not yet allocated.
   P(!s,l[read(0,l,mx)-1]=0)                        //!< (r)ead: if no filename s is given, read line from stdin up to mx bytes, clamp trailing \n and return 0.
   t=t?:fopen(s,"r");Qs(!t,s)                       //!< open file s for reading if not yet open, throw error in case of problems.
   r(getline(&l,&mx,t),                             //!< read next line from stream t into l up to mx bytes.
     r=r<mx?l[r-('\n'==l[r-1])]=0:Q))               //!< if reached end of file, return Q, otherwise clamp trailing \n and return 0.

//!eval
us(e,                                               //!< (e)val: recursively evaluate input tape s in reverse order (left of right), and return the final result:
   c*t=s;c i=*t++;                                  //!< t is a temporary pointer to s. read the current token into i and advance temporary tape pointer.
   !*t?x(n(i),Qp()x)                                //!< if next token after i is null (ie end of tape): final token must be a noun, so return it, otherwise:
      :v(i)                                         //!< in case if i is a valid verb:
           ?d(*t)?x(e(t+1),Q(x)                     //!<   if the verb is followed by an adverb, recursively evaluate token after adverb into x. bail out on error.
                    D[d(*t)](v(i),x))               //!<     dispatch an adverb: first argument is the index of the verb, second is the operand.
           :x(e(t),Q(x)                             //!<   otherwise, recursively evaluate next token after verb and put resulting noun into x. bail out on error.
              f[v(i)](x))                           //!<   apply monadic verb i to the operand x and return the result, which can be either nounmn or error.
           :y(                                      //!< in case if i is not a verb, it must be a valid noun, and the next token after a noun should be a verb,
              e(t+1),Q(y)                           //!<   recursively evaluate next token to the right of the verb and put result into y. bail out on error.
              58==*t                                //!<   special case: if y is preceded by a colon instead of a verb, it is an inline assignment (eg 1+a:1),
                    ?x(g(i),Qp()ag(i-97,y))         //!<   so i should be a (g)lobal varname a..z. if so, increment y's refcount, store it in U[26], and return it.
                    :x(n(i),Qp()                    //!<   x is a noun to the left of the verb. throw parse error if it is invalid.
                         c f=v(*t);Qd(!f)           //!<   f is the index of the verb to the left of noun y. if it's not a valid verb, throw domain error.
                         F[f](x,y))))               //!< apply dyadic verb f to nouns x and y (e.g. 2+3) and return result (noun or error).

//!repl/batch
int main(int c,char**v){u r=2==c;                   //!< entry point: r=0 is repl mode, r=1 is batch mode i.e. when a filename is passed.
  r?:O("%s",BA);                                    //!< system banner is only printed in interactive mode.
  while(r?:w(32),Q!=rl(v[1]))                       //!< enter infinite read-eval-print loop until ctrl+c is pressed, error or EOF is reached.
   if(*l){                                          //!< write prompt (single space), then wait for input from stdin which is read into b.
    $(92==*l&&!l[2],                                //!< if buffer starts with bashslash and is two bytes long:
     $(92==l[1],break)                              //!<   if buffer is a double backslash, exit repl and terminate process.
       $(119==l[1],wu(WS))                          //!<   if buffer is a \w, print workspace usage and cycle repl.
        $(118==l[1],wg()))                          //!<   if buffer is a \v, print globals and their refcounts (debug).
         $('/'==*l,continue)                        //!< if buffer starts with /, treat the rest of the line as comment and cycle repl.
          x(e(l),                                   //!< else, evaluate buffer b[] and put result into x, then:
            58==l[1]?x                              //!<   if b starts with a global assignment e.g. a:7, suppress output and cycle repl.
                  :_x(W(x)));}                      //!<   otherwise, pretty print evaluation result to stdout, then cycle repl.
  R free(l),fclose(t),0;}                           //!< in c, return value of main() is the exit code of the process, 0 is success.

//:~
