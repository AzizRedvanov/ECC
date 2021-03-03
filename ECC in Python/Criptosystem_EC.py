from partition_of_number import *
from modinverse import *
from random import *

def add_points(p,xp,yp,zp,xq,yq,zq):
    u = (yq*zp - yp*zq)%p
    v = (xq*zp - xp*zq)%p
    t = (xq*zp + xp*zq)%p
    o = (u*u*zp*zq - v*v*t)%p
    xr = (v*o)%p
    yr = (u*(v*v*xp*zq-o)-(v**3)*yp*zq)%p
    zr = ((v**3)*zp*zq)%p
    return xr,yr,zr

def multiply_scalar(p,a,X1,Y1,Z1,N):
    x, y, z = X1, Y1, Z1
    k = bin(N)[2:]
    for i in range(len(k)-2,-1,-1):
        if X1 != 0 or Y1 != 0 or Z1 != 0:
            s = (Y1*Z1)%p
            w = (3*(X1**2) + a*(Z1**4))%p
            e = (Y1*s)%p
            f = (X1*e)%p
            h = (w*w-8*f)%p
            X1 = (2*s*h)%p
            Y1 = (w*(4*f-h)-8*e*e)%p
            Z1 = (8*(s**3))%p
        if X1 < 0:
            X1 += p
        if Y1 < 0:
            Y1 += p
        if Z1 < 0:
            Z1 += p
        if (i == k[:len(k)-1].rfind('1')) and k[len(k)-1] != '1':
            x, y, z = X1, Y1, Z1
        elif k[i] == '1':
            x,y,z = add_points(p,X1,Y1,Z1,x,y,z)
        if x < 0 :
            x += p
        if y < 0 :
            y += p
        if z < 0 :
            z += p
    return x,y,z    

def EnCode(M,p,X,Y,Z):
    M = int(M.encode().hex(), 16)
    Xm,Ym = divide(M,p)
    Zm = [0]*len(Xm)
    for i in range(len(Xm)):
        Zm[i] = randint(1,p-1)
        Xm[i] = (Xm[i]*Zm[i])%p
        Ym[i] = (Ym[i]*Zm[i])%p

    Mxa, Mya, Mza = [0]*len(Xm),[0]*len(Ym),[0]*len(Xm)
    for i in range(len(Xm)):
        Mxa[i], Mya[i], Mza[i] = add_points(p,Xm[i],Ym[i],Zm[i],X,Y,Z)
    Ma = Mxa+Mya
    return Ma,Mza

def DeCode(Ma,Mza,p,X,Y,Z):
    Xm1 = list(Ma[0:len(Ma)//2])
    Ym1 = list(Ma[len(Ma)//2::])
    Zm1 = Mza
    
    Mxb, Myb, Mzb = [0]*len(Xm1),[0]*len(Ym1),[0]*len(Zm1)
    for i in range(len(Xm1)):
        Mxb[i], Myb[i], Mzb[i] = add_points(p,Xm1[i],Ym1[i],Zm1[i],X,-Y,Z)
        Mxb[i], Myb[i] = (Mxb[i]*modinverse(Mzb[i],p))%p,(Myb[i]*modinverse(Mzb[i],p))%p

    Mb = Mxb+Myb
    Mb = list(map(str,Mb))
    Mb = hex(int(''.join(Mb)))[2::]
    Mb = bytearray.fromhex(Mb).decode()
    return Mb
