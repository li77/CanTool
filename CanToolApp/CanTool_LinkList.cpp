#include <iostream>
#include "stdafx.h"
#include "CanTool_LinkList.h"
using namespace std;

/*****************************************************

函数名：InsertMessageNode 信息节点插入函数
功能：尾插法插入信息节点

*****************************************************/

void MessageLinkList::InsertMessageNode(uint32 _id, uchar _dlc, uint64_t _data)
{
	MessageNode* p = mHead;
	while (p->nextMessageNode == NULL)          //遍历查看是否有相同id，有则删除
	{
		if (p->nextMessageNode->id == l->id)
			p->nextMessageNode = p->nextMessageNode->nextMessageNode;
		p = p->nextMessageNode;
	}
	l->nextMessageNode = p->nextMessageNode;     //尾插新节点
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
			cout << "错误！未找到此id！";
			return nullptr;
		}
		p = p->nextMessageNode;
	}
}

/*****************************************************

函数名：UpdateMessageNode 更新信息节点函数
功能：更新指定信息节点数据

*****************************************************/

void MessageLinkList::UpdateMessageNode(uint64_t _data, PMessageNode pm)
{
	if (pm == nullptr)
		cout << "Error！" << endl;
	else
	{
		pm->data = _data;
		cout << "更新完成！" << endl;
	}
}

/*****************************************************

函数名：UpdateSignalNode 更新信号节点函数
功能：更新指定信号节点数据

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
				cout << "更新完成！" << endl;
			}
			ps = ps->nextSignalNode;
		}
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