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
		cout << "请选择操作模式：1：明文加密；2：密文解密；3：获取密钥对；4：生成大素数" << endl;
		cin >> model;
		if (model == 1) {
			string m;
			cout << "输入十六进制明文数据:";
			cin >> m;
			BigInt M = BigInt(m);

			cout << "输入公钥对:输入e:";
			string e;
			cin >> e;
			BigInt E = BigInt(e);
			cout << "输入n:";
			string n;
			cin >> n;
			BigInt N = BigInt(n);

			BigInt C = rsa->Encrypt(M, E, N);
			C.print();
		}

		else if (model == 2) {
			string m;
			cout << "输入十六进制密文数据:";
			cin >> m;
			BigInt M = BigInt(m);

			cout << "输入私钥对:输入d:";
			string d;
			cin >> d;
			BigInt D = BigInt(d);
			cout << "输入n:";
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
			cout << "公开钥：" << endl;
			cout << "e:";
			e.print();
			cout << "n:";
			n.print();
			cout << "秘密钥：" << endl;
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