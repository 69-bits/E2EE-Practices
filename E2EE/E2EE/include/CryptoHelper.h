#pragma once
#include "Prerequisites.h"
#include "openssl\rsa.h"
#include "openssl\aes.h"

class 
CryptoHelper {
public:
	CryptoHelper();
	~CryptoHelper();

  // RSA


  /* @brief Generates a new RSA key pair.
   * The public key can be retrieved as a PEM string.
   * The private key is used for signing and decryption.
   * The public key is used for encryption and verification.
   */
  void 
  GenerateRSAKeys();
  

  /* @brief Loads a peer's public key from a PEM string.
   * This is used to encrypt the AES key for the peer.
   */
  std::string 
  GetPublicKeyString() const;
  
  /* @brief Loads a peer's public key from a PEM string.
   * This is used to encrypt the AES key for the peer.
   */
  void 
  LoadPeerPublicKey(const std::string& pemKey);

  // AES

   /* @brief Generates a new random AES key.
    * The key is 256 bits (32 bytes) long.
    * This key is used for symmetric encryption/decryption of messages.
    */
  void 
  GenerateAESKey();

  /* @brief Encrypts the AES key with the peer's public RSA key.
   * Returns the encrypted AES key as a vector of unsigned char.
   * This can be sent to the peer for them to decrypt with their private key.
   */
  std::vector<unsigned char> 
  EncryptAESKeyWithPeer();

  /* @brief Decrypts the AES key using the private RSA key.
   * This is used to retrieve the AES key after receiving it from the peer.
   * The encrypted key should be in PEM format.
   */
  void 
  DecryptAESKey(const std::vector<unsigned char>& encryptedKey);

  /* @brief Encrypts a plaintext string using AES.
   * The AES key must be set before calling this function.
   * Returns the ciphertext as a vector of unsigned char.
   * The IV (initialization vector) is also returned for decryption.
   */
  std::vector<unsigned char> 
  AESEncrypt(const std::string& plaintext, std::vector<unsigned char>& outIV);
  
  /* @brief Decrypts a ciphertext using AES.
   * The AES key must be set before calling this function.
   * The IV used for encryption must also be provided.
   * Returns the decrypted plaintext as a string.
   */
  std::string 
  AESDecrypt(const std::vector<unsigned char>& ciphertext, 
             const std::vector<unsigned char>& iv);

private:
  RSA* rsaKeyPair; // RSA key pair (private and public keys)
  RSA* peerPublicKey;     // Peer public key for encryption
  unsigned char aesKey[32]; // AES key (256 bits)
};