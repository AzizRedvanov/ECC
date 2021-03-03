#pragma once
#include"NTL/ZZ.h"
#include"GroupLaw.h"

NTL_CLIENT

void naf(int *k, int &l, ZZ n) {
	while (n >= conv<ZZ>(1)) {
		if (n % 2 == 1) {
			k[l] = 2 - n % 4;
			n -= k[l];
		}
		else
			k[l] = 0;
		n /= conv<ZZ>(2);
		l++;
	}
}
void NAF_multiply_scalar_affine(ZZ &x3, ZZ &y3, ZZ &x1, ZZ &y1, ZZ &N, ZZ &p, ZZ &a, int *k, int &l) {
	int I = 0;
	for (int i = 0; i < l; i++) {
		if (k[i] != 0) {
			x3 = x1;
			if (k[i] == 1) y3 = y1;
			else y3 = p - y1;
			I = i;
			break;
		}
		affine_doubling(x1, y1, p, a);
	}
	for (int i = I+1; i < l; i++) {
		affine_doubling(x1, y1, p, a);
		if (k[i] == 1)
			affine_add(x1, y1, x3, y3, p);
		if (k[i] == -1) {
			y1 =p-y1;
			affine_add(x1, y1, x3, y3, p);
		}
	}
}
void NAF_multiply_scalar_projective(ZZ &x3, ZZ &y3, ZZ &z3, ZZ &x1, ZZ &y1, ZZ &z1, ZZ &N, ZZ &p, ZZ &a, int *k, int &l) {
	int I = 0;
	for (int i = 0; i < l; i++) {
		if (k[i] != 0) {
			x3 = x1;
			if (k[i] == 1) y3 = y1;
			else y3 = p - y1;
			z3 = z1;
			I = i;
			break;
		}
		projective_doubling(x1, y1, z1, p, a);
	}
	for (int i = I+1; i < l; i++) {
		projective_doubling(x1, y1, z1, p, a);
		if (k[i] == 1)
			projective_add(x1, y1, z1, x3, y3, z3, p);
		if (k[i] == -1) {
			y1 = p - y1;
			projective_add(x1, y1, z1, x3, y3, z3, p);
		}
	}
}
void NAF_multiply_scalar_jacobian(ZZ &x3, ZZ &y3, ZZ &z3, ZZ &x1, ZZ &y1, ZZ &z1, ZZ &N, ZZ &p, ZZ &a, int *k, int &l) {
	int I = 0;
	for (int i = 0; i < l; i++) {
		if (k[i] != 0) {
			x3 = x1;
			if (k[i] == 1) y3 = y1;
			else y3 = p - y1;
			z3 = z1;
			I = i;
			break;
		}
		jacobian_doubling(x1, y1, z1, p, a);
	}
	for (int i = I+1; i < l; i++) {
		jacobian_doubling(x1, y1, z1, p, a);
		if (k[i] == 1)
			jacobian_add(x1, y1, z1, x3, y3, z3, p);
		if (k[i] == -1) {
			y1 = p - y1;
			jacobian_add(x1, y1, z1, x3, y3, z3, p);
		}
	}
}
void NAF_multiply_scalar_chud_jac(ZZ &x3, ZZ &y3, ZZ &z3, ZZ &z3_2, ZZ &z3_3, ZZ &x1, ZZ &y1, ZZ &z1, ZZ &z1_2, ZZ &z1_3, ZZ &N, ZZ &p, ZZ &a, int *k, int &l) {
	int I = 0;
	for (int i = 0; i < l; i++) {
		if (k[i] != 0) {
			x3 = x1;
			if (k[i] == 1) y3 = y1;
			else y3 = p - y1;
			z3 = z1;
			z3_2 = z1_2;
			z3_3 = z1_3;
			I = i;
			break;
		}
		chud_jac_doubling(x1, y1, z1, z1_2, z1_3, p, a);
	}
	for (int i = I+1; i < l; i++) {
		chud_jac_doubling(x1, y1, z1, z1_2, z1_3, p, a);
		if (k[i] == 1)
			chud_jac_add(x1, y1, z1, z1_2, z1_3, x3, y3, z3, z3_2, z3_3, p);
		if (k[i] == -1) {
			y1 = p - y1;
			chud_jac_add(x1, y1, z1, z1_2, z1_3, x3, y3, z3, z3_2, z3_3, p);
		}
	}
}
void NAF_multiply_scalar_modif_jac(ZZ &x3, ZZ &y3, ZZ &z3, ZZ &az3_4, ZZ &x1, ZZ &y1, ZZ &z1, ZZ &az1_4, ZZ &N, ZZ &p, ZZ &a, int *k, int &l) {
	int I = 0;
	for (int i = 0; i < l; i++) {
		if (k[i] != 0) {
			x3 = x1;
			if (k[i] == 1) y3 = y1;
			else y3 = p - y1;
			z3 = z1;
			az3_4 = az1_4;
			I = i;
			break;
		}
		modif_jac_doubling(x1, y1, z1, az1_4, p, a);
	}
	for (int i = I+1; i < l; i++) {
		modif_jac_doubling(x1, y1, z1, az1_4, p, a);
		if (k[i] == 1)
			modif_jac_add(x1, y1, z1, az1_4, x3, y3, z3, az3_4, p, a);
		if (k[i] == -1) {
			y1 = p - y1;
			modif_jac_add(x1, y1, z1, az1_4, x3, y3, z3, az3_4, p, a);
		}
	}
}