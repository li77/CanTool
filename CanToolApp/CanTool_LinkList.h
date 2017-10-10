#include <iostream>
using namespace std;

typedef struct MessageNode
{
	char CANmessage;
	unint id;
	char MessageName;
	unsigned char DLC;
	char NodeName;
}