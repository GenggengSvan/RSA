#include<iostream>
#include"BigInt.h"
#include"RSA.h"
using namespace std;

void ExtendEuclid(BigInt a, BigInt b, BigInt& x, BigInt& y, const BigInt& m) {
	if (a == BigInt("0")) {
		x = BigInt("0"), y = BigInt("1");
		return;
	}
	BigInt c = b / a, d = b % a;
	ExtendEuclid(d, a, y, x, m);
	x = (x + m - (c * y) % m) % m;  
}

int main() {

	RSA *rsa=new RSA();
	while (true)
	{
		int model;
		cout << "��ѡ�����ģʽ��1�����ļ��ܣ�2�����Ľ��ܣ�3����ȡ��Կ�ԣ�4�����ɴ�����" << endl;
		cin >> model;
		if (model == 1) {
			string m;
			cout << "����ʮ��������������:";
			cin >> m;
			BigInt M = BigInt(m);

			cout << "���빫Կ��:����e:";
			string e;
			cin >> e;
			BigInt E = BigInt(e);
			cout << "����n:";
			string n;
			cin >> n;
			BigInt N = BigInt(n);

			BigInt C = rsa->Encrypt(M, E, N);
			C.print();
		}

		else if (model == 2) {
			string m;
			cout << "����ʮ��������������:";
			cin >> m;
			BigInt M = BigInt(m);

			cout << "����˽Կ��:����d:";
			string d;
			cin >> d;
			BigInt D = BigInt(d);
			cout << "����n:";
			string n;
			cin >> n;
			BigInt N = BigInt(n);

			BigInt C = rsa->Decrypt(M, D, N);
			C.print();
		}

		else if (model == 3) {
			BigInt p(prime_1);
			BigInt q(prime_2);
			BigInt n = p * q;
			BigInt EulerN = (p - BigInt("1")) * (q - BigInt("1"));

			BigInt e = BigInt("10001");

			BigInt d, y;
			ExtendEuclid(e, EulerN, d, y, EulerN);
			cout << "����Կ��" << endl;
			cout << "e:";
			e.print();
			cout << "n:";
			n.print();
			cout << "����Կ��" << endl;
			cout << "d:";
			d.print();
			cout << "n:";
			n.print();
		}

		else if (model == 4) {
			BigInt A = rsa->CreatePrime(512);
			A.print();
		}
	}
}