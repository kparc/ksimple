# 2024.01.18 (#3)
## a.h
```c
typedef char*s,c;s Q=(s)128;
#define _(e...) ({e;})
#define x(a,e...) _(s x=a;e)
#define $(a,b) if(a)b;else
#define i(n,e) {int $n=n;int i=0;for(;i<$n;++i){e;}}

#define Q(e) if(Q==(e))return Q;
#define Qs(e,s) if(e)return err(__func__,s);
#define Qz(e) Qs(e,"nyi")
#define Qr(e) Qs(e,"rank")
#define Qd(e) Qs(e,"domain")

#define _s(f,e,x...) s f(x){return _(e);}
#define _i(f,e) _s(f,e,c x)
#define f(f,e)  _s(f,e,s x)
#define F(f,e)  _s(f,e,s a,s x)

#define ax (256>x)
#define ix (c)x
#define rx x[-2]
#define nx x[-1]
#define xi x[i]

#define aa x(a,ax)
#define ia x(a,ix)
#define na x(a,nx)

#define _a(e) r(e,_r(a))
#define _x(e) r(e,_r(x))
#define r(a,e) _(s r=a;e;r)
#define s(e) (s)(255&(e))

#define oo w("oo\n")
```
## a.c
```c
long write(),read(),strlen();void*malloc(),*memchr(),*memcpy(),*strchr();void free();
#define A(c) ((s)memchr(a,c,na)?:a+na)-a
#include"a.h"//fF[+-!#,@] atom/vector 1byte(int/token) clang-13 -Os -oa a.c -w 
_i(m,s a=malloc(2+x);*a++=0;*a++=x;a)f(_m,free(x-2);0)f(r_,ax?x:(++rx,x))f(_r,ax?x:rx?(--rx,x):_m(x))
f(w,write(1,ax?&x:x,ax?1:strlen(x));x)F(err,w(a);w((s)58);w(x);w((s)10);Q)
#define n(n,e) r(m(n),i(n,r[i]=e))
f(z,Qr(!ax)0>ix?n(-ix,-ix-1-i):n(ix,i))
c b[6]="???? ";_i(wi,c n=0>x;x=n?-x:x;s s=b+4;do*--s=48+x%10;while(x/=10);w(n?(*--s='-',s):s))f(W,Q(x)$(ax,wi(ix))i(nx,wi(xi))w((s)10);x)
f(qz,Qz(1)x)
f(srt,Qz(1)x)
f(uni,Qz(1)x)
F(Cut,Qz(1)x)
F(Drp,Qz(1)x)
#define g(a,v) ax?s(a):_x(n(nx,v))
f(not,g(!ix,!xi))f(sub,g(-ix,-xi))
F(At,Qr(aa)_a(g(a[ix],a[xi])))F(_A,Qr(aa)_a(g(A(ix),A(xi))))F(Z,Qr(!aa)Qd(1>ia)g(ix%ia,xi%ia))
#define G(f,o) F(f,ax?aa?s(ia o ix):Ltn==f?f(sub(x),sub(a)):f(x,a):_a(_x(n(nx,(aa?ia:a[i])o xi))))
G(Ltn,<)G(Eql,==)G(Not,!=)G(Sum,+)G(Prd,*)G(And,&)G(Or,|)f(cat,Qr(!ax)n(1,ix))
F(Cat,a=aa?cat(a):a;x=ax?cat(x):x;s r=m(na+nx);_x(memcpy(r+na,x,nx));_a(memcpy(r,a,na)))
f(at,At(x,0))f(rev,Qr(ax)At(x,z(s(-nx))))f(cnt,Qr(ax)_x(s(nx)))
F(Tak,Qr(!aa||ax)Qd(0>ia||ia>nx)At(x,z(a)))F(Sub,Sum(a,sub(x)))F(Mtn,Ltn(x,a))
#define v(e) (((s)strchr(V,e)?:V)-V)
s U[26],V=" +-*&|<>=~!@?#_^,",
//          +   -   *   &  |   <   >   =   ~   ! @  ?   #   _   ^   ,
(*f[])()={0,qz ,sub,qz ,qz,rev,qz ,qz, qz ,not,z,at,uni,cnt,qz ,srt,cat},
(*F[])()={0,Sum,Sub,Prd,And,Or,Ltn,Mtn,Eql,Not,Z,At,_A ,Tak,Drp,Cut,Cat};
_i(u,10u>x-48?x-48:26u>x-97?r_(U[x-97]):0)
f(e,s z=x;c i=*z++;!*z?u(i):v(i)?x(e(z),Q(x)f[v(i)](x)):x(e(z+1),Q(x)58==*z?U[i-97]=r_(x):_(c f=v(*z);Qd(!f)F[f](u(i),x))))
int main(){c b[99];while(1)if(w((s)32),b[read(0,b,99)-1]=0,*b)58==b[1]?e(b):W(e(b));}
```
# 2024.01.18 (#2)
## a.h
```c
typedef char*s,c;s Q=(s)128;
#define _(e...) ({e;})
#define x(a,e...) _(s x=a;e)
#define $(a,b) if(a)b;else
#define i(n,e) {int $n=n;int i=0;for(;i<$n;++i){e;}}

#define Q(e) if(Q==(e))return Q;
#define Qs(e,s) if(e)return err(__func__,s);
#define Qr(e) Qs(e,"rank")
#define Qd(e) Qs(e,"domain")
#define Qz(e) Qs(e,"nyi")

#define _s(f,e,x...) s f(x){return _(e);}
#define _i(f,e) _s(f,e,c x)
#define f(f,e)  _s(f,e,s x)
#define F(f,e)  _s(f,e,s a,s x)

#define ax (256>x)
#define ix (c)x
#define rx x[-2]
#define nx x[-1]
#define xi x[i]

#define aa x(a,ax)
#define ia x(a,ix)
#define na x(a,nx)

#define oo w("oo\n")
```
## a.c
```c
#define _a(e) r(e,_r(a))
#define _x(e) r(e,_r(x))
#define r(a,e) _(s r=a;e;r)
#define n(n,e) r(m(n),i(n,r[i]=e))
#define s(e) (s)(255&(e))
long write(),read(),strlen();void*malloc(),*memchr(),*memcpy(),*strchr();void free();
#define A(c) ((s)memchr(a,c,na)?:a+na)-a
#include"a.h"//fF[+-!#,@] atom/vector 1byte(int/token) clang-13 -Os -oa a.c -w 
_i(m,s a=malloc(2+x);*a++=0;*a++=x;a)f(_m,free(x-2);0)f(r_,ax?x:(++rx,x))f(_r,ax?x:rx?(--rx,x):_m(x))
f(w,write(1,ax?&x:x,ax?1:strlen(x));x)F(err,w(a);w((s)58);w(x);w((s)10);Q)
f(ind,Qr(!ax)0>ix?n(-ix,-ix-1-i):n(ix,i))
c b[6]="???? ";_i(wi,c n=0>x;x=n?-x:x;s s=b+4;do*--s=48+x%10;while(x/=10);w(n?(*--s='-',s):s))f(W,Q(x)$(ax,wi(ix))i(nx,wi(xi))w((s)10);x)
f(qz,Qz(1)x)
f(srt,Qz(1)x)
f(uni,Qz(1)x)
F(Cut,Qz(1)x)
F(Drp,Qz(1)x)
#define g(a,v) ax?s(a):_x(n(nx,v))
f(not,g(!ix,!xi))f(sub,g(-ix,-xi))
F(At,Qr(aa)_a(g(a[ix],a[xi])))F(_A,Qr(aa)_a(g(A(ix),A(xi))))F(Ind,Qr(!aa)Qd(1>ia)g(ix%ia,xi%ia))
#define G(f,o) F(f,ax?aa?s(ia o ix):Ltn==f?f(sub(x),sub(a)):f(x,a):_a(_x(n(nx,(aa?ia:a[i])o xi))))
G(Ltn,<)G(Eql,==)G(Not,!=)G(Sum,+)G(Prd,*)G(And,&)G(Or,|)f(cat,Qr(!ax)n(1,ix))
F(Cat,a=aa?cat(a):a;x=ax?cat(x):x;s r=m(na+nx);_x(memcpy(r+na,x,nx));_a(memcpy(r,a,na)))
f(at,At(x,0))f(rev,Qr(ax)At(x,ind(s(-nx))))f(cnt,Qr(ax)_x(s(nx)))
F(Tak,Qr(!aa||ax)Qd(0>ia||ia>nx)At(x,ind(a)))F(Sub,Sum(a,sub(x)))F(Mtn,Ltn(x,a))
#define v(e) (((s)strchr(V,e)?:V)-V)
s U[26],V=" +-*&|<>=~!@?#_^,",
(*f[])()={0,qz ,sub,qz ,qz,rev,qz ,qz, qz ,not,ind,at,uni,cnt,qz ,srt,cat},
(*F[])()={0,Sum,Sub,Prd,And,Or,Ltn,Mtn,Eql,Not,Ind,At,_A ,Tak,Drp,Cut,Cat};
_i(u,10u>x-48?x-48:26u>x-97?r_(U[x-97]):0)
f(e,s z=x;c i=*z++;!*z?u(i):v(i)?x(e(z),Q(x)f[v(i)](x)):x(e(z+1),Q(x)58==*z?U[i-97]=r_(x):_(c f=v(*z);Qd(!f)F[f](u(i),x))))
int main(){c b[99];while(1)if(w((s)32),b[read(0,b,99)-1]=0,*b)58==b[1]?e(b):W(e(b));}
```
# 2024.01.18
## a.h
```c
typedef char*s,c;s Q=(s)128;
#define _(e...) ({e;})
#define x(a,e...) _(s x=a;e)
#define $(a,b) if(a)b;else
#define i(n,e) {int $n=n;int i=0;for(;i<$n;++i){e;}}

#define Q(e) if(Q==(e))return Q;
#define Qs(e,s) if(e)return err(__func__,s);
#define Qr(e) Qs(e,"rank")
#define Qd(e) Qs(e,"domain")
#define Qz(e) Qs(e,"nyi")

#define _s(f,e,x...) s f(x){return _(e);}
#define _i(f,e) _s(f,e,c x)
#define f(f,e)  _s(f,e,s x)
#define F(f,e)  _s(f,e,s a,s x)

#define ax (256>x)
#define ix (c)x
#define nx x[-1]
#define xi x[i]

#define aa x(a,ax)
#define ia x(a,ix)
#define na x(a,nx)

#define oo w("oo\n")
```
## a.c
```c
#define s(e) (s)(255&(e))
#include"a.h"//fF[+-!#,@] atom/vector 1byte(int/token) clang-13 -Os -oa a.c -w 
long write(),read(),strlen();void*malloc(),*memchr(),*memcpy(),*strchr();
f(w,write(1,ax?&x:x,ax?1:strlen(x));x)F(err,w(a);w((s)58);w(x);w((s)10);Q)
c b[6]="???? ";_i(wi,c n=0>x;x=n?-x:x;s s=b+4;do*--s=48+x%10;while(x/=10);w(n?(*--s='-',s):s))f(W,Q(x)$(ax,wi(ix))i(nx,wi(xi))w((s)10);x)
#define r(n,e) _(s r=m(n);i(n,r[i]=e)r)
_i(m,s a=malloc(1+x);*a++=x;a)f(ind,Qr(!ax)0>ix?r(-ix,-ix-1-i):r(ix,i))
f(qz,Qz(1)x)
f(srt,Qz(1)x)
f(uni,Qz(1)x)
F(Cut,Qz(1)x)
F(Drp,Qz(1)x)
#define A(c) ((s)memchr(a,c,na)?:a+na)-a
#define g(a,v) ax?s(a):r(nx,v)
f(not,g(!ix,!xi))f(sub,g(-ix,-xi))F(At,Qr(aa)g(a[ix],a[xi]))F(_A,Qr(aa)g(A(ix),A(xi)))F(Ind,Qr(!aa)Qd(1>ia)g(ix%ia,xi%ia))
#define G(f,o) F(f,ax?aa?s(ia o ix):Ltn==f?f(sub(x),sub(a)):f(x,a):r(nx,(aa?ia:a[i])o xi))
G(Ltn,<)G(Eql,==)G(Not,!=)G(Sum,+)G(Prd,*)G(And,&)G(Or,|)
f(cat,Qr(!ax)r(1,ix))F(Cat,a=aa?cat(a):a;x=ax?cat(x):x;s r=m(na+nx);memcpy(r+na,x,nx);memcpy(r,a,na))
f(at,At(x,0))f(rev,Qr(ax)At(x,ind(s(-nx))))f(cnt,Qr(ax)s(nx))
F(Tak,Qr(!aa||ax)Qd(0>ia||ia>nx)At(x,ind(a)))F(Sub,Sum(a,sub(x)))F(Mtn,Ltn(x,a))
#define v(e) (((s)strchr(V,e)?:V)-V)
s U[26],V=" +-*&|<>=~!@?#_^,",
(*f[])()={0,qz ,sub,qz ,qz,rev,qz ,qz, qz ,not,ind,at,uni,cnt,qz ,srt,cat},
(*F[])()={0,Sum,Sub,Prd,And,Or,Ltn,Mtn,Eql,Not,Ind,At,_A ,Tak,Drp,Cut,Cat};
_i(n,10u>x-48?x-48:26u>x-97?U[x-97]:0)
f(e,s z=x;c i=*z++;!*z?n(i):v(i)?x(e(z),Q(x)f[v(i)](x)):x(e(z+1),Q(x)58==*z?U[i-97]=x:_(c f=v(*z);Qd(!f)F[f](n(i),x))))
int main(){c b[99];while(1)if(w((s)32),b[read(0,b,99)-1]=0,*b)58==b[1]?e(b):W(e(b));}
```
# 2024.01.16 (#2)
## a.h
```c
typedef char*s,c;s Q=(s)128;
#define _(e...) ({e;})
#define x(a,e...) _(s x=a;e)
#define $(a,b) if(a)b;else
#define i(n,e) {int $n=n;int i=0;for(;i<$n;++i){e;}}

#define Q(e) if(Q==(e))return Q;
#define Qs(e,s) if(e)return err(__func__,s);
#define Qr(e) Qs(e,"rank")
#define Qd(e) Qs(e,"domain")
#define Qz(e) Qs(e,"nyi")

#define _s(f,e,x...) s f(x){return _(e);}
#define _i(f,e) _s(f,e,c x)
#define f(f,e)  _s(f,e,s x)
#define F(f,e)  _s(f,e,s a,s x)

#define ax (256>x)
#define ix (c)x
#define nx x[-1]
#define xi x[i]

#define aa x(a,ax)
#define ia x(a,ix)
#define na x(a,nx)

#define oo w("oo\n")
```
## a.c
```c
#include"a.h"//fF[+-!#,@] atom/vector 1byte(int/token) clang-13 -Os -oa a.c -w 
#define r(n,e) _(s r=m(n);i(n,r[i]=e)r)
f(w,write(1,ax?&x:x,ax?1:strlen(x));x)F(err,w(a);w((s)58);w(x);w((s)10);Q)
_i(wi,s b[5];sprintf(b,"%d ",x);w(b);0)
f(W,Q(x)$(ax,wi(ix))i(nx,wi(xi))w(10);x)

f(srt,Qz(1)0)f(uni,Qz(1)0)F(Cut,Qz(1)0)F(Drp,Qz(1)0)_i(m,s a=malloc(1+x);*a++=x;a)
#define A(c) ((s)memchr(a,c,na)?:a+na)-a
#define g(a,v) ax?255&a:r(nx,v)
f(not,g(!ix,!xi))f(sub,g(-ix,-xi))F(At,Qr(aa)g(a[ix],a[xi]))F(_A,Qr(aa)g(A(ix),A(xi)))
f(ind,Qr(!ax)0>ix?r(-ix,-ix-1-i):r(ix,i))F(Ind,Qr(!aa)Qd(1>ia)g(ix%ia,xi%ia))
#define G(f,o) F(f,ax?aa?255&ia o ix:Ltn==f?f(sub(x),sub(a)):f(x,a):r(nx,(aa?ia:a[i])o xi))
G(Ltn,<)G(Eql,==)G(Not,!=)G(Sum,+)G(Prd,*)G(And,&)G(Or,|)
f(cat,Qr(!ax)r(1,ix))F(Cat,a=aa?cat(a):a;x=ax?cat(x):x;s r=m(na+nx);memcpy(r+na,x,nx);memcpy(r,a,na))
f(at,At(x,0))f(rev,Qr(ax)At(x,ind(255&-nx)))f(cnt,Qr(ax)nx)
F(Tak,Qr(!aa||ax)Qd(0>ia||ia>nx)At(x,ind(a)))F(Sub,Sum(a,sub(x)))F(Mtn,Ltn(x,a))f(qz,Qz(1)0)
#define v(e) ((strchr(V,e)?:V)-V)
s U[26],V=" +-*&|<>=~!@?#_^,",
(*f[])()={0,abs,sub,qz ,qz,rev,qz ,qz, qz ,not,ind,at,uni,cnt,qz ,srt,cat},
(*F[])()={0,Sum,Sub,Prd,And,Or,Ltn,Mtn,Eql,Not,Ind,At,_A ,Tak,Drp,Cut,Cat};
_i(n,10u>x-48?x-48:26u>x-97?U[x-97]:0)
f(e,s z=x;c i=*z++;!*z?n(i):v(i)?x(e(z),Q(x)f[v(i)](x)):x(e(z+1),Q(x)58==*z?U[i-97]=x:_(c f=v(*z);Qd(!f)F[f](n(i),x))))
int main(){c b[99];while(1)if(w(32),b[read(0,b,99)-1]=0,*b)58==b[1]?e(b):W(e(b));}
```

