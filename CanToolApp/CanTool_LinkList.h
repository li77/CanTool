#ifndef CANTOOL_LINKLIST_H
#define CANTOOL_LINKLIST_H
#include <iostream>
#include <string>
using namespace std;

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
	void Insert(MessageNode*);
	void Update(MessageNode*);
	void Search(MessageNode*);
	MessageNode* Delete(MessageNode*);
	void Traversal(MessageNode*);

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