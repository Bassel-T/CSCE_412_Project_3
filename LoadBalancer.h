#include <queue>
#include "Request.h"
#include "WebServer.h"

#pragma once


class CLoadBalancer {
public:
	CLoadBalancer(int nWebServers, int nRuntime);
	~CLoadBalancer();

	// Keeps track of time
	void Cycle();

	// Simulate getting a new request
	CRequest* CreateRequest();

	// Pass request in to child
	CRequest* AssignRequest();

	void SetTimeRemaining(int nTimeRemaining) { m_nTimeRemaining = nTimeRemaining; }

	void Start();
private:
	// Manages the webservers and request queue.
	// This should all for the creation of multiple load balancers and not just part of your driver program.
	std::vector<CWebServer*> m_vecWebServers;

	// Queue of requests
	std::queue<CRequest*> m_vecRequests;

	// After this point, stop creating requests
	int m_nTimeRemaining;

	// Track the next server that we'll be creating
	int m_nNextServerId = 0;

	// Requests will have task times from 5 to 5 + m_nRequestSizeRange
	int m_nRequestSizeRange = 10;
};