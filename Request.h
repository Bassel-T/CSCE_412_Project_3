#include <string>
#include <iostream>
#include <sstream>

#pragma once

// If I want to print an IP Address


class CRequest {
public:
	struct sIPAddress {
		unsigned char m_nFirstByte, m_nSecondByte, m_nThirdByte, m_nFourthByte;

		// C++ not being happy about << or making a "ToString" function. Copy below
		//static_cast<int>(addr.m_nFirstByte) << "." << static_cast<int>(addr.m_nSecondByte) << "." << static_cast<int>(addr.m_nThirdByte) << "." << static_cast<int>(addr.m_nFourthByte)
	};

	CRequest(int nTime);
	~CRequest();

	void SetIP(sIPAddress* sUpdateAddress, unsigned char nFirstByte, unsigned char nSecondByte, unsigned char nThirdByte, unsigned char nFourthByte);
	
	void PrintInAddress() { std::cout << m_sInAddr; }
	void PrintOutAddress() { std::cout << m_sOutAddr; }

	void CycleTime() { m_nTimer--; }
	bool IsProcessed() { return m_nTimer == 0; }

	sIPAddress* GetInAddress() { return m_sInAddr; }
	sIPAddress* GetOutAddress() { return m_sOutAddr; }

	int GetStartTime() { return m_nStartTimer; }
private:
	// IP of the requester
	sIPAddress* m_sInAddr;

	// IP of the results
	sIPAddress* m_sOutAddr;

	// Time (integer)
	int m_nTimer;
	int m_nStartTimer;
};