#include <iostream>
#include "stdafx.h"
#include "CanTool_LinkList.h"
using namespace std;

MessageLinkList::MessageLinkList()
{
	mHead = new MessageNode;
	mUpdate = NULL;
	pm = NULL;
	ps = NULL;
}

MessageLinkList::~MessageLinkList()
{
	DeleteAll();
}

/*****************************************************

��������InsertMessageNode ��Ϣ�ڵ���뺯��
���ܣ�β�巨������Ϣ�ڵ�

*****************************************************/

void MessageLinkList::InsertMessageNode(uint32 _id, uchar _dlc, uint64_t _data)
{
	pm = new MessageNode;
	pm->id = _id;
	pm->DLC = _dlc;
	pm->data = _data;
	pm->nextMessageNode = nullptr;
	pm->pSignalNode = nullptr;
	if (pm != nullptr)
	{
		if (mHead->nextMessageNode == NULL)
			mHead->nextMessageNode = pm;
		else
		{
			PMessageNode p = mHead;
			while (p->nextMessageNode != NULL)
				p = p->nextMessageNode;
			pm->nextMessageNode = p->nextMessageNode;     //β���½ڵ�
			p->nextMessageNode = pm;
		}
		mUpdate = pm;               //���µĽڵ�
	}
	else
		return;
}

/*****************************************************

��������InsertSignalNode �źŽڵ���뺯��
���ܣ�β�巨�����źŽڵ�

*****************************************************/

void MessageLinkList::InsertSignalNode(char _signalName[32], float _phy_A, float _phy_B, float _maxValue, float _minValue, char _units[32], char _nodeName[255], uint64_t _startBit, uint64_t _bitNum, char _endian[2])
{
	ps = new SignalNode;
	strcpy_s(ps->SignalName, _signalName);
	ps->phy_A = _phy_A;
	ps->phy_B = _phy_A;
	ps->maxValue = _maxValue;
	ps->minValue = _minValue;
	strcpy_s(ps->units, _units);
	strcpy_s(ps->NodeName, _nodeName);
	ps->startBit = _startBit;
	ps->bitNum = _bitNum;
	strcpy_s(ps->Endian, _endian);
	ps->nextSignalNode = nullptr;
	if (pm != nullptr && ps != nullptr)
	{
		if (pm->pSignalNode == nullptr)
			pm->pSignalNode = ps;
		else
		{
			PSignalNode p = pm->pSignalNode;
			while (p->nextSignalNode != NULL)
				p = p->nextSignalNode;
			ps->nextSignalNode = p->nextSignalNode;
			p->nextSignalNode = ps;
		}
	}
	else
		return;
}

/*****************************************************

��������Traversal ��������
���ܣ��������нڵ㲢����ڵ���Ϣ��������Ϣ�ڵ���źŽڵ�

*****************************************************/

void MessageLinkList::Traversal()
{
	PMessageNode head = mHead;
	PMessageNode p = head->nextMessageNode;
	while (p != NULL)                                             //����Message�ڵ�
	{
		PSignalNode ps = p->pSignalNode;
		while (ps != NULL)                                        //����Signal�ڵ�
		{
			ps = ps->nextSignalNode;
		}
		p = p->nextMessageNode;
	}
}

/*****************************************************

��������Search ���Һ���
���ܣ�����ָ��id�Ľڵ����ݲ����

*****************************************************/
PMessageNode MessageLinkList::Search(uint32 _id)
{
	PMessageNode p = mHead->nextMessageNode;
	while (p != NULL)
	{
		if (p->id == _id)
			return p;
		p = p->nextMessageNode;
	}
	return nullptr;
}

/*****************************************************

��������UpdateMessageNode ������Ϣ�ڵ㺯��
���ܣ�����ָ����Ϣ�ڵ�����

*****************************************************/

void MessageLinkList::UpdateMessageNode(uint64_t _data, PMessageNode pm)
{
	if (pm == nullptr)
		return;
	else
	{
		pm->data = _data;
		mUpdate = pm;                           //���µĽڵ�
	}
}

/*****************************************************

��������UpdateSignalNode �����źŽڵ㺯��
���ܣ�����ָ���źŽڵ�����

*****************************************************/

void MessageLinkList::UpdateSignalNode(char _signalName[32], float _value, PMessageNode pm)
{
	if (pm == nullptr)
		return;
	else
	{
		PSignalNode ps = pm->pSignalNode;
		while (ps != nullptr)
		{
			if (strcmp(ps->SignalName, _signalName) == 0)
			{
				ps->value = _value;
			}
			ps = ps->nextSignalNode;
		}
	}
}

/*****************************************************

��������Delete ɾ������
���ܣ�ɾ�����нڵ�

*****************************************************/

void MessageLinkList::DeleteAll()
{
	PMessageNode pm = mHead;
	pm = pm->nextMessageNode;
	while (pm != NULL)
	{
		PMessageNode p = pm;
		DeleteSignalNode(pm);
		pm = pm->nextMessageNode;
		delete p;
	}
}

/*****************************************************

��������DeleteSignalNode ɾ���źŽڵ㺯��
���ܣ�ɾ����Ϣ�ڵ��������źŽڵ�

*****************************************************/

void MessageLinkList::DeleteSignalNode(PMessageNode pm)
{
	PSignalNode ps = pm->pSignalNode;
	while (ps != NULL)
	{
		PSignalNode p = ps;
		ps = ps->nextSignalNode;
		delete p;
	}
}

/******************************************************

��������Get_mHead ��ȡͷ��㺯��
���ܣ���ȡ����ͷ�ڵ�

*******************************************************/

PMessageNode MessageLinkList::Get_mHead()
{
	return mHead;
}

/******************************************************

��������Get_mUpdate ��ȡ���¸��½�㺯��
���ܣ���ȡ���������¸��µĽڵ�

*******************************************************/

PMessageNode MessageLinkList::Get_mUpdate()
{
	return mUpdate;
}