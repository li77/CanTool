#pragma once
#include <iostream>

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
	void analyze(string);//信号解析
	string synthesis(string);//信号合成
	void setMessage(string);//传入Message字符串
	string getMessage();
	int getId();
	int getDlc();
	string getSData();
	void loadDB(string);

private:
	string m_message;
	int m_id;
	int m_dlc;
	char m_data[64];
	string m_data_bin;

	int getInt(string);//字符串中16进制数转10进制int	
	string HexToBin(const string);//16进制字符串转2进制
	char* signalAnalyze(int, int, string, string);
	void signalSynthesis(int, int, string, char*);
	void searchById(); //通过id在链表中查找，并存储数据
};

extern CANToolMessage cantool;