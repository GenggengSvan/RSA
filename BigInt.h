#pragma once
using namespace std;


int GetCalculateNum(char c);//��ȡ���ڼ�����ַ���Ӧ����ֵ���ر���Aת����10
char SetCalculateNum(int n);//������ֵ��Ӧ��ʮ��������

class BigInt {
private:
	string num="";//�洢ʮ�����������ַ�����ʽ
	
public:
	//���캯��
	BigInt();
	BigInt(string);
	BigInt(const BigInt&);
	
	string getnum() const;
	void setnum(string s);
	void print() const;
	int getbitnum() const;
	bool isEven() const;//�ж��Ƿ�Ϊż��
	bool isOdd() const;//�ж��Ƿ�Ϊ����

	//�߼�����
	bool operator == (const BigInt&) const;
	bool operator != (const BigInt&) const;
	bool operator > (const BigInt&) const;
	bool operator < (const BigInt&) const;
	bool operator >=  (const BigInt&) const;
	bool operator <= (const BigInt&) const;
	//��������
	BigInt operator + (const BigInt&) const;
	BigInt operator - (const BigInt&) const;
	BigInt operator * (const BigInt&) const;
	BigInt operator / (const BigInt&) const;
	BigInt operator % (const BigInt&) const;
	//λ����
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


//����һ���Ѿ����ɵĴ���������ʵ�ʼ����п��Բ����ٴ����ɴ�����
static string prime_1 = "F658394908C497875F21EC86A36293FC4D6931CE102D2F6BE09DA0276DA3DBAAF90BF4834906C1821B1515ABFAE8A0608CC9956743B537661C5FA5B7C10684DB";
static string prime_2 = "EAA1645713B01E0B797E969A26D393CDCBBC1AF6AF8DA45E2BF5DFFD8FFF8B300AC3B93E4A3C73DF98CCD3C2F3CE7673EEE06A3044B1544177682C3AB350123B";
