
#include <unistd.h>
#include <string>
#include <iostream>
#include <conio.h>

using namespace std;
int winnerId = 0;

int scoreCard[9] = {0};

class TicTacToe{
private:
	string playerName;
	bool isCurrentPlayer = false;

public:
	string getPlayerName(){
		return playerName;
	}

	bool isCurrentPlayer(){
		return isCurrentPlayer;
	}

	void setPlayerName(string name){
		playerName = name;
	}

	void setCurrentPlayer(bool val){
		isCurrentPlayer = val;
	}
};

int main(){
	cout<<"------------------TIC TAC TOE------------------"<<
			<<"\n\n"<<endl;
	TicTacToe *players = new TicTacToe[2];
    string nameBuf;
	cout << "Enter Player Name 1: ";
	cin >> nameBuf;
	players[0].setPlayerName(nameBuf);
	cout << "Enter Player Name 2: ";
	cin >> nameBuf;
	players[1].setPlayerName(nameBuf);

	printBoard();
	bool winner = false;

	while (!winner() && !noPosition()){

		for (int i = 0; i<2 ; i++){
			int val;
			cout<<"Player"<<i+1<<" "<< players[i].getPlayerName<<" input an empty position: ";
			cin >> val;

			scoreCard[val-1] = i+1;

			players[i].setCurrentPlayer(true);

			if(i==1){
				players[i-1].setCurrentPlayer(false);
			}
			else{
				players[i+1].setCurrentPlayer(false);
			}

			printBoard();
			winner = checkWinner();
;		}

	}
	if (winnerId!==0)
	cout<<"\n\n------------------Player "<<players[winnerId-1].getPlayerName
		<<" WON!!!------------------\n\n"<<endl;

	else if (noPosition())
		cout<<"\n\n------------------Nobody WON------------------\n\n"<<endl;



}
bool checkWinner(){

	int currPlayer;
		if(players[0].isCurrentPlayer){
			currPlayer = 1;
		}
		else
			currPlayer = 2;

	for (int pos = 0 ; pos < 9 ; pos++){

		bool horizontal = checkHorizontal(currPlayer, pos);
		if (horizontal){
			winnerId = currPlayer;
			return horizontal;
		}

		bool vertical = checkVertical(currPlayer, pos);
		if (vertical){
			winnerId = currPlayer;
			return vertical;
		}

		bool diagonal = checkDiagonal(currPlayer, pos);
		if (diagonal){
			winnerId = currPlayer;
			return diagonal;
		}

	}
	
	return false;

}
void printBoard(){
	printHorizontalPartition();
	for (int i = 0; i < 9 ; i++){

			printVerticalPartition();
		    
			if(scoreCard[i]!=0){
				cout<<"P"<<scoreCard[i]<<"   ";
			}
			else{
				cout<<i+1<<"    ";
			}
			
			printVerticalPartition();

			if((i+1) %3 ==0 )
				printHorizontalPartition();
	}

}
void printHorizontalPartition(){
	cout<<"----------+---------+----------";
}
void printVerticalPartition(){
	cout<<"|    ";
}

bool checkHorizontal(int playerId, int position){

	if (scoreCard[position]!= playerId)
		return false;

	int location = (position+1)%3;

	if (location == 1) {
		if (scoreCard[position+1] == playerId){
			if (scoreCard[position+2] == playerId){
				return true;
			}
			else 
				return false;
		}
		else 
			return false;

	}

	else if (location == 2) {
		if (scoreCard[position+1] == playerId){
			if(scoreCard[position -1] == playerId){
				return true;
			}
			else
				return false;
		}

		else
			return false;

	}

	else if (location == 0){

		if (scoreCard[position-1] == playerId){
			if(scoreCard[position -2] == playerId){
				return true;
			}
			else
				return false;
		}

		else
			return false;

	}

}

bool checkVertical(int playerId, int position){
	if (scoreCard[position]!= playerId)
		return false;

	int location = (position+1)%3;

	if (location == 1) {
		if (scoreCard[position+3] == playerId){
			if (scoreCard[position+6] == playerId){
				return true;
			}
			else 
				return false;
		}
		else 
			return false;

	}

	else if (location == 2) {
		if (scoreCard[position+3] == playerId){
			if(scoreCard[position -3] == playerId){
				return true;
			}
			else
				return false;
		}

		else
			return false;

	}

	else if (location == 0){

		if (scoreCard[position-3] == playerId){
			if(scoreCard[position -3] == playerId){
				return true;
			}
			else
				return false;
		}

		else
			return false;

	}

}

bool checkDiagonal(int playerId, int position){
	if (scoreCard[position]!= playerId)
		return false;

	//temporary hardcoded solution
	if(position == 0){
		if(scoreCard[position+4] == playerId){
			if(scoreCard[position+8] == playerId)
				return true;
			else
				return false;
		}
		else return false;
	}
	else if(position == 2){
		if(scoreCard[position+2] == playerId){
			if(scoreCard[position+4] == playerId)
				return true;
			else
				return false;
		}
		else return false;
	}
	else if(position == 4){
		if(scoreCard[position+4] == playerId){
			if(scoreCard[position-4] == playerId)
				return true;
			else
				return false;
		}
		else return false;
	}
	else if(position == 6){
		if(scoreCard[position-2] == playerId){
			if(scoreCard[position-4] == playerId)
				return true;
			else
				return false;
		}
		else return false;
	}
	else if(position == 8){
		if(scoreCard[position-4] == playerId){
			if(scoreCard[position-8] == playerId)
				return true;
			else
				return false;
		}
		else return false;
	}
	else
		return false;
} 
// ----------+---------+----------
// |    1    |    2    |    3    |    
// ----------+---------+----------
// |    4    |    5    |    6    |
// ----------+---------+----------
// |    7    |    8    |    9    |
// ----------+---------+----------
bool noPosition(){
	bool noPosition = true;
	for (int i = 0 ; i< 9 && noPosition = true ; i++){
		if(scoreCard[i] == 0)
			noPosition = false;
	}
	return noPosition;
}