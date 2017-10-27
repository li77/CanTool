// AdoLx.h: Version 1.1（支持Unicode、支持VS2015和VC6编译环境）
//支持Unicode、支持Access、SQLServer和Oracle三大数据库
//Author:吕鑫老师封装类 
//吕鑫老师微博：http://t.qq.com/richmain 吕鑫老师微信：richmain
//更多更好的是项目开发视频教程，请登录http://www.baojy.com
//////////////////////////////////////////////////////////////////////
#pragma once
#pragma warning (disable:4146)
#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename("EOF","adoEOF")rename("BOF","adoBOF")
#ifndef SQLSTRING
#define SQLSTRING
	//SQL语句
	//注意，当要选择所有数据时，where 字段可以写成"1"
	#define	ADDTAB  L"create table %s%s ;"   //"mytable"  "(id int(3) auto_increment not null primary key,timedate time,name char(10) not null,address varchar(20),year date,s1 char(11) ,s2 int default ‘1’ )"
	#define	SELTAB	L"select * from %s where %s;"//"mytable","name  = \"bj\""
	#define	DELTAB	L"drop table %s;" //"mytable"
	#define	CLRTAB	L"delete from %s;"//"mytable"
	#define	ORDTAB	L"select * from %s where %s order by %s;"	//"mytable","1","name"  这是全排列，可以替换‘*’
	//修改某几行的某个字段的值
	#define	MODFIELDVAL	L"update %s set %s where %s;"	//"mytable" , "address = \"桃园县一中\""," name  = \"jj\"";
	//按整行增删
	#define	ADDVAL	L"insert into %s values %s;"//"mytable","('1','2010-10-08', 'bj','深圳一中','2010-10-08','MySQLTest',20)"
	#define	DELVAL	L"delete from %s where %s;"//"mytable","id>4 and id<9"
	 //增删字段
	#define	ADDFIELD	L"alter table %s add %s;"	//添加表字段"mytable","id int unsigned not Null auto_increment primary key"
	#define	DELFIELD	L"alter table %s DROP %s;"	//"mytable","name"
	#define	MODFIELD	L"alter table %s modify %s;"	//"mytable","name"

//str.Format(TEXT("Provider=MSDASQL.1; Catalog=%s;Password=%s"),szDatabase, szPass);
#endif
class CAdoLx
{
protected:
	_RecordsetPtr m_pRst;
	_ConnectionPtr m_pConn;

	CString m_szLastError;
public:
	void Release()
	{
		m_pConn->Release();
	}
	BOOL GetFieldType(long nIndex, int &nType);
	enum EType { DBT_ACCESS, DBT_SQL, DBT_ORACLE ,DBT_MYSQL};

	BOOL Connect(EType eType, LPCTSTR szDatabase, LPCTSTR szPass = NULL, LPCTSTR szUser = NULL, LPCTSTR szHost = NULL, LPCTSTR szDSN=NULL);
	int ExecSQL(CString szSQL);//返回影响的行数,功能包括了Select函数

	BOOL IsEOF();//是数据末尾，返回1
	//可接受错误，一般不接收或不处理
	BOOL MoveNext();
	BOOL MovePrev();
	BOOL MoveFirst();
	BOOL MoveLast();
	//GetField**是输出函数，到某个变量
	//可接受错误输出
	BOOL GetFieldValue(LPCTSTR szField, COleDateTime &tValue);//按列进行输出，eg,szField="name",sValue就输出当前位置的姓名
	BOOL GetFieldValue(LPCTSTR szField, double &fValue);
	BOOL GetFieldValue(LPCTSTR szField, CString &sValue);
	BOOL GetFieldValue(LPCTSTR szField, int &iValue);
	BOOL GetFieldValueLL(LPCTSTR szField, __int64 &iValue);


