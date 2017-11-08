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

void play_game_verbose(){
//Choose AI here.
	Player first = ask_p1_color();
	Player_Abs* P1 = new Minmax(first, 5,5);
	//Player_Abs* P2 = new Human(opposite_player(first));
	Player_Abs* P2 = new Minmax(opposite_player(first), 7,4);
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

void play_game_silent(Player_Abs* P1, Player_Abs* P2, Game& G){

	while (!(G.is_over())) {
		if (G.get_turn() == P1->get_color()) {    
			Move m = P1->play(G);
			G.apply(m);
    	}
		else {    
			Move m = P2->play(G);
			G.apply(m);
		}
	}
}

void test_AI(){


	int red_wins = 0;
	int green_wins = 0;
	int draws = 0;
	
	//for(int j_depth = 3; j_depth <=7; j_depth++){
		for (int j_weight = 3;j_weight<=20;j_weight++){	
			Player_Abs* P1 = new Minmax(RED,j_weight,3);
			//for(int i_depth = 3; i_depth <=7; i_depth++){
				for (int i_weight = 3;i_weight<=20;i_weight++){	
					Player_Abs* P2 = new Minmax(GREEN,i_weight,3);
					Game G(RED);
					play_game_silent(P1,P2,G);
					Player winner = G.who_win();
					std::cout<<"R depth: " << "3" << " R Weight: "<< j_weight<<" G Depth: " << "3" << " G Weight: "<< i_weight << " Winner: "<< player_name(winner) << " Total moves: " << G.total_chips() << std::endl; 
					if (winner == RED) red_wins++;
					else if (winner == GREEN) green_wins++;
					else draws++;
				//}
			//}
		}
	}
	std::cout<<"Red wins: "<<red_wins<<" Green wins: "<<green_wins<<" Draws: "<< draws<< std::endl;
}

int main() {

	play_game_verbose();

	/*Player_Abs* P1 = new Minmax(RED, 5, 4);
	Player_Abs* P2 = new Minmax_tweak(GREEN, 5, 5);
	Game G(RED);
	play_game_silent(P1,P2,G);
	std::cout << G << std::endl;
	Player Result = G.who_win();
	std::cout << "And the winner is..." << player_name(Result) << "!!!" << std::endl;
	*/
	//test_AI();

}
