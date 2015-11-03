#pragma once
#include <string>
using namespace std;

string HexToBin(string sHex)
{
	string sReturn = "";
	for (int i = 0; i < sHex.length(); ++i)
	{
		switch (sHex[i])
		{
		case '0': sReturn.append("0000"); break;
		case '1': sReturn.append("0001"); break;
		case '2': sReturn.append("0010"); break;
		case '3': sReturn.append("0011"); break;
		case '4': sReturn.append("0100"); break;
		case '5': sReturn.append("0101"); break;
		case '6': sReturn.append("0110"); break;
		case '7': sReturn.append("0111"); break;
		case '8': sReturn.append("1000"); break;
		case '9': sReturn.append("1001"); break;
		case 'A': sReturn.append("1010"); break;
		case 'B': sReturn.append("1011"); break;
		case 'C': sReturn.append("1100"); break;
		case 'D': sReturn.append("1101"); break;
		case 'E': sReturn.append("1110"); break;
		case 'F': sReturn.append("1111"); break;
		}
	}
	return sReturn;
}