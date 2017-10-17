#ifndef CANTOOL_LINKLIST_H
#define CANTOOL_LINKLIST_H
#include <iostream>
#include <string>

typedef unsigned int uint32;
typedef unsigned char uchar;

typedef struct MessageNode
{
	char CANmessage[32] = "BO_";
	uint32 id;
	char MessageName[32];
	char Separater = ':';
	uchar DLC;
	char NodeName[32];
	MessageNode* nextMessageNode;
}*PMessageNode;

class MessageLinkList
{
public:
	MessageLinkList();
	~MessageLinkList();
	void Insert(MessageNode*);           //����
	//void Update(uint32);                 //����
	PMessageNode Search(uint32);                 //����
	void Delete(uint32);                 //ɾ��
	void Traversal(MessageNode*);        //����

private:
	PMessageNode mHead;
	PMessageNode mUpdate;                //ָ�����һ�θ��µĽڵ�
};

MessageLinkList::MessageLinkList()
{
	mHead = NULL;
	mUpdate = NULL;
}

MessageLinkList::~MessageLinkList()
{
	

}

#endif