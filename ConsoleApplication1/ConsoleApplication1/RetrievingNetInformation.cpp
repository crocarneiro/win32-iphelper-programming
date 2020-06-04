// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include <WinSock2.h>
#include <iphlpapi.h>

int main()
{
	FIXED_INFO *fixedInfo = (FIXED_INFO*) malloc(sizeof(FIXED_INFO));
	IP_ADDR_STRING *ipAddrString;
	ULONG buffer = sizeof(FIXED_INFO);
	DWORD retVal;

	if (GetNetworkParams(fixedInfo, &buffer) == ERROR_BUFFER_OVERFLOW)
	{
		free(fixedInfo);
		fixedInfo = (FIXED_INFO*)malloc(buffer);
		if (fixedInfo == NULL)
		{
			puts("Error allocating memory needed to call GetNetworkParams.");
		}
	}

	if (retVal = GetNetworkParams(fixedInfo, &buffer) != NO_ERROR)
	{
		printf("GetNetworkParams failed with error %d.\n", retVal);
		if (fixedInfo)
			free(fixedInfo);
	}

	printf("Host Name: %s\n", fixedInfo->HostName);
	printf("Domain Name: %s\n", fixedInfo->DomainName);
	printf("DNS Servers:\n");
	printf("\t%s\n", fixedInfo->DnsServerList.IpAddress.String);

	ipAddrString = fixedInfo->DnsServerList.Next;
	while (ipAddrString)
	{
		printf("\t%s\n", ipAddrString->IpAddress.String);
		ipAddrString = ipAddrString->Next;
	}

	printf("Node Type:");
	switch (fixedInfo->NodeType)
	{
		case 1:
			printf("Broadcast\n");
			break;
		case 2:
			printf("Peer to peer\n");
			break;
		case 4:
			printf("Mixed\n");
			break;
		case 8:
			printf("Hybrid\n");
			break;
		default:
			printf("\n");
	}

	printf("NetBIOS Scope ID: %s\n", fixedInfo->ScopeId);

	if (fixedInfo->EnableRouting)
		printf("IP Routing Enabled: Yes\n");
	else
		printf("IP Routing Enabled: No\n");

	if (fixedInfo->EnableProxy)
		printf("WINS Proxy Enabled: Yes\n");
	else
		printf("WINS Proxy Enabled: No\n");

	if (fixedInfo->EnableDns)
		printf("NetBIOS Resolution Uses DNS: Yes\n");
	else
		printf("NetBIOS Resolution Uses DNS: Yes\n");

	if (fixedInfo)
	{
		free(fixedInfo);
		fixedInfo = NULL;
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
