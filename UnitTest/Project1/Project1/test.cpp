#include <iostream>
#include "CanTool_LinkList.h"
using namespace std;
int main() {
	MessageLinkList mes;
	mes.InsertMessageNode(1, 1, "a", "a", "a", "a");
	mes.InsertSignalNode("a", 1, 2, 3, 4, "a", "b", 5, 6, "c");
	mes.Search(1);
	return 1;
}