#ifndef DATOS_HPP_INCLUDED
#define DATOS_HPP_INCLUDED

#include <string>

class Datos
{
public:
	void setNickname(std::string str){ nickname = str; } 
	void setIpServer(std::string str){ ipServer = str; }
	void setPuertoServer(int p){ puertoServer = p; }
	void setPuertoCliente(int p){ puertoCliente = p; }

	std::string getNickname() const{ return nickname; }
	std::string getIpServer() const{ return ipServer; }
	int getPuertoServer() const{ return puertoServer; }
	int getPuertoCliente() const{ return puertoCliente; }

private:
	std::string nickname;
	std::string ipServer;
	int puertoServer;
	int puertoCliente;
};

#endif