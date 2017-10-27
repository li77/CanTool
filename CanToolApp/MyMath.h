#pragma once
class CMyMath
{
	const char IDCardRadix[17] = { 7,9,10,5,8,  4,2,1,6,3,  7,9,10,5,8,  4,2 };
public:

	CString  getSingleMsg(const CString & str0, const CString  str1);//�����ֶΣ������ֶ�����
	wchar_t * strExtract(wchar_t *str);//�޳�ǰ���' ','\r''\n','\t'
	long long myWtoLL( wchar_t *string,int index);//�����Ǹɾ��Ĵ����֣�֧��2��8��10��16����
	BOOL myLLtoW(__int64 value, CString &str, int radix);
	//char ת WCHAR  ��Ҫ�ͷ�WCHAR * delete[] ...
	WCHAR * charToWchar(char *s);
	//У����󷵻�0
	//����Ϊ2��ĩλ��д��2,�����BIGNUM40��
	__int64 IDCardVerify(const CString str);
	CString getIDCardStr(__int64 num);
	
	template<class T>
	int getLength(T& data)
	{
		return sizeof(data) / sizeof(data[0]);
	}

	//	WCHAR תchar //���ؽ������Ҫfree��.
	char* WCharToChar(WCHAR *s);
	CMyMath();
	~CMyMath();
};

