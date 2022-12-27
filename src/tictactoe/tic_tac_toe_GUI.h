#ifndef TIC_TAC_TOE_GUI
#define TIC_TAC_TOE_GUI

#include <SFML/Graphics.hpp>

#include "tic_tac_toe.h"

class TicTacToeGUI : public TicTacToe
{
private:
	sf::RenderWindow window;
	sf::View view;
	sf::Event event;
	
	sf::Font font;
	
	sf::Text board_sf;
	sf::Text topText_sf;
	sf::Text errorText_sf;
	sf::Text bottomText_sf;

	virtual void getInput() override
	{
		input = 0;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}
			if(event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128)
				{
					input = event.text.unicode;
				}
				if(isEnd)
				{
					isRunning = false;
				}
				isKeyPressed = true;
			}
		}
	}
	
public:
	TicTacToeGUI(char p1, char p2) : 
		window(sf::VideoMode(720, 480), "CPSE2_5", sf::Style::Close), 
		view(sf::Vector2f(0.0f,0.0f), sf::Vector2f(720, 480)),
		TicTacToe(p1, p2),
		board_sf(board, font, 16),
		topText_sf(topText, font, 16),
		errorText_sf(errorText, font, 16),
		bottomText_sf(bottomText, font, 16)
	{
		window.setFramerateLimit(60);
		
		if(!font.loadFromFile("Consolas.ttf")) exit(-1);
		
		topText_sf.setPosition(sf::Vector2f(0,0));
		board_sf.setPosition(sf::Vector2f(0, 3*16));
		bottomText_sf.setPosition(sf::Vector2f(0, 9*16));
		errorText_sf.setPosition(sf::Vector2f(0, 11*16));
	}
	virtual ~TicTacToeGUI()
	{}

	virtual void update() override
	{
		if(isEnd)
		{
			getInput();
		}
		else
		{
			if(isKeyPressed)
			{
				if(isRunning && !error && input != 'u')
				{	
					board[(y * WIDTH) + (x + (x * 3) + 1)] = player1Turn ? player1 : player2;
					player1Turn = player1Turn ? false : true;
				}
				bottomText_sf.setString("player " + std::to_string(2 - player1Turn) + " (" + std::string(1, player1Turn ? player1 : player2) + ") input: ");
				if((isWinner = isWon()) || commandList.size() >= 9)
				{
					bottomText_sf.setString(isWinner ? std::string("player " + std::to_string(player1Turn+1) + " has won!") : std::string("game ended in a tie!"));
					isEnd = true;
					error = true;
					sprintf(errorText, "press any key to exit . . .\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");
				}
				board_sf.setString(board);
				errorText_sf.setString(errorText);				
				isKeyPressed = false;
			}
		}
		if(!window.isOpen()) isRunning = false;
	}
	
	virtual void draw() override
	{
		window.draw(topText_sf);
		window.draw(board_sf);
		window.draw(bottomText_sf);
		if(error) window.draw(errorText_sf);
		window.display();
	}
	virtual void clear() override
	{
		window.clear(sf::Color::Black);
	}
};

#endif // TIC_TAC_TOE_GUI