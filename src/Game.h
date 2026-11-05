
#pragma once

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Text.h"
#include "Server.h"
#include "Client.h"

enum Gamemode
{
	MENU,
	INGAME,
	GAMEOVER,
};




class Game
{

 public:
	Game(sf::RenderWindow& window);
	~Game();
	bool init();
	void update(float dt);
	void render();
	void mouseButtonPressed(const sf::Event::MouseButtonPressed* event);
	void mouseButtonReleased(const sf::Event::MouseButtonReleased* event);
	void keyPressed(const sf::Event::KeyPressed* event);
	void keyReleased(const sf::Event::KeyReleased* event);
	void mouseMoved(const sf::Event::MouseMoved* event);

 private:
	sf::RenderWindow& window;

	std::shared_ptr<Board> board;

	Text host_text;
	Text join_text;

	std::unique_ptr<Server> server;
	std::unique_ptr<Client> client;

	Gamemode mode = MENU;
	
};

