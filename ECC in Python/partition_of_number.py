from math import *
def divide(m,P):
    P = str(P)
    m = str(m)
    l = 0
    A = []
    a, b = 0, (len(P)-1)
    while (len(m)-a) >= (len(P)-1):
        e = 0
        if (len(m)-a) != (len(P)-1) and m[b] == '0':
            while m[b-e-1] == '0':
                e += 1
            else:
                e += 1
        A.append(m[a:b-e])
        a += (len(P)- 1 - e)
        b += (len(P)- 1 - e)
        l += 1
    else:
        if l%2==0 and (len(m)-a)!=0:
            a -=(len(P)- 1 - e) 
            A.pop(l-1)
            k1 = len(m) - a
            e1, e2= 0, 0
            if m[a+ceil(k1/3)] == '0':
                while m[a+ceil(k1/3)-e1-1] == '0':
                    e1 += 1
                else:
                    e1 += 1
            if m[len(m)-floor(k1/3)] == '0':
                while m[len(m)-floor(k1/3)-e2-1] == '0':
                    e2 += 1
                else:
                    e2 += 1
            A.append(m[a : a+ceil(k1/3)-e1])
            A.append(m[a+ceil(k1/3)-e1 : len(m)-floor(k1/3)-e2])
            A.append(m[len(m)-floor(k1/3)-e2 : len(m)])
        elif l%2==1 and (len(m)-a)!=0:
            A.append(m[a : len(m)])
        elif l%2==1 and (len(m)-a)==0:
            A.pop(l-1)
            a -=(len(P)- 1 - e)
            A.append(m[a:a+(len(m)-a)//2])
            A.append(m[a+(len(m)-a)//2:len(m)])
    A = list(map(int, A))
    ax = A[0:len(A)//2]
    ay = A[len(A)//2:len(A)]
    return ax,ay
