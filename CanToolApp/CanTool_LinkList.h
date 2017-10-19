#ifndef CANTOOL_LINKLIST_H
#define CANTOOL_LINKLIST_H
#include <iostream>
#include <string>

typedef unsigned int uint32;
typedef unsigned char uchar;

MessageLinkList  mList;
char isHaveDB;

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
	char Endian;//1是小端（intel），0是大端
	float value;
	DATE date;
	int  msec;//每秒的毫秒
	SignalNode* nextSignalNode;
}*PSignalNode;

typedef struct MessageNode
{
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
	PMessageNode CreatMessageNode();     //创建信息节点
	PSignalNode CreatSignalNode();       //创建信号节点
	void InitialMessageNode(PMessageNode, uint32, uchar, uint64_t);        //初始化信息节点
	void InitialSignalNode(PSignalNode, char _signalName[32], float, float, float, float, char _units[32], char _nodeName[255], char, char, char); //初始化信号节点
	void LinkMessage_Signal(PMessageNode, PSignalNode);                                  //连接信息节点和信号节点
	void InsertSignalNode(PMessageNode, PSignalNode);                                    //插入信号节点
	void InsertMessageNode(PMessageNode);                                                //插入信息节点
	void UpdateMessageNode(uint64_t, PMessageNode);                                      //更新信息
	void UpdateSignalNode(char _signalName[32], float, PMessageNode);                    //更新信号
	PMessageNode Search(uint32);                                                         //查找
	void DeleteAll();                                                                    //删除
	void Traversal();                                                                    //遍历
	PMessageNode Get_mHead();
	PMessageNode Get_mUpdate();
private:
	PMessageNode mHead;
	PMessageNode mUpdate;                                                                //指向最近一次更新的节点
	void DeleteSignalNode(PMessageNode);                                                 //删除信号节点
};

MessageLinkList::MessageLinkList()
{
	mHead = NULL;
	mUpdate = NULL;
}

MessageLinkList::~MessageLinkList()
{
	DeleteAll();
}

#endif