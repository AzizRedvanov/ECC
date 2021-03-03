def egcd(a,b):
    s,t = 1,0 #coefficients to express current a in terms of original a,b
    x,y = 0,1 #coefficients to express current b in terms of original a,b
    q,r = divmod(a,b)
    while(r > 0):
        a,b = b,r
        old_x, old_y = x,y
        x,y = s - q*x, t - q*y
        s,t = old_x, old_y
        q,r = divmod(a,b)
    return b, x ,y

def modinverse(a,n):
    d,x,y = egcd(a,n)
    if d > 1:
        return "No inverse"
    else:
        return x % n
