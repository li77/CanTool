//#ifndef   _CANTOOL_LINKLIST_H
//#define  _CANTOOL_LINKLIST_H
#pragma once



#include <iostream>
#include <string>

typedef unsigned int uint32;
typedef unsigned char uchar;



typedef struct SignalNode
{
	char CANSignal[32] = "SG_";
	char SignalName[32];
	float phy_A;
	float phy_B;
	float maxValue;
	float minValue;
	char units[32];
	char NodeName[255];
	char startBit;
	char endBit;
	char smallEndian;//1是小端（intel），0是大端
	float value;
	DATE date;
	int  msec;//每秒的毫秒
	SignalNode* nextSignalNode;
}*PSignalNode;

typedef struct MessageNode
{
	int received;   //0表示从未收到此数据,显示收到几个数据
	uint64_t data;
	char CANmessage[32] = "BO_";
	uint32 id;
	char MessageName[32];
	char Separater = ':';
	uchar DLC;
	char NodeName[32];
	MessageNode* nextMessageNode;
	PSignalNode pSignalNode;
}*PMessageNode;

class MessageLinkList
{
public:
	MessageLinkList();
	~MessageLinkList();
	void Insert(MessageNode*);           //插入
	void Update(uint32);                 //更新
	PMessageNode Search(uint32);         //查找
	void Delete(uint32);                 //删除
	void DeleteAll(void) ;
	void Traversal(MessageNode*);        //遍历

	PMessageNode mHead;
	PMessageNode mUpdate;                //指向最近一次更新的节点
};



extern  MessageLinkList  mList;
extern char isHaveDB;
//#endif // ! _CANTOOL_LINKLIST_H