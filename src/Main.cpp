#include "Game.hpp"
#include "iostream"
int main() {

  std::cout << "Pick a color. Red (R) or Green (G) ?" << std::endl;
  char d;
  std::cin >> d;
  Player Human = RED;
  while (d != 'G' && d != 'g' && d != 'r' && d != 'R') {
    std::cout << "Incorrect letter" << std::endl;
    std::cin >> d;
  }
  if (d == 'G' || d == 'g')
    Human = GREEN;

  std::cout << "Who starts ? Red (R) or Green (G) ?" << std::endl;
  char c;
  std::cin >> c;
  Player Starter = RED;
  while (c != 'G' && c != 'g' && c != 'r' && c != 'R') {
    std::cout << "Incorrect letter" << std::endl;
    std::cin >> c;
  }
  if (c == 'G' || c == 'g')
    Starter = GREEN;
  Game A(Starter);

  std::cout << A << std::endl;
  int column;
  while (!(A.is_over())) {

    if (A.get_turn() == Human) {
      std::cout << "It's " << Player_name(A.get_turn())
                << " turn! Where do you want to play?(1-7)" << std::endl;
      std::cin >> column;

      Move m(column - 1, A.get_turn(), A);
      if (m.is_valid() != OK)
        std::cout << "This movement is not valid. Try again!" << std::endl;
      A.apply(m);
      std::cout << A << std::endl;
    }

    else {
      Move m(rand() % 7, A.get_turn(), A);
      A.apply(m);
      std::cout << A << std::endl;
    }
  }
  std::cout << "And the winner is..." << Player_name(A.who_win()) << "!!!"
            << std::endl;
  return 0;
}
