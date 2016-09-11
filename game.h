#ifndef game_hpp
#define game_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Victory {
	string Victory_Name;
	int Victory_Point;
public:
	int get_Victory_Point();
	string get_Victory_Name();
	void set_Victory_Point();
	void set_Victory_Name();

};

class Game {
	int Game_ID;
	string Game_Name;
	vector<Victory> Game_Victories;


public:
    int get_Game_ID();
    // display the graph
    string get_Game_Name();
    void set_Game_ID();
    void set_Game_Name();
};

#endif /* game_hpp */
