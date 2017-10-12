#include <iostream>
#include "stdafx.h"
#include "CanTool_LinkList.h"
using namespace std;

/*****************************************************

函数名：Insert 插入函数
功能：若为新数据则尾插入链表，否则删除原数据尾插新数据

*****************************************************/

void MessageLinkList::Insert(MessageNode* l)
{
	MessageNode* p = mHead;
	while (p->nextMessageNode == NULL)
	{
		if (p->nextMessageNode->id == l->id)
			p->nextMessageNode = p->nextMessageNode->nextMessageNode;
		p = p->nextMessageNode;
	}
	l->nextMessageNode = p->nextMessageNode;
	p->nextMessageNode = l;
}

/*****************************************************

函数名：Traversal 遍历函数
功能：遍历节点并输出节点信息

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

函数名：Search 查找函数
功能：查找指定id的节点数据并输出

*****************************************************/
void MessageLinkList::Search(uint32 _id)
{
	MessageNode* p = mHead->nextMessageNode;
	while (p != NULL)
	{
		if (p->id == _id)
			cout << p->CANmessage << p->id << p->MessageName << p->Separater << p->DLC << p->NodeName;
		p = p->nextMessageNode;
	}
}

/*****************************************************

函数名：Update 更新函数
功能：更新指定id的节点数据

*****************************************************/

void MessageLinkList::Update(uint32 _id)
{
	MessageNode*p = mHead->nextMessageNode;
	while (p != NULL)
	{
		if (p->id == _id)
			cin >> p->CANmessage >> p->MessageName >> p->Separater >> p->DLC >> p->NodeName;
		p = p->nextMessageNode;
	}
}

/*****************************************************

函数名：Delete 删除函数
功能：删除指定id的节点数据

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