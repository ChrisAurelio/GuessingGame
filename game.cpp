/*
Author: Chris Aurelio
Date: 11/16/20
*/

#include <iostream>
#include <ctime>
using namespace std;

class Player {

  public:
    virtual int getGuess(int max, int min) = 0;   // initializes the getGuess function in the parent class
    virtual void update(int tempGuess, int &max, int &min, int answer) {}   // initializes the update function in the parent class
  private:
    int guess;
};

class HumanPlayer: public Player {    // HumanPlayer class derived from Player

  public:
    virtual int getGuess(int max, int min) override;    // overrides the getGuess function in HumanPlayer class
};

int HumanPlayer::getGuess(int min, int max) {

  int number;

  cout << "Please enter a a number as your guess: ";    // propmts the human to enter a number as their guess
  cin >> number;    // takes number input from the keyboard

  return number;    // returns human guess for use in the play function
}

class ComputerPlayer: public Player {   // ComputerPlayer class derived from Player

  public:
    virtual int getGuess(int max, int min) override;    // overrides getGuess in the ComputerPlayer class
    virtual void update(int tempGuess, int &max, int &min, int answer) override;    // overrides update function in ComputerPlayer class
};

int ComputerPlayer::getGuess(int max, int min) {

  int number;

  do {
    number = (max + min) / 2;   // algorithm to guess the number by selecting the median of the max and mix
  } while (number > max || number < min);   // while the guess is larger than max or smaller than min
  
  cout << "The computer guesses " << number << ". ";    // prints the ComputerPlayer guess to the terminal

  return number;
}

void ComputerPlayer::update(int tempGuess, int &max, int &min, int answer) {

  if (tempGuess > answer) {

    max = tempGuess;    // updates max to equal tempGuess if the tempGuess is greater than the answer
  }
  else {

    min = tempGuess;    // updates min to equal tempGuess if the tempGuess is less than the answer
  }
}

bool checkForWin(int guess, int answer);
void play(Player &player1, Player &player2);

bool checkForWin(int guess, int answer) {

  if (answer == guess) {

    cout << "You're right! You win!" << endl;
    return true;
  }
  else if (answer < guess) {
    
    cout << "Your guess is too high." << endl;
  }
  else {
 
    cout << "Your guess is too low." << endl;
  }
  return false;
}

void play(Player &player1, Player &player2) {

  int answer;
  int guess;
  int tempGuess;
  int max = 100;  // initializes max with an initial value of 100
  int min = 0;    // initializes min with an initial value of 0

  srand(static_cast<unsigned>(time(0)));
  answer = rand() % 100;    // creates a random answer 0 - 100
  bool win = false;

  while (!win) {
 
    cout << endl << "Player 1's turn to guess." << endl;
    guess = player1.getGuess(max, min);
    tempGuess = guess;
    player1.update(tempGuess, max, min, answer);
    win = checkForWin(guess, answer);
    if (win) return;

    cout << endl << "Player 2's turn to guess." << endl;
    guess = player2.getGuess(max, min);
    tempGuess = guess;
    player2.update(tempGuess, max, min, answer);
    win = checkForWin(guess, answer);
 }
}

int main(int argc, char * argv[]) {

  ComputerPlayer player1;
  ComputerPlayer player2;
  HumanPlayer player3;
  HumanPlayer player4;

  cout << "Computer v. Computer" << endl;
  play(player1, player2);

  cout << endl << endl << "Human v. Human" << endl;
  play(player3, player4);

  cout << endl << endl << "Computer v. Human" << endl;
  play(player1, player3);

  cout << endl << "Enter a character to exit." << endl;
  char exit;
  cin >> exit;

  return 0;
}