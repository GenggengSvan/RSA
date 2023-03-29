#pragma once
#include"BigInt.h"
#include"stdlib.h"
#include "time.h"
#include<cassert>

class RSA {

public:
	BigInt CreateOddNum(int);
	BigInt CreateSmallNum();
	bool isPrime(BigInt);
	BigInt CreatePrime(int);

	BigInt Encrypt(BigInt, BigInt, BigInt);
	BigInt Decrypt(BigInt, BigInt, BigInt);

};