# 2024.01.16
## a.h
```c
typedef char*s,c;s Q=(s)128;
#define _(e...) ({e;})
#define x(a,e...) _(s x=a;e)
#define $(a,b) if(a)b;else
#define i(n,e) {int $n=n;int i=0;for(;i<$n;++i){e;}}

#define Q(e) if(Q==(e))return Q;
#define Qs(e,s) if(e)return err(__func__,s);
#define Qr(e) Qs(e,"rank")
#define Qd(e) Qs(e,"domain")
#define Qz(e) Qs(e,"nyi")

#define _s(f,e,x...) s f(x){return _(e);}
#define f(g,e) _s(g,e,s x)
#define F(g,e) _s(g,e,s a,s x)

#define ax (256>x)
#define ix (c)x
#define nx x[-1]
#define xi x[i]

#define aa x(a,ax)
#define ia x(a,ix)
#define na x(a,nx)

#define oo w("oo\n")
```
## a.c
```c
#define v(e) ((strchr(V,e)?:V)-V)
#include"a.h"//fF[+-!#,@] atom/vector 1byteint 1bytetoken no(memmanage parser tokens ..) clang-13 -Os -oa a.c -w 
#define _i(f,e) s f(c x){return _(e);}
f(w,write(1,ax?&x:x,ax?1:strlen(x));x)_i(wi,s b[5];sprintf(b,"%d ",x);w(b);0)F(err,w(a);w((s)58);w(x);w((s)10);Q)
#define r(n,e) _(s r=m(n);i(n,r[i]=e)r)
f(W,Q(x)$(ax,wi(ix))i(nx,wi(xi))w(10);x)_i(m,s a=malloc(1+x);*a++=x;a)f(ind,Qr(!ax)0>ix?r(-ix,-ix-1-i):r(ix,i))
#define g(a,v) ax?255&a:r(nx,v)
f(sub,g(-ix,-xi))F(At,Qr(aa)g(a[ix],a[xi]))F(Ind,Qr(!aa)Qd(1>ia)g(ix%ia,xi%ia))f(rev,Qr(ax)At(x,ind(255&-nx)))
#define G(f,o) F(f,ax?aa?255&ia o ix:Ltn==f?f(sub(x),sub(a)):f(x,a):r(nx,(aa?ia:a[i])o xi))
G(Ltn,<)G(Eql,==)G(Sum,+)G(Prd,*)

f(cat,Qr(!ax)r(1,ix))F(Cat,a=aa?cat(a):a;x=ax?cat(x):x;s r=m(na+nx);memcpy(r+na,x,nx);memcpy(r,a,na))
f(at,At(x,0))f(cnt,Qr(ax)nx)F(Cnt,Q(a=ind(a))At(x,a))F(Sub,Sum(a,sub(x)))F(Mtn,Ltn(x,a))f(qz,Qz(1)0)
s U[26],V=" +-*|<>=!#,@",
(*f[])()={0,qz, sub,qz, rev,qz ,qz, qz ,ind,cnt,cat,at},
(*F[])()={0,Sum,Sub,Prd,qz ,Ltn,Mtn,Eql,Ind,Cnt,Cat,At};

_i(n,10u>x-48?x-48:26u>x-97?U[x-97]:0)
f(e,s z=x;c i=*z++;!*z?n(i):v(i)?x(e(z),Q(x)f[v(i)](x)):x(e(z+1),Q(x)58==*z?U[i-97]=x:_(c f=v(*z);Qd(!f)F[f](n(i),x))))
int main(){c b[99];while(1)if(w(32),b[read(0,b,99)-1]=0,*b)58==b[1]?e(b):W(e(b));}
```

