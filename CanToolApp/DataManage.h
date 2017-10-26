#pragma once
#include <iostream>
#include"stdafx.h"
//using namespace std;
using std::string;
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

class DataManage
{
public:
	//unordered_map<int, vector<CANSignal>> canmsg;
	DataManage();
	~DataManage();
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
	char m_data[64];
	string m_data_bin;

	int getInt(string);//�ַ�����16������ת10����int	
	string HexToBin(const string);//16�����ַ���ת2����
	char* signalAnalyze(int, int, string);
	void signalSynthesis(int, int, string, int);
	void searchById(); //ͨ��id�������в��ң����洢����
};

extern DataManage dataManage;