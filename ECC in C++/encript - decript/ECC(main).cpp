#include<iostream>
#include<conio.h>
#include<fstream>
#include<ctime>

#include"Criptosystem_EC.h"
#include"NTL/ZZ.h"

NTL_CLIENT

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");
	ZZ p,a,b,Xp,Yp,na,nb;
	string p1, a1,b1,Xp1,Yp1,na1,nb1;
	/*p1 = "6703903964971298549787012499102923063739682910296196688861780721860882015036773488400937149083451713845015929093243025426876941405973284973216824503042159";
	a1 = "6703903964971298549787012499102923063739682910296196688861780721860882015036773488400937149083451713845015929093243025426876941405973284973216824503042156";
	b1 = "5472517130514047254760433071281657274171034389553769779747941603125796549693907036696237273952702637857580071293254240945079496484373854264998452887027990";
	Xp1 = "132122452221456037910272545182107700417538397727401782378450723055639590952049906314687879999888990226624191407680058112336234056135021456127651633683301";
	Yp1 = "2838104848477134651582715838754282426220282933894951963573616176395564979308994482527801748137859851261970864186341333561905193001121937409474448925902433";
	na1 = "139108779779555725871173587475046332866672929764755386079434043498207276249127796332466848999318508936570303349420418056818";
	nb1 = "17130514047254760433071281657274171034389553769779747941603125796549693907036696237273952702637857580071293254240";*/

	p1 = "18467548642013459782465125548763244987000123456875200012456871123154789578425136470000000000000000467";
	a1 = "0";
	b1 = "3";
	Xp1 = "6865595954026188617245500478180211913546562990254560416067524839730616752567292107800243578095233027";
	Yp1 = "6850923837946840443838949995210458455044828496704246102971703264200321269585276880178655569141460122";
	na1 = "1391087797795557258711735874750463328666729297647553860794340434982072762";
	nb1 = "171305140472547604330712816572741710343895537697797479416031257965489544854785";

	p = conv<ZZ>(p1.c_str());
	a = conv<ZZ>(a1.c_str());
	b = conv<ZZ>(b1.c_str());
	Xp = conv<ZZ>(Xp1.c_str());
	Yp = conv<ZZ>(Yp1.c_str());
	na = conv<ZZ>(na1.c_str());
	nb = conv<ZZ>(nb1.c_str());
	
	ZZ Zp = conv<ZZ>(1);
	ZZ Xqa, Yqa, Zqa, Xqb, Yqb, Zqb;

	multiply_scalar(p, a, Xp, Yp, Zp, na);
	Xqa = Three[1].x;
	Yqa = Three[1].y;
	Zqa = Three[1].z;
	multiply_scalar(p, a, Xp, Yp, Zp, nb);
	Xqb = Three[1].x;
	Yqb = Three[1].y;
	Zqb = Three[1].z;

	ZZ Xa, Ya, Za, Xb, Yb, Zb;
	multiply_scalar(p, a, Xqb, Yqb, Zqb, na);
	Xa = Three[1].x;
	Ya = Three[1].y;
	Za = Three[1].z;
	multiply_scalar(p, a, Xqa, Yqa, Zqa, nb);
	Xb = Three[1].x;
	Yb = Three[1].y;
	Zb = Three[1].z;
	
	cout << "\nОбщий секретный ключ абонента А:\n(" << Xa << ";" << Ya << ";" << Za << ")";
	cout << "\nОбщий секретный ключ абонента В:\n(" << Xb << ";" << Yb << ";" << Zb << ")\n";

	cout << "\nОбщий секретный ключ абонента А:\n(" << MulMod(Xa,InvMod(Za,p),p) << ";" << MulMod(Ya,InvMod(Za, p), p) << ")";
	cout << "\nОбщий секретный ключ абонента В:\n(" << MulMod(Xb,InvMod(Zb, p),p) << ";" << MulMod(Yb,InvMod(Zb, p),p) << ")\n";


	const int N = 200000;
	unsigned char byte[N] = {};
	ifstream input("file.jpg", ios::binary | ios::in);
	input.seekg(0, ios::end);
	int file_size = input.tellg();
	input.seekg(0);
	input.read((char*)byte, file_size);
	input.close();
	cout << file_size;
	ZZ k;
	div(k, (p - 3), 4);
	operator++(k);
	EnCode(byte, file_size, k, p, a, b, Xa, Ya, Za);
	ofstream out("encript.txt");
	for (int i = 0; i < mass[0].n; i++) {
		out << mass[i].X << "\n";
	}
	out << "\n";
	for (int i = 0; i < mass[0].n; i++) {
		out << mass[i].Y << "\n";
	}
	out << "\n";
	for (int i = 0; i < mass[0].n; i++) {
		out << mass[i].Z << "\n";
	}
	out.close();

	unsigned char* byte1;
	byte1 = new unsigned char[N];
	byte1 = DeCode(p, Xb, Yb, Zb);

	ofstream output("file1.jpg", ios::binary | ios::out);
	output.write((char*)byte1, file_size);
	output.close();
	system("pause");

	return 0;
}