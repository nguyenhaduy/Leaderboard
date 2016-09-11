#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

void Add_Game(istringstream& iss){
    int game_id;
    string game_name;
    string temp;    
    iss >> game_id;
    getline(iss, temp, '"');
    getline(iss, game_name, '"');
    cout << game_id << endl;
    cout << game_name << endl;
}

void Add_Player(istringstream& iss){
    int player_id;
    string player_name;
    string temp;    
    iss >> player_id;
    getline(iss, temp, '"');
    getline(iss, player_name, '"');
    cout << player_id << endl;
    cout << player_name << endl;
}

void Add_Victory(istringstream& iss){
	int game_id, victory_id, victory_point;
    string victory_name;
    string temp;
    iss >> game_id;    
    iss >> victory_id;
    getline(iss, temp, '"');
    getline(iss, victory_name, '"');
    iss >> victory_point;
    cout << game_id << endl;    
    cout << victory_id << endl;
    cout << victory_name << endl;
    cout << victory_point << endl;
}

void Plays(istringstream& iss){
    int player_id, game_id;
    string player_ign;
    string temp;    
    iss >> player_id;
    iss >> game_id;
    getline(iss, temp, '"');
    getline(iss, player_ign, '"');
    cout << player_id << endl;
    cout << game_id << endl;
    cout << player_ign << endl;
	
}

void Add_Friends(istringstream& iss){
    int player_id_1, player_id_2;
    iss >> player_id_1;
    iss >> player_id_2;
    cout << player_id_1 << endl;
    cout << player_id_2 << endl;
}

void Win_Victory(istringstream& iss){
    int player_id, game_id, victory_id;
    iss >> player_id;
    iss >> game_id;
    iss >> victory_id;
    cout << player_id << endl;
    cout << game_id << endl;
    cout << victory_id << endl;
}

void Friends_Who_Play(istringstream& iss){
    int player_id, game_id;
    iss >> player_id;
    iss >> game_id;
    cout << player_id << endl;
    cout << game_id << endl;
}

void Compare_Players(istringstream& iss){
    int player_id_1, player_id_2, game_id;
    iss >> player_id_1;
    iss >> player_id_2;
    iss >> game_id;
    cout << player_id_1 << endl;
    cout << player_id_2 << endl;
    cout << game_id << endl;
}
void Summarize_Player(istringstream& iss){
    int player_id;
    iss >> player_id;
    cout << player_id << endl;
}
void Summarize_Game(istringstream& iss){
    int game_id;
    iss >> game_id;
    cout << game_id << endl;
}
void Summarize_Victory(istringstream& iss){
    int game_id, victory_id;
    iss >> game_id;
    iss >> victory_id;
    cout << game_id << endl;
    cout << victory_id << endl;
}
void Victory_Ranking(){
}

void parser(istream& cin){
    string command_line;
    getline(cin, command_line);
    cout << command_line << endl;
    istringstream iss(command_line);
    string command_code;
    iss >> command_code;
    cout << command_code << endl;

    if (command_code == "AddGame"){
        Add_Game(iss);
    } 
    else if (command_code == "AddVictory"){
        Add_Victory(iss);
    }
    else if (command_code == "AddPlayer"){
        Add_Player(iss);
    }
    else if (command_code == "Plays"){
        Plays(iss);
    }
    else if (command_code == "AddFriends"){
        Add_Friends(iss);
    }
    else if (command_code == "WinVictory"){
        Win_Victory(iss);
    }
    else if (command_code == "FriendsWhoPlay"){
        Friends_Who_Play(iss);
    }
    else if (command_code == "ComparePlayers"){
        Compare_Players(iss);
    }
    else if (command_code == "SummarizePlayer"){
        Summarize_Player(iss);
    }
    else if (command_code == "SummarizeGame"){
        Summarize_Game(iss);
    }
    else if (command_code == "SummarizeVictory"){
        Summarize_Victory(iss);
    }
    else if (command_code == "VictoryRanking"){
        Victory_Ranking();
    }
    else if (command_code == ""){

    } else {
        cout << "Wrong command! Please input again.\n";
    }
}

int main(int argc, char ** argv)
{
	// ifstream inFile ("command.txt");
 //    if (!inFile.good()) 
 //        return 1;

	string command_line;
	// while (inFile)
	// {
 //    	getline(inFile, command_line);
 //    	cout << command_line << endl;
 //        istringstream iss(command_line);
 //        string command_code;
 //        iss >> command_code;
 //        cout << command_code << endl;
    while (cin)
    {
        parser(cin);
    }
    cout << "Please input command: \n";
    cin >> command_line;
    while (cin)
    {
        parser(cin);
    }

	// inFile.close();

	return 0;


}