#include"stdafx.h"
#include"CanTool_LinkList.h"
using namespace std;
char isHaveDB;
MessageLinkList  mList;
MessageLinkList::MessageLinkList()
{
	mHead = NULL;
	mUpdate = NULL;
}

MessageLinkList::~MessageLinkList()
{


}

PMessageNode MessageLinkList::Search(uint32)
{
	return PMessageNode();
}

void MessageLinkList::DeleteAll(void)
{
}
 