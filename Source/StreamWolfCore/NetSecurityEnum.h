#pragma once

namespace Lupus {
    namespace Net {
        namespace Security {
            enum class CipherAlgorithmType {
                None,
                Aes,
                Aes128,
                Aes192,
                Aes256,
                TripleDes,
                Serpent,
                Rc5,
                Rc6,
                Twofish,
                Blowfish,
                Idea,
                Camellia,
                Seed,
                Panama,  // high-speed
                Sosemanuk,  // high-speed
                Salsa20  // high-speed
            };

            enum class HashAlgorithmType {
                None,
                Sha1,
                Sha224,
                Sha256,
                Sha385,
                Sha512,
                Sha3,
                Tiger,
                Whirlpool,
                Ripemd160,
                Ripemd320,
                Ripemd128,
                Ripemd256,
                Md5
            };

            enum class ExchangeAlgorithmType {
                None,
                DeffieHellman,
                UnifiedDeffieHellman,
                Mqv,
                Ecdh,
                Ecmqv,
                XtrDh
            };

            enum class SslProtocols {
                Default,
                None,
                Ssl3,
                Tls,
                Tsl11,
                Tls12
            };

            enum class EncryptionPolicy {
                AllowNoEncryption,
                NoEcryption,
                RequireEncryption
            };
        }
    }
}
