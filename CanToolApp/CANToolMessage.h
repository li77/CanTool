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
	void analyze(string);//�źŽ���
	string synthesis(string);//�źźϳ�
	void setMessage(string);//����Message�ַ���
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
		
	int getInt(string);//�ַ�����16������ת10����int	
	void HexToBin(string);//16�����ַ���ת2����
	string signalAnalyze(int, int, int, string);
	void signalSynthesis(int, int, int, string, int);
	void searchById(); //ͨ��id�������в��ң����洢����
	string BinToHex();
	string IToHex(int, int);
	int BinToD(string);
};

extern CANToolMessage cantool;