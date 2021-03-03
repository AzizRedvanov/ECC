#pragma once
#include"NTL/ZZ.h"
#include"GroupLaw.h"

NTL_CLIENT
void multiply_scalar_affine(ZZ &x3, ZZ &y3, ZZ &x1, ZZ &y1, ZZ &N, ZZ &p, ZZ &a) {
	string BitS = "";
	for (int i = 0; i < NumBits(N); i++) {
		if (i != 0)
			affine_doubling(x1, y1, p, a);
		BitS += to_string(bit(N, i));
		if (i == BitS.find('1')) {
			x3 = x1;
			y3 = y1;
			continue;
		}
		if (bit(N, i) == 1)
			affine_add(x1, y1, x3, y3, p);
	}
}
void multiply_scalar_projective(ZZ &x3, ZZ &y3, ZZ &z3, ZZ &x1, ZZ &y1, ZZ &z1, ZZ &N, ZZ &p, ZZ &a) {
	string BitS = "";
	for (int i = 0; i < NumBits(N); i++) {
		if (i != 0)
			projective_doubling(x1, y1, z1, p, a);
		BitS += to_string(bit(N, i));
		if (i == BitS.find('1')) {
			x3 = x1;
			y3 = y1;
			z3 = z1;
			continue;
		}
		if (bit(N, i) == 1)
			projective_add(x1, y1, z1, x3, y3, z3, p);
	}
}
void multiply_scalar_jacobian(ZZ &x3, ZZ &y3, ZZ &z3, ZZ &x1, ZZ &y1, ZZ &z1, ZZ &N, ZZ &p, ZZ &a) {
	string BitS = "";
	for (int i = 0; i < NumBits(N); i++) {
		if (i != 0)
			jacobian_doubling(x1, y1, z1, p, a);
		BitS += to_string(bit(N, i));
		if (i == BitS.find('1')) {
			x3 = x1;
			y3 = y1;
			z3 = z1;
			continue;
		}
		if (bit(N, i) == 1)
			jacobian_add(x1, y1, z1, x3, y3, z3, p);
	}
}
void multiply_scalar_chud_jac(ZZ &x3, ZZ &y3, ZZ &z3, ZZ &z3_2, ZZ &z3_3, ZZ &x1, ZZ &y1, ZZ &z1, ZZ &z1_2, ZZ &z1_3, ZZ &N, ZZ &p, ZZ &a) {
	string BitS = "";
	for (int i = 0; i < NumBits(N); i++) {
		if (i != 0)
			chud_jac_doubling(x1, y1, z1, z1_2, z1_3, p, a);
		BitS += to_string(bit(N, i));
		if (i == BitS.find('1')) {
			x3 = x1;
			y3 = y1;
			z3 = z1;
			z3_2 = z1_2;
			z3_3 = z1_3;
			continue;
		}
		if (bit(N, i) == 1)
			chud_jac_add(x1, y1, z1, z1_2, z1_3, x3, y3, z3, z3_2, z3_3, p);
	}
}
void multiply_scalar_modif_jac(ZZ &x3, ZZ &y3, ZZ &z3, ZZ &az3_4, ZZ &x1, ZZ &y1, ZZ &z1, ZZ &az1_4, ZZ &N, ZZ &p, ZZ &a) {
	string BitS = "";
	for (int i = 0; i < NumBits(N); i++) {
		if (i != 0)
			modif_jac_doubling(x1, y1, z1, az1_4, p, a);
		BitS += to_string(bit(N, i));
		if (i == BitS.find('1')) {
			x3 = x1;
			y3 = y1;
			z3 = z1;
			az3_4 = az1_4;
			continue;
		}
		if (bit(N, i) == 1)
			modif_jac_add(x1, y1, z1, az1_4, x3, y3, z3, az3_4, p, a);
	}
}