#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <streambuf>
#include <vector>
#include <regex>
using namespace std;

class CANMessage
{
public:
	void analyze()
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

			int start;//��ʼλ���
			int length;//DATA����
			string format;//0+��motorala��ʽ 1+��intel��ʽ


		}
		else if (m_message[0] == 't')
		{
			s_id = m_message.substr(1, 3);
			m_id = getInt(s_id);
			s_dlc = m_message[4];
			m_dlc = getInt(s_dlc);

			s_data = m_message.substr(10, m_dlc * 2);

			m_data_bin = HexToBin(s_data);

			int start;//��ʼλ���
			int length;//DATA����
			string format;//0+��motorala��ʽ 1+��intel��ʽ
		}
	}



	void setMessage(string message)
	{
		m_message = message;
	}

	string getMessage()
	{
		return m_message;
	}

	//void setId(int id) 
	//{
	//	m_id = id;
	//}

	int getId()
	{
		return m_id;
	}

	//void setDlc(int dlc) 
	//{
	//	m_dlc = dlc;
	//}

	int getDlc()
	{
		return m_dlc;
	}

	string getSData()
	{
		return m_data_bin;
	}

	//�������ݿ⣬���洢
	void loadDB(string filename)
	{
		ifstream file;
		file.open(filename);

		if (file.is_open())
		{
			cout << "file is open" << endl;
			string s;
			while (getline(file, s))
			{
				string id;
				string signal_name;
				string start;
				string length;
				string format;
				string offset;
				string scope;
				string unit;
				string node_name;
				if (s.substr(0, 3).compare("BO_") == 0)
				{
					regex reg("(\\w+)\\s+(\\d+)\\s+(\\w+):\\s+(\\d)\\s+(\\w+)");
					smatch m;
					regex_match(s, m, reg);
					id = m[2];
					//cout << id << endl;
				}
				else if (s.substr(0, 4).compare(" SG_") == 0)
				{
					regex reg("\\s+(\\w+)\\s+(\\w+)\\s+:\\s+(\\d+)\\|(\\d+)@([1|0][+|-])\\s+(\\S+)\\s+(\\S+)\\s+(.*)\\s+(.*)");
					smatch m;
					regex_match(s, m, reg);
					signal_name = m[2];
					start = m[3];
					length = m[4];
					format = m[5];
					offset = m[6];
					scope = m[7];
					unit = m[8];
					node_name = m[9];
					//cout << signal_name << " " << start << " " << length << " " << format << " " << offset << " " << scope << " " << unit << " " << node_name << endl;
				}
			}
		}
		else
		{
			cout << "can't open file" << endl;
		}

		file.close();
	}


private:
	string m_message;
	int m_id;
	int m_dlc;
	string m_data_bin;

	//�ַ�����16������ת10����int
	int getInt(string str)
	{
		const char *p = str.c_str();
		char *c_str;
		int num = (int)strtol(p, &c_str, 16);
		return num;
	}

	//16�����ַ���ת2����
	string HexToBin(const string strHex)
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

	//DATA�źŽ���
	int signalAnalyze(int start, int length, string format, string data_bin)
	{
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
			}
		}
		else
		{

		}
	}

};



int main()
{
	CANMessage canMessage;
	canMessage.setMessage("T1234567F81122334455667788\r");
	canMessage.analyze();
	int id = canMessage.getId();
	int dlc = canMessage.getDlc();
	string data = canMessage.getSData();
	cout << id << endl;
	cout << dlc << endl;
	cout << data << endl;
	canMessage.loadDB("D:\\canmsg-sample.txt");
	cin >> id;

	return 0;
}