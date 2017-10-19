#include <iostream>
#include "stdafx.h"
#include "CanTool_LinkList.h"
using namespace std;

/*****************************************************

��������CreatMessageNode ������Ϣ�ڵ㺯��
���ܣ�����һ���µ���Ϣ�ڵ�

*****************************************************/

PMessageNode MessageLinkList::CreatMessageNode()
{
	PMessageNode pm;
	pm = new MessageNode;
	return pm;
}

/*****************************************************

��������CreatSignalNode �����źŽڵ㺯��
���ܣ�����һ���µ��źŽڵ�

*****************************************************/

PSignalNode MessageLinkList::CreatSignalNode()
{
	PSignalNode ps;
	ps = new SignalNode;
	return ps;
}

/*****************************************************

��������InitialMessageNode ��ʼ����Ϣ�ڵ㺯��
���ܣ���ʼ����Ϣ�ڵ�

*****************************************************/

void MessageLinkList::InitialMessageNode(PMessageNode pm, uint32 _id, uchar _dlc, uint64_t _data)
{
	pm->id = _id;
	pm->DLC = _dlc;
	pm->data = _data;
	pm->nextMessageNode = nullptr;
	pm->pSignalNode = nullptr;
}

/*****************************************************

��������InitialSignalNode ��ʼ���źŽڵ㺯��
���ܣ���ʼ���źŽڵ�

*****************************************************/

void MessageLinkList::InitialSignalNode(PSignalNode ps, char _signalName[32], float _phy_A, float _phy_B, float _maxValue, float _minValue, char _units[32], char _nodeName[255], char _startBit, char _endBit, char _endian)
{
	strcpy_s(ps->SignalName, _signalName);
	ps->phy_A = _phy_A;
	ps->phy_B = _phy_A;
	ps->maxValue = _maxValue;
	ps->minValue = _minValue;
	strcpy_s(ps->units, _units);
	strcpy_s(ps->NodeName, _nodeName);
	ps->startBit = _startBit;
	ps->endBit = _endBit;
	ps->Endian = _endian;
	ps->nextSignalNode = nullptr;
}

/*****************************************************

��������LinkMessage_Signal ��Ϣ�ڵ������źŽڵ㺯��
���ܣ�����Ϣ�ڵ����źŽڵ���������

*****************************************************/

void MessageLinkList::LinkMessage_Signal(PMessageNode pm, PSignalNode ps)
{
	if (pm != nullptr && ps != nullptr)
		pm->pSignalNode = ps;
	else
		cout << "����ʧ�ܣ�" << endl;
}

/*****************************************************

��������InsertSignalNode �źŽڵ���뺯��
���ܣ�β�巨�����źŽڵ�

*****************************************************/

void MessageLinkList::InsertSignalNode(PMessageNode pm, PSignalNode ps)
{
	if (pm != nullptr && ps != nullptr)
	{
		PSignalNode p = pm->pSignalNode;
		while (p->nextSignalNode != NULL)
			p = p->nextSignalNode;
		ps->nextSignalNode = p->nextSignalNode;
		p->nextSignalNode = ps;
	}
	else
		cout << "�����źŽڵ�ʧ�ܣ�" << endl;
}

/*****************************************************

��������InsertMessageNode ��Ϣ�ڵ���뺯��
���ܣ�β�巨������Ϣ�ڵ�

*****************************************************/

void MessageLinkList::InsertMessageNode(PMessageNode pm)
{
	if (pm != nullptr)
	{
		PMessageNode head = mHead;
		PMessageNode p = head;
		if (head == NULL)
			head->nextMessageNode = pm;
		else
		{
			while (p->nextMessageNode != NULL)
				p = p->nextMessageNode;
			pm->nextMessageNode = p->nextMessageNode;     //β���½ڵ�
			p->nextMessageNode = pm;
		}
		mUpdate = pm;               //���µĽڵ�
	}
	else
		cout << "��Ϣ�ڵ����ʧ�ܣ�" << endl;
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
		cout << p->data << p->CANmessage << p->id << p->MessageName << p->Separater << p->DLC << p->NodeName << endl;
		PSignalNode ps = p->pSignalNode;
		while (ps != NULL)                                        //����Signal�ڵ�
		{
			cout << ps->CANSignal << ps->SignalName << ps->phy_A << ps->phy_B << ps->maxValue << ps->minValue << ps->units << ps->NodeName << ps->startBit << ps->endBit << ps->Endian << ps->value << ps->date << ps->msec << endl;
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
		{
			cout << p->CANmessage << p->id << p->MessageName << p->Separater << p->DLC << p->NodeName;
			return p;
		}
		p = p->nextMessageNode;
	}
	cout << "����δ�ҵ���id��";
	return nullptr;
}

/*****************************************************

��������UpdateMessageNode ������Ϣ�ڵ㺯��
���ܣ�����ָ����Ϣ�ڵ�����

*****************************************************/

void MessageLinkList::UpdateMessageNode(uint64_t _data, PMessageNode pm)
{
	if (pm == nullptr)
		cout << "Error��" << endl;
	else
	{
		pm->data = _data;
		mUpdate = pm;                           //���µĽڵ�
		cout << "������ɣ�" << endl;
	}
}

/*****************************************************

��������UpdateSignalNode �����źŽڵ㺯��
���ܣ�����ָ���źŽڵ�����

*****************************************************/

void MessageLinkList::UpdateSignalNode(char _signalName[32], float _value, PMessageNode pm)
{
	if (pm == nullptr)
		cout << "Error!" << endl;
	else
	{
		PSignalNode ps = pm->pSignalNode;
		while (ps != nullptr)
		{
			if (strcmp(ps->SignalName, _signalName) == 0)
			{
				ps->value = _value;
				cout << "������ɣ�" << endl;
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