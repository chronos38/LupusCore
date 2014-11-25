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

#include "../HashAlgorithm.h"
#include "../Stream.h"
#include <cryptopp/sha3.h>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Security {
        namespace Cryptography {
            template <typename T>
            class CryptoHash : public HashAlgorithm
            {
            public:

                virtual ~CryptoHash() = default;

                virtual Pointer<HashAlgorithm> Clone() const NOEXCEPT override
                {
                    return MakePointer<CryptoHash<T>>();
                }

                virtual U32 BlockSize() const NOEXCEPT override
                {
                    return T::BLOCKSIZE * 8;
                }

                virtual U32 HashSize() const NOEXCEPT override
                {
                    return T::DIGESTSIZE * 8;
                }

                virtual Vector<U8> ComputeHash(const Vector<U8>& buffer) throw(OutOfRange) override
                {
                    return ComputeHash(buffer, 0, (U32)buffer.size());
                }

                virtual Vector<U8> ComputeHash(Pointer<Stream> stream) throw(OutOfRange) override
                {
                    U32 size = (U32)(stream->Length() - stream->Position());
                    Vector<U8> buffer(size);
                    stream->Read(buffer, 0, size);
                    return ComputeHash(buffer, 0, size);
                }

                virtual Vector<U8> ComputeHash(const Vector<U8>& input, U32 inputOffset, U32 inputCount) throw(OutOfRange) override
                {
                    static const int digestsize = T::DIGESTSIZE;

                    if (inputOffset > input.size()) {
                        throw OutOfRange("inputOffset");
                    } else if (inputCount > input.size() - inputOffset) {
                        throw OutOfRange("inputCount");
                    }

                    U8 digest[digestsize];

                    mAlgorithm.CalculateDigest(digest, input.data() + inputOffset, inputCount);

                    return std::move(Vector<U8>(digest, digest + digestsize));
                }

            private:

                T mAlgorithm;
            };

            template <>
            class CryptoHash<CryptoPP::SHA3_224> : public HashAlgorithm
            {
            public:

                virtual ~CryptoHash() = default;

                virtual Pointer<HashAlgorithm> Clone() const NOEXCEPT override
                {
                    return MakePointer<CryptoHash<CryptoPP::SHA3_224>>();
                }

                virtual U32 BlockSize() const NOEXCEPT override
                {
                    return mAlgorithm.BlockSize();
                }

                virtual U32 HashSize() const NOEXCEPT override
                {
                    return mAlgorithm.DigestSize();
                }

                virtual Vector<U8> ComputeHash(const Vector<U8>& buffer) throw(OutOfRange) override
                {
                    return ComputeHash(buffer, 0, (U32)buffer.size());
                }

                virtual Vector<U8> ComputeHash(Pointer<Stream> stream) throw(OutOfRange) override
                {
                    U32 size = (U32)(stream->Length() - stream->Position());
                    Vector<U8> buffer(size);
                    stream->Read(buffer, 0, size);
                    return ComputeHash(buffer, 0, size);
                }

                virtual Vector<U8> ComputeHash(const Vector<U8>& input, U32 inputOffset, U32 inputCount) throw(OutOfRange) override
                {
                    if (inputOffset > input.size()) {
                        throw OutOfRange("inputOffset");
                    } else if (inputCount > input.size() - inputOffset) {
                        throw OutOfRange("inputCount");
                    }

                    Vector<U8> digest(mAlgorithm.DigestSize());

                    mAlgorithm.CalculateDigest(digest.data(), input.data() + inputOffset, inputCount);

                    return std::move(digest);
                }

            private:

                CryptoPP::SHA3_224 mAlgorithm;
            };

            template <>
            class CryptoHash<CryptoPP::SHA3_256> : public HashAlgorithm
            {
            public:

                virtual ~CryptoHash() = default;

                virtual Pointer<HashAlgorithm> Clone() const NOEXCEPT override
                {
                    return MakePointer<CryptoHash<CryptoPP::SHA3_256>>();
                }

                virtual U32 BlockSize() const NOEXCEPT override
                {
                    return mAlgorithm.BlockSize();
                }

                virtual U32 HashSize() const NOEXCEPT override
                {
                    return mAlgorithm.DigestSize();
                }

                virtual Vector<U8> ComputeHash(const Vector<U8>& buffer) throw(OutOfRange) override
                {
                    return ComputeHash(buffer, 0, (U32)buffer.size());
                }

                virtual Vector<U8> ComputeHash(Pointer<Stream> stream) throw(OutOfRange) override
                {
                    U32 size = (U32)(stream->Length() - stream->Position());
                    Vector<U8> buffer(size);
                    stream->Read(buffer, 0, size);
                    return ComputeHash(buffer, 0, size);
                }

                virtual Vector<U8> ComputeHash(const Vector<U8>& input, U32 inputOffset, U32 inputCount) throw(OutOfRange) override
                {
                    if (inputOffset > input.size()) {
                        throw OutOfRange("inputOffset");
                    } else if (inputCount > input.size() - inputOffset) {
                        throw OutOfRange("inputCount");
                    }

                    Vector<U8> digest(mAlgorithm.DigestSize());

                    mAlgorithm.CalculateDigest(digest.data(), input.data() + inputOffset, inputCount);

                    return std::move(digest);
                }

            private:

                CryptoPP::SHA3_256 mAlgorithm;
            };

            template <>
            class CryptoHash<CryptoPP::SHA3_384> : public HashAlgorithm
            {
            public:

                virtual ~CryptoHash() = default;

                virtual Pointer<HashAlgorithm> Clone() const NOEXCEPT override
                {
                    return MakePointer<CryptoHash<CryptoPP::SHA3_384>>();
                }

                virtual U32 BlockSize() const NOEXCEPT override
                {
                    return mAlgorithm.BlockSize();
                }

                virtual U32 HashSize() const NOEXCEPT override
                {
                    return mAlgorithm.DigestSize();
                }

                virtual Vector<U8> ComputeHash(const Vector<U8>& buffer) throw(OutOfRange) override
                {
                    return ComputeHash(buffer, 0, (U32)buffer.size());
                }

                virtual Vector<U8> ComputeHash(Pointer<Stream> stream) throw(OutOfRange) override
                {
                    U32 size = (U32)(stream->Length() - stream->Position());
                    Vector<U8> buffer(size);
                    stream->Read(buffer, 0, size);
                    return ComputeHash(buffer, 0, size);
                }

                virtual Vector<U8> ComputeHash(const Vector<U8>& input, U32 inputOffset, U32 inputCount) throw(OutOfRange) override
                {
                    if (inputOffset > input.size()) {
                        throw OutOfRange("inputOffset");
                    } else if (inputCount > input.size() - inputOffset) {
                        throw OutOfRange("inputCount");
                    }

                    Vector<U8> digest(mAlgorithm.DigestSize());

                    mAlgorithm.CalculateDigest(digest.data(), input.data() + inputOffset, inputCount);

                    return std::move(digest);
                }

            private:

                CryptoPP::SHA3_384 mAlgorithm;
            };

            template <>
            class CryptoHash<CryptoPP::SHA3_512> : public HashAlgorithm
            {
            public:

                virtual ~CryptoHash() = default;

                virtual Pointer<HashAlgorithm> Clone() const NOEXCEPT override
                {
                    return MakePointer<CryptoHash<CryptoPP::SHA3_512>>();
                }

                virtual U32 BlockSize() const NOEXCEPT override
                {
                    return mAlgorithm.BlockSize();
                }

                virtual U32 HashSize() const NOEXCEPT override
                {
                    return mAlgorithm.DigestSize();
                }

                virtual Vector<U8> ComputeHash(const Vector<U8>& buffer) throw(OutOfRange) override
                {
                    return ComputeHash(buffer, 0, (U32)buffer.size());
                }

                virtual Vector<U8> ComputeHash(Pointer<Stream> stream) throw(OutOfRange) override
                {
                    U32 size = (U32)(stream->Length() - stream->Position());
                    Vector<U8> buffer(size);
                    stream->Read(buffer, 0, size);
                    return ComputeHash(buffer, 0, size);
                }

                virtual Vector<U8> ComputeHash(const Vector<U8>& input, U32 inputOffset, U32 inputCount) throw(OutOfRange) override
                {
                    if (inputOffset > input.size()) {
                        throw OutOfRange("inputOffset");
                    } else if (inputCount > input.size() - inputOffset) {
                        throw OutOfRange("inputCount");
                    }

                    Vector<U8> digest(mAlgorithm.DigestSize());

                    mAlgorithm.CalculateDigest(digest.data(), input.data() + inputOffset, inputCount);

                    return std::move(digest);
                }

            private:

                CryptoPP::SHA3_512 mAlgorithm;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
