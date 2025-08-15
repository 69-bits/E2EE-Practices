#include "Server.h"

Server::Server(int port) : m_port(port), m_clientSock(-1) {
  // Initialize network and crypto helpers
	m_crypto.GenerateRSAKeys();
}

Server::~Server() {
  // Close the client socket if it's open
	if (m_clientSock != -1) {
		m_net.close(m_clientSock);
	}
}


bool Server::Start() {
	std::cout << "[Server] Iniciando servidor en el puerto " << m_port << "...\n";
	return m_net.StartServer(m_port);
}


void Server::WaitForClient() {
	std::cout << "[Server] Esperando conexión de un cliente...\n";

  // Wait for a client to connect
	m_clientSock = m_net.AcceptClient();
	if (m_clientSock == INVALID_SOCKET) {
		std::cerr << "[Server] No se pudo aceptar cliente.\n";
		return;
	}
	std::cout << "[Server] Cliente conectado.\n";

  // 1. Send server's public key
	std::string serverPubKey = m_crypto.GetPublicKeyString();
	m_net.SendData(m_clientSock, serverPubKey);

  // 2. Receive client's public key
	std::string clientPubKey = m_net.ReceiveData(m_clientSock);
	m_crypto.LoadPeerPublicKey(clientPubKey);

  // 3. Receive encrypted AES key
	std::vector<unsigned char> encryptedAESKey = m_net.ReceiveDataBinary(m_clientSock, 256);
	m_crypto.DecryptAESKey(encryptedAESKey);

	std::cout << "[Server] Clave AES intercambiada exitosamente.\n";
}


void Server::ReceiveEncryptedMessage() {
	// 1.Receive IV 
	std::vector<unsigned char> iv = m_net.ReceiveDataBinary(m_clientSock, 16);

  // 2. Receive size (4 bytes network/big-endian)
	std::vector<unsigned char> encryptedMsg = m_net.ReceiveDataBinary(m_clientSock, 128);

  // 3. Decrypt message
	std::string msg = m_crypto.AESDecrypt(encryptedMsg, iv);

  // 4. Display the message
	std::cout << "[Server] Mensaje recibido: " << msg << "\n";
}

void Server::StartReceiveLoop() {
	while (true) {
		// 1) IV (16)
		auto iv = m_net.ReceiveDataBinary(m_clientSock, 16);
		if (iv.empty()) {
			std::cout << "\n[Server] Conexión cerrada por el cliente.\n";
			break;
		}

		// 2) Size (4 bytes network/big-endian)
		auto len4 = m_net.ReceiveDataBinary(m_clientSock, 4);
		if (len4.size() != 4) {
			std::cout << "[Server] Error al recibir tamaño.\n";
			break;
		}
		uint32_t nlen = 0;
		std::memcpy(&nlen, len4.data(), 4);
    uint32_t clen = ntohl(nlen);   // <- convert to host order

		// 3) Ciphertext (clen bytes)
		auto cipher = m_net.ReceiveDataBinary(m_clientSock, static_cast<int>(clen));
		if (cipher.empty()) {
			std::cout << "[Server] Error al recibir datos.\n";
			break;
		}

    // 4) Decrypt the message
		std::string plain = m_crypto.AESDecrypt(cipher, iv);
		std::cout << "\n[Cliente]: " << plain << "\nServidor: ";
		std::cout.flush();
	}
}



void Server::SendEncryptedMessageLoop() {
	std::string msg;
	while (true) {
		std::cout << "Servidor: ";
		std::getline(std::cin, msg);
		if (msg == "/exit") break;

		std::vector<unsigned char> iv;
		auto cipher = m_crypto.AESEncrypt(msg, iv);

		// 1) IV (16)
		m_net.SendData(m_clientSock, iv);

		// 2) Size in network order (htonl)
		uint32_t clen = static_cast<uint32_t>(cipher.size());
		uint32_t nlen = htonl(clen);
		std::vector<unsigned char> len4(
			reinterpret_cast<unsigned char*>(&nlen),
			reinterpret_cast<unsigned char*>(&nlen) + 4
		);
		m_net.SendData(m_clientSock, len4);

		// 3) Ciphertext
		m_net.SendData(m_clientSock, cipher);
	}
	std::cout << "[Server] Saliendo del chat.\n";
}

void 
Server::StartChatLoop() {
	std::thread recvThread([&]() {
		StartReceiveLoop();
		});

	SendEncryptedMessageLoop();

	if (recvThread.joinable())
		recvThread.join();
}
