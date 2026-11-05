
#include "Game.h"
#include "Tile.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
    : window(game_window)
{
  
}

Game::~Game()
{
    
}

bool Game::init()
{
    board = std::make_shared<Board>(window);
    board->init();   

    host_text.initialiseText("Host Game");
    host_text.getText()->setPosition(
        sf::Vector2f(window.getSize().x * 0.85 - host_text.getText()->getGlobalBounds().size.x * 0.85,
            window.getSize().y * 0.2 - host_text.getText()->getGlobalBounds().size.y * 0.2));

    join_text.initialiseText("Join Game");
    join_text.getText()->setPosition(
        sf::Vector2f(window.getSize().x * 0.85 - join_text.getText()->getGlobalBounds().size.x * 0.85,
            window.getSize().y * 0.4 - join_text.getText()->getGlobalBounds().size.y * 0.4));

    return true;
}

void Game::update(float dt)
{
    switch (mode)
    {
    case MENU:

        break;

    case INGAME:


        break;

    case GAMEOVER:
        break;

    }
}

void Game::render()
{
    switch (mode)
    {
    case MENU:

        board->render();
        window.draw(*host_text.getText());
        window.draw(*join_text.getText());
        break;

    case INGAME:


        break;

    case GAMEOVER:
        break;

    }

}

void Game::mouseButtonPressed(const sf::Event::MouseButtonPressed* event)
{
    switch (mode)
    {
    case MENU:

        board->mouseButtonPressed(event);

        if(host_text.getText()->getGlobalBounds().contains(sf::Vector2f(event->position)))
        {
            mode = INGAME;
            std::cout << "Creating Server." << std::endl;
            server = std::make_unique<Server>();
            server->init();
            server->run();
        }

        else if (join_text.getText()->getGlobalBounds().contains(sf::Vector2f(event->position)))
        {
            mode = INGAME;
            std::cout << "Attempting to connect to server." << std::endl;
            client = std::make_unique<Client>();
            client->connect();
            client->run();
            
        }


        break;

    case INGAME:


        break;

    case GAMEOVER:
        break;

    }

}

void Game::mouseButtonReleased(const sf::Event::MouseButtonReleased* event)
{
    switch (mode)
    {
    case MENU:

        board->mouseButtonReleased(event);
        break;

    case INGAME:


        break;

    case GAMEOVER:
        break;

    }

}

void Game::keyPressed(const sf::Event::KeyPressed* event)
{
    switch (mode)
    {
    case MENU:

        break;

    case INGAME:


        break;

    case GAMEOVER:
        break;

    }
}

void Game::keyReleased(const sf::Event::KeyReleased* event)
{
    switch (mode)
    {
    case MENU:

        break;

    case INGAME:


        break;

    case GAMEOVER:
        break;

    }
}

void Game::mouseMoved(const sf::Event::MouseMoved* event)
{
    switch (mode)
    {
    case MENU:

        board->mouseMoved(event);
        break;

    case INGAME:


        break;

    case GAMEOVER:
        break;

    }

}




