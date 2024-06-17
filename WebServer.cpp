#include "WebServer.h"
#include "LoadBalancer.h"
#include <iostream>

CWebServer::CWebServer(CLoadBalancer* pParent, int nId)
{
	m_pParent = pParent;
	m_nId = nId;

	std::cout << "Creating new web server with ID: " << nId << std::endl;

	GetRequest();
}

CWebServer::~CWebServer()
{
	m_pParent = nullptr;
	delete m_pParent;
}

bool CWebServer::Process()
{
	if (m_pRequest == nullptr) {
		GetRequest();

		return false;
	}

	// Each cycle, remove one from the request
	m_pRequest->CycleTime();

	// Request is processed if its timer is 0
	bool bIsProcessed = m_pRequest->IsProcessed();

	if (bIsProcessed) {
		std::cout << "Server " << m_nId << " processed request with IP Address "
			<< static_cast<int>(m_pRequest->GetInAddress()->m_nFirstByte) << "." << static_cast<int>(m_pRequest->GetInAddress()->m_nSecondByte) << "."
			<< static_cast<int>(m_pRequest->GetInAddress()->m_nThirdByte) << "." << static_cast<int>(m_pRequest->GetInAddress()->m_nFourthByte)
			<< " after " << m_pRequest->GetStartTime() << " cycles. Sending results to "
			<< static_cast<int>(m_pRequest->GetOutAddress()->m_nFirstByte) << "." << static_cast<int>(m_pRequest->GetOutAddress()->m_nSecondByte) << "."
			<< static_cast<int>(m_pRequest->GetOutAddress()->m_nThirdByte) << "." << static_cast<int>(m_pRequest->GetOutAddress()->m_nFourthByte)
			<< std::endl;

		m_pRequest = nullptr;
		delete m_pRequest;
		
		GetRequest();
	}

	return bIsProcessed;
}

void CWebServer::GetRequest()
{
	// Receive a request from the load balancer
	m_pRequest = m_pParent->AssignRequest();
	
	if (m_pRequest != nullptr) {
		std::cout << "Server " << m_nId << " received request from "
			<< static_cast<int>(m_pRequest->GetInAddress()->m_nFirstByte) << "." << static_cast<int>(m_pRequest->GetInAddress()->m_nSecondByte) << "."
			<< static_cast<int>(m_pRequest->GetInAddress()->m_nThirdByte) << "." << static_cast<int>(m_pRequest->GetInAddress()->m_nFourthByte)
			<< std::endl;
	}

	// Track how many cycles passed since it's been used
	// Will use this to spin down if unused long enough
	if (m_pRequest == nullptr)
		m_nCyclesSinceUsed++;
	else
		m_nCyclesSinceUsed = 0;
}

bool CWebServer::ShouldSpinDownServer()
{
	return m_nCyclesSinceUsed >= m_nWebServerErasureThreshold;
}
