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
#pragma once

#include "AuthenticatedStream.h"
#include "SecurityAuthEnum.h"

#include <functional>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Security {
        namespace Cryptography {
            class SymmetricCipher;

            namespace X509Certificates {
                class X509Certificate;
            }
        }
    }

    namespace Net {
        namespace Security {
            class LUPUSCORE_API SslStream : public AuthenticatedStream
            {
            public:

                SslStream(Pointer<Stream>);
                SslStream(Pointer<Stream>, bool);
                virtual ~SslStream();

                virtual bool CanRead() const NOEXCEPT override;
                virtual bool CanWrite() const NOEXCEPT override;
                virtual bool CanSeek() const NOEXCEPT override;

                virtual void Close() override;
                virtual S64 Length() const override;
                virtual void Length(S64) throw(OutOfRange) override;
                virtual S64 Position() const override;
                virtual void Position(S64) throw(OutOfRange) override;
                virtual int Read(Vector<U8>& buffer, U32 offset, U32 size) throw(OutOfRange) override;
                virtual int ReadByte() override;
                virtual int Write(const Vector<U8>& buffer, U32 offset, U32 size) throw(OutOfRange) override;
                virtual void WriteByte(U8 byte) override;
                virtual S64 Seek(S64 offset, SeekOrigin origin) override;

                virtual bool IsAuthenticated() const override;
                virtual bool IsEncrypted() const override;
                virtual bool IsMutuallyAuthenticated() const override;
                virtual bool IsServer() const override;
                virtual bool IsSigned() const override;

                virtual bool CheckCertRevocationStatus() const NOEXCEPT;
                virtual Lupus::Security::Authentication::CipherAlgorithmType CipherAlgorithm() const NOEXCEPT;
                virtual int CipherStrength() const NOEXCEPT;
                virtual Lupus::Security::Authentication::HashAlgorithmType HashAlgorithm() const NOEXCEPT;
                virtual int HashStrength() const NOEXCEPT;
                virtual Lupus::Security::Authentication::ExchangeAlgorithmType KeyExchangeAlgorithm() const NOEXCEPT;
                virtual int KeyExchangeStrength() const NOEXCEPT;
                virtual Lupus::Security::Authentication::SslProtocols SslProtocol() const NOEXCEPT;

                virtual void AuthenticateAsClientAsync(const String& host, std::function<void(std::exception_ptr, SslStream*)>) NOEXCEPT;
                virtual void AuthenticateAsClientAsync(
                    const String& host,
                    Vector<
                        Pointer<
                            Lupus::Security::Cryptography::X509Certificates::X509Certificate
                        >
                    > certificates,
                    Lupus::Security::Authentication::SslProtocols protocols,
                    bool checkRevocation,
                    std::function<void(std::exception_ptr, SslStream*)>) NOEXCEPT;
                virtual void AuthenticateAsServerAsync(Pointer<Lupus::Security::Cryptography::X509Certificates::X509Certificate> certificate, std::function<void(std::exception_ptr, SslStream*)>) NOEXCEPT;
                virtual void AuthenticateAsServerAsync(
                    Pointer<
                        Lupus::Security::Cryptography::X509Certificates::X509Certificate
                    > certificate,
                    bool clientCertRequired,
                    Lupus::Security::Authentication::SslProtocols protocols,
                    bool checkRevocation,
                    std::function<void(std::exception_ptr, SslStream*)>) NOEXCEPT;

                virtual void AuthenticateAsClient(const String& host);
                virtual void AuthenticateAsClient(
                    const String& host, 
                    Vector<
                        Pointer<
                            Lupus::Security::Cryptography::X509Certificates::X509Certificate
                        >
                    > certificates, 
                    Lupus::Security::Authentication::SslProtocols protocols,
                    bool checkRevocation);
                virtual void AuthenticateAsServer(Pointer<Lupus::Security::Cryptography::X509Certificates::X509Certificate> certificate);
                virtual void AuthenticateAsServer(
                    Pointer<
                        Lupus::Security::Cryptography::X509Certificates::X509Certificate
                    > certificate, 
                    bool clientCertRequired, 
                    Lupus::Security::Authentication::SslProtocols protocols,
                    bool checkRevocation);

            private:

                Pointer<Lupus::Security::Cryptography::SymmetricCipher> mCipher;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
