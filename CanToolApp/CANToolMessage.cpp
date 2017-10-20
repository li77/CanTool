#include "CANToolMessage.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <streambuf>
#include <regex>
#include <sstream>
#include "CanTool_LinkList.h"

using namespace std;

MessageLinkList linkList;
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
	string s_id;
	string s_dlc;
	string s_data;
	m_message = _message;
	if (m_message[0] == 'T')
	{
		s_id = m_message.substr(1, 8);
		stringstream ss;
		ss << s_id;
		ss >> m_id;
		s_dlc = m_message[9];
		ss << s_dlc;
		ss >> m_dlc;

		s_data = m_message.substr(10, m_dlc * 2);

		m_data_bin = HexToBin(s_data);
		/*if (canmsg.find(m_id) != canmsg.end())
		{
		for (int i = 0; i <= canmsg[m_id].size(); i++)
		{
		int start;
		stringstream ss;
		ss << canmsg[m_id][i].start;
		ss >> start;//��ʼλ���
		int length;//DATA����
		ss << canmsg[m_id][i].length;
		ss >> length;
		string format = canmsg[m_id][i].format;//0+��motorala��ʽ 1+��intel��ʽ
		//cout << signalAnalyze(start, length, format, m_data_bin) << endl;
		}
		}*/
		//����search(m_id)��ȡָ�룻
		int data;

		ss << m_data_bin;
		ss >> data;
		pm = linkList.Search(m_id);
		//������id�����insertMessage(id,dlc,data)�洢Message�ڵ㣻
		if (pm == nullptr)
		{
			//linkList.CreatMessageNode();
			linkList.InsertMessageNode(m_id, m_dlc, data);
		}
		//���������updateMessage()�洢data��
		else
		{
			linkList.UpdateMessageNode(data, pm);
		}
		//�õ�signal��ʼλ�����Ⱥ͸�ʽ��
		int start = pm->pSignalNode->startBit;
		int length = pm->pSignalNode->bitNum;
		string format;//0+��motorala��ʽ 1+��intel��ʽ
					  //����
		char * value = signalAnalyze(start, length, format, m_data_bin);
		//����updateSignal()�洢value��

	}
	else if (m_message[0] == 't')
	{
		stringstream ss;
		s_id = m_message.substr(1, 3);
		ss << s_id;
		ss >> m_id;
		s_dlc = m_message[4];
		ss << s_dlc;
		ss >> m_dlc;

		s_data = m_message.substr(10, m_dlc * 2);

		m_data_bin = HexToBin(s_data);

		/*if (canmsg.find(m_id) != canmsg.end())
		{
		for (int i = 0; i <= canmsg[m_id].size(); i++)
		{
		int start;
		stringstream ss;
		ss << canmsg[m_id][i].start;
		ss >> start;//��ʼλ���
		int length;//DATA����
		ss << canmsg[m_id][i].length;
		ss >> length;
		string format = canmsg[m_id][i].format;//0+��motorala��ʽ 1+��intel��ʽ
		//cout << signalAnalyze(start, length, format, m_data_bin) << endl;
		}
		}*/
	}
}

string CANToolMessage::synthesis(string _str)
{
	//�����ַ������id��signalName��value��
	int id = 0;
	string signalName;
	int value = 0;
	//����search(id)�ҵ�MessageNode��ͨ��signalName�ҵ���Ӧ��Signal���õ�start��length��format
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
		//cout << "file is open" << endl;
		string s;
		//vector<CANSignal> signals;
		int id;
		int dlc;
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
				ss << m[4];
				ss >> dlc;
				//����insertMessage(id,dlc,null);				
				linkList.InsertMessageNode(id, dlc, NAN);
				ps = nullptr;
				cout << id << endl;
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
				//����insertSignal();
				//if (ps = nullptr)
				//{
				//linkList.CreatSignalNode();
				//}

				linkList.InsertSignalNode(signalName, A, B, maxValue, minValue, unit, nodeName, start, length, format);
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
				//cout << A << endl;
				cout << signalName << " " << start << " " << length << " " << format << " " << A << " " << B << " " << minValue << " " << maxValue << " " << unit << " " << nodeName << endl;
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

/*int CANToolMessage::getInt(string str)
{
const char *p = str.c_str();
char *c_str;
int num = (int)strtol(p, &c_str, 16);
return num;
}*/

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
	//��Ӧλ��
	int byte = start / 8;
	int bit = start % 8;
	//motorola��ʽ
	if (format.compare("0+") == 0)
	{
		for (int i = 0; i < length; i++)
		{
			//��Ӧ����
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
			//cout << bit << " " << byte << endl;
		}
	}
	//intel��ʽ
	else if (format.compare("1+") == 0)
	{
		for (int i = 0; i < length; i++)
		{
			//��Ӧ����
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
			//cout << bit << " " << byte << endl;
		}
	}
	else
	{

	}
	//_itoa(num, number,);
	return number;
}

//ͨ��start��length,format�Լ������Ƶ�value�õ���Ӧ��m_data_bin
void CANToolMessage::signalSynthesis(int start, int length, string format, char* value)
{
	int byte = start / 8;
	int bit = start % 8;
	//motorola��ʽ
	if (format.compare("0+") == 0)
	{
		for (int i = 0; i < length; i++)
		{
			//��Ӧ����
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
			//cout << bit << " " << byte << endl;
		}
	}
	//intel��ʽ
	else if (format.compare("1+") == 0)
	{
		for (int i = 0; i < length; i++)
		{
			//��Ӧ����
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
			//cout << bit << " " << byte << endl;
		}
	}
	else
	{

	}
}
