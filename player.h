#ifndef player_hpp
#define player_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>


#include "Vertex.hpp"

using namespace std;

class Player {
	int Player_ID;
	string Player_Name;
	vector<Game> Player_Games;
	vector<Victory> Player_Victories;


public:

    string get_player_name();
   	int get_player_ID();
   	void set_player_name();
   	void set_player_ID();
};

#endif /* Graph_hpp */