// ManagingNetworkAdapters.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include <stdio.h>
#include <stdlib.h>

#include <WinSock2.h>
#include <iphlpapi.h>

int main()
{
	IP_ADAPTER_INFO *pAdapterInfo;
	ULONG ulOutBufLen;
	DWORD dwRetVal;

	pAdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));
	ulOutBufLen = sizeof(IP_ADAPTER_INFO);

	if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) != ERROR_SUCCESS)
	{
		free(pAdapterInfo);
		pAdapterInfo = (IP_ADAPTER_INFO*)malloc(sizeof(ulOutBufLen));
	}

	if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) != ERROR_SUCCESS)
		printf("GetAdaptersInfo call failed with %d\n", dwRetVal);

	PIP_ADAPTER_INFO pAdapter = pAdapterInfo;
	while (pAdapter)
	{
		printf("\n\n");
		printf("Adapter name: %s\n", pAdapter->AdapterName);
		printf("Adapter desc: %s\n", pAdapter->Description);
		printf("Adapter addr:\n");
		for (UINT i = 0; i < pAdapter->AddressLength; i++)
		{
			if (i == (pAdapter->AddressLength - 1))
				printf("%.2X\n", (int)pAdapter->Address[i]);
			else
				printf("%.2X-", (int)pAdapter->Address[i]);
		}
		printf("IP Address: %s\n", pAdapter->IpAddressList.IpAddress.String);
		printf("IP Mask: %s\n", pAdapter->IpAddressList.IpMask.String);
		printf("Gateway: %s\n", pAdapter->GatewayList.IpAddress.String);
		if (pAdapter->DhcpEnabled)
		{
			printf("DHCP Enabled: Yes\n");
			printf("DHCP Server: %s\n", pAdapter->DhcpServer.IpAddress.String);
		}
		else
			printf("DHCP Enabled: No");

		pAdapter = pAdapter->Next;
	}

	if (pAdapterInfo)
		free(pAdapterInfo);

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
