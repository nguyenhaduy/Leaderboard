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

//Add game to the database
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

//Add player to the database
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

//Add Victory to the game denoted by <Game ID>
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

//Add entry for player playing a specific game
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

//Makes players 1 & 2 friends
void Add_Friends(istringstream& iss, map <int, Player>& playerlist){
    int player_id_1, player_id_2;
    iss >> player_id_1;
    iss >> player_id_2;
    cout << player_id_1 << endl;
    cout << player_id_2 << endl;
    playerlist.at(player_id_1).add_friend(player_id_2);
    playerlist.at(player_id_2).add_friend(player_id_1);
}

//Adds Victory indicated to <Player ID>'s record
void Win_Victory(istringstream& iss, map <int, Game>& gamelist, map <int, Player>& playerlist){
    int player_id, game_id, victory_id;
    iss >> player_id;
    iss >> game_id;
    iss >> victory_id;
    playerlist.at(player_id).add_victory(gamelist.at(game_id).get_Victory(victory_id));
}

//Report which of player's friends play the specified game
void Friends_Who_Play(istringstream& iss, map <int, Game>& gamelist, map <int, Player>& playerlist){
    int player_id, game_id;
    iss >> player_id;
    iss >> game_id;
    Player temp_player(playerlist.at(player_id));
    vector<int> friend_id = temp_player.get_player_friend();    
    cout << "\nFriends of \"" << temp_player.get_player_name()<< "\" who play \"" 
         <<gamelist.at(game_id).get_Game_Name() << "\"  are :" << endl
         << "-----------------------------------------------\n";
    //Loop through vector of friends and compare the game they play with this game_id
    for (int i = 0; i < friend_id.size(); ++i){
        Player temp_friend(playerlist.at(friend_id[i]));
        vector<int> games_played = temp_friend.get_player_games();
        for (int j = 0; j < games_played.size(); ++j){
            if (game_id == games_played[j])
                cout << temp_friend.get_player_name()<<endl;
        }
    }
}

//Print report comparing player 1 and player 2's Victory records and total Victory scores for the given game
void Compare_Players(istringstream& iss, map <int, Game>& gamelist, map <int, Player>& playerlist){
    int player_id_1, player_id_2, game_id;
    iss >> player_id_1;
    iss >> player_id_2;
    iss >> game_id;
    Player player_1(playerlist.at(player_id_1));
    Player player_2(playerlist.at(player_id_2));
    vector<Victory> player1_victories (player_1.get_player_victories());
    vector<Victory> player2_victories (player_2.get_player_victories());
    int player1_score = 0;
    int player2_score = 0;
    //Check Player 1 and calculate player 1's total score
    cout << "\nPlayer \"" << player_1.get_player_name() << "\" status for the game \""
         << gamelist.at(game_id).get_Game_Name() << "\" is: \n"
         << "---------------------------------------------------------------------\n";
    for (int i = 0; i < player1_victories.size(); ++i){
        if (player1_victories[i].get_Game_ID() == game_id){
            cout << setw(30) << left << player1_victories[i].get_Victory_Name()
                 << setw(3) << left <<player1_victories[i].get_Victory_Point()
                 << " pts" << endl;
            player1_score = player1_score +player1_victories[i].get_Victory_Point();
        }
    }
    cout << "---------------------------------------------------------------------\n"
         << setw(30) << left << "Total score is: " << setw(3) <<  player1_score << " pts" << endl; 
    
    //Check Player 2 and calculate player 2's total score
    cout << "\n\nPlayer \"" << player_2.get_player_name() << "\" status for the game \""
         << gamelist.at(game_id).get_Game_Name() << "\" is: \n"
         << "---------------------------------------------------------------------\n";
    for (int i = 0; i < player2_victories.size(); ++i){
        if (player2_victories[i].get_Game_ID() == game_id){
            cout << setw(30) << left << player2_victories[i].get_Victory_Name()
                 << setw(3) << left <<player2_victories[i].get_Victory_Point()
                 << " pts" << endl;
            player2_score = player2_score +player2_victories[i].get_Victory_Point();
        }
    }    
    cout << "---------------------------------------------------------------------\n"
         << setw(30) << left << "Total score is: " << setw(3) <<  player2_score << " pts" << endl; 
}

