#pragma once
#include"NTL/ZZ.h"
#include<math.h>
#include<sstream>

NTL_CLIENT

ZZ base = power(conv<ZZ>(2), 8);

ZZ* DIVIDE(unsigned char *byte, int &file_size, ZZ &p, int &k, int &l) {
	ZZ *A = new ZZ[100000];
	int I = 0, kol = 0;
	ZZ mm = conv<ZZ>(0);
	ZZ pp;
	div(pp, p, k);
	operator--(pp);
	for (int i = 0; i < file_size; i++) {
		if (operator==(byte[i], conv<ZZ>(0)))
			kol++;
		else {
			if ((mm + byte[i] * power(base, I)) < pp) {
				operator+=(mm, byte[i] * power(base, I));
			}
			else {
				A[l] = mm;
				l++;
				I = kol;
				mm = byte[i] * power(base, I);
			}
			kol = 0;
		}
		I++;
	}
	A[l] = mm;
	l++;
	cout << "\nl= " << l;
	return A;
}