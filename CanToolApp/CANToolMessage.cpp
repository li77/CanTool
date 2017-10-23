#include "CANToolMessage.h"
#include <iostream>
#include "stdafx.h"
#include <string>
#include <fstream>
#include <streambuf>
#include <regex>
#include <sstream>
#include "CanTool_LinkList.h"

using namespace std;

CANToolMessage cantool;
PMessageNode pm;
PSignalNode ps;


CANToolMessage::CANToolMessage()
{
}

CANToolMessage::~CANToolMessage()
{
}

void CANToolMessage::analyze(string _message)
{
	stringstream ss;
	m_message = _message;
	if (m_message[0] == 'T')
	{
		m_id = getInt(m_message.substr(1, 8));

		cout << m_id << endl;
		ss.str("");
		ss.clear();

		ss << m_message[9];
		ss >> m_dlc;
		ss.str("");
		ss.clear();

		m_data_bin = HexToBin(m_message.substr(10, m_dlc * 2));
		ss << m_data_bin;
		ss >> m_data;
		ss.str("");
		ss.clear();

		searchById();

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
		}
		}*/
	}
	else if (m_message[0] == 't')
	{
		m_id = getInt(m_message.substr(1, 3));

		ss << m_message[4];
		ss >> m_dlc;
		ss.str("");
		ss.clear();

		m_data_bin = HexToBin(m_message.substr(5, m_dlc * 2));
		ss << m_data_bin;
		ss >> m_data;
		ss.str("");
		ss.clear();

		searchById();

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
		}
		}*/
	}
}

string CANToolMessage::synthesis(string _str)
{
	//解析字符串获得id，signalName和value；
	int id = 0;
	string signalName;
	int value = 0;
	//调用search(id)找到MessageNode，通过signalName找到相应的Signal，得到start，length和format
	int start;
	int length;
	string format;
	string data;
	return data;
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
		string s;
		//vector<CANSignal> signals;
		int id;
		char dlc;
		while (getline(file, s))
		{
			if (s.substr(0, 3).compare("BO_") == 0)
			{
				regex reg("(\\w+)\\s+(\\d+)\\s+(\\w+):\\s+(\\d)\\s+(\\w+)");
				smatch m;
				regex_match(s, m, reg);
				stringstream ss;
				ss << m[2];
				ss >> id;
				ss.str("");
				ss.clear();
				ss << m[4];
				ss >> dlc;
				ss.str("");
				ss.clear();
				//调用insertMessage(id,dlc,null);				
				mList.InsertMessageNode(id, dlc, "");
				//ps = nullptr;
			}
			else if (s.substr(0, 4).compare(" SG_") == 0)
			{
				regex reg("\\s+(\\w+)\\s+(\\w+)\\s+:\\s+(\\d+)\\|(\\d+)@([1|0][+|-])\\s+(\\S+)\\s+(\\S+)\\s+(.*)\\s+(.*)");
				smatch m;
				regex_match(s, m, reg);
				stringstream ss;
				char signalName[32];
				ss << m[2];
				ss >> signalName;
				ss.str("");
				ss.clear();
				int start;
				ss << m[3];
				ss >> start;
				ss.str("");
				ss.clear();
				int length;
				ss << m[4];
				ss >> length;
				ss.str("");
				ss.clear();
				char format[4];
				ss << m[5];
				ss >> format;
				ss.str("");
				ss.clear();
				string offset = m[6];
				int	index = offset.find(",");
				float A;
				float B;
				ss << offset.substr(1, index - 1);
				ss >> A;
				ss.str("");
				ss.clear();
				ss << offset.substr(index + 1, offset.size() - index - 2);
				ss >> B;
				ss.str("");
				ss.clear();
				string scope = m[7];
				float maxValue;
				float minValue;
				index = scope.find("|");
				ss << scope.substr(1, index - 1);
				ss >> minValue;
				ss.str("");
				ss.clear();
				ss << scope.substr(index + 1, scope.size() - index - 2);
				ss >> maxValue;
				ss.str("");
				ss.clear();
				char unit[32];
				ss << m[8];
				ss >> unit;
				ss.str("");
				ss.clear();
				char nodeName[255];
				ss << m[9];
				ss >> nodeName;
				ss.str("");
				ss.clear();

				//调用insertSignal();
				//if (ps = nullptr)
				//{
				//mList.CreatSignalNode();
				//}

				mList.InsertSignalNode(signalName, A, B, maxValue, minValue, unit, nodeName, start, length, format);
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
		}
	}
	else
	{

	}
	//_itoa(num, number,);
	return number;
}

//通过start，length,format以及二进制的value得到对应的m_data_bin
void CANToolMessage::signalSynthesis(int start, int length, string format, char* value)
{
	int byte = start / 8;
	int bit = start % 8;
	//motorola格式
	if (format.compare("0+") == 0)
	{
		for (int i = 0; i < length; i++)
		{
			//对应数据
			m_data_bin[byte * 8 + 7 - bit] = value[i];
			if (bit != 0)
			{
				bit = bit - 1;
			}
			else
			{
				byte = byte + 1;
				bit = 7;
			}
		}
	}
	//intel格式
	else if (format.compare("1+") == 0)
	{
		for (int i = 0; i < length; i++)
		{
			//对应数据
			m_data_bin[(m_data_bin.size() / 8 - byte) * 8 + 7 - bit] = value[i];
			if (bit != 7)
			{
				bit = bit + 1;
			}
			else
			{
				byte = byte + 1;
				bit = 0;
			}
		}
	}
	else
	{

	}
}

void CANToolMessage::searchById()
{
	stringstream ss;
	//调用search(m_id)获取指针；
	pm = mList.Search(m_id);
	//不存在id则调用insertMessage(id,dlc,data)存储Message节点；
	if (pm == nullptr)
	{
		//linkList.CreatMessageNode();
		mList.InsertMessageNode(m_id, m_dlc, m_data);

	}
	//存在则调用updateMessage()存储data；
	else
	{
		mList.UpdateMessageNode(m_data, pm);
		//得到signal起始位，长度和格式；
		ps = pm->pSignalNode;
		while (ps != nullptr)
		{
			int start = ps->startBit;
			int length = ps->bitNum;
			float A = ps->phy_A;
			float B = ps->phy_B;
			string format = ps->Endian;//0+：motorala格式 1+：intel格式
									   //解析
			char * value = signalAnalyze(start, length, format, m_data_bin);
			float i_value;
			float x;
			ss << value;
			ss >> x;
			ss.str("");
			ss.clear();
			i_value = A*x + B;
			//调用updateSignal()存储value；
			mList.UpdateSignalNode(ps->SignalName, i_value, pm);
			ps = ps->nextSignalNode;
		}

	}
}
