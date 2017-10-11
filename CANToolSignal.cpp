#include <iostream>
#include <string>
using namespace std;

class CANMessage()
{  
public£º
	void analysis() 
	{
		string s_id;
		string s_dlc;
		string s_data;
		if (message[0] == 'T') 
		{
			s_id = message.substr(1, 8);
			s_dlc = message[9];
		}
		else if (message[0] == 't') 
		{
			s_id = message.substr(1, 3);
			s_dlc = message[4];
		}
		else 
		{

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


}