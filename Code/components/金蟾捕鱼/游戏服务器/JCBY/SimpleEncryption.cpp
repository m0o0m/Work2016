#include "Stdafx.h"
#include "String.h"
#include "SimpleEncryption.h"




//交换两个BYTE
void Swap2Byte(unsigned char* v1, unsigned char* v2)
{
	*v1 ^= *v2;
	*v2 ^= *v1;
	*v1 ^= *v2;
}

void GetMyCypher(const char* pKey, int iKeyLen, unsigned char* pMyCypher)
{
	//原始加密索引
	const unsigned char cypherOrg[256] =
	{
		1, 3, 5, 15, 17, 51, 85, 255, 26, 46, 114, 150, 161, 248, 19, 53, 
		95, 225, 56, 72, 216, 115, 149, 164, 247, 2, 6, 10, 30, 34, 102, 170, 
		229, 52, 92, 228, 55, 89, 235, 38, 106, 190, 217, 112, 144, 171, 230, 49, 
		83, 245, 4, 12, 20, 60, 68, 204, 79, 209, 104, 184, 211, 110, 178, 205, 
		76, 212, 103, 169, 224, 59, 77, 215, 98, 166, 241, 8, 24, 40, 120, 136, 
		131, 158, 185, 208, 107, 189, 220, 127, 129, 152, 179, 206, 73, 219, 118, 154, 
		181, 196, 87, 249, 16, 48, 80, 240, 11, 29, 39, 105, 187, 214, 97, 163, 
		254, 25, 43, 125, 135, 146, 173, 236, 47, 113, 147, 174, 233, 32, 96, 160, 
		251, 22, 58, 78, 210, 109, 183, 194, 93, 231, 50, 86, 250, 21, 63, 65, 
		195, 94, 226, 61, 71, 201, 64, 192, 91, 237, 44, 116, 156, 191, 218, 117, 
		159, 186, 213, 100, 172, 239, 42, 126, 130, 157, 188, 223, 122, 142, 137, 128, 
		155, 182, 193, 88, 232, 35, 101, 175, 234, 37, 111, 177, 200, 67, 197, 84, 
		252, 31, 33, 99, 165, 244, 7, 9, 27, 45, 119, 153, 176, 203, 70, 202, 
		69, 207, 74, 222, 121, 139, 134, 145, 168, 227, 62, 66, 198, 81, 243, 14, 
		18, 54, 90, 238, 41, 123, 141, 140, 143, 138, 133, 148, 167, 242, 13, 23, 
		57, 75, 221, 124, 132, 151, 162, 253, 28, 36, 108, 180, 199, 82, 246, 1
	};

	memcpy(pMyCypher, cypherOrg, 256);

	//根据密码调整加密索引
	int i, j;
	for(i=0; i<iKeyLen; i++)
	{
		for(j=0; j<256; j++)
		{
			int iSwitchIndex = (pMyCypher[j] * pKey[i])%255;
			if(iSwitchIndex!=j)
				Swap2Byte(&(pMyCypher[j]), &(pMyCypher[iSwitchIndex]));
		}
	}
}

void JiangCode(unsigned char* pBuff, int iBuffLen, char* pKey, int iKeyLen)
{
	unsigned char cypher[256];
	GetMyCypher(pKey, iKeyLen, cypher);
	int iIndex=0;
	while (iIndex<iBuffLen)
	{
		//其实……也就一个异或操作，所以加密和解密的过程完全一样
		pBuff[iIndex] ^= cypher[iIndex%256];
		++iIndex;
	}
}

void JiangEncode(unsigned char* pBuff, int iBuffLen, char* pKey, int iKeyLen)
{
	JiangCode(pBuff, iBuffLen, pKey, iKeyLen);
}

void JiangDecode(unsigned char* pBuff, int iBuffLen, char* pKey, int iKeyLen)
{
	JiangCode(pBuff, iBuffLen, pKey, iKeyLen);
}