#ifndef player_h
#define player_h

#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "game.h"

using namespace std;

class Player {
	int Player_ID;
	string Player_Name;
	vector<int> Player_Games_ID;
	vector<string> Player_ign;
	vector<Victory> Player_Victories;
	vector<int> Player_Friend;
	int Player_Point;


public:
	Player(string name, int id)
	:Player_Name(name), Player_ID(id), Player_Point(0) {}

	//Copy contructor
	Player(const Player& temp_player)
    {       
        Player_ID = temp_player.Player_ID;
        Player_Name = temp_player.Player_Name;
        Player_Point = temp_player.Player_Point;
        Player_ign =  temp_player.Player_ign;
        Player_Games_ID = temp_player.Player_Games_ID;
        Player_Victories = temp_player.Player_Victories;
        Player_Friend = temp_player.Player_Friend;
    }

    //Copy assignemnt operator
    Player& operator= (const Player& temp_player)
    {
        if (this != &temp_player) // prevent self-assignment
        {
          Player_ID = temp_player.Player_ID;
        	Player_Name = temp_player.Player_Name;
        	Player_Point = temp_player.Player_Point;
        	Player_ign =  temp_player.Player_ign;
        	Player_Games_ID = temp_player.Player_Games_ID;
        	Player_Victories = temp_player.Player_Victories;
        	Player_Friend = temp_player.Player_Friend;
        }
        return *this;
    }
    vector<int> get_player_games() const {
    	return Player_Games_ID;
    }
    string get_player_ign(int i) const {
    	return Player_ign[i];
    }
    vector<Victory> get_player_victories() const {
    	return Player_Victories;
    }
    string get_player_name() const {
    	return Player_Name;
    }
    vector<int> get_player_friend() const {
    	return Player_Friend;
    }
   	int get_player_ID() const {
   		return Player_ID;
   	}
   	int get_player_point() const {
   		return Player_Point;
   	}
   	void set_player_name(string name){
   		Player_Name = name;
   	}
   	void set_player_ID(int id){
   		Player_ID = id;
   	}
   	void add_game(int temp_game_id, string temp_ign){
   		Player_Games_ID.push_back(temp_game_id);
   		Player_ign.push_back(temp_ign);
   	}
   	void add_victory(Victory temp_victory){
   		Player_Victories.push_back(temp_victory);
   		Player_Point = Player_Point + temp_victory.get_Victory_Point();
   	}
   	void add_friend(int id){
   		Player_Friend.push_back(id);
   	}

};

#endif