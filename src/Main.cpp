#include "Game.hpp"
#include "iostream"
#include "../include/Reactions.hpp"



const std::string ipnao = "128.39.75.111";
AL::ALTextToSpeechProxy tts(ipnao, 9559);

int win_possibility(Game g){

	Player nao = g.get_turn();
	Player p;
	if (nao == RED) p = GREEN;
	else p = RED; 
	int i = -1;
	for (int j = 0; j<7; j++){
		i = g.get_first_empty_space(j);
		if (i != -1){
			g.set(i,j,Player_to_Board_state(nao));
			if (g.is_over()) {
			g.set(i,j,EMPTY);
			return j;
			}
			g.set(i,j,EMPTY);			
		}
	}
	
	for (int j = 0; j<7; j++){
		i = g.get_first_empty_space(j);
		if (i != -1){
			g.set(i,j,Player_to_Board_state(p));
			if (g.is_over()) {
			g.set(i,j,EMPTY);
			return j;
			}
			g.set(i,j,EMPTY);
		}
	}
	
	return -1;

}
int main() {

  //Initialize the game, the human picks a color and who starts. 
  std::cout << "Pick a color. Red (R) or Green (G) ?" << std::endl;
  char d;
  std::cin >> d;
  Player Human = RED;
  while (d != 'G' && d != 'g' && d != 'r' && d != 'R') {
    std::cout << "Incorrect input" << std::endl;
    std::cin >> d;
  }
  if (d == 'G' || d == 'g'){
    Human = GREEN;
    nao_is_red(tts);
    }
  else nao_is_green(tts);

  std::cout << "Who starts ? Red (R) or Green (G) ?" << std::endl;
  char c;
  std::cin >> c;
  Player Starter = RED;
  while (c != 'G' && c != 'g' && c != 'r' && c != 'R') {
    std::cout << "Incorrect input" << std::endl;
    std::cin >> c;
  }
  if (c == 'G' || c == 'g')
    Starter = GREEN;
  Game A(Starter);
  if (Starter == Human) human_start(tts);
  else nao_start(tts);

  std::cout << A << std::endl;
  int column;
  int ai_column;
  int check;
  //After every turn, we check if the game is over. If it's not, we check if it's human turn or nao's turn. 
  while (!(A.is_over())) {

    if (A.get_turn() == Human) {
      std::cout << "It's " << Player_name(A.get_turn())
                << " turn! Where do you want to play?(1-7)" << std::endl;
      std::cin >> column;

      Move m(column - 1, A.get_turn(), A);
      if (m.is_valid() != OK)
        std::cout << "This movement is not valid. Try again!" << std::endl;
      else {
      	A.apply(m);
      	std::cout << A << std::endl;
      	if (!A.is_over()) after_human_turn(tts);
      }
    }

    else {
      check = win_possibility(A);
      if(check != -1) ai_column = check; 
      else ai_column = rand() % 7;
      play_on_row(ai_column, tts);
      Move m(ai_column, A.get_turn(), A);
      A.apply(m);
      std::cout << A << std::endl;
      if (!A.is_over()) after_nao_turn(tts);
    }
  }
  Player Result = A.who_win();
  if (Result == Human) nao_lose(tts);
  else if (Result == NO_ONE) nao_draw(tts);
  else nao_win(tts);
  std::cout << "And the winner is..." << Player_name(Result) << "!!!"
            << std::endl;
  return 0;
}
