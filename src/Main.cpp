#include <iostream>
#include <string>
#include <fstream>
#include <typeinfo>
#include "Game.hpp"
#include "Reactions.hpp"
#include "Minmax.hpp"
#include "Minmax_tweak.hpp"
#include "Minmax_tweak_arthur.hpp"
#include "Basic.hpp"
#include "Human.hpp"
#include <opencv2/opencv.hpp>
#include "Cv_c4_option_helper.hpp"
#include "Cv_c4_optim.hpp"





const std::string ipnao = "128.39.75.111";
AL::ALTextToSpeechProxy TTS(ipnao, 9559);

void config_run(Cv_c4_option_helper& cvh,  cv::VideoCapture vcap) {
  cv::Mat image;
  vcap.read(image);
  cvh.chose_blue(image);
  cvh.chose_red(image);
  cvh.chose_green(image);
  std::cout << cvh.cv.opt<<std::endl;
}

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

Game vision_to_game(std::vector<CV_BOARD_STATE> cv_game){
Game g;
for(int y = 0; y < 6 ;y++ )
    {
      for(int x = 0; x <7 ;x++ )
        {
          int v = cv_game[x+y*7];
          if (v == CV_RED) g.set(5-y,x,BS_RED);
          else if (v == CV_GREEN) g.set(5-y,x,BS_GREEN);
		}
    }
    return g;
}


