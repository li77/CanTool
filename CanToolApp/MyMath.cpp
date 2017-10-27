#include "stdafx.h"
#include "MyMath.h"
#define BIGNUM40 0x4000000000000000
#define IDCOUNT 18
CString CMyMath::getSingleMsg(const CString & str0, const CString  str1)
{
	int mPos = str0.Find(str1);
	CString str2 = str0.Mid(mPos + str1.GetLength(), str0.GetLength() - mPos - str1.GetLength());
	//mPos = str2.Find(L'%');
	//strExtract((wchar_t *)(LPCWCHAR)str2.Left(mPos));
	wchar_t *p = wcschr((wchar_t *)(LPCWCHAR)str2, L'%');
	*p = L'\0';
	p = strExtract((wchar_t *)(LPCWCHAR)str2);
	return (CString)p;
}

//去除字符串两端的控制字符
//eg  wchar_t *asd = data0.strExtract((wchar_t *)(LPCWCHAR)str1);
wchar_t * CMyMath::strExtract(wchar_t * str)
{
	while (*str <= L' ' && *str != L'\0')
	{
		str++;
	}
	if (*str == L'\0')
		return nullptr;
	wchar_t *str1;
	str1 = str + wcslen(str) - 1;//指向‘\0’
	while (*str1 <= L' ')
	{
		str1--;
	}
	*(++str1) = L'\0';//2个字节
					  //	memcpy(++str1, L'\0',1);
	return str;

}

long long CMyMath::myWtoLL(  wchar_t * string,int index)
{
	assert(index==2|| index == 8 || index == 10 || index == 16);
	long long  num=0;
	wchar_t * p = string;

	if (index != 16)
	{
		//p先移到数字的部分
		while (!(*p >= L'0'&&*p <= L'9') && *p != L'\0')
		{
			p++;
		}
		while (*p >= L'0'&&*p <= L'9')
		{
			num = num*index+ *p-L'0';
			p++;
		}
		return num;
	}
	else //16进制，可自动0x
	{
		//p先移到数字或数字的部分
		while (!((*p >= L'0'&&*p <= L'9')|| (*p >= L'A'&&*p <= L'F')) && *p != L'\0')
		{
			p++;
		}
		if (*(p + 1) == L'x' || *(p + 1) == L'X')
		{
			p += 2;
		}
		while (1)
		{
			if (*p >= L'0'&&*p <= L'9')
				num = num*index + *p - L'0';
			else if (*p >= L'A'&&*p <= L'F')
				num = num*index + *p - L'A' + 10;
			else
				return num;
			p++;
		}
	}
	
}

BOOL CMyMath::myLLtoW(__int64 value, CString & str, int radix)
{
	assert(radix == 2 || radix == 8 || radix == 10 || radix == 16);
	wchar_t res[20];
	wchar_t *p = res;
	int i;
	if (radix != 16)
	{
		do {
			*p = value%radix + L'0';
			p++;
		} while ((value /= radix) != 0);
		*p = L'\0';
	}
	else //16进制
	{
		do {
			if((i= value%radix)>=10)
				*p = value%radix -10 + L'A';
			else
				*p = value%radix + L'0';
			p++;
		} while ((value /= radix) != 0);
		*p++ = L'x';
		*p++ = L'0';
		*p = L'\0';
	}
	str.Format(L"%s",res) ;
	str.MakeReverse();
	return true;
}

WCHAR * CMyMath::charToWchar(char * s)
{
	int w_nlen = MultiByteToWideChar(CP_ACP, 0, s, -1, NULL, 0);
	WCHAR *ret;
	ret = (WCHAR*)new wchar_t[sizeof(WCHAR)*w_nlen];
	memset(ret, 0, sizeof(ret));
	MultiByteToWideChar(CP_ACP, 0, s, -1, ret, w_nlen);
	return ret;
}

__int64 CMyMath::IDCardVerify(const CString str)
{
	//BIGNUM40
	int sig = 0;
	__int64 bigNum=myWtoLL((wchar_t *)(LPCWCHAR)str, 10);
	if (bigNum < 10 ^ (IDCOUNT - 1))//最后一位是个x
	{
		if (bigNum < 10 ^ (IDCOUNT - 2))//最高位为0
			return 0;
		bigNum *= 10;
		 sig = 1;
	}
	__int64 bigNumBuf;
			bigNumBuf = bigNum/10;//bigNum含18位数据
	//校验
	//bigNum IDCardRadix
	long count =0 ;
	for (int i=0;i<IDCOUNT-1;i++)
	{
		count += bigNumBuf % 10 * IDCardRadix[IDCOUNT-i-2];
		bigNumBuf /= 10;
	}
	if (count % 11 == 10)//要判断2，末位写成了2
	{
		if (bigNum / 10 != 2) 
			return 0;

	}
	else 
	{
		if (sig)//末位为x  取余结果应为2
		{
			if(count % 11 != 2)
				return 0;
		}
		else//大部分情况
		{
			if (bigNum / 10 != count % 11)
				return 0;
		}
	}
	//校验成功
	if (!sig)//大部分
		return bigNum;
	else
		return bigNum| BIGNUM40;
}

CString CMyMath::getIDCardStr(__int64 num)
{
	int sig = 0;
	CString str;
	if (num & BIGNUM40)//含X
	{
		num = num & (~BIGNUM40);
		sig = 1;
	}
	myLLtoW(num, str, 10);
	if (sig)
	{
		str = str.Left(17);
		str += L'x';
	}
	return str;
}

char * CMyMath::WCharToChar(WCHAR * s)
{
	int w_nlen = WideCharToMultiByte(CP_ACP, 0, s, -1, NULL, 0, NULL, false);
	char *ret = new char[w_nlen];
	memset(ret, 0, w_nlen);
	WideCharToMultiByte(CP_ACP, 0, s, -1, ret, w_nlen, NULL, false);
	return ret;
}

CMyMath::CMyMath()
{
}


CMyMath::~CMyMath()
{
}

