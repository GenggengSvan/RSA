#pragma once
using namespace std;


int GetCalculateNum(char c);//获取用于计算的字符对应的数值，特别是A转换成10
char SetCalculateNum(int n);//设置数值对应的十六进制数

class BigInt {
private:
	string num="";//存储十六进制数的字符串形式
	
public:
	//构造函数
	BigInt();
	BigInt(string);
	BigInt(const BigInt&);
	
	string getnum() const;
	void setnum(string s);
	void print() const;
	int getbitnum() const;
	bool isEven() const;//判断是否为偶数
	bool isOdd() const;//判断是否为奇数

	//逻辑运算
	bool operator == (const BigInt&) const;
	bool operator != (const BigInt&) const;
	bool operator > (const BigInt&) const;
	bool operator < (const BigInt&) const;
	bool operator >=  (const BigInt&) const;
	bool operator <= (const BigInt&) const;
	//算术运算
	BigInt operator + (const BigInt&) const;
	BigInt operator - (const BigInt&) const;
	BigInt operator * (const BigInt&) const;
	BigInt operator / (const BigInt&) const;
	BigInt operator % (const BigInt&) const;
	//位运算
	BigInt operator <<(unsigned int n) const;
};

class Bit{
private:
	string num_bit="";
	
public:
	string getnum_bit() { return num_bit; };
	void setnum_bit(string s);
	Bit(const BigInt&);
	Bit(const string);
	int size();
	bool at(int);
	void print();
	void leftShift(unsigned int n);
};


//给出一个已经生成的大素数，在实际加密中可以不用再次生成大素数
static string prime_1 = "F658394908C497875F21EC86A36293FC4D6931CE102D2F6BE09DA0276DA3DBAAF90BF4834906C1821B1515ABFAE8A0608CC9956743B537661C5FA5B7C10684DB";
static string prime_2 = "EAA1645713B01E0B797E969A26D393CDCBBC1AF6AF8DA45E2BF5DFFD8FFF8B300AC3B93E4A3C73DF98CCD3C2F3CE7673EEE06A3044B1544177682C3AB350123B";
