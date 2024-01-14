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

