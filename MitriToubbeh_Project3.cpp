// MitriToubbeh_Project3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "LoadBalancer.h"

int main()
{
    // Want to make sure it's not the same every time
    srand(time(NULL));

    std::cout << "How many web servers do you want to start with?" << std::endl;
    int nServerCount = 0;

    std::cin >> nServerCount;

    std::cout << "How long should this run for?" << std::endl;
    int nRuntime = 0;
    std::cin >> nRuntime;

    CLoadBalancer* pLoadBalancer = new CLoadBalancer(nServerCount, nRuntime);
    pLoadBalancer->Start();

    pLoadBalancer = nullptr;
    delete pLoadBalancer;
}