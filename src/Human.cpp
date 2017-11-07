#include "../include/Human.hpp"

Human::Human(Player p):Player_Abs(p){}

Human::~Human(){}

Move Human::play(Game G){
	int column;
	std::cout << "It's " << player_name(G.get_turn()) << " turn! Where do you want to play?(1-7)" << std::endl;
	while(true){
		std::cin >> column;
		Move m(column - 1, G.get_turn(), G);
	    if (m.is_valid() != OK){
		  	std::cout << "This movement is not valid. Try again!" << std::endl;
		}
		else return m;
	}
}