# 2024.01.12
## a.h
```c
typedef unsigned char c;typedef unsigned long u;u Q=96;
#define $(a,b) if(a)b;else
#define ax (256>x)
#define xi (nx>i?sx[i]:0)
#define i(n,e) {int $n=n;int i=0;for(;i<$n;++i){e;}}
#define _(e) ({e;})
#define _u(f,e,x...) u f(x){return({e;});}
#define nx sx[-1]
#define sx ((c*)x)
#define x(a,e) _(u x=a;e)
#define y(a,e) _(u y=a;e)
#define f(g,e) _u(g,e,u x)
#define F(g,e) _u(g,e,u f,u x)
#define G(g,e) _u(g,e,u f,u x,u y)
#define us(f,e) _u(f,e,c*s)
#define Q(e) if(Q==(e))return Q;
#define Qr(e) if(e){return err((u)__func__,(u)"rank");}
#define Qz(e) if(e){return err((u)__func__,(u)"nyi");}
#define sr x(r,sx)
#define ri sr[i]

#define af x(f,ax)
#define nf x(f,nx)
#define sf x(f,sx)
#define fi x(f,xi)
```
## a.c
```c
#include"a.h"//fF[+-!#,@] atom/vector 1byteint 1bytetoken  no(memmanage parser tokens ..) clang-13 -Os -oa a.c -w 
#define r(n,e) _(u r=a(n);i(n,ri=e)r)
f(w,write(1,ax?(u)&x:x,ax?1:strlen(x)))
c b[12];
f(si,sprintf(b,"%d ",128>x?x:x-256);b)
f(wi,w(si(x)))
f(w_,$(ax,wi(x))i(nx,wi(xi))w(10))

F(err,w(f);w(58);w(x);w(10);96)
G(m,(u)memcpy((void*)x,(void*)y,f))
f(a,c*s=malloc(x+1);*s++=x;(u)s)
f(foo,Qz(1)0)
f(sub,ax?(c)-x:r(nx,-xi))
f(ind,Qr(!ax)r(x,i))
f(cnt,Qr(ax)nx)
f(cat,Qr(!ax)r(1,x))
F(Add,ax?af?f+x:Add(x,f):r(nx,(af?f:fi)+xi))
F(Sub,Add(f,sub(x)))
F(Ind,Qr(!f)r(nx,xi%f))
F(Cnt,Qr(!af)r(f,ax?x:xi))
F(Cat,f=af?cat(f):f;x=ax?cat(x):x;u r=a(nf+nx);m(nx,r+nf,x);m(nf,r,f))
F(At,Qr(af)ax?sf[x]:r(nx,sf[xi]))f(at,At(x,0))
char*V=" +-!#,@";u(*f[])()={0,foo,sub,ind,cnt,cat,at},(*F[])()={0,Add,Sub,Ind,Cnt,Cat,At},U[26];
f(v,(strchr(V,x)?:V)-V)
f(n,10>x-48?x-48:U[x-97])
us(e,u i=*s++;v(i)?x(e(s),Q(x)f[v(i)](x)):x(n(i),*s?y(e(s+1),Q(y)F[v(*s)](x,y)):x))
int main(){char s[99];while(1)if(w(32),s[read(0,s,99)-1]=0,*s)w_(e(s));}
```
# 2024.01.10
## a.h
```c
typedef unsigned long u;
#define _u(f,e,x...) u f(x){return _(e);}
#define ax (10>x)
#define nx sx[-1]
#define sx ((char*)x)
#define xi sx[i]
#define _(e) ({e;})
#define r(a,e) _(u r=a;e;r)
#define x(a,e) _(u x=a;e)
#define y(a,e) _(u y=a;e)
#define i(n,e) {int $n=n;int i=0;for(;i<$n;++i){e;}}
#define f(f,e) _u(f,e,u x)
#define F(f,e) _u(f,e,u x,u y)
#define G(g,e) _u(g,e,u f,u x,u y)
#define us(f,e) _u(f,e,char*s)
#define Q(e) if(96==(e))return 96;
#define Qr(e) if(e){return err((u)__func__,(u)"rank");}
#define Qz(e) if(e){return err((u)__func__,(u)"todo");}
#define ri sr[i]
#define yi x(y,xi)
#define nr x(r,nx)
#define ny x(y,nx)
#define sr x(r,sx)
#define sy x(y,sx)
#define ay x(y,ax)

```
## a.c
```c
#include"a.h"//cc -Os -oa a.c -w
F(w_,write(1,y,x))f(w,127>x?w_(1,(u)&x):w_(strlen(x),x))F(err,w(x);w(58);w(y);w(10);96)f(qz,Qz(1)0)
G(m,(u)memcpy((void*)x,(void*)y,f))
f(a,char*s=malloc(x+1);*s++=x;(u)s)
f(ind,Qr(!ax)x=a(x);i(nx,xi=i)x)
f(cat,Qr(!ax)u r=a(1);*sr=x;r)
F(Cat,x=ax?cat(x):x;y=ay?cat(y):y;u r=a(nx+ny);m(ny,r+nx,y);m(nx,r,x))
f(at,Qr(ax)*sx)
F(At,Qr(ax||!ay)sx[y])
f(cnt,Qr(ax)nx)
F(Cnt,Qr(!ax||ay)x=a(x);m(nx,x,y))
F(Add,ax?ay?x+y:Add(y,x):r(a(ny),i(nr,ri=(ax?x:xi)+yi)))
u(*f[])()={0,qz,ind,cnt,cat,at},(*F[])()={0,Add,qz,Cnt,Cat,At};
u U[26];f(n,10>x-48?x-48:U[x-97])
char*V=" +!#,@";f(v,(strchr(V,x)?:V)-V)
us(e,u i=*s++;v(i)?x(e(s),Q(x)f[v(i)](x)):x(n(i),*s?y(e(s+1),Q(y)F[v(*s)](x,y)):x))
us(ws,u x=*s?e(s):0;Q(x)ax?w(48+x):_(i(nx,w(48+xi);w(32))0);w(10))
int main(){char s[99];while(1)w(32),s[read(0,s,99)-1]=0,ws(s);}

char *kinit(){char s[99];return s;}
```
# initial 2024.01.10
```c
typedef char c;typedef unsigned long(*_)(),u;
#define _(e) ({e;})
#define s(f,e,x...) c*f(x){return _(e);}
#define u(f,e,x...) u f(x){return _(e);}
#define I(n,e) {int $n=n;int i=0;for(;i<$n;++i){e;}}
#define f(f,e) u(f,e,u x)
#define F(f,e) u(f,e,u x,u y)
#define sr ((c*)r)
#define sx ((c*)x)
#define sy ((c*)y)
#define nr sr[-1]
#define nx sx[-1]
#define ny sy[-1]
#define rc sr[i]
#define xc sx[i]
#define yc sy[i]
#define ax (10>x)
#define ay (10>y)
#define oo w_(3,"oo\n")
#define r(a,e) _(u r=a;e;r)
u(m,(u)memcpy((void*)x,(void*)y,n),u n,u x,u y)u(w_,write(1,s,n),u n,c*s)f(w,w_(1,&x))
f(a,c*s=malloc(x+1);*s++=x;(u)s)f(ind,x=a(x);I(nx,xc=i)x)
f(cat,u r=a(1);*sr=x;r)F(Cat,x=ax?cat(x):x;y=ay?cat(y):y;u r=a(nx+ny);m(ny,r+nx,y);m(ny,r,x))
f(at,*sx)F(At,sx[y])f(cnt,nx)F(Cnt,x=a(x);m(nx,x,y))
F(Add,ax?ay?x+y:Add(y,x):r(a(ny),I(nr,rc=(ax?x:xc)+yc)))
f(q,0)_ f[]={0,q,ind,cnt,cat,at},F[]={0,Add,q,Cnt,Cat,At};
u U[26];f(n,10>x-48?x-48:U[x-97])c*V=" +!#,@";f(v,(strchr(V,x)?:V)-V)
u(e,c i=*s++;v(i)?f[v(i)](e(s)):*s?F[v(*s)](n(i),e(s+1)):n(i),c*s)
u(ws,u x=*s?e(s):0;ax?w(48+x):_(I(nx,w(48+xc);w(32))0);w(10),c*s)
int main(){c s[99];while(1)w(32),s[read(0,s,99)-1]=0,ws(s);}
```
