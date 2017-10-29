#ifndef CANTOOL_LINKLIST_H
#define CANTOOL_LINKLIST_H
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
	uint64_t startBit;
	uint64_t bitNum;
	char Endian[3];     //1+是小端（intel），0+是大端
	float value;
	SignalNode* nextSignalNode;
}*PSignalNode;

typedef struct MessageNode
{
	int received;
	char data[64];
	char dataShow[20];  //改
	char CANmessage[32] = "BO_";
	uint32 id;
	char MessageName[32];
	char Separater = ':';
	uchar DLC;
	//DATE date;
	int  msec;       //每秒的毫秒
	char NodeName[32];
	MessageNode* nextMessageNode;
	PSignalNode pSignalNode;
}*PMessageNode;

class MessageLinkList
{
public:
	MessageLinkList();
	~MessageLinkList();
	//PMessageNode CreatMessageNode();     //创建信息节点
	//PSignalNode CreatSignalNode();       //创建信号节点
	void InsertMessageNode(uint32, uchar, char _nodeName[32], char _messageName[32], char _data[64], char _dataShow[20]);//改        //初始化信息节点
	void InsertSignalNode(char _signalName[32], float, float, float, float, char _units[32], char _nodeName[255], uint64_t, uint64_t, char _endian[2]); //初始化信号节点
																																						//void LinkMessage_Signal(PMessageNode, PSignalNode);                                  //连接信息节点和信号节点
																																						//void InsertSignalNode(PMessageNode, PSignalNode);                                    //插入信号节点
																																						//void InsertMessageNode(PMessageNode);                                                //插入信息节点
	void UpdateMessageNode(char _data[64], char _dataShow[20], PMessageNode pm);     //改                                 //更新信息
	void UpdateSignalNode(float, PSignalNode);                    //更新信号
	PMessageNode Search(uint32);                                                         //查找
	void DeleteAll();                                                                    //删除
	void Traversal();                                                                    //遍历
	PMessageNode Get_mHead();
	PMessageNode Get_mUpdate();

	PMessageNode mHead;
	PMessageNode mUpdate;                                                                //指向最近一次更新的节点
private:
	PMessageNode pm;                                                                     //指向信息节点
	PSignalNode ps;                                                                      //指向信号节点
	void DeleteSignalNode(PMessageNode);                                                 //删除信号节点
};


extern char isHaveDB;
extern MessageLinkList  mList;
#endif