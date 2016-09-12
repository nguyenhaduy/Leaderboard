#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <iomanip>
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
    Game temp_game(game_name, game_id);
    gamelist.insert(make_pair(game_id, temp_game));
}

void Add_Player(istringstream& iss, map <int, Player>& playerlist){
    int player_id;
    string player_name;
    string temp;    
    iss >> player_id;
    getline(iss, temp, '"');
    getline(iss, player_name, '"');
    Player temp_player(player_name, player_id);
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
    Victory temp_victory(victory_name, victory_id, game_id, victory_point);
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
    playerlist.at(player_id).add_victory(gamelist.at(game_id).get_Victory(victory_id));
}

void Friends_Who_Play(istringstream& iss, map <int, Player>& playerlist){
    int player_id, game_id;
    iss >> player_id;
    iss >> game_id;
    cout << player_id << endl;
    cout << game_id << endl;
    cout << "Friends Who Play this game are :" << endl;
    Player temp_player(playerlist.at(player_id));
    vector<int> friend_id = temp_player.get_player_friend();
    for (int i = 0; i < friend_id.size(); ++i){
        Player temp_friend(playerlist.at(friend_id[i]));
        vector<int> games_played = temp_friend.get_player_games();
        for (int j = 0; j < games_played.size(); ++j){
            if (game_id == games_played[j])
                cout << playerlist.at(i).get_player_name()<<endl;
        }
    }
    // temp_player = playerlist.at(player_id);
    // for (auto const& x : playerlist)
    // {

    //     std::cout << x.first  // Player_id (key)
    //               << ':' 
    //               << x.second // string's value 
    //               << endl ;
    // }
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
void Summarize_Player(istringstream& iss, map <int, Game>& gamelist, map <int, Player>& playerlist){
    int player_id;
    iss >> player_id;
    Player temp_player(playerlist.at(player_id));
    vector<int> friend_id = temp_player.get_player_friend();
    vector<int> games_played = temp_player.get_player_games();
    vector<Victory> player_victories =  temp_player.get_player_victories();

    cout << "Player: " << temp_player.get_player_name() << endl;
    cout << "Total Gamerscore: " << temp_player. get_player_point() << "pts\n\n";
    cout << endl << "\tGane \t\tVictories     Gamerscore \tIGN" << endl
         <<"--------------------------------------------------------------------------"<< endl;
    for (int i = 0; i < games_played.size(); ++i){
        int num_victory = 0;
        int game_point = 0;
        for (int j = 0; j < player_victories.size(); ++j) {            
            if (player_victories[j].get_Game_ID() == games_played[i]){
                ++num_victory;
                game_point = game_point + player_victories[j].get_Victory_Point();
            }
        }
        cout << i+1 <<". " << setw(23) << left
             << gamelist.at(games_played[i]).get_Game_Name() 
             << num_victory << '/' << setw(10) << left 
             << gamelist.at(games_played[i]).get_number_Victories()
             << setw(5) << left << game_point << setw(10) << left << " pts" 
             << setw(25) << left << temp_player.get_player_ign(i)
             << endl;
    }
    cout << endl << "\tFriend \t\t\t  Gamerscore" << endl
         << "--------------------------------------------------"<< endl;
    for (int i = 0; i < friend_id.size(); ++i){
        cout << i+1 <<". " << setw(32) << left
             << playerlist.at(friend_id[i]).get_player_name()
             << setw(5) << left << playerlist.at(friend_id[i]).get_player_point()
             << " pts" << endl;
        
    }
}

void Summarize_Game(istringstream& iss, map <int, Game>& gamelist, map <int, Player>& playerlist){
    int game_id;
    iss >> game_id;
    Game temp_game(gamelist.at(game_id));
    map <int, Victory> victorylist (temp_game.get_Game_Victories());
    map <int, int> victories_check;
    cout << "\nAll players who play this game are: \n"    
         << "--------------------------------------------------"<< endl;
    for (auto const& curr_player : playerlist) {
        vector <int> games_played;
        games_played = curr_player.second.get_player_games();
        for (int i = 0; i < games_played.size(); ++i){
            if (game_id == games_played[i]){
                cout << curr_player.second.get_player_name() << endl;
                vector<Victory> tmp_vic_list = curr_player.second.get_player_victories();
                for (int j = 0; j < tmp_vic_list.size(); ++j){
                    for (auto const& curr_victory : victorylist) {
                        if ((curr_victory.second.get_Game_ID() == tmp_vic_list[j].get_Game_ID())
                            &&(curr_victory.second.get_Victory_ID() == tmp_vic_list[j].get_Victory_ID())){
                            ++victories_check [tmp_vic_list[j].get_Victory_ID()];
                        }
                    }
                }
            }

        }
    }
    cout << "\nNumber of times each Victory have been accomplished.\n"
         << "--------------------------------------------------" << endl;
    for (auto const& curr_victory : victorylist){
        cout << "Victory \"" << curr_victory.second.get_Victory_Name() << "\" has been accomplished " 
             << victories_check[curr_victory.second.get_Victory_ID()] << " times. \n";
    }
}

void Summarize_Victory(istringstream& iss, map <int, Game>& gamelist, map <int, Player>& playerlist){
    int game_id, victory_id;
    iss >> game_id;
    iss >> victory_id;
    cout << game_id << endl;
    cout << victory_id << endl;    
    Game temp_game(gamelist.at(game_id));
    
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
    // cout << "Calling " << command_code << " function!" << endl;

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
        Summarize_Player(iss, gamelist, playerlist);
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
    cout << "Please input command: \n";
    while (cin)
    {
        parser(cin, playerlist, gamelist);
    }
	return 0;
}