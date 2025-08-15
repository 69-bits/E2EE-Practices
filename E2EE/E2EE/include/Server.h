#pragma once
#include "NetworkHelper.h"
#include "CryptoHelper.h"
#include "Prerequisites.h"

class 
Server {
public:
	Server() = default;
	Server(int port);

	~Server();

  /* Starts the server and binds it to the specified port.
   * Returns true if successful, false otherwise.
   */
	bool 
	Start();
	
  /* * Waits for a client to connect.
   * This will block until a client connects.
   */
	void 
	WaitForClient();
	
  /* * Exchanges keys with the client.
 * This will block until the key exchange is complete.
 */
	void 
	ReceiveEncryptedMessage();

  /* * Sends an encrypted message to the client.
	*/
	void
	StartReceiveLoop();

  /* * Sends an encrypted message to the client.
   * This will block until the message is sent.
   */
	void
	SendEncryptedMessageLoop();

  /* * Starts the chat loop.
	*/
	void
	StartChatLoop();

private:

  int m_port; // Port to bind the server to
  SOCKET m_clientSock; // Client socket
  NetworkHelper m_net; // Network helper for sending and receiving data
  CryptoHelper m_crypto; // Crypto helper for encryption/decryption
  std::thread m_rxThread; // Thread for receiving messages
  std::atomic<bool> m_running{ false };

  /* * Receives a message from the client.
   * This will block until a message is received.
   */
};