#include "Game.hpp"
#include "iostream"
//#include "../include/Reactions.hpp"
#include "../include/Minmax.hpp"
#include "../include/Minmax_tweak.hpp"
#include "../include/Basic.hpp"
#include "../include/Human.hpp"



//const std::string ipnao = "128.39.75.111";
/*const std::string ipnao = "127.0.0.1";
AL::ALTextToSpeechProxy tts(ipnao, 9559);*/

//We ask the color for player 1
Player ask_p1_color(){
	std::cout << "Pick color for player 1. Red (R) or Green (G) ?" << std::endl;
	char d;
	std::cin >> d;
	while (d != 'G' && d != 'g' && d != 'r' && d != 'R') {
		std::cout << "Incorrect input" << std::endl;
		std::cin >> d;
	}
	if (d == 'G' || d == 'g'){
		return GREEN;
	}
	else return RED;
}

//We ask who starts the game
Player ask_starter(){
	std::cout << "Who starts ? Red (R) or Green (G) ?" << std::endl;
	char c;
	std::cin >> c;
	while (c != 'G' && c != 'g' && c != 'r' && c != 'R') {
		std::cout << "Incorrect input" << std::endl;
		std::cin >> c;
	}
	if (c == 'G' || c == 'g') return GREEN;
	else return RED;
}

int main() {
	//Choose AI here.
	Player first = ask_p1_color();
	Player_Abs* P1 = new Minmax(first, 4);
	//Player_Abs* P2 = new Human(opposite_player(first));
	Player_Abs* P2 = new Minmax_tweak(opposite_player(first), 5);
	//Initialize the game, the human picked a color and who starts.
	srand(time(NULL));
 
	Game A(ask_starter());
  	/*if (Starter == Human) human_start(tts);
	else nao_start(tts);*/

	std::cout << A << std::endl;

	//After every turn, we check if the game is over. If it's not, we check if it's P1 turn or P2 turn.
	while (!(A.is_over())) {
		if (A.get_turn() == P1->get_color()) {    
			Move m = P1->play(A);
			A.apply(m);
    	}
		else {    
			Move m = P2->play(A);
			A.apply(m);
			//if (!A.is_over()) after_nao_turn(tts);
		}
		std::cout << A << std::endl;
	}
	Player Result = A.who_win();
	/*if (Result == Human) nao_lose(tts);
	else if (Result == NO_ONE) nao_draw(tts);
	else nao_win(tts);*/
	std::cout << "And the winner is..." << player_name(Result) << "!!!" << std::endl;
}
