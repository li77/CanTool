#ifndef CANTOOLMessage_H
#define CANTOOLMessage_H
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/*struct CANSignal
{
string signalName;
string start;
string length;
string format;
string offset;
string scope;
string unit;
string nodeName;
};*/

class CANToolMessage
{
public:
	//unordered_map<int, vector<CANSignal>> canmsg;
	CANToolMessage();
	~CANToolMessage();
	void analyze(string);//�źŽ���
	string synthesis(string);//�źźϳ�
	void setMessage(string);//����Message�ַ���
	string getMessage();
	int getId();
	int getDlc();
	string getSData();
	void loadDB(string);

private:
	string m_message;
	int m_id;
	int m_dlc;
	string m_data_bin;

	//�ַ�����16������ת10����int
	int getInt(string);
	//16�����ַ���ת2����
	string HexToBin(const string);
	char* signalAnalyze(int, int, string, string);
	void signalSynthesis(int, int, string, char*);
};

#endif