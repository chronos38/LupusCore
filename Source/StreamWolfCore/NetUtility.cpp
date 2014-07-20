﻿#include "NetUtility.h"
#include "IPAddress.h"
#include "IPEndPoint.h"
#include "Socket.h"

namespace Lupus {
    namespace Net {
        namespace Sockets {
            uint16_t HostToNetworkOrder(uint16_t host)
            {
                return htons(host);
            }

            uint32_t HostToNetworkOrder(uint32_t host)
            {
                return htonl(host);
            }

            uint64_t HostToNetworkOrder(uint64_t host)
            {
                return htonll(host);
            }

            uint16_t NetworkToHostOrder(uint16_t network)
            {
                return ntohs(network);
            }

            uint32_t NetworkToHostOrder(uint32_t network)
            {
                return ntohl(network);
            }

            uint64_t NetworkToHostOrder(uint64_t network)
            {
                return ntohll(network);
            }

            std::vector<std::shared_ptr<IPEndPoint>> GetAddressInformation(const std::string& node, const std::string& service)
            {
                return GetAddressInformation(node, service, AddressFamily::Unspecified, SocketType::Unspecified, ProtocolType::Unspecified);
            }

            std::vector<std::shared_ptr<IPEndPoint>> GetAddressInformation(const std::string& node, const std::string& service, AddressFamily family)
            {
                return GetAddressInformation(node, service, family, SocketType::Unspecified, ProtocolType::Unspecified);
            }

            std::vector<std::shared_ptr<IPEndPoint>> GetAddressInformation(const std::string& node, const std::string& service, SocketType type)
            {
                return GetAddressInformation(node, service, AddressFamily::Unspecified, type, ProtocolType::Unspecified);
            }

            std::vector<std::shared_ptr<IPEndPoint>> GetAddressInformation(const std::string& node, const std::string& service, ProtocolType protocol)
            {
                return GetAddressInformation(node, service, AddressFamily::Unspecified, SocketType::Unspecified, protocol);
            }

            std::vector<std::shared_ptr<IPEndPoint>> GetAddressInformation(const std::string& node, const std::string& service, AddressFamily family, SocketType type, ProtocolType protocol)
            {
                if (service.empty()) {
                    throw std::invalid_argument("service argument must have a valid value");
                }

                std::vector<std::shared_ptr<IPEndPoint>> addresses;
                const char* nodename = node.empty() ? node.c_str() : nullptr;
                AddrInfo hints, *begin = nullptr, *it = nullptr;

                memset(&hints, 0, sizeof(hints));
                hints.ai_family = (int)family;
                hints.ai_socktype = (int)type;
                hints.ai_protocol = (int)protocol;

                if (!nodename) {
                    hints.ai_flags = AI_PASSIVE;
                }

                if (getaddrinfo(nodename, service.c_str(), &hints, &begin) != 0) {
                    if (begin) {
                        freeaddrinfo(begin);
                    }

                    throw std::runtime_error(GetLastAddressInfoErrorString());
                }

                for (it = begin; it; it = it->ai_next) {
                    AddrStorage storage;

                    memset(&storage, 0, sizeof(AddrStorage));
                    memcpy(&storage, it->ai_addr, it->ai_addrlen);
                    addresses.push_back(IPEndPointPtr(new IPEndPoint(std::vector<uint8_t>((uint8_t*)&storage, (uint8_t*)&storage + sizeof(AddrStorage)))));
                }

                freeaddrinfo(begin);
                return addresses;
            }
        }
    }
}
