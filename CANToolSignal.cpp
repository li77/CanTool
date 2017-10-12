#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

class CANMessage
{  
public:
	void analysis() 
	{
		string s_id;
		string s_dlc;
		string s_data;
		if (message[0] == 'T') 
		{
			s_id = message.substr(1, 8);
			id = getInt(s_id);
			s_dlc = message[9];
			dlc = getInt(s_dlc);
			
			s_data = message.substr(10, dlc*2);

			data = getInt(s_data);
		}
		else if (message[0] == 't') 
		{
			s_id = message.substr(1, 3);
			id = getInt(s_id);
			s_dlc = message[4];
			dlc = getInt(s_dlc);

			s_data = message.substr(10, dlc * 2);

			data = getInt(s_data);
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

	void setId(int _id) 
	{
		id = _id;
	}

	int getId()
	{
		return id;
	}

	void setDlc(int _dlc) 
	{
		dlc = _dlc;
	}

	int getDlc()
	{
		return dlc;
	}

	void setData(int _data) 
	{
		data = _data;
	}

	int getData()
	{
		return data;
	}

private:
	string message;
	int id;
	int dlc;
	int data;

	//字符串中16进制数转10进制int
	int getInt(string _str) 
	{
		const char *p = _str.c_str();
		char *str;
		int num = (int)strtol(p, &str, 16);
		return num;
	}


};

int main()
{
	CANMessage canMessage;
	canMessage.setMessage("T1234567F81122334455667788\r");
	canMessage.analysis();
	int id = canMessage.getId();
	int dlc = canMessage.getDlc();
	int data = canMessage.getData();
	cout << id << endl;
	cout << dlc << endl;
	cout << data << endl;
	cin >> id;

	return 0;
}