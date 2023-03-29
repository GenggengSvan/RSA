#include <iostream>
#include"RSA.h"
using namespace std;

BigInt Moden(const BigInt& a,const BigInt& b, const BigInt& m)
{

	if (b == BigInt("0")) return BigInt("1");
	if (b == BigInt("1")) return (a % m);
	BigInt hb = b/BigInt("2");
	BigInt phb = Moden(a, hb, m);
	BigInt res = (phb * phb) % m;
	if (!b.isEven())
		res = (a * res) % m;
	return res;
}

//生成一个大的奇数，len是奇数的bit长度
BigInt RSA::CreateOddNum(int len)//512bit的最高位应该固定为1
{
	srand(time(0));
	len = len / 4 + ((len % 4 > 0) ? 1 : 0);//因为string中使用十六进制表示，所以位数应该是4的倍数，不是将它近似为4的倍数
	char hex_table[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	char hex_table_odd[] = { '1','3','5','7','9','B','D','F' };
	string str = "";
	str.push_back(hex_table[rand() % 8 + 8]);//最高位固定为1
	for (int i = 1;i < len-1;i++) {
		str.push_back(hex_table[rand() % 16]);
	}
	str.push_back(hex_table_odd[rand() % 8]);//最后一位确保它为奇数

	return BigInt(str);
}

//生成一个小的随机数，BigInt表示,最高为16bit
BigInt RSA::CreateSmallNum()
{
	srand(time(0));
	int len = rand()%3;
	char hex_table[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	char hex_table_odd[] = { '1','3','5','7','9','B','D','F' };
	string str = "";
	str.push_back(hex_table[rand() % 8 + 8]);//最高位固定为1
	for (int i = 1;i < len;i++) {
		str.push_back(hex_table[rand() % 16]);
	}
	return BigInt(str);
}



bool RSA::isPrime(BigInt num)
{
	srand(time(0));
	if (num == BigInt("2"))//2是素数
		return true;
	if (num < BigInt("2"))//0，1不是素数
		return false;
	BigInt num_1 = num - BigInt("1");
	Bit b(num_1);
	

	for (int t = 0;t < 20;t++)
	{
		BigInt a = CreateSmallNum();//随机数
		BigInt x;
		BigInt d("1");
		
		for (int i = num.getbitnum() - 1;i >= 0;--i)
		{
			x.setnum(d.getnum());
			d = (d * d) % num;
			if (d == BigInt("1") && x != BigInt("1") && x != (num- BigInt("1")))
				return false;

			if (b.at(i))
			{
				d = (a * d) % num;
			}
		}
		if (d != BigInt("1"))
			return false;
	}
	return true;

	
}

BigInt RSA::CreatePrime(int len) {
	BigInt result = CreateOddNum(len);
	int count = 0;
	while (!isPrime(result))
	{
		result = result + BigInt("2");
		count++;
		if (count > 10) {
			result = CreateOddNum(len);
			count = 0;
		}	
	}
	return result;
}

BigInt RSA::Encrypt(BigInt m, BigInt e, BigInt n) {
	return Moden(m, e, n);
}

BigInt RSA::Decrypt(BigInt c, BigInt d, BigInt n) {
	return Moden(c,d, n);
}