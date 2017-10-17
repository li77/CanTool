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
	void Insert(MessageNode*);           //插入
	//void Update(uint32);                 //更新
	PMessageNode Search(uint32);                 //查找
	void Delete(uint32);                 //删除
	void Traversal(MessageNode*);        //遍历

private:
	PMessageNode mHead;
	PMessageNode mUpdate;                //指向最近一次更新的节点
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