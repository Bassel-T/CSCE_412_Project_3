#include "Request.h"

#pragma once

class CLoadBalancer;

class CWebServer
{
public:
	CWebServer(CLoadBalancer* pParent, int nId);
	~CWebServer();

	// Process the requests
	// Returns true if we got a new process
	bool Process();

	// Asks for another
	void GetRequest();

	bool ShouldSpinDownServer();
	int GetId() { return m_nId; }
	bool HasActiveRequest() { return m_pRequest != nullptr; }

	// How long this has been unused
	int m_nCyclesSinceUsed;
private:
	// Universally identifiable
	int m_nId;

	// Takes requests from the Load Balancer
	CRequest* m_pRequest;
	CLoadBalancer* m_pParent;

	static const int m_nWebServerErasureThreshold = 30;

};