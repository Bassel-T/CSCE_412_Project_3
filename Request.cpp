#include "Request.h"

CRequest::CRequest(int nTime)
{
	m_sInAddr = new sIPAddress();
	m_sOutAddr = new sIPAddress();

	m_nTimer = nTime;
	m_nStartTimer = nTime;
}

CRequest::~CRequest()
{
	// Cleanup
	m_sInAddr = nullptr;
	delete m_sInAddr;

	m_sOutAddr = nullptr;
	delete m_sOutAddr;
}

void CRequest::SetIP(sIPAddress* sUpdateAddress, unsigned char nFirstByte, unsigned char nSecondByte, unsigned char nThirdByte, unsigned char nFourthByte)
{
	// unsigned char -> 0 - 255
	// Assign to in or out based on pointer
	sUpdateAddress->m_nFirstByte = nFirstByte;
	sUpdateAddress->m_nSecondByte = nSecondByte;
	sUpdateAddress->m_nThirdByte = nThirdByte;
	sUpdateAddress->m_nFourthByte = nFourthByte;
}
