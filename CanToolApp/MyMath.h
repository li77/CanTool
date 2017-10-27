#pragma once
class CMyMath
{
	const char IDCardRadix[17] = { 7,9,10,5,8,  4,2,1,6,3,  7,9,10,5,8,  4,2 };
public:

	CString  getSingleMsg(const CString & str0, const CString  str1);//输入字段，返回字段内容
	wchar_t * strExtract(wchar_t *str);//剔除前后的' ','\r''\n','\t'
	long long myWtoLL( wchar_t *string,int index);//必须是干净的纯数字，支持2，8，10，16进制
	BOOL myLLtoW(__int64 value, CString &str, int radix);
	//char 转 WCHAR  需要释放WCHAR * delete[] ...
	WCHAR * charToWchar(char *s);
	//校验错误返回0
	//余数为2，末位就写成2,结果或（BIGNUM40）
	__int64 IDCardVerify(const CString str);
	CString getIDCardStr(__int64 num);
	
	template<class T>
	int getLength(T& data)
	{
		return sizeof(data) / sizeof(data[0]);
	}

	//	WCHAR 转char //返回结果用完要free掉.
	char* WCharToChar(WCHAR *s);
	CMyMath();
	~CMyMath();
};

