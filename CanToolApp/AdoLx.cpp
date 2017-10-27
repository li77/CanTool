// AdoLx.cpp: Version 1.1��֧��Unicode��֧��VS2015��VC6���뻷����
//֧��Unicode��֧��Access��SQLServer��Oracle�������ݿ�
//Author:������ʦ��װ�� 
//������ʦ΢����http://t.qq.com/richmain ������ʦ΢�ţ�richmain
//������õ�����Ŀ������Ƶ�̳̣����¼http://www.baojy.com
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AdoLx.h"
#include "intsafe.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAdoLx::CAdoLx()
{
	::OleInitialize(NULL);
}

CAdoLx::~CAdoLx()
{
	//if (m_pRst)
	//	m_pRst->Close();
	//m_pConn->Close();
}

BOOL CAdoLx::Connect(EType eType, LPCTSTR szDatabase, LPCTSTR szPass, LPCTSTR szUser, LPCTSTR szHost, LPCTSTR szDSN)
{
	CString str;
	switch (eType)
	{
	case DBT_ACCESS:
	{
		str.Format(TEXT("Provider=MSDASQL.1;Persist Security Info=False;Data Source=MS Access Database;Initial Catalog=%s;Password=%s"),
			szDatabase,szPass);
	}
	break;
	case DBT_SQL:
	{
		str = TEXT("Driver=SQL Server;Server=");
		str += szHost;
		str += TEXT(";Database=");
		str += szDatabase;
		str += TEXT(";UID=");
		str += szUser;
		str += TEXT(";PWD=");
		str += szPass;
	}

	break;
	case DBT_ORACLE:
		str = TEXT("Provider=OraOLEDB.Oracle.1;Persist Security Info=False;User ID=");
		str += szUser;
		str += TEXT(";Password=");
		str += szPass;
		str += TEXT(";Data Source=");
		str += szDatabase;
		break;
	case DBT_MYSQL:
		//"DSN=MySQL-ODBC;server=localhost;database=mydb;"
		str = TEXT("DSN=");
		str += szDSN;
		str += TEXT(";server=");
		str += szHost;
		str += TEXT(";database=");
		str += szDatabase;
		break;
	}

	try
	{
		m_pConn.CreateInstance(__uuidof(Connection));
		m_pConn->Open(_bstr_t(str), szUser, szPass, adModeUnknown);///�������ݿ�
//		if (m_pRst)
//			m_pRst->Close();
		m_pRst.CreateInstance(__uuidof(Recordset));

	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		//	TRACE(m_szLastError+"\n");
		return FALSE;
	}
	return TRUE;

}


int CAdoLx::ExecSQL(CString szSql)
{
	_variant_t vRet;
	try
	{
		/*if (m_pRst)
			m_pRst->Close();*/
		m_pRst=m_pConn->Execute((_bstr_t)szSql, &vRet, adCmdText);
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return e.Error();
	}

	return (long)vRet;
}
BOOL CAdoLx::IsEOF()
{
	/*try
	{
		if (m_pRst->GetadoEOF())
			return TRUE;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
	}
	return FALSE;*/
	return m_pRst->adoEOF;
}


BOOL CAdoLx::Select(LPCTSTR szSQL)
{
	try
	{
		//if (m_pRst)
		//	m_pRst->Close();
		//m_pRst.CreateInstance(__uuidof(Recordset));
		//		m_pRst ->Open(szSQL,m_pConn.GetInterfacePtr(),adOpenForwardOnly,adLockReadOnly,adCmdText);
		m_pRst->Open(szSQL, m_pConn.GetInterfacePtr(), adOpenStatic, adLockReadOnly, adCmdText);
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}

	return TRUE;
}
int CAdoLx::GetFieldCount()
{
	try
	{
		return m_pRst->Fields->Count;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return -1;
	}
	return -1;
}

