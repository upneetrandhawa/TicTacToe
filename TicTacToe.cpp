#include <unistd.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <unistd.h>

using namespace std;

int winnerId = 0;
int gameType;

int scoreCard[9] = {0};

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
bool checkHorizontal(int playerId, int position);
bool checkVertical(int playerId, int position);
bool checkDiagonal(int playerId, int position);
bool noPosition(TicTacToe *players);
bool isOccupied(int position);
int randomSlot();
void multiplayerGame(TicTacToe *players);
void singlePlayerEasy(TicTacToe *players);
void singlePlayerDifficult(TicTacToe *players);
int gameOptions();
void loadingCursor();


int main(){
    cout<<"------------------TIC TAC TOE------------------"
            <<"\n\n"<<endl;

    TicTacToe *players = new TicTacToe[2];

    gameType = gameOptions();

    switch(gameType){
        case 1: multiplayerGame(players); 
        case 2: singlePlayerEasy(players);
        case 3: singlePlayerDifficult(players);
    }




    
    

return 1;
}
bool checkWinner(TicTacToe *players){

    int currPlayer;
        if(players[0].isCurrentPlayer()){
            currPlayer = 1;
        }
        else 
            currPlayer = 2;
        

    for (int pos = 0 ; pos < 9 ; pos++){
        
        if (scoreCard[pos] == currPlayer) {
        

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

    }
    
    return false;

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

bool checkHorizontal(int playerId, int position){

    

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
    return false;

}

bool checkVertical(int playerId, int position){
   

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
    return false;
}

bool checkDiagonal(int playerId, int position){
    

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
// |         |         |         |
// |    1    |    2    |    3    |  
// |         |         |         |
// ----------+---------+----------
// |         |         |         |
// |    4    |    5    |    6    |
// |         |         |         |
// ----------+---------+----------
// |         |         |         |
// |    7    |    8    |    9    |
// |         |         |         |
// ----------+---------+----------
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
            int val;
            cout<<"Player"<<i+1<<" "<< players[i].getPlayerName()<<" input an empty position: ";
            cin >> val;

            while(isOccupied(val)){
                cout<<"Position already taken!!"<<endl;
                cout<<"Player"<<i+1<<" "<< players[i].getPlayerName()<<" input an empty position: ";
                cin >> val;
            }

            scoreCard[val-1] = i+1;

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
                
                cout<<"Player"<<i+1<<" "<< players[i].getPlayerName()<<" input an empty position: ";
                cin >> val;

                while(isOccupied(val)){
                    cout<<"Position already taken!!"<<endl;
                    cout<<"Player"<<i+1<<" "<< players[i].getPlayerName()<<" input an empty position: ";
                    cin >> val;
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

// void score(){
//     int maxScore = 0;
//     int maxScoreSlot = randomSlot();

//     vector <int> emptySlots;

//     for(int i = 0; i < 9 ; i++){
//         if(scoreCard[i]==0){
//             emptySlots.push_back(i+1);
//         }
//     }
    


//     for (int i = 0 ; i < emptySlots.size() ; i++){

//         int scoreCardClone[9] = {0};
//         for(int j = 0 ; j < 9 ; j++)
//           scoreCardClone[j] = scoreCard[j];

//         scoreCardClone[emptySlots[i]-1] = 1;

//         int scoreHorizontal(scoreCardClone,emptySlots[i]-1);

//     }
// }

// int scoreHorizontal(int scoreCardClone, int current){
//     int maxHorScore = 1;


//     int location = (current+1)%3;

//     if (location == 1) {
//         if (scoreCardClone[position+1] == playerId){
//             if (scoreCardClone[position+2] == playerId){
//                 maxHorScore = 3;
//             }
//             else 
//                 maxHorScore = 2;
//         }
//     }

//     else if (location == 2) {
//         if (scoreCardClone[position+1] == playerId){
//             if(scoreCardClone[position -1] == playerId){
//                 maxHorScore = 3;
//             }
//             else
//                 maxHorScore = 2;
//         }

//     }

//     else if (location == 0){

//         if (scoreCardClone[position-1] == playerId){
//             if(scoreCardClone[position -2] == playerId){
//                 maxHorScore = 3;
//             }
//             else
//                 maxHorScore = 2;
//         }
//     }

//     return maxHorScore;
    
// }

// int scoreVertical(int scoreCardClone, int current){
//    int maxVerScore = 1;

//     int location = (current+1)%3;

//     if (location == 1) {
//         if (scoreCardClone[position+3] == playerId){
//             if (scoreCardClone[position+6] == playerId){
//                 maxVerScore = 3;
//             }
//             else 
//                 maxVerScore = 2;
//         }
//     }

//     else if (location == 2) {
//         if (scoreCardClone[position+3] == playerId){
//             if(scoreCardClone[position -3] == playerId){
//                 maxVerScore = 3;
//             }
//             else
//                 maxVerScore = 2;
//         }
//     }

//     else if (location == 0){

//         if (scoreCardClone[position-3] == playerId){
//             if(scoreCardClone[position -3] == playerId){
//                 maxVerScore = 3;
//             }
//             else
//                 maxVerScore = 2;
//         }
//     }
//     return maxVerScore;
// }

// int scoreDiagonal(int scoreCardClone, int current){
    
//     int maxDiaScore = 1;
//     //temporary hardcoded solution
//     if(current == 0){
//         if(scoreCardClone[position+4] == playerId){
//             if(scoreCardClone[position+8] == playerId)
//                 maxDiaScore = 3;
//             else
//                 maxDiaScore = 2;
//         }
        
//     }
//     else if(position == 2){
//         if(scoreCardClone[position+2] == playerId){
//             if(scoreCardClone[position+4] == playerId)
//                 maxDiaScore = 3;
//             else
//                 maxDiaScore = 2;
//         }
        
//     }
//     else if(position == 4){
//         if(scoreCardClone[position+4] == playerId){
//             if(scoreCardClone[position-4] == playerId)
//                 maxDiaScore = 3;
//             else
//                 maxDiaScore = 2;
//         }
        
//     }
//     else if(position == 6){
//         if(scoreCardClone[position-2] == playerId){
//             if(scoreCardClone[position-4] == playerId)
//                 maxDiaScore = 3;
//             else
//                 maxDiaScore = 2;
//         }
        
//     }
//     else if(position == 8){
//         if(scoreCardClone[position-4] == playerId){
//             if(scoreCardClone[position-8] == playerId)
//                 maxDiaScore = 3;
//             else
//                 maxDiaScore = 2;
//         }
       
//     }
//     return maxDiaScore;
// } 

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
