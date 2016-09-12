#ifndef game_h
#define game_h

#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Victory {
	string Victory_Name;
	int Victory_Id;
	int Victory_Point;
	int Game_ID;
public:
	Victory(string name, int id, int game_id, int point)
	:Victory_Name(name), Victory_Id(id), Game_ID(game_id), Victory_Point(point) {}
	//Copy constructor
	Victory(const Victory& temp_victory)
    {       
        Victory_Id = temp_victory.Victory_Id;
        Victory_Name = temp_victory.Victory_Name;
        Victory_Point = temp_victory.Victory_Point;
        Game_ID =  temp_victory.Game_ID;
    }

    //Copy assignemnt operator
    Victory& operator= (const Victory& temp_victory)
    {
        if (this != &temp_victory) // prevent self-assignment
        {
          	Victory_Id = temp_victory.Victory_Id;
        Victory_Name = temp_victory.Victory_Name;
        Victory_Point = temp_victory.Victory_Point;
        Game_ID =  temp_victory.Game_ID;
        }
        return *this;
    }
	int get_Victory_Point() const {
		return Victory_Point;
	}
	string get_Victory_Name() const {
		return Victory_Name;
	}
	void set_Victory_Point(int point){
		Victory_Point = point;
	}
	void set_Victory_Name(string name){
		Victory_Name = name;
	}
	int get_Victory_ID() const {
		return Victory_Id;
	}
	int get_Game_ID() const {
    	return Game_ID;
    }
    void set_Game_ID(int id){
    	Game_ID = id;
    }
};

class Game {
	int Game_ID;
	string Game_Name;
	map<int, Victory> Game_Victories;
	int number_of_Victories;

public:
	Game(string name, int id)
	:Game_Name(name), Game_ID(id), number_of_Victories(0) {}

	//Copy constructor
	Game(const Game& temp_game)
    {       
        Game_ID = temp_game.Game_ID;
        Game_Name = temp_game.Game_Name;
        Game_Victories = temp_game.Game_Victories;
        number_of_Victories =  temp_game.number_of_Victories;
    }

    //Copy assignemnt operator
    Game& operator= (const Game& temp_game)
    {
        if (this != &temp_game) // prevent self-assignment
        {
          	Game_ID = temp_game.Game_ID;
        	Game_Name = temp_game.Game_Name;
        	Game_Victories = temp_game.Game_Victories;
        	number_of_Victories =  temp_game.number_of_Victories;
        }
        return *this;
    }

    int get_Game_ID(){
    	return Game_ID;
    }
    string get_Game_Name(){
    	return Game_Name;
    }
    Victory get_Victory(int id){
    	return Game_Victories.at(id);
    }
    map<int, Victory> get_Game_Victories(){
    	return Game_Victories;
    }
    int get_number_Victories(){
    	return number_of_Victories;
    }
    void set_Game_ID(int id){
    	Game_ID = id;
    }
    void set_Game_Name(string name){
    	Game_Name = name;
    }
    void add_Game_Victory(Victory temp_victory){
    	Game_Victories.insert(make_pair(temp_victory.get_Victory_ID(), temp_victory));
    	++number_of_Victories;
    }
};

#endif