BOOL CAdoLx::GetFieldByIndex(long nIndex, TCHAR sValue[], int nSize)
{
	try
	{
		_variant_t v = m_pRst->GetCollect(nIndex);
		if (v.vt == VT_NULL)
		{
			*sValue = 0;
			return TRUE;
		}
		CString str = v.bstrVal;
		LPCTSTR p = str;
		int i = 0;
		while (--nSize && (*sValue = *p) != 0)
		{
			sValue++;
			p++;
		}
		if (!nSize)
			*sValue = 0;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}

	return TRUE;
}
BOOL CAdoLx::GetFieldName(long nIndex, CString &szName)
{
	try
	{
		szName = (LPCTSTR)m_pRst->Fields->Item[nIndex]->Name;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
	return TRUE;
}
BOOL CAdoLx::GetFieldValue(LPCTSTR szField, int &iValue)
{

	try
	{
		iValue = (long)m_pRst->GetCollect(szField);
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
	return TRUE;
}
BOOL CAdoLx::GetFieldValueLL(LPCTSTR szField, __int64 &iValue)
{

	try
	{
		iValue = (long long)m_pRst->GetCollect(szField);
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
	return TRUE;
}
BOOL CAdoLx::GetFieldValue(LPCTSTR szField, double &fValue)
{
	try
	{
		fValue = (double)m_pRst->GetCollect(szField);
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
	return TRUE;
}
BOOL CAdoLx::GetFieldByIndex(long nIndex, int &iValue)
{
	try
	{
		_variant_t v = m_pRst->GetCollect(nIndex);
		iValue = (long)v;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
	return TRUE;
}

BOOL CAdoLx::GetFieldByIndex(long nIndex, CString &szValue)
{
	try
	{
		_variant_t v = m_pRst->GetCollect(nIndex);
		if (v.vt == VT_NULL)
			szValue.Empty();
		else
			szValue = v.bstrVal;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
	return TRUE;
}

BOOL CAdoLx::GetFieldByIndex(long nIndex, COleDateTime &tValue)
{
	try
	{
		_variant_t v = m_pRst->GetCollect(nIndex);
		if (v.vt == VT_NULL)
			tValue = 0.0;
		else
			tValue = v;
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdoLx::GetFieldByIndex(long nIndex, double &fValue)
{
	try
	{
		_variant_t v = m_pRst->GetCollect(nIndex);
		if (v.vt == VT_NULL)
			fValue = 0.0;
		else
			fValue = v;
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}

}

BOOL CAdoLx::GetFieldByIndex(long nIndex, long &lValue)
{
	try
	{
		_variant_t v = m_pRst->GetCollect(nIndex);
		if (v.vt == VT_NULL)
			lValue = 0;
		else
			lValue = v;
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}

}
/*
LONG lVal;
BYTE bVal;
SHORT iVal;
FLOAT fltVal;
DOUBLE dblVal;
*/
BOOL CAdoLx::GetFieldByIndex(long nIndex, DWORD &dwValue)
{
	try
	{
		_variant_t v = m_pRst->GetCollect(nIndex);
		if (v.vt == VT_NULL)
			dwValue = 0;
		else
			dwValue = v.lVal;
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}

}

BOOL CAdoLx::GetFieldByIndex(long nIndex, UINT &iValue)
{
	try
	{
		_variant_t v = m_pRst->GetCollect(nIndex);
		if (v.vt == VT_NULL)
			iValue = 0;
		else
			iValue = v.lVal;
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}

}
BOOL CAdoLx::GetFieldByIndex(long nIndex, char &cValue)
{
	try
	{
		_variant_t v = m_pRst->GetCollect(nIndex);
		if (v.vt == VT_NULL)
			cValue = 0;
		else
			cValue = v.bVal;
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}

}

BOOL CAdoLx::GetFieldByIndex(long nIndex, short &nValue)
{
	try
	{
		_variant_t v = m_pRst->GetCollect(nIndex);
		if (v.vt == VT_NULL)
			nValue = 0;
		else
			nValue = v;
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}

}
BOOL CAdoLx::GetFieldByIndex(long nIndex, BYTE &cbValue)
{
	try
	{
		_variant_t v = m_pRst->GetCollect(nIndex);
		if (v.vt == VT_NULL)
			cbValue = 0;
		else
			cbValue = v;
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
}
BOOL CAdoLx::GetFieldByIndex(long nIndex, WORD &wValue)
{
	try
	{
		_variant_t v = m_pRst->GetCollect(nIndex);
		if (v.vt == VT_NULL)
			wValue = 0;
		else
			wValue = v.iVal;
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}

}

BOOL CAdoLx::MoveFirst()
{
	try
	{
		return m_pRst->MoveFirst() == S_OK;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
}
BOOL CAdoLx::MoveLast()
{
	try
	{
		return m_pRst->MoveLast() == S_OK;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdoLx::MoveNext()
{
	try
	{
		return m_pRst->MoveNext() == S_OK;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
}
BOOL CAdoLx::MovePrev()
{
	try
	{
		return m_pRst->MovePrevious() == S_OK;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
}

BOOL CAdoLx::GetFieldType(long nIndex, int &nType)
{
	try
	{
		nType = m_pRst->Fields->Item[nIndex]->Type;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
	return TRUE;

}

BOOL CAdoLx::GetFieldValue(LPCTSTR szField, CString &sValue)
{
	try
	{
		sValue = m_pRst->GetCollect(szField).bstrVal;
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}


}
BOOL CAdoLx::GetFieldValue(LPCTSTR szField, COleDateTime &tValue)
{
	try
	{
		tValue = (DATE)m_pRst->GetCollect(szField);
		return TRUE;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
}



int CAdoLx::GetRecordCount()
{
	try
	{
		return m_pRst->GetRecordCount();
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
}





BOOL CAdoLx::CProc::Create(_ConnectionPtr &pConn, LPCTSTR szProc)
{
	try
	{
		m_pCmd.CreateInstance(__uuidof(Command));
		m_pCmd->ActiveConnection = pConn;
		m_pCmd->CommandType = adCmdStoredProc;
		m_pCmd->CommandText = _bstr_t(szProc);
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
	return TRUE;
}

CAdoLx::CProc* CAdoLx::CreateProc(LPCTSTR szProc)
{
	if (m_pConn == NULL)return FALSE;
	CProc* pProc = new CProc;
	if (pProc->Create(m_pConn, szProc))
		return pProc;
	delete pProc;
	return NULL;
}

BOOL CAdoLx::CProc::AddParam(LPCTSTR szVName, long lParam, ParameterDirectionEnum eDir)
{
	if (m_pCmd == NULL)
		return FALSE;
	try
	{
		_ParameterPtr pParam = m_pCmd->CreateParameter(szVName, adInteger, eDir, sizeof(long), lParam);
		m_pCmd->Parameters->Append(pParam);
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}

	return TRUE;
}
BOOL CAdoLx::CProc::AddParam(LPCTSTR szVName, LPCTSTR szParam, ParameterDirectionEnum eDir)
{
	if (m_pCmd == NULL)
		return FALSE;
	try
	{
		_ParameterPtr pParam = m_pCmd->CreateParameter(_bstr_t(szVName), adVarChar, eDir, lstrlen(szParam) + 2, szParam);
		m_pCmd->Parameters->Append(pParam);
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}

	return TRUE;
}

int CAdoLx::CProc::Exec()
{
	try
	{
		m_pCmd->Execute(NULL, NULL, adCmdStoredProc);

	}
	catch (_com_error& e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return e.Error();
	}
	return 0;
}

BOOL CAdoLx::CProc::GetValue(LPCTSTR szVName, long &lParam)
{
	try
	{
		_variant_t var = m_pCmd->Parameters->GetItem(_bstr_t(szVName))->GetValue();
		lParam = var;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
	return TRUE;
}

BOOL CAdoLx::CProc::GetValue(LPCTSTR szVName, CString &szParam)
{
	try
	{
		_bstr_t bstr = m_pCmd->Parameters->GetItem(_bstr_t(szVName))->GetValue();
		szParam = (LPCTSTR)bstr;
	}
	catch (_com_error &e)
	{
		m_szLastError = (LPCTSTR)e.Description();
		return FALSE;
	}
	return TRUE;

}

int CAdoLx::ExecProc(CProc* pProc)
{
	try
	{
	//if(FAILED(pProc->m_pCmd.CreateInstance(__uuidof(Command))))
	//{
	//return -1;

	//}
	//pProc->m_pCmd->ActiveConnection   =   m_pConn;
	//pProc->m_pCmd->CommandType   =   adCmdStoredProc;
	//pProc->m_pCmd->CommandText = L"P_LOGIN";

	_ParameterPtr pParam = pProc->m_pCmd->CreateParameter(_bstr_t("v_empno"), adInteger, adParamInput ,4,7839L);
	pProc->m_pCmd ->Parameters ->Append(pParam);

	pParam = pProc->m_pCmd->CreateParameter(_bstr_t("v_pass"), adVarChar, adParamInput ,20, "123456");
	pProc->m_pCmd ->Parameters ->Append(pParam);

	pParam = pProc->m_pCmd->CreateParameter(_bstr_t("v_return"), adInteger, adParamReturnValue, 0);
	pProc->m_pCmd ->Parameters ->Append(pParam);

	pProc->m_pCmd->Execute(NULL, NULL, adCmdStoredProc);
	long nRet = pProc->m_pCmd->Parameters->GetItem("v_return")->GetValue();
	CString nRe = (LPCTSTR)(_bstr_t)(pProc->m_pCmd->Parameters->GetItem("v_pass")->GetValue());
	}
	catch(_com_error &e)
	{

	m_szLastError =(LPCTSTR) e.Description();
	return e.Error();
	}
	return 0;
}