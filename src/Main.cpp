#include "Game.hpp"
#include "iostream"
//#include "../include/Reactions.hpp"
#include "../include/Minmax.hpp"
#include "../include/Minmax_tweak.hpp"
#include "../include/Minmax_tweak_arthur.hpp"
#include "../include/Basic.hpp"
#include "../include/Human.hpp"
#include <fstream>
#include <typeinfo>



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
	Player_Abs* P1 = new Minmax_tweak_arthur(first, 1,3);
	//Player_Abs* P2 = new Human(opposite_player(first));
	Player_Abs* P2 = new Minmax_tweak_arthur(opposite_player(first), 3,5);
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

void test_AI_to_csv(Player_Abs* P1, Player_Abs* P2, std::string filename){
	
	std::ofstream myfile;
	myfile.open (filename.c_str(), std::ios_base::app);
	//myfile<<"Starter,P1name,P1weight,P1depth,P1color,P2name,P2weight,P2depth,P2color, Winner, TotalChips\n";
	
	//Basic games starting wherever the AI wants to, 3 times starting each.
	for (int i = 0; i<6; i++){	
		Game G;
		if (i%2 == 0){
		G = Game(P1->get_color());
		}
		else {
		G = Game(P2->get_color());
		}
		myfile<<player_name(G.get_turn())<<","<<P1->class_name()<<","<<P1->get_weight()<<","<<P1->get_depth()<<","<<player_name(P1->get_color())<<","<<P2->class_name()<<","<<P2->get_weight()<<","<<P2->get_depth()<<","<<player_name(P2->get_color())<<",";
		play_game_silent(P1,P2,G);
		Player winner = G.who_win();
		myfile<<player_name(winner)<<","<<G.total_chips()<<"\n";
	}
	//Games where we force the AI to start on each column in the game. 
	for (int i = 0; i<14; i++){	
		Game G;
		if (i%2 == 0){
		G = Game(P1->get_color());
		G.play(i/2);
		}
		else {
		G = Game(P2->get_color());
		G.play(i/2);
		}
		myfile<<player_name(G.get_turn())<<","<<P1->class_name()<<","<<P1->get_weight()<<","<<P1->get_depth()<<","<<player_name(P1->get_color())<<","<<P2->class_name()<<","<<P2->get_weight()<<","<<P2->get_depth()<<","<<player_name(P2->get_color())<<",";
		play_game_silent(P1,P2,G);
		Player winner = G.who_win();
		myfile<<player_name(winner)<<","<<G.total_chips()<<"\n";
	}
	
	//Games where we for the AI to start on a column and the other AI to start on the another one. 
		for (int i = 0; i<14; i++){	
			for (int j = 0; j< 7; j++){
			Game G;
			if (i%2 == 0){
			G = Game(P1->get_color());
			G.play(i/2);
			G.play(j);
			}
			else {
			G = Game(P2->get_color());
			G.play(i/2);
			G.play(j);
			}
			myfile<<player_name(G.get_turn())<<","<<P1->class_name()<<","<<P1->get_weight()<<","<<P1->get_depth()<<","<<player_name(P1->get_color())<<","<<P2->class_name()<<","<<P2->get_weight()<<","<<P2->get_depth()<<","<<player_name(P2->get_color())<<",";
			play_game_silent(P1,P2,G);
			Player winner = G.who_win();
			myfile<<player_name(winner)<<","<<G.total_chips()<<"\n";
		}
	}
	myfile.close();

}
int main(int argc, char* argv[]) {
	Game G;
	Player_Abs* P1 = new Minmax_tweak_arthur(GREEN, 5, atoi(argv[1]));
	Player_Abs* P2 = new Minmax_tweak_arthur(RED, 5, 3);
    play_game_silent(P1,P2,G);
    
	//play_game_verbose();
/*	 std::string filename = "MMTArthur5-3vsMMTArthurNoDepthDegressionx3.csv";
		std::ofstream myfile;
	myfile.open (filename.c_str(), std::ios_base::app);
	myfile<<"Starter,P1name,P1weight,P1depth,P1color,P2name,P2weight,P2depth,P2color, Winner, TotalChips\n";
	myfile.close();
	
	Player_Abs* P2 = new Minmax_tweak_arthur(RED, 5, 3);
	for (int depth = 1; depth<7; depth++){
		for(int weight = 1; weight<11; weight++){
	Player_Abs* P1 = new Minmax_tweak_arthur(GREEN, weight, depth);
	std::cout << "Doing weight-depth " << weight << "-" << depth << std::endl;
	test_AI_to_csv(P1,P2, filename);
	}
	}*/
	

	
	/*Game G(RED);
	play_game_silent(P1,P2,G);
	std::cout << G << std::endl;
	Player Result = G.who_win();
	std::cout << "And the winner is..." << player_name(Result) << "!!!" << std::endl;
	*/
	//test_AI();
	

}
