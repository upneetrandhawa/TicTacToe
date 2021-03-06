#include <unistd.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <unistd.h>


using namespace std;

#define maxRows 3
#define maxColumns 3

int winnerId = 0;
int gameType;

int scoreCard[9] = {0};
//int scoreCard[maxRows][maxColumns] = {0};

class TicTacToe{
private:
    string playerName;
    bool isCurrPlayer = false;

public:
    string getPlayerName(){
        return playerName;
    }

    bool isCurrentPlayer(){
        return isCurrPlayer;
    }

    void setPlayerName(string name){
        playerName = name;
    }

    void setCurrentPlayer(bool val){
        isCurrPlayer = val;
    }
};

bool checkWinner(TicTacToe *players);
void printBoard(TicTacToe *players);
void printHorizontalBoundary();
void printHorizontalPartition();
void printEmptyHorVerPartition();
void printVerticalPartition();
int checkHorizontal(int playerId);
int checkVertical(int playerId);
int checkDiagonal(int playerId);
bool noPosition(TicTacToe *players);
bool isOccupied(int position);
int randomSlot();
void multiplayerGame(TicTacToe *players);
void singlePlayerEasy(TicTacToe *players);
void singlePlayerDifficult(TicTacToe *players);
int gameOptions();
void loadingCursor();
bool checkPlayAgain();
void resetGameData();
void playGame(TicTacToe *players);
void updateScoreCard(int pos, int playerId);
int getInput(TicTacToe *players, int playerId);


int main(){
    cout<<"\n\n------------------TIC TAC TOE------------------"
            <<"\n\n"<<endl;

    TicTacToe *players = new TicTacToe[2];
    bool play = true;
    
    while(play){
        playGame(players);
        play = checkPlayAgain();
        resetGameData();
    }
 return 1;
}

void printBoard(TicTacToe *players){
    // cout << "\033[1;47m";//white background
    printHorizontalBoundary();
    printEmptyHorVerPartition();

    for (int i = 0; i < 9 ; i++){
            

            printVerticalPartition();
            
            if(scoreCard[i]!=0){
                cout << "\033[1;33m";//black font for taken
                cout<<"P"<<scoreCard[i]<<"   ";
                cout<<"\033[0m";
            }
            else{
                cout << "\033[1;34m";//blue font for not taken
                cout<<i+1<<"    ";
                cout<<"\033[0m";
            }
            
            

            if((i+1) %3 ==0 ){
                printVerticalPartition();
                cout<<"\n";
                printEmptyHorVerPartition();
                
                if(i!=8)
                    printHorizontalPartition();
                else
                    printHorizontalBoundary();
             
            }
    }
    // cout<<"\033[0m";
}
void printHorizontalBoundary(){
    cout << "\033[1;31m";//red lines
    cout<<"-------------------------------"<<endl;
    cout<<"\033[0m";
}
void printHorizontalPartition(){
    cout << "\033[1;31m";//red lines
    cout<<"----------+---------+----------"<<endl;
    cout<<"\033[0m";
}
void printVerticalPartition(){
    cout << "\033[1;31m";//red lines
    cout<<"|    ";
    cout<<"\033[0m";
}
void printEmptyHorVerPartition(){
    cout << "\033[1;31m";//red lines
    cout<<"|         |         |         |\n";
    cout<<"\033[0m";
}
bool checkWinner(TicTacToe *players){
    int currPlayer;
        if(players[0].isCurrentPlayer()){
            currPlayer = 1;
        }
        else 
            currPlayer = 2;
        

    int horizontalScore = checkHorizontal(currPlayer);
    if (horizontal == 3){
        winnerId = currPlayer;
        return true;
    }
    
    int verticalScore = checkVertical(currPlayer);
    if (vertical == 3){
        winnerId = currPlayer;
        return true;
    }
    
    int diagonalScore = checkDiagonal(currPlayer);
    if (diagonal == 3){
        winnerId = currPlayer;
        return true;
    }
        
}
int checkHorizontal(int currPlayer){
    int score = 0;
    for(int i = 0 ; i < 3; i++){
        if(scoreCard[i][0] == currPlayer && scoreCard[i][1] == currPlayer && scoreCard[i][2] == currPlayer){
            score = 3;
            return score;
        }
    }
}
int checkVertical(int currPlayer){
    int score = 0;
    for(int i = 0 ; i < 3; i++){
        if(scoreCard[0][i] == currPlayer && scoreCard[0][i] == currPlayer && scoreCard[0][i] == currPlayer){
            score = 3;
            return score;
        }
    }
}
int checkDiagonal(int currPlayer){
    int score = 0;
   
    if(scoreCard[0][0] == currPlayer && scoreCard[1][1] == currPlayer && scoreCard[2][2] == currPlayer
        || scoreCard[2][0] == currPlayer && scoreCard[1][1] == currPlayer && scoreCard[2][0] == currPlayer){
        score = 3;
        return score;
    }
    
}
bool noPosition(TicTacToe *players){
    bool noPosition = true;
    for (int i = 0 ; i< 9 && noPosition == true ; i++){
        if(scoreCard[i] == 0)
            noPosition = false;
    }
    return noPosition;
}

bool isOccupied(int position){
    if(scoreCard[position-1]!=0)
        return true;

    return false;
}

