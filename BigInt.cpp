#include <iostream>
#include"BigInt.h"

int GetCalculateNum(char c) {
	int result = 0;
	if (c >= '0' && c <= '9')
		result = c - '0';
	else if (c >= 'A' && c <= 'F')
		result = c - 'A' + 10;

	return result;
}

char SetCalculateNum(int n) {
	char c = '0';
	n = n % 16;
	if (n >= 0 && n <= 9)
		c = '0' + n;
	else if (n >= 10 && n <= 15)
		c = 'A' + (n - 10);
	return c;
}

string Addition(string a, string b)
{
	int la = a.length();
	int lb = b.length();
	int l = max(la, lb);
	int carry = 0;//进位的值
	string result(l, 0);
	for (int i = 0;i < l;i++)
	{
		int temp_a=0, temp_b=0;
		//计算a的第i位的16进制值,从最后一个字节，最低位开始计算
		if (i < la)
			temp_a = GetCalculateNum(a[la - 1 - i]);

		if (i < lb)
			temp_b = carry + GetCalculateNum(b[lb - 1 - i]);
		else
			temp_b = carry;

		result[l - 1 - i] = SetCalculateNum((temp_a+temp_b));
		carry = (temp_a + temp_b) / 16;
	}
	if (carry > 0)
		result = "1" + result;
	return result;
}

string LeftShift(string s, unsigned int len) {
	for (int i = 0;i < len;i++) {
		s = Addition(s, s);
	}
	return s;
}

//substract
string Substract(string a, string b)
{
	int la = a.length();
	int lb = b.length();
	if (la < lb) return "-1";
	if (la == lb && a < b) return "-1";
	if (a == b) return "0";

	int carry = 0;
	for (int i = 0;i < lb;i++)
	{
		int temp_a = GetCalculateNum(a[la - 1 - i]);
		int temp_b = GetCalculateNum(b[lb - 1 - i]);
		int temp_now = temp_a - temp_b-carry;
		if (temp_now<0)
		{
			temp_now += 16;
			carry = 1;
		}
		else
			carry = 0;
		a[la - 1 - i] = SetCalculateNum(temp_now);
	}
	if (carry)
	{
		for (int i = lb;i < la;i++)
		{
			if (a[la - 1 - i] == '0')
				a[la - 1 - i] = 'F';
			else
			{
				int temp_a = GetCalculateNum(a[la - 1 - i]);
				temp_a -= 1;
				a[la - 1 - i]=SetCalculateNum(temp_a);
				break;
			}
		}
	}
	//删去字符串前面的0
	int st = 0;
	while (st < la)
	{
		if (a[st] != '0') break;
		st++;
	}
	a = a.substr(st);
	return a;
}

string Mult(string num, string s)
{
	if (num == "0" || s == "0")
		return "0";
	Bit small("");
	string temp_num;
	if (num.length() > s.length()) {
		small.setnum_bit(s);
		temp_num = num;
	}
	else {
		small.setnum_bit(num);
		temp_num = s;
	}

	string result = "";
	for (int i = small.size() - 1;i >= 0;--i)
	{
		if (small.at(i)) {
			result = Addition(result, temp_num);
		}
		temp_num = Addition(temp_num, temp_num);
	}
	return result;
}

//Divide
bool Div(string num, string s, string& q, string& r)
{
	if (s == "0")
		return false;

	int la = num.length();
	int lb = s.length();
	if ((la < lb) || (la == lb && num < s))//如果除数大于被除数，商为0
	{
		q = "0";
		r = num;
		return true;
	}
	int l = la - lb + 1;
	string quotient(l, '0');//商
	string last = num.substr(0, lb - 1);//余数
	string stmp;

	for (int i = 0;i < l;i++)
	{
		int temp_quot = 0;
		stmp = last + num[lb + i - 1];
		last = stmp;
		while ((stmp = Substract(stmp, s)) != "-1")
		{
			temp_quot += 1;
			last = stmp;
		}
		quotient[i] = SetCalculateNum(temp_quot);
		if (last == "0") last = "";
	}
	q = (quotient[0] == '0' ? quotient.substr(1) : quotient);
	r = (last == "" ? "0" : last);
	return true;
}




//构造函数
BigInt::BigInt() {}

BigInt::BigInt(string s)
{
	num = s;
}
BigInt::BigInt(const BigInt& b) {
	this->num = b.num;
}

// get number of BigInt
string BigInt::getnum() const
{
	return num;
}

//set number of BigInt, if invalid set "0"
void BigInt::setnum(string s)
{
	num = s;
}

//print number
void BigInt::print() const
{
	cout << num << endl;
}

int BigInt::getbitnum() const
{
	return num.length() * 4;
}

