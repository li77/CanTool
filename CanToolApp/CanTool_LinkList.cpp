#include <iostream>
#include "stdafx.h"
#include "CanTool_LinkList.h"
using namespace std;

/*****************************************************

函数名：CreatMessageNode 创建信息节点函数
功能：创建一个新的信息节点

*****************************************************/

PMessageNode MessageLinkList::CreatMessageNode()
{
	PMessageNode pm;
	pm = new MessageNode;
	return pm;
}

/*****************************************************

函数名：CreatSignalNode 创建信号节点函数
功能：创建一个新的信号节点

*****************************************************/

PSignalNode MessageLinkList::CreatSignalNode()
{
	PSignalNode ps;
	ps = new SignalNode;
	return ps;
}

/*****************************************************

函数名：InitialMessageNode 初始化信息节点函数
功能：初始化信息节点

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

函数名：InitialSignalNode 初始化信号节点函数
功能：初始化信号节点

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

函数名：LinkMessage_Signal 信息节点连接信号节点函数
功能：将信息节点与信号节点连接起来

*****************************************************/

void MessageLinkList::LinkMessage_Signal(PMessageNode pm, PSignalNode ps)
{
	if (pm != nullptr && ps != nullptr)
		pm->pSignalNode = ps;
	else
		cout << "连接失败！" << endl;
}

/*****************************************************

函数名：InsertSignalNode 信号节点插入函数
功能：尾插法插入信号节点

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
		cout << "插入信号节点失败！" << endl;
}

/*****************************************************

函数名：InsertMessageNode 信息节点插入函数
功能：尾插法插入信息节点

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
			pm->nextMessageNode = p->nextMessageNode;     //尾插新节点
			p->nextMessageNode = pm;
		}
		mUpdate = pm;               //最新的节点
	}
	else
		cout << "信息节点插入失败！" << endl;
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
		cout << p->data << p->CANmessage << p->id << p->MessageName << p->Separater << p->DLC << p->NodeName << endl;
		PSignalNode ps = p->pSignalNode;
		while (ps != NULL)                                        //遍历Signal节点
		{
			cout << ps->CANSignal << ps->SignalName << ps->phy_A << ps->phy_B << ps->maxValue << ps->minValue << ps->units << ps->NodeName << ps->startBit << ps->endBit << ps->Endian << ps->value << ps->date << ps->msec << endl;
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
		{
			cout << p->CANmessage << p->id << p->MessageName << p->Separater << p->DLC << p->NodeName;
			return p;
		}
		p = p->nextMessageNode;
	}
	cout << "错误！未找到此id！";
	return nullptr;
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
		mUpdate = pm;                           //最新的节点
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