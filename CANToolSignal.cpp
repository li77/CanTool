#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

class CANMessage
{  
public:
	void analyze() 
	{
		string s_id;
		string s_dlc;
		string s_data;
		//string s_data_bin;
		if (message[0] == 'T') 
		{
			s_id = message.substr(1, 8);
			id = getInt(s_id);
			s_dlc = message[9];
			dlc = getInt(s_dlc);
			
			s_data = message.substr(10, dlc*2);

			s_data_bin = HexToBin(s_data);

			int start;//起始位编号
			int length;//DATA长度
			string format;//0+：motorala格式 1+：intel格式

			
		}
		else if (message[0] == 't') 
		{
			s_id = message.substr(1, 3);
			id = getInt(s_id);
			s_dlc = message[4];
			dlc = getInt(s_dlc);

			s_data = message.substr(10, dlc * 2);

			s_data_bin = HexToBin(s_data);

			int start;//起始位编号
			int length;//DATA长度
			string format;//0+：motorala格式 1+：intel格式
		}
	}

	void setMessage(string _message) 
	{
		message = _message;
	}

	string getMessage() 
	{
		return message;
	}

	//void setId(int _id) 
	//{
	//	id = _id;
	//}

	int getId()
	{
		return id;
	}

	//void setDlc(int _dlc) 
	//{
	//	dlc = _dlc;
	//}

	int getDlc()
	{
		return dlc;
	}

	//void setData(int _data) 
	//{
	//	data = _data;
	//}

	int getData()
	{
		return data;
	}

	string getSData()
	{
		return s_data_bin;
	}

private:
	string message;
	int id;
	int dlc;
	int data;
	string s_data_bin;

	//字符串中16进制数转10进制int
	int getInt(string _str) 
	{
		const char *p = _str.c_str();
		char *str;
		int num = (int)strtol(p, &str, 16);
		return num;
	}

	//16进制字符串转2进制
	string HexToBin(const string &strHex)
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

	//DATA信号解析
	int signalAnalyze(int start, int length, string format, string s_data_bin)
	{
		char number[length] = new char;
		//对应位置
		int byte = start / 8;
		int bit = start % 8;
		//motorola格式
		if(strcmp(format, "0+") == 0)
		{
			for(int i = 0; i < length; i++)
			{				
				//对应数据
				number[i] = s_data_bin[byte * 8 + 7 - bit];
				if(bit != 0)
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
		else if (strcmp(format, "1+") == 0)
		{
			for (int i = 0; i < length; i++)
			{
				//对应数据
				number[i] = s_data_bin[(s_data_bin.size()/8 - byte) * 8 + 7 - bit];
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
	canMessage.analysis();
	int id = canMessage.getId();
	int dlc = canMessage.getDlc();
	string data = canMessage.getSData();
	cout << id << endl;
	cout << dlc << endl;
	cout << data << endl;
	cin >> id;

	return 0;
}