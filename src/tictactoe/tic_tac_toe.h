#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#include "command_list.h"

/* * * * * * * * * * *
*
*	Tic-tac-toe board
*
*	 O | X | X 
*	---|---|---
*	 X | O | X
*	---|---|---
*	 X | O | O
*
* * * * * * * * * * */

class TicTacToe
{
protected:
	static constexpr unsigned int WIDTH = 12;
	static constexpr unsigned int HEIGHT = 5;

	unsigned int x = 0;
	unsigned int y = 0;
	unsigned int numOfUndos = 0;
	unsigned int maxNumOfUndos = 1;
	
	char * board;
	char * topText;
	char * errorText;
	char * bottomText;
	
	bool error = false;
	bool isEnd = false;
	bool isWinner = false;
	bool player1Turn = true;
	bool isKeyPressed = false;
	
	char input;
	char player1;
	char player2;
	
	CommandList commandList;
	
	virtual void getInput()
	{
		isKeyPressed = true;
		input = getchar();
		for(int c; (c = getchar()) != EOF && c != '\n';);
	}
	
	bool isWon()
	{
		if(commandList.size() > 4)
		{
			char board[3 * 3];
			memset(board, 0, 3 * 3);
			for(unsigned int i = 0; i < commandList.size(); ++i)
			{
				int x = ( (commandList.list[i]->index % WIDTH - 1) / 3 );
				int y = (commandList.list[i]->index / WIDTH) ? (commandList.list[i]->index / WIDTH) / 2 : 0;
				board[(y * 3) + x] = commandList.list[i]->actor;
			}

			bool isSame = true;
			char player = player1Turn ? player2 : player1;
			
			// horizontal
			for(unsigned int y = 0; y < 3; ++y)
			{
				isSame = true;
				for(unsigned int x = 0; (x < 3) && isSame; ++x)
				{
					if(board[(y * 3) + x] != player) isSame = false;
					else if(x >= 2) return true;
				}
			}
			// vertical
			for(unsigned int x = 0; x < 3; ++x)
			{
				isSame = true;
				for(unsigned int y = 0; (y < 3) && isSame; ++y)
				{
					if(board[(y * 3) + x] != player) isSame = false;
					else if(y >= 2) return true;
				}
			}
			// diagonally
			if((board[4] == player) && (((board[0] == player) && (board[8] == player)) || ((board[2] == player) && (board[6] == player))))
			{
				return true;
			}
		}
		return false;
	}
	
public:
	bool isRunning = true;

	TicTacToe(char p1, char p2) : player1(p1), player2(p2), commandList(9)
	{
		board = (char *) calloc(WIDTH * HEIGHT, sizeof(char));

		errorText = (char *) calloc(128, sizeof(char));
		topText = (char *) calloc(128, sizeof(char));
		bottomText = (char *) calloc(32, sizeof(char));

		sprintf(board, "   |   |   \n---|---|---\n   |   |   \n---|---|---\n   |   |   \n");
		sprintf(topText, "Controls:\ntop row: 1,2,3; mid row: 4, 5, 6; bottom row: 7,8,9; quit: q; undo: u;\n");
		sprintf(bottomText, "player %d (%c) input: ", 2 - player1Turn, player1Turn ? player1 : player2);
	}
	virtual ~TicTacToe()
	{
		free(board);
		free(topText);
		free(errorText);
		free(bottomText);
	}
	
	virtual void clear()
	{
		printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
	}
	
	virtual void handleInput()
	{
		if(isEnd || (commandList.size() >= 9)) return;
		
		getInput();
		
		if(isKeyPressed)
		{
			try
			{	
				error = false;
				
				if(input == 'q')
				{
					isRunning = false;
					return;
				}
				if(input == 'u')
				{
					if( !commandList.isBegin() && (commandList.get() != NULL) && (commandList.size() > 0) && (numOfUndos < maxNumOfUndos) )
					{
						commandList.get()->undo();
						commandList--;
						numOfUndos++;
						player1Turn = player1Turn ? false : true;
					}
					else
					{
						throw "could not undo";
					}
					return;
				}
				
				input = input - '0';
				if((input < 1) || (input > 9)) throw "invalid input";
				
				x = ((input-1)%3);
				y = input <= 3 ? 0 : input <= 6 ? 2 : 4;
				unsigned int pos = (y * WIDTH) + (x + (x * 3) + 1);
				
				if(commandList.size() > 0)
				{
					for(unsigned int i = 0; i < commandList.size(); ++i)
					{
						if(commandList.list[i]->index == pos) throw "space is already occupied";
					}
				}
				commandList.push_back( new PlaceCommand(player1Turn ? player1 : player2, board, pos ) );
				numOfUndos = 0;
			}
			catch(const char * exception)
			{
				error = true;
				sprintf(errorText, "%s . . .\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n", exception);
			}
		}
	}
	
	virtual void update()
	{
		if(isEnd)
		{
			isRunning = false;
			return;
		}
		if(isKeyPressed)
		{
			if(isRunning && !error && input != 'u')
			{	
				board[(y * WIDTH) + (x + (x * 3) + 1)] = player1Turn ? player1 : player2;
				player1Turn = player1Turn ? false : true;
			}

			sprintf(bottomText, "player %d (%c) input: ", 2 - player1Turn, player1Turn ? player1 : player2);
			if((isWinner = isWon()) || commandList.size() >= 9)
			{
				if(isWinner)
				{
					sprintf(bottomText, "player %d has won!", player1Turn + 1);
				}
				else
				{
					sprintf(bottomText, "game ended in a tie!");
				}
				isEnd = true;
			}
			isKeyPressed = false;
		}
	}
	virtual void draw()
	{
		printf("\n%s%s%s%s", error ? errorText : "", topText, board, bottomText);
	}
};

#endif // TIC_TAC_TOE_H