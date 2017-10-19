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
	char smallEndian;//1��С�ˣ�intel����0�Ǵ��
	float value;
	DATE date;
	int  msec;//ÿ��ĺ���
	SignalNode* nextSignalNode;
}*PSignalNode;

typedef struct MessageNode
{
	int received;   //0��ʾ��δ�յ�������,��ʾ�յ���������
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
	void Insert(MessageNode*);           //����
	void Update(uint32);                 //����
	PMessageNode Search(uint32);         //����
	void Delete(uint32);                 //ɾ��
	void DeleteAll(void) ;
	void Traversal(MessageNode*);        //����

	PMessageNode mHead;
	PMessageNode mUpdate;                //ָ�����һ�θ��µĽڵ�
};



extern  MessageLinkList  mList;
extern char isHaveDB;
//#endif // ! _CANTOOL_LINKLIST_H