# E2EE-Practices

Prácticas de **cifrado de extremo a extremo (E2EE)** implementadas en C++ usando **RSA** para intercambio de claves y **AES** para cifrado simétrico, con comunicación cliente–servidor vía sockets TCP (WinSock2 en Windows).

El objetivo es educativo: mostrar un flujo completo de intercambio de claves y comunicación cifrada, utilizando **OpenSSL** para las operaciones criptográficas.

---

## 📂 Estructura del proyecto

E2EE-Practices/
├─ include/
│ ├─ Prerequisites.h
│ ├─ NetworkHelper.h
│ ├─ CryptoHelper.h
│ ├─ Client.h
│ └─ Server.h
├─ src/
│ ├─ E2EE.cpp
│ ├─ NetworkHelper.cpp
│ ├─ CryptoHelper.cpp
│ ├─ Client.cpp
│ └─ Server.cpp
└─ README.md

---

## 🔐 Flujo del protocolo

1. **Servidor**
   - Genera par de claves RSA.
   - Escucha conexiones TCP.

2. **Cliente**
   - Se conecta al servidor.
   - Obtiene la clave pública RSA del servidor.
   - Genera una clave AES de sesión y la envía cifrada con RSA.

3. **Ambos**
   - Usan AES para cifrar y descifrar todos los mensajes posteriores.

⚠ **Nota**: Este proyecto es demostrativo y no implementa autenticación mutua ni mecanismos de protección adicionales como AEAD, firmas o rotación de claves.

---

## 🛠 Requisitos

- **CMake ≥ 3.15**
- **C++17**
- **OpenSSL**
- **Windows, Linux o macOS**
- En Windows: SDK de Windows + WinSock2
# Instalar OpenSSL
vcpkg install openssl