//Print record of all of player's friends, games the player plays, and gamer point totals.
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

    //Loop through the games that player plays
    for (int i = 0; i < games_played.size(); ++i){
        int num_victory = 0;
        int game_point = 0;
        //Loop through the victories of that the player achieved
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

//Print a record of all players who play the specified game and the number of times each of its victories have been accomplished.
void Summarize_Game(istringstream& iss, map <int, Game>& gamelist, map <int, Player>& playerlist){
    int game_id;
    iss >> game_id;
    Game temp_game(gamelist.at(game_id));
    map <int, Victory> victorylist (temp_game.get_Game_Victories());
    map <int, int> victories_check;
    cout << "\nAll players who play this game are: \n"    
         << "--------------------------------------------------"<< endl;
    //Loop through the whole map of players
    for (auto const& curr_player : playerlist) {
        vector <int> games_played;
        games_played = curr_player.second.get_player_games();
        //Loop through the games that player plays
        for (int i = 0; i < games_played.size(); ++i){
            //check it the games is the same
            if (game_id == games_played[i]){
                cout << curr_player.second.get_player_name() << endl;
                vector<Victory> tmp_vic_list = curr_player.second.get_player_victories();
                //Loop through the achieved victories 
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

//Print a list of all players who have achieved a Victory, and the percentage of players who play that game who have the Victory.
void Summarize_Victory(istringstream& iss, map <int, Game>& gamelist, map <int, Player>& playerlist){
    int game_id, victory_id;
    iss >> game_id;
    iss >> victory_id;    
    Game temp_game(gamelist.at(game_id));    
    map <int, Victory> victorylist (temp_game.get_Game_Victories());
    int player_got_victory = 0;
    int player_play_game = 0;
    double percentage;
    cout << "\nAll players who have achieved this victory are: \n"    
         << "---------------------------------------------------------------------"<< endl;
    //Loop through the whole map of players
    for (auto const& curr_player : playerlist) {
        vector <int> games_played;
        games_played = curr_player.second.get_player_games();
        //Loop through the games that player plays
        for (int i = 0; i < games_played.size(); ++i){
            //check it the games is the same
            if (game_id == games_played[i]){
                ++player_play_game;
                vector<Victory> tmp_vic_list = curr_player.second.get_player_victories();
                //Loop through the achieved victories and check if it is the same with victory_id
                for (int j = 0; j < tmp_vic_list.size(); ++j){
                    if ((game_id == tmp_vic_list[j].get_Game_ID())
                        &&(victory_id == tmp_vic_list[j].get_Victory_ID())){
                        ++player_got_victory;
                        cout << curr_player.second.get_player_name() << endl;
                    }
                }
            }
        }
    }
    percentage = 100.00*((double)player_got_victory)/((double)player_play_game);
    cout << "---------------------------------------------------------------------"<< endl
         << "Percentage of player who play this game who have this Victory: " 
         << percentage << endl;
}

//Print a summary ranking all players by their total number of gamer points
void Victory_Ranking(map <int, Player>& playerlist){
    vector<int> ranking_id, ranking_point;
    //get the player total score and player ID to vectors prepare for sorting
    for (auto const& curr_player : playerlist) {
        ranking_point.push_back(curr_player.second.get_player_point());
        ranking_id.push_back(curr_player.second.get_player_ID());
    }
    //Do bubble short for two vector at the same times, using total score as the
    for (int i = 1; i < ranking_id.size(); ++i){
        for (int j = 0; j < ranking_id.size() - i; ++j){
            if (ranking_point[j+1] > ranking_point[j]) {
                int tmp = ranking_point[j]; // swap ranking_point[j] and ranking_point[j+1]
                ranking_point[j] = ranking_point[j+1];
                ranking_point[j+1] = tmp;
                int tmp2 = ranking_id[j];
                ranking_id[j] = ranking_id[j+1];
                ranking_id[j+1] = tmp2;
                }
        }
    }
    cout << "\nRanking all players by total number of gamer points.\n"
         << "\tPlayer \t\t         Total Point\n"
         << "--------------------------------------------------------" << endl;
    for (int i = 0; i < ranking_id.size(); ++i){
        cout << i+1 << ".  "
             << setw(30) << left << playerlist.at(ranking_id[i]).get_player_name()
             << setw (5) << left << ranking_point[i] << "pts" << endl;
    }
}


void parser(istream& cin, map <int, Player>& playerlist, map <int, Game>& gamelist){
    string command_line;
    getline(cin, command_line);
    cout << command_line << endl;
    istringstream iss(command_line);
    string command_code;
    iss >> command_code;

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
        Friends_Who_Play(iss, gamelist, playerlist);
    }
    else if (command_code == "ComparePlayers"){
        Compare_Players(iss, gamelist, playerlist);
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
    //Using map to make the database for player and game
    map <int, Player> playerlist;
    map <int, Game> gamelist;    
    cout << "Please input command: \n";
    while (cin)
    {
        parser(cin, playerlist, gamelist);
    }
	return 0;
}