bool BigInt::isEven() const
{
	//判断奇偶数性，判断最后一个十六进制数是否是以下数组中的字符，如果是，就是奇数、否则为偶数
	char hex_table_odd[] = { '1','3','5','7','9','B','D','F' };
	char c = num.back();
	bool result = true;
	for (int i = 0;i < 8;i++) {
		if (c == hex_table_odd[i]) {
			result = false;
			break;
		}
	}
	return result;
}

bool BigInt::isOdd() const
{
	char hex_table_odd[] = { '0','2','4','6','8','A','C','E' };
	char c = num.back();
	bool result = true;
	for (int i = 0;i < 8;i++) {
		if (c == hex_table_odd[i]) {
			result = false;
			break;
		}
	}
	return result;
}

bool BigInt::operator == (const BigInt& b) const
{
	return num == b.getnum();
}
bool BigInt::operator != (const BigInt& b) const
{
	return !(num == b.getnum());
}
bool BigInt::operator > (const BigInt& b) const
{
	string s = b.getnum();
	//先比较字符串长度，长度相同，比较字符串大小
	return((num.length() > s.length()) || (num.length() == s.length() && num > s));
}

bool BigInt::operator < (const BigInt& b) const
{
	string s = b.getnum();
	return((num.length() < s.length()) || (num.length() == s.length() && num < s));
}

bool BigInt::operator >= (const BigInt& b) const
{
	string s = b.getnum();
	return((num.length() > s.length()) || (num.length() == s.length() && num >= s));
}

bool BigInt::operator <= (const BigInt& b) const
{
	string s = b.getnum();
	return((num.length() < s.length()) || (num.length() == s.length() && num <= s));
}

BigInt BigInt::operator + (const BigInt& b) const
{
	return BigInt(Addition(num, b.getnum()));
}

BigInt BigInt::operator - (const BigInt& b) const
{
	return BigInt(Substract(num, b.getnum()));
}

BigInt BigInt::operator * (const BigInt& b) const
{
	return BigInt(Mult(num, b.getnum()));
}

BigInt BigInt::operator / (const BigInt& b) const
{
	string q, r;
	if (Div(num, b.getnum(), q, r))
		return BigInt(q);
	else
		return BigInt("-1");
}

BigInt BigInt::operator % (const BigInt& b) const
{
	string q, r;
	if (Div(num, b.getnum(), q, r))
		return BigInt(r);
	else
		return BigInt("-1");
}





Bit::Bit(const BigInt& bigint) {
	string num = bigint.getnum();
	string hex_bin[] = { "0000","0001","0010","0011","0100","0101","0110","0111",
						 "1000","1001","1010","1011","1100","1101","1110","1111" };
	string hex_bin_first[] = { "","1","10","11","100","101","110","111",
						 "1000","1001","1010","1011","1100","1101","1110","1111" };
	int len = num.length();
	int temp_num = GetCalculateNum(num[0]);
	num_bit.append(hex_bin_first[temp_num]);
	for (int i = 1;i < len;i++) {
		int temp_num = GetCalculateNum(num[i]);
		num_bit.append(hex_bin[temp_num]);
	}
}

Bit::Bit(const string bigint) {
	string hex_bin[] = { "0000","0001","0010","0011","0100","0101","0110","0111",
						 "1000","1001","1010","1011","1100","1101","1110","1111" };
	string hex_bin_first[] = { "","1","10","11","100","101","110","111",
						 "1000","1001","1010","1011","1100","1101","1110","1111" };
	int len = bigint.length();
	int temp_num = GetCalculateNum(bigint[0]);
	num_bit.append(hex_bin_first[temp_num]);
	for (int i = 1;i < len;i++) {
		int temp_num = GetCalculateNum(bigint[i]);
		num_bit.append(hex_bin[temp_num]);
	}
}

int Bit::size() {
	return num_bit.length();
}

bool Bit::at(int loc) {
	if (num_bit[loc] == '1')
		return true;
	else
		return false;
}

void Bit::print() {
	cout << num_bit << endl;
}

void Bit::setnum_bit(string bigint)
{
	string hex_bin[] = { "0000","0001","0010","0011","0100","0101","0110","0111",
						 "1000","1001","1010","1011","1100","1101","1110","1111" };
	string hex_bin_first[] = { "","1","10","11","100","101","110","111",
						 "1000","1001","1010","1011","1100","1101","1110","1111" };
	int len = bigint.length();
	int temp_num = GetCalculateNum(bigint[0]);
	num_bit.append(hex_bin_first[temp_num]);
	for (int i = 1;i < len;i++) {
		int temp_num = GetCalculateNum(bigint[i]);
		num_bit.append(hex_bin[temp_num]);
	}
}

void Bit::leftShift(unsigned int n) {
	string add_str(n, '0');
	num_bit.append(add_str);
}