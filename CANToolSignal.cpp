#include <iostream>
#include <string>
using namespace std;

class CANMessage()
{  
public£º
	void analysis() 
	{
		if (message[0] == 'T') {

		}
		else if (message[0] == 't') {

		}
		else {

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