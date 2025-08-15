#pragma once
#include "Prerequisites.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

class 
NetworkHelper {
public:
	NetworkHelper();
	~NetworkHelper();

  /* @brief Starts the server and binds it to the specified port.
   * Returns true if successful, false otherwise.
	 */
	bool 
	StartServer(int port);
	
  /* @brief Waits for a client to connect.
	* This will block until a client connects.
	* Returns the client socket if successful, -1 otherwise.
	*/
	SOCKET 
	AcceptClient();

  /* @brief Connects to a server at the specified IP and port.
	* Returns true if successful, false otherwise.
	*/
	bool 
	ConnectToServer(const std::string& ip, int port);

  /* @brief Sends data to the specified socket.
   * Returns true if successful, false otherwise.
   */
	bool 
	SendData(SOCKET socket, const std::string& data);
	
  /* @brief Sends binary data to the specified socket.
   * Returns true if successful, false otherwise.
   */
	bool 
	SendData(SOCKET socket, const std::vector<unsigned char>& data);
	
  /* @brief Receives data from the specified socket.
	* Returns the received data as a string.
	*/
	std::string
	ReceiveData(SOCKET socket);
	
  /* @brief Receives binary data from the specified socket.
  * Returns the received data as a vector of unsigned char.
  * If size is specified, it will receive exactly that many bytes.
  * If size is 0, it will receive until the socket is closed.
  */
	std::vector<unsigned char> 
	ReceiveDataBinary(SOCKET socket, int size = 0);

  /* @brief Closes the specified socket.
  * This will close the socket and set it to INVALID_SOCKET.
  */
	void 
	close(SOCKET socket);

  /* @brief Sends all data to the specified socket.
  * This will block until all data is sent or an error occurs.
  * Returns true if successful, false otherwise.
	*/
	bool 
	SendAll(SOCKET s, const unsigned char* data, int len);
	
  /* @brief Receives exact number of bytes from the specified socket.
  * This will block until the exact number of bytes is received or an error occurs.
  * Returns true if successful, false otherwise.
  */
	bool 
	ReceiveExact(SOCKET s, unsigned char* out, int len);

public:
  SOCKET m_serverSocket = -1; // Server socket
private:
  bool m_initialized; // Whether Winsock is initialized
};