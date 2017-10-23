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
	char Endian[2];     //1+��С�ˣ�intel����0+�Ǵ��
	float value;
	SignalNode* nextSignalNode;
}*PSignalNode;

typedef struct MessageNode
{
	char data[64];
	char CANmessage[32] = "BO_";
	uint32 id;
	char MessageName[32];
	char Separater = ':';
	uchar DLC;
	char NodeName[32];
	//DATE date;
	int  msec;       //ÿ��ĺ���
	int received;    //���մ���
	MessageNode* nextMessageNode;
	PSignalNode pSignalNode;
}*PMessageNode;

class MessageLinkList
{
public:
	MessageLinkList();
	~MessageLinkList();
	//PMessageNode CreatMessageNode();     //������Ϣ�ڵ�
	//PSignalNode CreatSignalNode();       //�����źŽڵ�
	void InsertMessageNode(uint32, uchar, char _data[64]);        //��ʼ����Ϣ�ڵ�
	void InsertSignalNode(char _signalName[32], float, float, float, float, char _units[32], char _nodeName[255], uint64_t, uint64_t, char _endian[2]); //��ʼ���źŽڵ�
	//void LinkMessage_Signal(PMessageNode, PSignalNode);                                  //������Ϣ�ڵ���źŽڵ�
	//void InsertSignalNode(PMessageNode, PSignalNode);                                    //�����źŽڵ�
	//void InsertMessageNode(PMessageNode);                                                //������Ϣ�ڵ�
	void UpdateMessageNode(char _data[64], PMessageNode);                                //������Ϣ
	void UpdateSignalNode(char _signalName[32], float, PMessageNode);                    //�����ź�
	PMessageNode Search(uint32);                                                         //����
	void DeleteAll();                                                                    //ɾ��
	void Traversal();                                                                    //����
	PMessageNode Get_mHead();
	PMessageNode Get_mUpdate();

	PMessageNode mHead;
	PMessageNode mUpdate;                                                                //ָ�����һ�θ��µĽڵ�
private:
	PMessageNode pm;                                                                     //ָ����Ϣ�ڵ�
	PSignalNode ps;                                                                      //ָ���źŽڵ�
	void DeleteSignalNode(PMessageNode);                                                 //ɾ���źŽڵ�
};


extern char isHaveDB;
extern MessageLinkList  mList;
#endif