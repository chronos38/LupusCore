#include "HashAlgorithm.h"
#include "CryptoHash.h"
#include <algorithm>
#include <cctype>
#include <cryptopp/sha.h>
#include <cryptopp/md5.h>
#include <cryptopp/ripemd.h>
#include <cryptopp/whrlpool.h>
#include <cryptopp/tiger.h>

using namespace std;

namespace Lupus {
    namespace Security {
        namespace Cryptography {
            vector<uint8_t> HashAlgorithm::TransformFinalBlock(const vector<uint8_t>& input, uint32_t inputOffset, uint32_t inputCount)
            {
                return ComputeHash(input, inputOffset, inputCount);
            }

            uint32_t HashAlgorithm::TransformBlock(const vector<uint8_t>& input, uint32_t inputOffset, uint32_t inputCount, vector<uint8_t>& output, uint32_t outputOffset)
            {
                vector<uint8_t> buffer = ComputeHash(input, inputOffset, inputCount);
                auto iterator = begin(output) + outputOffset;

                if (buffer.size() > output.size() - outputOffset) {
                    throw out_of_range("transformed bytes exceeding output vector");
                }


                for_each(begin(buffer), end(buffer), [&iterator](const uint8_t& byte) {
                    *(iterator++) = byte;
                });

                return (uint32_t)buffer.size();
            }

            HashAlgorithmFactory::HashAlgorithmFactory()
            {
                smPrototypes["sha1"] = make_shared<CryptoHash<CryptoPP::SHA1>>();
                smPrototypes["sha224"] = make_shared<CryptoHash<CryptoPP::SHA224>>();
                smPrototypes["sha256"] = make_shared<CryptoHash<CryptoPP::SHA256>>();
                smPrototypes["sha384"] = make_shared<CryptoHash<CryptoPP::SHA384>>();
                smPrototypes["sha512"] = make_shared<CryptoHash<CryptoPP::SHA512>>();
                smPrototypes["tiger"] = make_shared<CryptoHash<CryptoPP::Tiger>>();
                smPrototypes["whirlpool"] = make_shared<CryptoHash<CryptoPP::Whirlpool>>();
                smPrototypes["ripemd128"] = make_shared<CryptoHash<CryptoPP::RIPEMD128>>();
                smPrototypes["ripemd160"] = make_shared<CryptoHash<CryptoPP::RIPEMD160>>();
                smPrototypes["ripemd256"] = make_shared<CryptoHash<CryptoPP::RIPEMD256>>();
                smPrototypes["ripemd320"] = make_shared<CryptoHash<CryptoPP::RIPEMD320>>();
                smPrototypes["md5"] = make_shared<CryptoHash<CryptoPP::Weak::MD5>>();
            }

            shared_ptr<HashAlgorithmFactory> HashAlgorithmFactory::GetInstance()
            {
                static auto instance = shared_ptr<HashAlgorithmFactory>(new HashAlgorithmFactory());
                return instance;
            }

            shared_ptr<HashAlgorithm> HashAlgorithmFactory::Create(const string& hash) const
            {
                auto it = smPrototypes.find(hash);

                if (it != end(smPrototypes)) {
                    return dynamic_pointer_cast<HashAlgorithm>(it->second->Clone());
                }

                return nullptr;
            }

            unordered_map<string, shared_ptr<HashAlgorithm>> HashAlgorithmFactory::smPrototypes;
        }
    }
}