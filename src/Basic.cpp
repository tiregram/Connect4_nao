#include "../include/Basic.hpp"

Basic::Basic(){
}

Basic::~Basic(){
}

int Basic::win_possibility(Game g){

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
Move Basic::AI_play(Game G){
      srand (time(NULL));
      int check;
      int ai_column;
      check = win_possibility(G);
      if(check != -1) ai_column = check;
      else ai_column = rand() % 7;
      Move m(ai_column, G.get_turn(), G);
      return m;

}
