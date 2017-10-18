#include <iostream>
#include "stdafx.h"
#include "CanTool_LinkList.h"
using namespace std;

/*****************************************************

��������InsertMessageNode ��Ϣ�ڵ���뺯��
���ܣ�β�巨������Ϣ�ڵ�

*****************************************************/

void MessageLinkList::InsertMessageNode(uint32 _id, uchar _dlc, uint64_t _data)
{
	MessageNode* p = mHead;
	while (p->nextMessageNode == NULL)          //�����鿴�Ƿ�����ͬid������ɾ��
	{
		if (p->nextMessageNode->id == l->id)
			p->nextMessageNode = p->nextMessageNode->nextMessageNode;
		p = p->nextMessageNode;
	}
	l->nextMessageNode = p->nextMessageNode;     //β���½ڵ�
	p->nextMessageNode = l;
}

/*****************************************************

��������Traversal ��������
���ܣ������ڵ㲢����ڵ���Ϣ

*****************************************************/

void MessageLinkList::Traversal(MessageNode* l)
{
	MessageNode* p = l->nextMessageNode;
	while (p != NULL)
	{
		cout << p->CANmessage << p->id << p->MessageName << p->Separater << p->DLC << p->NodeName;
		p = p->nextMessageNode;
	}
}

/*****************************************************

��������Search ���Һ���
���ܣ�����ָ��id�Ľڵ����ݲ����

*****************************************************/
PMessageNode MessageLinkList::Search(uint32 _id)
{
	MessageNode* p = mHead->nextMessageNode;
	while (p != NULL)
	{
		if (p->id == _id)
		{
			cout << p->CANmessage << p->id << p->MessageName << p->Separater << p->DLC << p->NodeName;
			return p;
		}
		else
		{
			cout << "����δ�ҵ���id��";
			return nullptr;
		}
		p = p->nextMessageNode;
	}
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
���ܣ�ɾ��ָ��id�Ľڵ�����

*****************************************************/

void MessageLinkList::Delete(uint32 _id)
{
	MessageNode*p = mHead;
	while (p->nextMessageNode != NULL)
	{
		if (p->nextMessageNode->id == _id)
			p->nextMessageNode = p->nextMessageNode->nextMessageNode;
		p = p->nextMessageNode;
	}
}