int randomSlot(){
    vector <int> emptySlots;

    for(int i = 0; i < 9 ; i++){
        if(scoreCard[i]==0){
            emptySlots.push_back(i+1);
        }
    }
    srand(time(0));
    int slot = rand() % emptySlots.size();

    return emptySlots[slot];

}
void multiplayerGame(TicTacToe *players){
    cout<<"\n----Starting Multiplayer game----\n\n";
    string nameBuf;
    cout << "Enter Player Name 1: ";
    cin >> nameBuf;
    players[0].setPlayerName(nameBuf);
    cout << "Enter Player Name 2: ";
    cin >> nameBuf;
    players[1].setPlayerName(nameBuf);

    printBoard(players);
    bool winner = false;

    while (!winner && !noPosition(players)){

        for (int i = 0; i<2 && winner != true && !noPosition(players) ; i++){
            
            int val = getInput(players,i);

            while(isOccupied(val)){
                cout<<"Position already taken!!"<<endl;
                val = getInput(players,i);
            }

            scoreCard[val-1] = i+1;
            //call updateScoreCard here
            players[i].setCurrentPlayer(true);

            if(i==1){
                players[i-1].setCurrentPlayer(false);
            }
            else{
                players[i+1].setCurrentPlayer(false);
            }

            printBoard(players);
            winner = checkWinner(players);
       }

    }
    if (winnerId!=0)
    cout<<"\n\n------------------Player "<<players[winnerId-1].getPlayerName()
        <<" WON!!!------------------\n\n"<<endl;

    else if (noPosition(players))
        cout<<"\n\n------------------Nobody WON------------------\n\n"<<endl;


}
void singlePlayerEasy(TicTacToe *players){
    cout<<"\n----Single Player [Easy level]----\n\n";

    string nameBuf;
    cout << "Enter Player Name 1: ";
    cin >> nameBuf;
    players[0].setPlayerName(nameBuf);
    
    players[1].setPlayerName("Computer");
    cout << "Player 2 \"Computer\"\n\n";

    printBoard(players);
    bool winner = false;

    while (!winner && !noPosition(players)){

        for (int i = 0; i<2 && winner != true && !noPosition(players); i++){
            int val;

            if(i==0){//for our player
                
                val = getInput(players,i);

                while(isOccupied(val)){
                    cout<<"Position already taken!!"<<endl;
                    val = getInput(players,i);
                }
                
                players[i].setCurrentPlayer(true);
                players[i+1].setCurrentPlayer(false);
            }

            else if(i==1){//for computer
                val = randomSlot();
                cout<<"Player Computer deciding... ";
                //usleep(2000000 );
                loadingCursor();
                
                cout<<"\nPlayer Computer chose position "<<val<<endl;

                
                players[i].setCurrentPlayer(true);
                players[i-1].setCurrentPlayer(false);
            }
            scoreCard[val-1] = i+1;
            printBoard(players);
            winner = checkWinner(players);

        }

    }
    if (winnerId!=0)
        cout<<"\n\n------------------Player "<<players[winnerId-1].getPlayerName()
                <<" WON!!!------------------\n\n"<<endl;
        
    else if (noPosition(players))
        cout<<"\n\n------------------Nobody WON------------------\n\n"<<endl;
}

void singlePlayerDifficult(TicTacToe *players){

}
int gameOptions(){
    int val;
    cout<<"\n\nEnter 1 for two player game\n"
            "      2 for Single Player Easy Level\n"
            "      3 for Single Player Difficult Level\n"<<endl;
    cin >> val;
    return val;
}

void loadingCursor(){
    cout<<"-"<<flush;

    for(int i = 0; i < 3 ; i++){
        usleep(200000);
        cout << "\b\\" << flush;
        usleep(200000);
        cout << "\b|" << flush;
        usleep(200000);
        cout << "\b/" << flush;
        usleep(200000);
        cout << "\b-" << flush;
    }
   //cout << "\b" << flush;
    cout<< '\r';
    
}
bool checkPlayAgain(){
    string answer;
    cout<<"\n\nDo you want to play again? (yes/no): ";
    cin>>answer;
    if(answer=="y" || answer=="Y" || answer=="YES" || answer=="yes" )
        return true;
    else if (answer=="n" || answer=="N" || answer=="no" || answer=="NO" )
        return false;
    else{
        cout<<"(please Enter YES or NO)"<<endl;
        return checkPlayAgain();
    }
}
void resetGameData(){
    for(int i = 0 ; i < 9 ; i++)
        scoreCard[i] = 0;
}
void playGame(TicTacToe *players){
    gameType = gameOptions();

    switch(gameType){
        case 1: multiplayerGame(players); break;
        case 2: singlePlayerEasy(players); break;
        case 3: singlePlayerDifficult(players); break;
    }
}
void updateScoreCard(int pos, int playerId){
    int column = (pos-1)%3;//0,1,2
    int row = (pos-1)/3;//0,1,2
    //scoreCard[row][column] = playerId;
}
int getInput(TicTacToe *players, int playerId){
   int val;
   cout<<"Player"<<playerId+1<<" "<< players[playerId].getPlayerName()<<" input an empty position: ";
   cin >> val;
    
   while(cin.fail() || val > 9 || val < 1){
        cout << "Error! please enter an Integer value from 1-9" << endl;
        cin.clear();
        cin.ignore(256,'\n');
        val = getInput(players, playerId);
    }
   return val;
}
