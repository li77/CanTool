#ifndef CANTOOL_LINKLIST_H
#define CANTOOL_LINKLIST_H
#include <string>

typedef unsigned int uint32;
typedef unsigned char uchar;

//char isHaveDB;

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
	char Endian[2];     //1��С�ˣ�intel����0�Ǵ��
	float value;
	//DATE date;
	int  msec;       //ÿ��ĺ���
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
	//PMessageNode CreatMessageNode();     //������Ϣ�ڵ�
	//PSignalNode CreatSignalNode();       //�����źŽڵ�
	void InsertMessageNode(uint32, uchar, uint64_t);        //��ʼ����Ϣ�ڵ�
	void InsertSignalNode(char _signalName[32], float, float, float, float, char _units[32], char _nodeName[255], uint64_t, uint64_t, char _endian[2]); //��ʼ���źŽڵ�
																																						//void LinkMessage_Signal(PMessageNode, PSignalNode);                                  //������Ϣ�ڵ���źŽڵ�
																																						//void InsertSignalNode(PMessageNode, PSignalNode);                                    //�����źŽڵ�
																																						//void InsertMessageNode(PMessageNode);                                                //������Ϣ�ڵ�
	void UpdateMessageNode(uint64_t, PMessageNode);                                      //������Ϣ
	void UpdateSignalNode(char _signalName[32], float, PMessageNode);                    //�����ź�
	PMessageNode Search(uint32);                                                         //����
	void DeleteAll();                                                                    //ɾ��
	void Traversal();                                                                    //����
	PMessageNode Get_mHead();
	PMessageNode Get_mUpdate();
private:
	PMessageNode mHead;
	PMessageNode mUpdate;                                                                //ָ�����һ�θ��µĽڵ�
	PMessageNode pm;                                                                     //ָ����Ϣ�ڵ�
	PSignalNode ps;                                                                      //ָ���źŽڵ�
	void DeleteSignalNode(PMessageNode);                                                 //ɾ���źŽڵ�
};

#endif