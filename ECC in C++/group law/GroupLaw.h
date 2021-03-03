#pragma once
#include"NTL/ZZ.h"

NTL_CLIENT

ZZ ModInverse(ZZ a, ZZ &p) {
	return PowerMod(a, (p - 2), p);
}

//y^2 = x^3 + a*x + b
void affine_add(ZZ &x1, ZZ &y1, ZZ &x2, ZZ &y2, ZZ &p) {
	ZZ z = (x1 - x2) % p;
	ZZ s = ((y1 - y2)*ModInverse(z, p)) % p;
	x2 = (power(s, 2) - x1 - x2) % p;
	y2 = (s*(x1 - x2) - y1) % p;
}
void affine_doubling(ZZ &x1, ZZ &y1, ZZ &p, ZZ &a) {
	ZZ z = (2 * y1) % p;
	ZZ s = ((3 * power(x1, 2) + a)*ModInverse(z, p)) % p;
	ZZ x3 = (power(s, 2) - 2 * x1) % p;
	y1 = (s*(x1 - x3) - y1) % p;
	x1 = x3;
}

//y^2*z = x^3 + a*x*z^2 + b*z^3
void projective_add(ZZ &x1, ZZ &y1, ZZ &z1, ZZ &x2, ZZ &y2, ZZ &z2, ZZ &p) {
	ZZ u, v, t, o;
	u = (y2*z1 - y1 * z2) % p;
	v = (x2*z1 - x1 * z2) % p;
	t = (x2*z1 + x1 * z2) % p;
	o = (u*u*z1*z2 - v * v*t) % p;
	x2 = MulMod(v, o, p);
	y2 = (u*(v*v*x1*z2 - o) - power(v, 3)*y1*z2) % p;
	z2 = MulMod(power(v, 3), z1*z2, p);
}
void projective_doubling(ZZ &x1, ZZ &y1, ZZ &z1, ZZ &p, ZZ &a) {
	ZZ w = (a*power(z1, 2) + 3 * power(x1, 2)) % p;
	ZZ s = (y1*z1) % p;
	ZZ B = (x1*y1*s) % p;
	ZZ h = (power(w, 2) - 8 * B) % p;
	x1 = (2 * h*s) % p;
	y1 = (w*(4 * B - h) - 8 * power(y1, 2)*power(s, 2)) % p;
	z1 = (8 * power(s, 3)) % p;
}

//y^2 = x^3 + a*x*z^4 + b*z^6
void jacobian_add(ZZ &x1, ZZ &y1, ZZ &z1, ZZ &x2, ZZ &y2, ZZ &z2, ZZ &p) {
	ZZ U1 = (x1*power(z2, 2)) % p;
	ZZ U2 = (x2*power(z1, 2)) % p;
	ZZ S1 = (y1*power(z2, 3)) % p;
	ZZ S2 = (y2*power(z1, 3)) % p;
	ZZ H = (U2 - U1) % p;
	ZZ r = (S2 - S1) % p;
	x2 = (-power(H, 3) - 2 * U1*power(H, 2) + power(r, 2)) % p;
	y2 = (-S1 * power(H, 3) + r * (U1*power(H, 2) - x2)) % p;
	z2 = (z1*z2*H) % p;
}
void jacobian_doubling(ZZ &x1, ZZ &y1, ZZ &z1, ZZ &p, ZZ &a) {
	ZZ S = (4 * x1*power(y1, 2)) % p;
	ZZ M = (3 * power(x1, 2) + a * power(z1, 4)) % p;
	ZZ T = (-2 * S + power(M, 2)) % p;
	x1 = T;
	z1 = (2 * y1*z1) % p;
	y1 = (-8 * power(y1, 4) + M * (S - T)) % p;
}

void chud_jac_add(ZZ &x1, ZZ &y1, ZZ &z1, ZZ &z1_2, ZZ &z1_3, ZZ &x2, ZZ &y2, ZZ &z2, ZZ &z2_2, ZZ &z2_3, ZZ &p) {
	ZZ U1 = (x1*z2_2) % p;
	ZZ U2 = (x2*z1_2) % p;
	ZZ S1 = (y1*z2_3) % p;
	ZZ S2 = (y2*z1_3) % p;
	ZZ H = (U2 - U1) % p;
	ZZ r = (S2 - S1) % p;
	x2 = (-power(H, 3) - 2 * U1*power(H, 2) + power(r, 2)) % p;
	y2 = (-S1 * power(H, 3) + r * (U1*power(H, 2) - x2)) % p;
	z2 = (z1*z2*H) % p;
	z2_2 = PowerMod(z2, 2, p);
	z2_3 = PowerMod(z2, 3, p);
}
void chud_jac_doubling(ZZ &x1, ZZ &y1, ZZ &z1, ZZ &z1_2, ZZ &z1_3, ZZ &p, ZZ &a) {
	ZZ S = (4 * x1*power(y1, 2)) % p;
	ZZ M = (3 * power(x1, 2) + a * z1_3*z1) % p;
	ZZ T = (-2 * S + power(M, 2)) % p;
	x1 = T;
	z1 = (2 * y1*z1) % p;
	y1 = (-8 * power(y1, 4) + M * (S - T)) % p;
	z1_2 = power(z1, 2) % p;
	z1_3 = power(z1, 3) % p;
}

void modif_jac_add(ZZ &x1, ZZ &y1, ZZ &z1, ZZ &az1_4, ZZ &x2, ZZ &y2, ZZ &z2, ZZ &az2_4, ZZ &p, ZZ &a) {
	ZZ U1 = (x1*power(z2, 2)) % p;
	ZZ U2 = (x2*power(z1, 2)) % p;
	ZZ S1 = (y1*power(z2, 3)) % p;
	ZZ S2 = (y2*power(z1, 3)) % p;
	ZZ H = (U2 - U1) % p;
	ZZ r = (S2 - S1) % p;
	x2 = (-power(H, 3) - 2 * U1*power(H, 2) + power(r, 2)) % p;
	y2 = (-S1 * power(H, 3) + r * (U1*power(H, 2) - x2)) % p;
	z2 = (z1*z2*H) % p;
	az2_4 = (a*power(z2, 4)) % p;
}
void modif_jac_doubling(ZZ &x1, ZZ &y1, ZZ &z1, ZZ &az1_4, ZZ &p, ZZ &a) {
	ZZ S = (4 * x1*power(y1, 2)) % p;
	ZZ M = (3 * power(x1, 2) + az1_4) % p;
	ZZ T = (-2 * S + power(M, 2)) % p;
	x1 = T;
	z1 = (2 * y1*z1) % p;
	y1 = (-8 * power(y1, 4) + M * (S - T)) % p;
	az1_4 = (a*power(z1, 4)) % p;
}