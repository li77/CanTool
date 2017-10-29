#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <streambuf>
#include <vector>
#include <regex>
#include <unordered_map>
#include <sstream>
#include "CANToolMessage.h"
using namespace std;

int main()
{
	//cantool.loadDB("D://canmsg-sample.dbc");
    cantool.loadDB("D://Comfort.dbc");
	cantool.setAddress("D://data_received1.csv");
	cantool.analyze("t1F0163\r");
	//cantool.analyze("t320880478C2F05A1D29A\r");
	//cantool.analyze("t10080000000000000000\r");
	//cantool.analyze("t111800D9010000005300");
	//cantool.analyze("t32080027500000000000\r");
	//解析字符串获得id，signalName和value；
	//string _str = "id:888\r\ntime:5555\r\nhahaha:44\r\nhahahaha:44\r\n";
	//regex reg("\\w+:.*\\r\\n");
	//smatch m;
	//regex_match(_str, m, reg);
	//for (sregex_iterator it(_str.begin(), _str.end(), reg), end; it != end; it++)
	//{
	//	cout << it->str() << endl;

	//}
	string m = cantool.synthesis("ID : 496\r\nDLC : 1\r\ntime_interval : 0 ms[0, 65535]\r\nWN_Position : 99""取值范围[0, 100]\r\n");
	//string m1 = cantool.synthesis("ID : 1067\r\nDLC : 56\r\ntime_interval : 4  ms[0, 65535]\r\nCDU_NMDestAddress : 180 ""取值范围[0, 255]\r\nCDU_NMAlive : 0 ""取值范围[0, 1]\r\nCDU_NMRing : 0 ""取值范围[0, 1]\r\nCDU_NMLimpHome : 0 ""取值范围[0, 1]\r\nCDU_NMSleepInd : 0 ""取值范围[0, 1]\r\nCDU_NMSleepAck : 0 ""取值范围[0, 1]\r\nCDU_NMWakeupOrignin : 0 ""取值范围[0, 255]\r\nCDU_NMDataField : 0 ""取值范围[0, 1]");
	//string m2 = cantool.synthesis("ID : 856\r\nDLC : 8\r\ntime_interval : 4  ms[0, 65535]\r\nCDU_HVACOffButtonSt : 1 取值范围[0, 1]\r\nCDU_HVACOffButtonStVD : 0 取值范围[0, 1]\r\nCDU_HVACAutoModeButtonSt : 0 取值范围[0, 1]\r\nCDU_HVACAutoModeButtonStVD : 0 取值范围[0, 1]\r\nCDU_HVACFDefrostButtonSt : 0 取值范围[0, 1]\r\nCDU_HVACFDefrostButtonStVD : 0 取值范围[0, 1]\r\nCDU_HVACDualButtonSt : 0 取值范围[0, 1]\r\nCDU_HVACDualButtonStVD : 0 取值范围[0, 1]\r\nCDU_HVACIonButtonSt : 0 取值范围[0, 1]\r\nCDU_HVACIonButtonStVD : 0 取值范围[0, 1]\r\nCDU_HVACCirculationButtonSt : 1 取值范围[0, 1]\r\nCDU_HVACCirculationButtonStVD : 0 取值范围[0, 1]\r\nCDU_HVACACButtonSt : 0 取值范围[0, 1]\r\nCDU_HVACACButtonStVD : 0 取值范围[0, 1]\r\nCDU_HVACACMaxButtonSt : 0 取值范围[0, 1]\r\nCDU_HVACACMaxButtonStVD : 0 取值范围[0, 1]\r\nCDU_HVACModeButtonSt : 0 取值范围[0, 7]\r\nHVAC_WindExitSpd : 0 取值范围 [ 0, 15 ]\r\nCDU_HVAC_DriverTempSelect : 20.5 °C \"取值范围 [ 18, 32 ]\r\nHVAC_PsnTempSelect : 0 取值范围 [ 18, 32 ]\r\nCDU_HVACCtrlModeSt : 0 取值范围[0, 7]\r\nCDU_ControlSt : 0 取值范围[0, 1]");
	//string m2 = cantool.synthesis("ID : 800\r\nDLC : 8\r\ntime_interval : 4  ms[0, 65535]\r\nHVAC_PsnTempSelect : 0 取值范围 [ 18, 32 ]\r\nCDU_HVACCtrlModeSt : 0 取值范围[0, 7]\r\nCDU_ControlSt : 0 取值范围[0, 1]");
	/*string m = cantool.synthesis("ID : 800\r\n"
		"DLC : 8\r\n"
		"time_interval : 0  ms[0, 65535]\r\n"
		"HVAC_AirCompressorSt : 0 取值范围[0, 1]\r\n"
		"HVAC_CorrectedExterTempVD : 0 取值范围[0, 1]\r\n"
		"HVAC_RawExterTempVD : 0 取值范围[0, 1]\r\n"
		"HVAC_EngIdleStopProhibitReq : 0 取值范围[0, 1]\r\n"
		"HVAC_ACSt : 0 取值范围[0, 1]\r\n"
		"HVAC_ACmaxSt : 0 取值范围[0, 1]\r\n"
		"HVAC_CorrectedExterTemp : -20.5°C取值范围[-40, 87.5]\r\n"
		"HVAC_RawExterTemp : 0 °C取值范围[-40, 87.5]\r\n"
		"HVAC_TempSelect : 0 °C取值范围[18, 32]\r\n"
		"HVAC_DualSt : 0 取值范围[0, 1]\r\n"
		"HVAC_AutoSt : 0 取值范围[0, 1]\r\n"
		"HVAC_Type : 0 取值范围[0, 1]\r\n"
		"HVAC_WindExitMode : 0 取值范围[0, 7]\r\n"
		"HVAC_SpdFanReq : 0 取值范围[0, 1]\r\n"
		"HVAC_TelematicsSt : 0 取值范围[0, 7]\r\n"
		"HVAC_AirCirculationSt : 0 取值范围[0, 3]\r\n"
		"HVAC_PopUpDisplayReq : 0 取值范围[0, 1]\r\n"
		"HVAC_DriverTempSelect : 0 °C取值范围[18, 32]\r\n"
		"HVAC_IonMode : 0 取值范围[0, 3]\r\n"
		"HVAC_WindExitSpd : 0 取值范围[0, 15]\r\n"
		"HVAC_PsnTempSelect : 0 取值范围[18, 32]\r\n");*/
	return 0;
}
