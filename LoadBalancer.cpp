#include "LoadBalancer.h"

#define NEW_BYTE rand() % 255

CLoadBalancer::CLoadBalancer(int nWebServers, int nRuntime)
{
	for (int i = 0; i < nWebServers; i++) {
		for (int j = 0; j <= 100; j++) {
			// Generates full queue, "usually servers * 100"
			m_vecRequests.push(CreateRequest());
		}

		m_vecWebServers.push_back(new CWebServer(this, m_nNextServerId));

		// Make it easier to track our servers
		m_nNextServerId++;
	}

	m_nTimeRemaining = nRuntime;

	std::cout << "Created " << m_vecWebServers.size() << " web servers and " << m_vecRequests.size() << " requests." << std::endl << std::endl;
}

CLoadBalancer::~CLoadBalancer()
{
	for (int i = 0; i < m_vecWebServers.size(); i++) {
		m_vecWebServers[i] = nullptr;
		delete m_vecWebServers[i];
	}

	for (int j = 0; j < m_vecRequests.size(); j++) {
		m_vecRequests.front() = nullptr;
		delete m_vecRequests.front();
		m_vecRequests.pop();
	}
}

void CLoadBalancer::Cycle()
{
	// Simulate a cycle for each server
	m_nTimeRemaining--;
	bool bSpinUpNewServer = true;

	// Spin up a new process if one doesn't exist
	for (int i = 0; i < m_vecWebServers.size(); i++) {
		bSpinUpNewServer &= !m_vecWebServers[i]->Process();

		if (m_vecWebServers[i]->ShouldSpinDownServer()) {
			// Web server was not used in 30 cycles. Remove it
			std::cout << "Server " << m_vecWebServers[i]->GetId() << " has not been used recently. Spinning down that server." << std::endl;
			delete m_vecWebServers[i];
			m_vecWebServers.erase(m_vecWebServers.begin() + i);
			i--;
		}
	}

	if (bSpinUpNewServer && !m_vecRequests.empty()) {
		m_vecWebServers.push_back(new CWebServer(this, m_nNextServerId));
		m_nNextServerId++;
	}
}

CRequest* CLoadBalancer::CreateRequest() {
	
	// Set max processing time and create request
	// Requests have at least 5 moves: Read, Load, Process, Return
	int nNewTimer = rand() % m_nRequestSizeRange + 5;
	CRequest* pNewRequest = new CRequest(nNewTimer);

	// Set up the needed IP Addresses
	pNewRequest->SetIP(pNewRequest->GetInAddress(), NEW_BYTE, NEW_BYTE, NEW_BYTE, NEW_BYTE);
	pNewRequest->SetIP(pNewRequest->GetOutAddress(), NEW_BYTE, NEW_BYTE, NEW_BYTE, NEW_BYTE);

	return pNewRequest;
}

CRequest* CLoadBalancer::AssignRequest()
{
	if (m_vecRequests.empty())
		return nullptr;

	CRequest* pRequest = m_vecRequests.front();
	m_vecRequests.pop();
	return pRequest;
}

void CLoadBalancer::Start()
{
	while (m_nTimeRemaining > 0) {

		// Randomly create requests 1/3 of the time while there's still time in the simulation
		if (m_nTimeRemaining > 0 && rand() % 3 == 0)
			m_vecRequests.push(CreateRequest());

		Cycle();
	}

	// Debugging for log
	int nActiveRequests = 0;
	for (const auto& pWebServer : m_vecWebServers) {
		if (pWebServer->HasActiveRequest())
			nActiveRequests++;
	}

	std::cout << std::endl << "Simulation terminated with " << nActiveRequests << " requests currently being processed, " << m_vecRequests.size() << " requests in the queue, and " << m_vecWebServers.size() - nActiveRequests << " web servers waiting for requests." << std::endl << std::endl;
	std::cout << "Tasks had ranges from 5 to " << 5 + m_nRequestSizeRange << "." << std::endl;
}

