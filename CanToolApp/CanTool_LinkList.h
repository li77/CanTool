#ifndef CANTOOL_LINKLIST_H
#define CANTOOL_LINKLIST_H
#include <iostream>
#include <string>

typedef unsigned int uint32;
typedef unsigned char uchar;

struct MessageNode
{
	char CANmessage = 'BO_';
	uint32 id;
	char MessageName;
	char Separater = ':';
	uchar DLC;
	char NodeName;
	MessageNode* nextMessageNode;
};

class MessageLinkList
{
public:
	MessageLinkList();
	~MessageLinkList();
	void Insert(MessageNode*);           //����
	void Update(uint32);                 //����
	void Search(uint32);                 //����
	void Delete(uint32);                 //ɾ��
	void Traversal(MessageNode*);        //����

private:
	MessageNode* mHead;

};

MessageLinkList::MessageLinkList()
{
	mHead = NULL;
}

MessageLinkList::~MessageLinkList()
{
}

#endif