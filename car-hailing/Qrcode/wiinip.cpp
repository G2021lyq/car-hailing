#include <iostream>
#include <winsock2.h>
#include <iphlpapi.h>
#include <string>
#include "funcation.h"

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

std::string GetLocalIPv4Address() {
	DWORD bufferSize = 0;
	std::string ipAddress = "无法获取地址";

	// 获取缓冲区大小
	if (GetAdaptersAddresses(AF_INET, GAA_FLAG_INCLUDE_PREFIX, nullptr, nullptr, &bufferSize) == ERROR_BUFFER_OVERFLOW) {
		IP_ADAPTER_ADDRESSES* adaptersAddresses = reinterpret_cast<IP_ADAPTER_ADDRESSES*>(malloc(bufferSize));
		if (adaptersAddresses) {
			if (GetAdaptersAddresses(AF_INET, GAA_FLAG_INCLUDE_PREFIX, nullptr, adaptersAddresses, &bufferSize) == NO_ERROR) {
				for (IP_ADAPTER_ADDRESSES* adapter = adaptersAddresses; adapter != nullptr; adapter = adapter->Next) {
					if (adapter->IfType == IF_TYPE_IEEE80211 && adapter->OperStatus == IfOperStatusUp) {
						sockaddr_in* address = reinterpret_cast<sockaddr_in*>(adapter->FirstUnicastAddress->Address.lpSockaddr);
						ipAddress = inet_ntoa(address->sin_addr);
						break; // 获取第一个Wi-Fi网络的IPv4地址
					}
				}
			}
			free(adaptersAddresses);
		}
	}
	return ipAddress;
}