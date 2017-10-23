#include <iostream>
#include "stdafx.h"
#include "CanTool_LinkList.h"
using namespace std;

MessageLinkList::MessageLinkList()
{
	mHead = new MessageNode;
	mHead->nextMessageNode = NULL;
	mHead->pSignalNode = NULL;
	mUpdate = NULL;
	pm = NULL;
	ps = NULL;
}

MessageLinkList::~MessageLinkList()
{
	DeleteAll();
}

/*****************************************************

函数名：InsertMessageNode 信息节点插入函数
功能：尾插法插入信息节点

*****************************************************/

void MessageLinkList::InsertMessageNode(uint32 _id, uchar _dlc, char _data[64])
{
	pm = new MessageNode;
	pm->id = _id;
	pm->DLC = _dlc;
	strcpy_s(pm->data, strlen(_data) + 1, _data);
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
			pm->nextMessageNode = p->nextMessageNode;     //尾插新节点
			p->nextMessageNode = pm;
		}
		mUpdate = pm;               //最新的节点
	}
	else
		return;
}

/*****************************************************

函数名：InsertSignalNode 信号节点插入函数
功能：尾插法插入信号节点

*****************************************************/

void MessageLinkList::InsertSignalNode(char _signalName[32], float _phy_A, float _phy_B, float _maxValue, float _minValue, char _units[32], char _nodeName[255], uint64_t _startBit, uint64_t _bitNum, char _endian[2])
{
	ps = new SignalNode;
	strcpy_s(ps->SignalName, strlen(_signalName)+1, _signalName);
	ps->phy_A = _phy_A;
	ps->phy_B = _phy_A;
	ps->maxValue = _maxValue;
	ps->minValue = _minValue;
	strcpy_s(ps->units, strlen(_units) + 1, _units);
	strcpy_s(ps->NodeName, strlen(_nodeName) + 1, _nodeName);
	ps->startBit = _startBit;
	ps->bitNum = _bitNum;
	strcpy_s(ps->Endian, strlen(_endian) + 1, _endian);
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

函数名：Traversal 遍历函数
功能：遍历所有节点并输出节点信息，包括信息节点和信号节点

*****************************************************/

void MessageLinkList::Traversal()
{
	PMessageNode head = mHead;
	PMessageNode p = head->nextMessageNode;
	while (p != NULL)                                             //遍历Message节点
	{
		PSignalNode ps = p->pSignalNode;
		while (ps != NULL)                                        //遍历Signal节点
		{
			ps = ps->nextSignalNode;
		}
		p = p->nextMessageNode;
	}
}

/*****************************************************

函数名：Search 查找函数
功能：查找指定id的节点数据并输出

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

函数名：UpdateMessageNode 更新信息节点函数
功能：更新指定信息节点数据

*****************************************************/

void MessageLinkList::UpdateMessageNode(char _data[64], PMessageNode pm)
{
	if (pm == nullptr)
		return;
	else
	{
		strcpy_s(pm->data, strlen(_data) + 1, _data);
		mUpdate = pm;                           //最新的节点
	}
}

/*****************************************************

函数名：UpdateSignalNode 更新信号节点函数
功能：更新指定信号节点数据

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

函数名：Delete 删除函数
功能：删除所有节点

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

函数名：DeleteSignalNode 删除信号节点函数
功能：删除信息节点后的所有信号节点

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

函数名：Get_mHead 获取头结点函数
功能：获取链表头节点

*******************************************************/

PMessageNode MessageLinkList::Get_mHead()
{
	return mHead;
}

/******************************************************

函数名：Get_mUpdate 获取最新更新结点函数
功能：获取链表中最新更新的节点

*******************************************************/

PMessageNode MessageLinkList::Get_mUpdate()
{
	return mUpdate;
}