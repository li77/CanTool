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
	char getDlc();
	string getData();
	void setAddress(string);
	string getAddress();
	void loadDB(string);
	void save();

private:
	string m_message;
	int m_id;
	char m_dlc;
	int m_dlc_i;
	char m_data[64];
	char m_dataShow[20];
	char m_nodeName[32];
	char m_messageName[32];
	string m_address;
		
	int getInt(string);//字符串中16进制数转10进制int	
	void HexToBin(string);//16进制字符串转2进制
	string signalAnalyze(int, int, int, string);
	void signalSynthesis(int, int, int, string, int);
	void searchById(); //通过id在链表中查找，并存储数据
	string BinToHex();
	string IToHex(int, int);
	int BinToD(string);
};

extern CANToolMessage cantool;