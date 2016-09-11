#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <map>
#include "game.h"
#include "player.h"

using namespace std;

void Add_Game(istringstream& iss, map <int, Game>& gamelist){
    int game_id;
    string game_name;
    string temp;    
    iss >> game_id;
    getline(iss, temp, '"');
    getline(iss, game_name, '"');
    cout << game_id << endl;
    cout << game_name << endl;
    Game temp_game(game_name, game_id);
    // gamelist[game_id] = temp_game;
    gamelist.insert(make_pair(game_id, temp_game));
}

void Add_Player(istringstream& iss, map <int, Player>& playerlist){
    int player_id;
    string player_name;
    string temp;    
    iss >> player_id;
    getline(iss, temp, '"');
    getline(iss, player_name, '"');
    cout << player_id << endl;
    cout << player_name << endl;
    Player temp_player(player_name, player_id);
    // playerlist[player_id] = temp_player;    
    playerlist.insert(make_pair(player_id, temp_player));
}

void Add_Victory(istringstream& iss, map <int, Game>& gamelist){
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
    Victory temp_victory(victory_name, victory_id, game_id, victory_point);
    //gamelist[game_id].add_Game_Victory(temp_victory);
    gamelist.at(game_id).add_Game_Victory(temp_victory);
    
}

void Plays(istringstream& iss, map <int, Player>& playerlist){
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
    playerlist.at(player_id).add_game(game_id, player_ign);
}

void Add_Friends(istringstream& iss, map <int, Player>& playerlist){
    int player_id_1, player_id_2;
    iss >> player_id_1;
    iss >> player_id_2;
    cout << player_id_1 << endl;
    cout << player_id_2 << endl;
    playerlist.at(player_id_1).add_friend(player_id_2);
    playerlist.at(player_id_2).add_friend(player_id_1);
}

void Win_Victory(istringstream& iss, map <int, Game>& gamelist, map <int, Player>& playerlist){
    int player_id, game_id, victory_id;
    iss >> player_id;
    iss >> game_id;
    iss >> victory_id;
    cout << player_id << endl;
    cout << game_id << endl;
    cout << victory_id << endl;
    playerlist.at(player_id).add_victory(gamelist.at(game_id).get_Victory(victory_id));
}

void Friends_Who_Play(istringstream& iss, map <int, Player>& playerlist){
    int player_id, game_id;
    iss >> player_id;
    iss >> game_id;
    cout << player_id << endl;
    cout << game_id << endl;
}

void Compare_Players(istringstream& iss, map <int, Player>& playerlist){
    int player_id_1, player_id_2, game_id;
    iss >> player_id_1;
    iss >> player_id_2;
    iss >> game_id;
    cout << player_id_1 << endl;
    cout << player_id_2 << endl;
    cout << game_id << endl;
}
void Summarize_Player(istringstream& iss, map <int, Player>& playerlist){
    int player_id;
    iss >> player_id;
    cout << player_id << endl;
}
void Summarize_Game(istringstream& iss, map <int, Game>& gamelist, map <int, Player>& playerlist){
    int game_id;
    iss >> game_id;
    cout << game_id << endl;
}
void Summarize_Victory(istringstream& iss, map <int, Game>& gamelist, map <int, Player>& playerlist){
    int game_id, victory_id;
    iss >> game_id;
    iss >> victory_id;
    cout << game_id << endl;
    cout << victory_id << endl;
}
void Victory_Ranking(map <int, Player>& playerlist){
}

void parser(istream& cin, map <int, Player>& playerlist, map <int, Game>& gamelist){
    string command_line;
    getline(cin, command_line);
    cout << command_line << endl;
    istringstream iss(command_line);
    string command_code;
    iss >> command_code;
    cout << command_code << endl;

    if (command_code == "AddGame"){
        Add_Game(iss, gamelist);
    } 
    else if (command_code == "AddVictory"){
        Add_Victory(iss, gamelist);
    }
    else if (command_code == "AddPlayer"){
        Add_Player(iss, playerlist);
    }
    else if (command_code == "Plays"){
        Plays(iss, playerlist);
    }
    else if (command_code == "AddFriends"){
        Add_Friends(iss, playerlist);
    }
    else if (command_code == "WinVictory"){
        Win_Victory(iss, gamelist, playerlist);
    }
    else if (command_code == "FriendsWhoPlay"){
        Friends_Who_Play(iss, playerlist);
    }
    else if (command_code == "ComparePlayers"){
        Compare_Players(iss, playerlist);
    }
    else if (command_code == "SummarizePlayer"){
        Summarize_Player(iss, playerlist);
    }
    else if (command_code == "SummarizeGame"){
        Summarize_Game(iss, gamelist, playerlist);
    }
    else if (command_code == "SummarizeVictory"){
        Summarize_Victory(iss, gamelist, playerlist);
    }
    else if (command_code == "VictoryRanking"){
        Victory_Ranking(playerlist);
    }
    else if (command_code == ""){

    } else {
        cout << "Wrong command! Please input again.\n";
    }
}

int main()
{
	string command_line;
    map <int, Player> playerlist;
    map <int, Game> gamelist;
//    vector<Player> playerlist;
//    vector<Game> gamelist;
    while (cin)
    {
        parser(cin, playerlist, gamelist);
    }
    cout << "Please input command: \n";
    cin >> command_line;
    while (cin)
    {
        parser(cin, playerlist, gamelist);
    }
	return 0;
}