	BOOL GetFieldByIndex(long nIndex, COleDateTime &tValue);//nIndex表示第几列
	BOOL GetFieldByIndex(long nIndex, double &fValue);
	BOOL GetFieldByIndex(long nIndex, CString &sValue);  //str= WCHAR*
	BOOL GetFieldByIndex(long nIndex, int &iValue);
	BOOL GetFieldByIndex(long nIndex, long &lValue);
	BOOL GetFieldByIndex(long nIndex, DWORD &dwValue);
	BOOL GetFieldByIndex(long nIndex, UINT &iValue);
	BOOL GetFieldByIndex(long nIndex, char &cValue);
	BOOL GetFieldByIndex(long nIndex, short &nValue);
	BOOL GetFieldByIndex(long nIndex, BYTE &cbValue);
	BOOL GetFieldByIndex(long nIndex, WORD &wValue);

	BOOL GetFieldByIndex(long nIndex, TCHAR sValue[], int nSize);



	int GetFieldCount();//取得列数
	BOOL GetFieldName(long nIndex, CString &szName);
	int GetRecordCount();//普通的表返回的是-1;(未出错)，需要MessageBox的时候需要判断一下GetLastError（）是否为空

	CString GetLastError()
	{
		CString str = m_szLastError;
		m_szLastError.Empty();
		return str;
	}
	//不处理报错！
	BOOL ExitConnect(void)
	{
		//关闭记录集和连接  
		try
		{
			if (m_pRst != NULL)
				m_pRst->Close();
//			if (m_pConn != NULL)
				m_pConn->Close();
		}
		catch (_com_error &e)
		{
			m_szLastError = (LPCTSTR)e.Description();
			//	TRACE(m_szLastError+"\n");
			return FALSE;
		}
		return true;
	}
	//此类中类的使用没看明白
	class CProc   
	{
		/*
		enum ParameterDirectionEnum
		{
		adParamUnknown = 0,
		adParamInput = 1,
		adParamOutput = 2,
		adParamInputOutput = 3,
		adParamReturnValue = 4
		};
		*/
		CString m_szLastError;
	public:
		_CommandPtr m_pCmd;
		//_ConnectionPtr & m_pConn;
	
		LPCTSTR GetLastError() const
		{
			return m_szLastError;
		}
		int Exec();
		BOOL Create(_ConnectionPtr &pConn, LPCTSTR szProc);

		BOOL AddParam(LPCTSTR szVName, long lParam, ParameterDirectionEnum eDir = adParamInput);
		BOOL AddParam(LPCTSTR szVName, LPCTSTR szParam, ParameterDirectionEnum eDir = adParamInput);

		BOOL GetValue(LPCTSTR szVName, long &lParam);
		BOOL GetValue(LPCTSTR szVName, CString &lParam);

		void Release()
		{
			delete this;
		}
		CProc()
		{
		}

	};
	CProc* CreateProc(LPCTSTR szProc);//L"P_LOGIN"
	int ExecProc(CProc* pProc);
	//CAdoLx::CProc* pro = myMySql.CreateProc(L"P_LOGIN");//L"P_LOGIN"
	//myMySql.ExecProc(pro);

	BOOL Select(LPCTSTR szSQL);
	CAdoLx();
	virtual ~CAdoLx();

};


/*
CAdoLx myMySql;
if (!myMySql.Connect(CAdoLx::EType::DBT_MYSQL, L"mydb", L"1638081534l", L"root", L"localhost", L"MySQL-ODBC"))
{
	MessageBox(myMySql.GetLastError());
}
CString str;

//ADDTAB
str.Format(ADDTAB, L"firstTable", L"(mNum int  not null primary key)");
myMySql.ExecSQL(str);
if (myMySql.GetLastError().Find(L"already exists") != -1)
{
	//notify!!
}

//DELTAB
str.Format(DELTAB, L"firstTable");
myMySql.ExecSQL(str);

//MODFIELD
str.Format(ADDFIELD, L"firstTable", L"mTableName VARCHAR(6)");
myMySql.ExecSQL(str);
if (myMySql.GetLastError().Find(L"Duplicate column name") != -1)
{
	str.Format(MODFIELD, L"firstTable", L"mTableName VARCHAR(6)");
	myMySql.ExecSQL(str);
}



myMySql.ExitConnect();
*/