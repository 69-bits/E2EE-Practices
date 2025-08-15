#pragma once
#include "NetworkHelper.h"
#include "CryptoHelper.h"
#include "Prerequisites.h"

class Client {
public:
	Client() = default;
	Client(const std::string& ip, int port);
	~Client();

  /* @brief Connects to the server at the specified IP and port.
  * Returns true if successful, false otherwise.
  */
	bool 
	Connect();
	
  /* @brief Exchanges keys with the server.
	* This will block until the key exchange is complete.
	*/
	void 
	ExchangeKeys();

  /* @brief Receives an encrypted message from the server.
  * This will block until a message is received.
  */
	void 
	SendAESKeyEncrypted();
	
  /* @brief Sends an encrypted message to the server.
	* This will block until the message is sent.
	*/
	void 
	SendEncryptedMessage(const std::string& message);

  /* @brief Receives an encrypted message from the server.
  * This will block until a message is received.
  */ 
	void
	SendEncryptedMessageLoop();

  /* @brief Starts the chat loop.
  * This will run in a separate thread to allow sending and receiving messages simultaneously.
  */
	void
	StartChatLoop();

  /* @brief Starts the receive loop.
  * This will run in a separate thread to continuously receive messages from the server.
  */
	void 
	StartReceiveLoop();    

private:
  std::string m_ip; // Server IP
  int m_port; // Server port
  SOCKET m_serverSock;	// Server socket
  NetworkHelper m_net;	 // Network helper for sending and receiving data
  CryptoHelper m_crypto; // Crypto helper for encryption/decryption
};
