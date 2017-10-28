#include "CANToolMessage.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
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
	m_id = NAN;
	m_dlc_i = NAN;
	memset(m_data, 0, sizeof(m_data) / sizeof(char));
	memset(m_dataShow, 0, sizeof(m_dataShow) / sizeof(char));
	memset(m_nodeName, 0, sizeof(m_nodeName) / sizeof(char));
	memset(m_messageName, 0, sizeof(m_messageName) / sizeof(char));
	if (m_message[0] == 'T')
	{
		m_id = getInt(m_message.substr(1, 8));

		ss << m_message[9];
		ss >> m_dlc_i;
		ss.str("");
		ss.clear();

		string data = m_message.substr(5, m_dlc_i * 2);
		ss << data;
		ss >> m_dataShow;
		ss.str("");
		ss.clear();
		HexToBin(data);

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
		ss >> m_dlc_i;
		ss.str("");
		ss.clear();

		string data = m_message.substr(5, m_dlc_i * 2);
		ss << data;
		ss >> m_dataShow;
		ss.str("");
		ss.clear();
		HexToBin(data);

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
	stringstream ss;
	int stringLength = 0;
	//解析字符串获得id，signalName和value；
	/*regex reg("\\w+:(\\d+)\\r\\n\\w+:(.*)\\r\\n((\\w+):(.*)\\r\\n){0,}");
	smatch m;
	regex_match(_str, m, reg);*/
	regex reg(".*\\s+:\\s+.*\\r\\n");
	m_message = "";
	m_id = NAN;
	m_dlc_i = NAN;
	memset(m_data, 0, sizeof(m_data) / sizeof(char));

	string kind;       //T  t
	string id;         //id
	string dlc;        //dlc
	string data;       //data
	string interval;    //时间间隔

	for (sregex_iterator it(_str.begin(), _str.end(), reg), end; it != end; it++)
	{
		string str = it->str();
		regex reg1("(\\w+)\\s+:\\s+(.*)\\r\\n");
		smatch m;
		regex_match(str, m, reg1);

		string str2 = m[2];
		regex reg2("(\\S+)\\s+.*");
		smatch m2;
		regex_match(str2, m2, reg2);
		if (m[1].compare("ID") == 0)
		{
			ss << m[2];
			ss >> m_id;
			ss.str("");
			ss.clear();
			if (m_id <= 2047)
			{
				stringLength += 3;
				kind = "t";
			}
			else
			{
				stringLength += 8;
				kind = "T";
			}
			id = IToHex(m_id, stringLength);
			stringLength += 2;
			pm = mList.Search(m_id);
			if (pm != nullptr)
			{
				ss << pm->DLC;
				ss >> m_dlc_i;
				ss.str("");
				ss.clear();
				ss << pm->DLC;
				ss >> dlc;
				ss.str("");
				ss.clear();
				strcpy_s(m_data, strlen(pm->data) + 1, pm->data);
				if (m_data[0] == '\0')
				{
					for (int i = 0; i < m_dlc_i * 8; i++)
					{
						m_data[i] = '0';
					}
				}
				stringLength += m_dlc_i * 2;
			}
		}
		else if (m[1].compare("time_interval") == 0)
		{
			stringLength += 4;
			int num = 0;
			ss << m2[1];
			ss >> num;
			ss.str("");
			ss.clear();
			interval = IToHex(num, 4);
		}
		else if (m[1].compare("DLC") == 0)
		{

		}
		else
		{

			//读取signal
			char signalName[32];
			ss << m[1];
			ss >> signalName;
			ss.str("");
			ss.clear();

			float value = 0;
			ss << m2[1];
			ss >> value;
			ss.str("");
			ss.clear();
			//调用search(id)找到MessageNode，通过signalName找到相应的Signal，得到start，length和format
			int start = 0;
			int length = 0;
			float A = 0;
			float B = 0;
			float max = 0;
			float min = 0;
			string format;
			if (pm != nullptr)
			{
				ps = pm->pSignalNode;
				while (ps != nullptr)
				{
					if (strcmp(ps->SignalName, signalName) == 0)
					{
						start = ps->startBit;
						length = ps->bitNum;
						format = ps->Endian;
						A = ps->phy_A;
						B = ps->phy_B;
						max = ps->maxValue;
						min = ps->minValue;
						break;
					}
					ps = ps->nextSignalNode;
				}
			}
			if (value < min)
			{
				value = min;
			}
			else if (value > max)
			{
				value = max;
			}
			int x = 0;
			x = (value - B) / A;
			signalSynthesis(start, length, m_dlc_i, format, x);
		}
	}

	data = BinToHex();
	stringLength += 2;
	m_message.resize(stringLength);
	string end = "\r";
	m_message = kind + id + dlc + data + interval + end;
	return m_message;
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

char CANToolMessage::getDlc()
{
	return m_dlc;
}

string CANToolMessage::getData()
{
	return m_data;
}

void CANToolMessage::setAddress(string _address)
{
	m_address = _address;
	fstream file;
	file.open(m_address, ios::in);
	if (!file)
	{
		ofstream outfile(m_address, ios::app);
		outfile << "id,MessageName,data,date,SignalName,value" << endl;
		outfile.close();
	}
	file.close();

}

string CANToolMessage::getAddress()
{
	return m_address;
}

void CANToolMessage::loadDB(string filename)
{
	ifstream file;
	file.open(filename);

	if (file.is_open())
	{
		string s;
		//vector<CANSignal> signals;
		while (getline(file, s))
		{
			if (s.substr(0, 3).compare("BO_") == 0)
			{
				regex reg("(\\w+)\\s+(\\d+)\\s+(\\w+):\\s+(\\d)\\s+(\\w+)");
				smatch m;
				regex_match(s, m, reg);
				stringstream ss;
				ss << m[2];
				ss >> m_id;
				ss.str("");
				ss.clear();
				ss << m[3];
				ss >> m_messageName;
				ss.str("");
				ss.clear();
				ss << m[4];
				ss >> m_dlc;
				ss.str("");
				ss.clear();
				ss << m[5];
				ss >> m_nodeName;
				ss.str("");
				ss.clear();
				//调用insertMessage(id,dlc,nodeName,messageName,null);				
				mList.InsertMessageNode(m_id, m_dlc, m_nodeName, m_messageName, "", "");
				//ps = nullptr;
			}
			else if (s.substr(0, 4).compare(" SG_") == 0)
			{
				regex reg("\\s+(\\w+)\\s+(\\w+)\\s+:\\s+(\\d+)\\|(\\d+)@([1|0][+|-])\\s+(\\S+)\\s+(\\S+)\\s+\"(.*)\"\\s+(.*)");
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
				//string s_unit = m[8];
				//ss << s_unit.substr(1, s_unit.size() - 3);	
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

void CANToolMessage::HexToBin(const string strHex)
{
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
			m_data[i * 4 + j] = bin;
			i_hex /= 2;
		}

		/*for (int j = 0; j < 4; j++)
		{
		strBin[i * 4 + j] = bin[j];
		}*/

	}
}

string CANToolMessage::signalAnalyze(int start, int length, int dlc, string format)
{
	string number;
	number.resize(length);
	//对应位置
	int byte = start / 8;
	int bit = start % 8;
	//motorola格式
	if (format.compare("0+") == 0)
	{
		for (int i = 0; i <length; i++)
		{
			//对应数据
			number[i] = m_data[byte * 8 + 7 - bit];
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
		for (int i = length - 1 ; i >= 0; i--)
		{
			//对应数据
			//number[i] = m_data[(dlc - byte - 1) * 8 + 7 - bit];
			number[i] = m_data[byte*8 - bit + 7];
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
void CANToolMessage::signalSynthesis(int _start, int _length, int _dlc, string _format, int _value)
{
	string value;
	value.resize(_length);
	for (int i = _length - 1; i >= 0; i--)
	{
		value[i] = char(_value % 2 + '0');
		_value = _value / 2;
	}
	int byte = _start / 8;
	int bit = _start % 8;
	//motorola格式
	if (_format.compare("0+") == 0)
	{
		for (int i = 0; i < _length; i++)
		{
			//对应数据
			m_data[byte * 8 + 7 - bit] = value[i];
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
	else if (_format.compare("1+") == 0)
	{
		for (int i = _length - 1; i >= 0; i--)
		{
			//对应数据
			//m_data[(_dlc - byte - 1) * 8 + 7 - bit] = value[i];
			m_data[byte * 8 - bit + 7] = value[i];
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
		mList.InsertMessageNode(m_id, m_dlc, m_nodeName, m_messageName, m_data, m_dataShow);
		//pm = mList.Search(m_id);
		//pm->received++;
	}
	//存在则调用updateMessage()存储data；
	else
	{
		mList.UpdateMessageNode(m_data, m_dataShow, pm);
		pm->received++;
		
		//存储为csv文件
		if (!m_address.empty())
		{
			ofstream outfile(m_address, ios::app);
			//outfile << pm->CANmessage << " " << m_id << " " << pm->MessageName << ": " << m_dlc << " " << pm->NodeName << endl;
			outfile << m_id << "," << pm->MessageName << "," << m_dataShow << "," << pm->date << ",";

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
				string value = signalAnalyze(start, length, m_dlc_i, format);
				int x = BinToD(value);
				float i_value;
				/*float x;
				ss << value;
				ss >> x;
				ss.str("");
				ss.clear();*/
				i_value = A*x + B;
				cout << ps->SignalName << "  " << i_value << endl;
				//调用updateSignal()存储value；
				mList.UpdateSignalNode(i_value, ps);
				//存储为csv文件
				outfile << ps->SignalName << "," << i_value << " " << ps->units << endl;
				ps = ps->nextSignalNode;
			}
			outfile.close();
		}
		else 
		{
			ps = pm->pSignalNode;
			while (ps != nullptr)
			{
				int start = ps->startBit;
				int length = ps->bitNum;
				float A = ps->phy_A;
				float B = ps->phy_B;
				string format = ps->Endian;//0+：motorala格式 1+：intel格式
										   //解析
				string value = signalAnalyze(start, length, m_dlc_i, format);
				int x = BinToD(value);
				float i_value;
				/*float x;
				ss << value;
				ss >> x;
				ss.str("");
				ss.clear();*/
				i_value = A*x + B;
				cout << ps->SignalName << "  " << i_value << endl;
				//调用updateSignal()存储value；
				mList.UpdateSignalNode(i_value, ps);
				//存储为csv文件
				ps = ps->nextSignalNode;
			}
		}
	}
}

string CANToolMessage::BinToHex()
{
	string data;
	string str;
	str.resize(m_dlc_i * 8);
	str = m_data;
	data.resize(m_dlc_i * 2);

	for (int i = 0; i < m_dlc_i * 2; i++)
	{

		string s = str.substr(i * 4, 4);
		int i_data = (s[0] - '0') * 8 + (s[1] - '0') * 4 + (s[2] - '0') * 2 + (s[3] - '0');
		if (i_data < 10)
		{
			data[i] = char(i_data + 48);
		}
		else
		{
			data[i] = char(i_data + 55);
		}
	}
	return data;
}

string CANToolMessage::IToHex(int num, int length)
{
	string strHex;
	strHex.resize(length);
	int id = num;
	for (int i = length - 1; i >= 0; i--)
	{
		int in = id % 16;
		if (in < 10)
		{
			strHex[i] = char(in + 48);
		}
		else
		{
			strHex[i] = char(in + 55);
		}
		id /= 16;
	}

	return strHex;
}

int CANToolMessage::BinToD(string _num)
{
	int num = 0;
	int l = _num.size();
	for (int i = 0; i < l; i++)
	{
		num = (_num[i] - '0') + num * 2;
	}
	return num;
}

