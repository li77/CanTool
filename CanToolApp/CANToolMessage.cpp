#include "CANToolMessage.h"
#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include <regex>
#include <unordered_map>
#include <sstream>

using namespace std;


CANToolMessage::CANToolMessage()
{
}

CANToolMessage::~CANToolMessage()
{
}

void CANToolMessage::analyze()
{
	string s_id;
	string s_dlc;
	string s_data;
	if (m_message[0] == 'T')
	{
		s_id = m_message.substr(1, 8);
		m_id = getInt(s_id);
		s_dlc = m_message[9];
		m_dlc = getInt(s_dlc);

		s_data = m_message.substr(10, m_dlc * 2);

		m_data_bin = HexToBin(s_data);
		/*if (canmsg.find(m_id) != canmsg.end())
		{
			for (int i = 0; i <= canmsg[m_id].size(); i++)
			{
				int start;
				stringstream ss;
				ss << canmsg[m_id][i].start;
				ss >> start;//起始位编号
				int length;//DATA长度
				ss << canmsg[m_id][i].length;
				ss >> length;
				string format = canmsg[m_id][i].format;//0+：motorala格式 1+：intel格式
				//cout << signalAnalyze(start, length, format, m_data_bin) << endl;
			}
		}*/
		//调用search(m_id)获取指针；
		//不存在id则调用insertMessage(id,dlc,data)存储Message节点；
		//存在则调用updateMessage()存储data；
		//得到signal起始位，长度和格式；
		int start;
		int length;
		string format;//0+：motorala格式 1+：intel格式
		//解析
		char * value = signalAnalyze(int start, int length, string format, string m_data_bin);
		//调用updateSignal()存储value；

	}
	else if (m_message[0] == 't')
	{
		s_id = m_message.substr(1, 3);
		m_id = getInt(s_id);
		s_dlc = m_message[4];
		m_dlc = getInt(s_dlc);

		s_data = m_message.substr(10, m_dlc * 2);

		m_data_bin = HexToBin(s_data);

		/*if (canmsg.find(m_id) != canmsg.end())
		{
			for (int i = 0; i <= canmsg[m_id].size(); i++)
			{
				int start;
				stringstream ss;
				ss << canmsg[m_id][i].start;
				ss >> start;//起始位编号
				int length;//DATA长度
				ss << canmsg[m_id][i].length;
				ss >> length;
				string format = canmsg[m_id][i].format;//0+：motorala格式 1+：intel格式
				//cout << signalAnalyze(start, length, format, m_data_bin) << endl;
			}
		}*/
	}
}

void CANToolMessage::synthesis(string _str)
{

}

void CANToolMessage::setMessage(string message)
{
	m_message = message;
}

string CANToolMessage::getMessage()
{
	return m_message;
}

int CANToolMessage::getId()
{
	return m_id;
}

int CANToolMessage::getDlc()
{
	return m_dlc;
}

string CANToolMessage::getSData()
{
	return m_data_bin;
}

void CANToolMessage::loadDB(string filename)
{
	ifstream file;
	file.open(filename);

	if (file.is_open())
	{
		//cout << "file is open" << endl;
		string s;
		//vector<CANSignal> signals;
		int id;
		int dlc;
		while (getline(file, s))
		{
			if (s.substr(0, 3).compare("BO_") == 0)
			{
				signals.clear();
				regex reg("(\\w+)\\s+(\\d+)\\s+(\\w+):\\s+(\\d)\\s+(\\w+)");
				smatch m;
				regex_match(s, m, reg);
				stringstream ss;
				ss << m[2];
				ss >> id;
				ss << m[4];
				ss >> dlc;
				//调用insertMessage(id,dlc,null);
				//cout << id << endl;
			}
			else if (s.substr(0, 4).compare(" SG_") == 0)
			{
				regex reg("\\s+(\\w+)\\s+(\\w+)\\s+:\\s+(\\d+)\\|(\\d+)@([1|0][+|-])\\s+(\\S+)\\s+(\\S+)\\s+(.*)\\s+(.*)");
				smatch m;
				regex_match(s, m, reg);
				string signalName = m[2];
				string start = m[3];
				string length = m[4];
				string format = m[5];
				string offset = m[6];
				string scope = m[7];
				string unit = m[8];
				string nodeName = m[9];
				//调用insertSignal();
				/*struct CANSignal signal;
				signal.signalName = m[2];
				signal.start = m[3];
				signal.length = m[4];
				signal.format = m[5];
				signal.offset = m[6];
				signal.scope = m[7];
				signal.unit = m[8];
				signal.nodeName = m[9];
				signals.push_back(signal);*/
				//cout << signal_name << " " << start << " " << length << " " << format << " " << offset << " " << scope << " " << unit << " " << node_name << endl;
			}
		}
		//canmsg.insert(make_pair(id, signals));
	}
	else
	{
		cout << "can't open file" << endl;
	}

	file.close();
}

int CANToolMessage::getInt(string str)
{
	const char *p = str.c_str();
	char *c_str;
	int num = (int)strtol(p, &c_str, 16);
	return num;
}

string CANToolMessage::HexToBin(const string strHex)
{
	string strBin;
	strBin.resize(strHex.size() * 4);
	//cout << strBin.size() << endl;
	for (int i = 0; i < strHex.size(); i++)
	{
		char c_hex = strHex[i];
		int i_hex = 0;
		//char bin[4];
		if (c_hex >= '0' && c_hex <= '9')
		{
			i_hex = c_hex - '0';
		}
		else if (c_hex >= 'a' && c_hex <= 'f')
		{
			i_hex = c_hex - 'a' + 10;
		}
		else if (c_hex >= 'A' && c_hex <= 'F')
		{
			i_hex = c_hex - 'A' + 10;
		}

		//_itoa_s(i_hex, bin, 10, 2);

		for (int j = 3; j >= 0; j--)
		{
			char bin = '0' + i_hex % 2;
			strBin[i * 4 + j] = bin;
			i_hex /= 2;
		}

		/*for (int j = 0; j < 4; j++)
		{
		strBin[i * 4 + j] = bin[j];
		}*/

	}

	return strBin;
}

char * CANToolMessage::signalAnalyze(int start, int length, string format, string data_bin)
{
	int num;
	char* number = new char[64];
	//对应位置
	int byte = start / 8;
	int bit = start % 8;
	//motorola格式
	if (format.compare("0+") == 0)
	{
		for (int i = 0; i < length; i++)
		{
			//对应数据
			number[i] = data_bin[byte * 8 + 7 - bit];
			if (bit != 0)
			{
				bit = bit - 1;
			}
			else
			{
				byte = byte + 1;
				bit = 7;
			}
			cout << bit << " " << byte << endl;
		}
	}
	//intel格式
	else if (format.compare("1+") == 0)
	{
		for (int i = 0; i < length; i++)
		{
			//对应数据
			number[i] = data_bin[(data_bin.size() / 8 - byte) * 8 + 7 - bit];
			if (bit != 7)
			{
				bit = bit + 1;
			}
			else
			{
				byte = byte + 1;
				bit = 0;
			}
			cout << bit << " " << byte << endl;
		}
	}
	else
	{

	}
	//_itoa(num, number,);
	return number;
}

int CANToolMessage::signalSynthesis(int _id, string _signalName, int _value)
{
	int value = 0;

	return value;
}
