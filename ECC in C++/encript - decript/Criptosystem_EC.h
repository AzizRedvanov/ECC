#pragma once
#include"NTL/ZZ.h"
#include"partition_of_number.h"
#include<iostream>
#include<string>
#include<ctime>

NTL_CLIENT

struct three_values {
	ZZ X;
	ZZ Y;
	ZZ Z;
	int n;
}mass[100000];

struct THREE {
	ZZ x;
	ZZ y;
	ZZ z;
}Three[2];

void add_points(ZZ &p, ZZ &xp, ZZ &yp, ZZ &zp, ZZ &xq, ZZ &yq, ZZ &zq) {
	ZZ u, v, t, o;;
	u = (yq*zp - yp * zq) % p;
	v = (xq*zp - xp * zq) % p;
	t = (xq*zp + xp * zq) % p;
	o = (u*u*zp*zq - v * v*t) % p;
	Three[0].x = MulMod(v, o, p);
	Three[0].y = (u*(v*v*xp*zq - o) - power(v, 3)*yp*zq) % p;
	Three[0].z = MulMod(power(v, 3), zp*zq, p);
}

void multiply_scalar(ZZ &p, ZZ &a, ZZ &X1, ZZ &Y1, ZZ &Z1, ZZ &N) {
	ZZ x1(X1), y1(Y1), z1(Z1);
	Three[1].x = x1;
	Three[1].y = y1;
	Three[1].z = z1;
	string BitS = "";
	BitS += to_string(bit(N, 0));
	for (int i = 1; i < NumBits(N); i++) {
		BitS += to_string(bit(N, i));
		if (x1 != conv<ZZ>(0) || y1 != conv<ZZ>(0)) {
			ZZ s, w, e, f, h;;
			s = MulMod(y1, z1, p);
			w = (3 * power(x1, 2) + a * power(z1, 4)) % p;
			e = MulMod(y1, s, p);
			f = MulMod(x1, e, p);
			h = (w*w - 8 * f) % p;
			x1 = MulMod(2 * s, h, p);
			y1 = (w*(4 * f - h) - 8 * e*e) % p;
			z1 = MulMod(8, power(s, 3), p);
		}
		if (i == BitS.find("1") && bit(N, 0) != 1) {
			Three[1].x = x1;
			Three[1].y = y1;
			Three[1].z = z1;
			continue;
		}
		if (bit(N, i) == 1) {
			add_points(p, x1, y1, z1, Three[1].x, Three[1].y, Three[1].z);
			Three[1].x = Three[0].x;
			Three[1].y = Three[0].y;
			Three[1].z = Three[0].z;
		}
	}
}
int k1 = 50;
void alg_Koblitz(ZZ* M, int &n, ZZ &k, ZZ &p, ZZ &a, ZZ &b) {
	ZZ t;
	div(t, (p - conv<ZZ>(1)), 2);
	for (int i = 0; i < n; i++)
		for (int j=1; j<=k1; j++) {
			if (operator==(PowerMod(((power((M[i] * k1 + j), 3) + a * (M[i] * k1 + j) + b) % p), t, p), conv<ZZ>(1))) {
				mass[i].X = M[i] * k1 + j;
				mass[i].Y = PowerMod(((power(mass[i].X, 3) + a * mass[i].X + b) % p), k, p);
				break;
			}
		}
}

void EnCode(unsigned char *byte, int &file_size, ZZ &k, ZZ &p, ZZ &a, ZZ &b, ZZ &X, ZZ &Y, ZZ &Z) {
	int l = 0;
	ZZ *Ma = new ZZ[l];
	cout << endl;
	Ma = DIVIDE(byte, file_size, p, k1, l);
	cout << endl;
	time_t t1 = clock();
	alg_Koblitz(Ma, l, k, p, a, b);
	time_t t2 = clock();
	ZZ z = conv<ZZ>(1);
	for (int i = 0; i < l; i++) {
		add_points(p, mass[i].X, mass[i].Y, z, X, Y, Z);
		mass[i].X = Three[0].x;
		mass[i].Y = Three[0].y;
		mass[i].Z = Three[0].z;
	}
	time_t t3 = clock();
	mass[0].n = l;

	cout << "алг. Коблица" << (t2 - t1) / 1000. << endl;
	cout << "file encripted" << (t3-t1)/1000. << endl;
}

unsigned char* DeCode(ZZ &p, ZZ &X, ZZ &Y, ZZ &Z) {
	int n = mass[0].n;
	ZZ *Mb = new ZZ[n];
	unsigned char ch[200000] = {};
	int ii = 0;
	time_t t4 = clock();
	ZZ yy(-Y);
	for (int i = 0; i < n; i++) {
		add_points(p, mass[i].X, mass[i].Y, mass[i].Z, X, yy, Z);
		div(Mb[i], MulMod(Three[0].x, InvMod(Three[0].z, p), p), k1);
	}
	time_t t5 = clock();
	cout << "file decripted" << (t5 - t4) / 1000. << endl;
	for (int i = 0; i < n; i++)
		while (operator!=(Mb[i], conv<ZZ>(0))) {
			ch[ii] = static_cast<unsigned char>(conv<int>(Mb[i] % base));
			div(Mb[i], Mb[i], base);
			ii++;
		}
	cout<<endl<< ii<<endl;
	return ch;
}