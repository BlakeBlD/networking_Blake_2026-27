#include "Server.h"

void Server::init()
{
	if (listener == nullptr)
	{
		listener = std::make_unique<sf::TcpListener>();
	}

	//bind listener to a port
	if(listener->listen(53000) != sf::Socket::Status::Done)
	{
		std::cout << "Couldn't bind listener to port 53000." << std::endl;
	}



}

void Server::run()
{
	std::thread input_thread([&] {input(); });

	while(running)
	{

		//add new connection to connections vector
		sf::TcpSocket& c_sock = *connections.emplace_back(std::make_unique<sf::TcpSocket>());

		//Check that new connection finishes
		if(listener->accept(c_sock) != sf::Socket::Status::Done)
		{
			//connection didn't finish so remove it
			connections.pop_back();
			std::cout << "Connection failed on server side." << std::endl;
			continue;
		}

		std::cout << "Client connected @ " << c_sock.getRemotePort() << std::endl;

		//create a thread that listens to the connected socket, constructed inside the workers vector
		workers.emplace_back([&] {
			listen(c_sock);
			std::cout << "Disconnect detected" << std::endl;
			std::lock_guard<std::mutex> lck(mutex); //guard access to connection vector

			for (int i = 0; i < connections.size(); i++) 
			{
				if (connections[i]->getRemotePort() == c_sock.getRemotePort())
				{
					connections.erase(std::next(connections.begin(), i));
					break;
				}
			}
			});
	}
}

void Server::listen(sf::TcpSocket& c_socket)
{
	//keep socket active until connection is no longer valid
	bool continue_receiveing = true;

	char data[1028];
	std::size_t received;

	while (continue_receiveing) 
	{
		sf::Socket::Status status = c_socket.receive(data, 1028, received);

		if (status == sf::Socket::Status::Disconnected)
		{
			continue_receiveing = false;
			std::cout << "Disconnected" << std::endl;
		}

		if (received < 1028) { data[received] = '\0'; }
		relay(data, c_socket);

		std::cout << reinterpret_cast<char*>(data) << std::endl;
	}

	c_socket.disconnect();
}

void Server::send(std::string buffer, sf::TcpSocket& c_socket)
{
}

void Server::input()
{
	while (running)
	{
		std::string str;
		std::getline(std::cin, str);
		std::cin.clear();

		std::lock_guard<std::mutex> lck(mutex);
		for (std::unique_ptr<sf::TcpSocket>& connection : connections)
		{
			connection->send(reinterpret_cast<char*>(str.data()), str.length());
		}

	}
}

void Server::relay(std::string buffer, sf::TcpSocket& c_socket)
{
	char* message = reinterpret_cast<char*>(buffer.data());

	std::lock_guard<std::mutex> lck(mutex);

	for (std::unique_ptr<sf::TcpSocket>& connection : connections) 
	{
		if (connection->getRemotePort() != c_socket.getRemotePort())
		{
			connection->send(message, buffer.size());
		}
	}
	
}
