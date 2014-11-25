/**
 * Copyright (C) 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of Lupus.
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "IPEndPoint.h"
#include "IPAddress.h"
#include "NetUtility.h"

namespace Lupus {
    namespace Net {
        namespace Sockets {
            IPEndPoint::IPEndPoint(U32 address, U16 port) :
                IPEndPoint(MakePointer<IPAddress>(address), port)
            {
            }

            IPEndPoint::IPEndPoint(Pointer<IPAddress> address, U16 port)
            {
                if (!address) {
                    throw NullPointer("address");
                }

                AddrIn* addr;
                AddrIn6* addr6;

                memset(&mAddrStorage, 0, sizeof(AddrStorage));

                switch (address->Family()) {
                    case AddressFamily::InterNetwork:
                        addr = (AddrIn*)&mAddrStorage;
                        addr->sin_family = AF_INET;
                        addr->sin_port = HostToNetworkOrder(port);
                        memcpy(&addr->sin_addr, address->Bytes().data(), 4);
                        break;

                    case AddressFamily::InterNetworkV6:
                        addr6 = (AddrIn6*)&mAddrStorage;
                        addr6->sin6_family = AF_INET;
                        addr6->sin6_port = HostToNetworkOrder(port);
                        memcpy(&addr6->sin6_addr, address->Bytes().data(), 16);
                        break;
                }

                mAddress = address;
            }

            IPEndPoint::IPEndPoint(const Vector<U8>& buffer)
            {
                if (buffer.size() != sizeof(AddrStorage)) {
                    throw InvalidArgument("buffer contains invalid data");
                }

                memset(&mAddrStorage, 0, sizeof(AddrStorage));
                memcpy(&mAddrStorage, buffer.data(), sizeof(AddrStorage));
            }

            AddressFamily IPEndPoint::Family() const
            {
                return mAddress->Family();
            }

            Pointer<IPAddress> IPEndPoint::Address() const
            {
                return mAddress;
            }

            void IPEndPoint::Address(Pointer<IPAddress> address)
            {
                if (!address) {
                    throw NullPointer("address");
                }

                U16 port = Port();
                AddrIn* addr;
                AddrIn6* addr6;

                memset(&mAddrStorage, 0, sizeof(AddrStorage));

                switch (address->Family()) {
                    case AddressFamily::InterNetwork:
                        addr = (AddrIn*)&mAddrStorage;
                        addr->sin_family = AF_INET;
                        addr->sin_port = HostToNetworkOrder(port);
                        memcpy(&addr->sin_addr, address->Bytes().data(), 4);
                        break;

                    case AddressFamily::InterNetworkV6:
                        addr6 = (AddrIn6*)&mAddrStorage;
                        addr6->sin6_family = AF_INET;
                        addr6->sin6_port = HostToNetworkOrder(port);
                        memcpy(&addr6->sin6_addr, address->Bytes().data(), 16);
                        break;
                }

                mAddress = address;
            }

            U16 IPEndPoint::Port() const
            {
                switch (mAddrStorage.ss_family) {
                    case AF_INET:
                        return NetworkToHostOrder(((AddrIn*)&mAddrStorage)->sin_port);

                    case AF_INET6:
                        return NetworkToHostOrder(((AddrIn6*)&mAddrStorage)->sin6_port);
                }

                return 0;
            }

            void IPEndPoint::Port(U16 port)
            {
                switch (mAddrStorage.ss_family) {
                    case AF_INET:
                        ((AddrIn*)&mAddrStorage)->sin_port = HostToNetworkOrder(port);

                    case AF_INET6:
                        ((AddrIn6*)&mAddrStorage)->sin6_port = HostToNetworkOrder(port);
                }
            }

            Vector<U8> IPEndPoint::Serialize() const
            {
                return Vector<U8>((U8*)&mAddrStorage, (U8*)&mAddrStorage + sizeof(AddrStorage));
            }
        }
    }
}