void play_game_verbose(){
//Choose AI here.
	Player first = ask_p1_color();
	Player_Abs* P1 = new Human(first);
	//Player_Abs* P2 = new Human(opposite_player(first));
	Player_Abs* P2 = new Minmax_tweak_arthur(opposite_player(first), 5,5);
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
		//std::cout<<G<<std::endl;
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

void test_AI_to_csv_lite(Player_Abs* P1, Player_Abs* P2, std::string filename){
	std::ofstream myfile;
	myfile.open (filename.c_str(), std::ios_base::app);
	//myfile<<"Starter,P1name,P1weight,P1depth,P1color,P2name,P2weight,P2depth,P2color, Winner, TotalChips\n";
	
	//Basic games starting wherever the AI wants to, 1 time starting each.
	for (int i = 0; i<3; i++){	
		Game G;
		G = Game(P1->get_color());
		myfile<<player_name(G.get_turn())<<","<<P1->class_name()<<","<<P1->get_weight()<<","<<P1->get_depth()<<","<<player_name(P1->get_color())<<","<<P2->class_name()<<","<<P2->get_weight()<<","<<P2->get_depth()<<","<<player_name(P2->get_color())<<",";
		play_game_silent(P1,P2,G);
		Player winner = G.who_win();
		myfile<<player_name(winner)<<","<<G.total_chips()<<"\n";
	}
	//Games where we force the AI to start on each column in the game. 
	for (int i = 0; i<7; i++){	
		Game G;
		G = Game(P1->get_color());
		G.play(i);
		
				//std::cout<<G<<std::endl;
		myfile<<player_name(G.get_turn())<<","<<P1->class_name()<<","<<P1->get_weight()<<","<<P1->get_depth()<<","<<player_name(P1->get_color())<<","<<P2->class_name()<<","<<P2->get_weight()<<","<<P2->get_depth()<<","<<player_name(P2->get_color())<<",";
		play_game_silent(P1,P2,G);
		Player winner = G.who_win();
		//std::cout<<G<<std::endl;
		myfile<<player_name(winner)<<","<<G.total_chips()<<"\n";
		}
	
	//Games where we for the AI to start on a column and the other AI to start on the another one. 
		for (int i = 0; i<7; i++){	
			for (int j = 0; j< 7; j++){
			Game G;
			G = Game(P1->get_color());
			G.play(i);
			G.play(j);
		
			
			myfile<<player_name(G.get_turn())<<","<<P1->class_name()<<","<<P1->get_weight()<<","<<P1->get_depth()<<","<<player_name(P1->get_color())<<","<<P2->class_name()<<","<<P2->get_weight()<<","<<P2->get_depth()<<","<<player_name(P2->get_color())<<",";
			play_game_silent(P1,P2,G);
			Player winner = G.who_win();
			myfile<<player_name(winner)<<","<<G.total_chips()<<"\n";
		}
	}
	myfile.close();
}

void league(){
	
	std::vector<Player_Abs*> teams;
	for (int i = 3; i<5; i++){
		for (int j = 4; j<7;j++){
			teams.push_back(new Minmax(GREEN, i, j));
			teams.push_back(new Minmax_tweak(GREEN, i, j));
			teams.push_back(new Minmax_tweak_arthur(GREEN, i, j));
		}
	}
	
	for (unsigned int i = 0; i<teams.size(); i++){
		for (unsigned int j = i+1; j <teams.size(); j++){
			teams[i]->set_color(GREEN);
			teams[j]->set_color(RED);
			test_AI_to_csv_lite(teams[j], teams[i], "League-Away.csv");
			std::cout << i << " fight " << j << std::endl;
		}
	}
}
void short_league(){
	
	std::vector<Player_Abs*> teams;
	for (int i = 3; i<4; i++){
		for (int j = 3; j<8;j++){
			teams.push_back(new Minmax(GREEN, i, j));
			//teams.push_back(new Minmax_tweak(GREEN, i, j));
			//teams.push_back(new Minmax_tweak_arthur(GREEN, i, j));
		}
	}
	std::vector<int> result(teams.size());
	std::vector<int> lose(teams.size());
	std::vector<int> draw(teams.size());	
	for (unsigned int i = 0; i<teams.size(); i++){
		for (unsigned int j = i+1; j <teams.size(); j++){
			teams[i]->set_color(GREEN);
			teams[j]->set_color(RED);
			Game G(RED),G2(GREEN);
			std::cout << i << " fight " << j << std::endl;
			play_game_silent(teams[i],teams[j],G);
			play_game_silent(teams[i],teams[j],G2);
			if (G.who_win() == GREEN){
				result[i]++;
				lose[j]++;
				}
			else if (G.who_win() == RED){
				result[j]++;
				lose[i]++;
			}
			else {
				draw[i]++;
				draw[j]++;
			} 
			
			if (G2.who_win() == GREEN){
				result[i]++;
				lose[j]++;
				}
			else if (G2.who_win() == RED){
				result[j]++;
				lose[i]++;
			}
			else {
				draw[i]++;
				draw[j]++;
			} 
		}
	}
	//128.39.75.111
	for (unsigned int i = 0; i<result.size(); i++){
		std::cout<< " wins: " << result[i] <<" "
		  				<< " loses: " << lose[i]<< " "
		  				<< " draws: " << draw[i] <<" IA "
		  				<< teams[i]->class_name() << " " 
						<< teams[i]->get_weight() << " " 
						<< teams[i]->get_depth() << " " 
		  				<< std::endl;
	} 
}

void play_game_real_board(){
srand(time(NULL));
cv::VideoCapture vcap;
 if(!vcap.open("tcp://128.39.75.111:3001")) {
    std::cout << "Error opening video stream or file" << std::endl;
  }
  Cv_c4_option opt;
  opt.load("save.cvconf");
  
  Cv_c4 cv(opt);
  std::vector<CV_BOARD_STATE> old_board(6*7,CV_VIDE);
  CV_BOARD_STATE expect = CV_RED;
  Cv_c4_optim  optim_cv(cv);
  
  
Player_Abs* Human_player = new Human(GREEN);
Player_Abs* Nao = new Minmax_tweak_arthur(RED, 3,5);
Game A(RED);
std::cout << A << std::endl;
int nextplay = 0;
while (!(A.is_over())) {
		if (A.get_turn() == Human_player->get_color()) { 
		    expect = CV_GREEN;   
			old_board = optim_cv.predict_next_board(old_board,8,10,vcap,expect);
			A = vision_to_game(old_board);
			A.set_turn(RED);
    	}
		else {    
			
			Move m = Nao->play(A);
			//A.apply(m);
			nextplay = m.column;
			play_on_row(nextplay,TTS);
			expect = CV_RED;
			old_board = optim_cv.predict_next_board(old_board,8,10,vcap,expect);
			A = vision_to_game(old_board);
			A.set_turn(GREEN);
			//if (vision_to_game(old_board) != A)  
			
			
			//if (!A.is_over()) after_nao_turn(tts);
		}
		std::cout << A << std::endl;
	}
	Player Result = A.who_win();

}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	
	/*
	  cv::VideoCapture vcap;
 if(argc!=4)
    {
      std::cout << "need 4 arg" << "\n";
    }
  // This works on a D-Link CDS-932L
  std::cout << argv[1] << "\n";
  std::string videoStreamAddress(argv[1]);

  //open the video stream and make sure it's opened
  if(!vcap.open(videoStreamAddress)) {
    std::cout << "Error opening video stream or file" << std::endl;
    return -1;
  }

  Cv_c4_option opt;
  opt.load(argv[2]);



  if(std::string(argv[3]) == "config")
    {
      Cv_c4_option_helper cvh(opt);
      config_run(cvh, vcap);
      cvh.cv.opt.save(std::string(argv[2]));

      return 0;
    }
*/

//human_start(TTS);
play_game_real_board();
	/*Game G;
	Player_Abs* P1 = new Minmax(GREEN, 5, atoi(argv[1]));
	Player_Abs* P2 = new Minmax(RED, 5, 3);
    play_game_silent(P1,P2,G);
    */
	//play_game_verbose();
	 /*std::string filename = "Test_game_simmetry.csv";
		std::ofstream myfile;
	myfile.open (filename.c_str(), std::ios_base::app);
	myfile<<"Starter,P1name,P1weight,P1depth,P1color,P2name,P2weight,P2depth,P2color, Winner, TotalChips\n";
	myfile.close();
	
	Player_Abs* P2 = new Minmax_tweak_arthur(RED, 4, 3);
	for (int depth = 1; depth<10; depth++){
		for(int weight = 4; weight<5; weight++){
	Player_Abs* P1 = new Minmax_tweak_arthur(GREEN, weight, depth);
	std::cout << "Doing weight-depth " << weight << "-" << depth << std::endl;
	test_AI_to_csv(P1,P2, filename);
	}
	}
	*/
	
	//for (int depth = 1; depth<11; depth++){
	//Player_Abs* P1 = new Minmax_tweak_arthur(GREEN, 4, 3);
	//std::cout << "Doing weight-depth " << "4" << "-" << depth << std::endl;
	//test_AI_to_csv_lite(P1,P2, filename);
	//}

	
	/*Game G(RED);
	play_game_silent(P1,P2,G);
	std::cout << G << std::endl;
	Player Result = G.who_win();
	std::cout << "And the winner is..." << player_name(Result) << "!!!" << std::endl;
	*/
	//test_AI();
	

}
