/*
	Author: Max Edward
	Email: maxedwar@uat.edu
	Assignment Name: UAT Professors & Guessing Game
*/

// Random Numbers, Arrays, and Sound in C++ - Part 2

// These bring in the iostream for console readout, algorithm for the shuffle function, and the string object for the string variable.
// There is also a Windows API for the beep sound. Not totally necessary but it allows for the programmer to be able to adjust the sound and length of sound.
#include <iostream>
#include <algorithm>
#include <string>
#include <windows.h>

using namespace std;

// Variables
int choice;
int guess = 0;
int startGrade = 2;
const char grades[] = { 'A', 'B', 'C', 'D', 'F' };
char currentGrade = grades[startGrade];
bool profFound;
void guessLength(int);
bool gameOver = false;
string endChoice;

// Arrays for professors, rooms, and occupied rooms.
string profArray[20] = { "Maureen Beam", "Sharon Bolman", "Brad Bowling", "David Brokaw", "Derric Clark", "Heather Peters", "Nathan Glover", "Alan Hromas", "Kendra Kim", "Juan Rodriguez", 
// Below are the "Empty" objects to place in rooms with no professors in them. 
"Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", "Empty", };
string roomArray[20] = { "135","108","107","106","235","234","232","231","252","253","245","244","207","206","208","205","203","202","204","201" };
string occArray[20]; // This array remains empty until the shuffle happens. Once the shuffle occurs this array gets filled with the rooms matched with the professor array.

int main() {
gameStart: // Start of the game anchor for the restart function.
	printf("\n------------------------------------\n\n");
	printf("Welcome to the UAT Campus Classroom Tour by Max Edward\n\n");
	printf("There are 20 different classrooms and 10 different professors to see.\n");
	printf("Your job is to choose a room in which a professor is in.\n");
	printf("If you wind up in a room with a professor, your grade will go up.\n");
	printf("However, if you wind up in a room with no one in it, your grade will go down.\n\n");
	printf("You will start with the letter grade C. If you get an A, you win! If you get an F, you lose!\n");
	printf("Once you press a button, the professors will randomly get placed into a classroom.\n");
	printf("\nGood luck and have fun!\n");
	printf("\n------------------------------------\n");
	system("pause"); // Pause to make sure the player is ready to play. Almost like a "Click start to start game".

	printf("\nHello! Thanks for coming to UAT!\n");
	printf("We have a handful of rooms to visit today.\n");

	do {
		printf("\nHere's a list of rooms to visit:\n");
		random_shuffle(&profArray[0], &profArray[19]); // This mixes up the professors names.
		for (int j = 0; j < 20; j++) {
			occArray[j] = roomArray[j] + ": " + profArray[j]; // This assigns the professor to a specific room.
			cout << "\n" << j << ". ) Room " << roomArray[j]; // This will print out the new list of class rooms the player can choose from.
		}
		cout << "\n\nFrom the list above, choose the number next to the classroom in which you think a professor is in.\n\n";
		cin >> choice; // Takes player input for guess.
		guessLength(choice);
	}

	// This while loop will compare the current grade and determine if the player will continue playing, if they win, or if they lose.
	while (gameOver == false);
	if (currentGrade == 'A' || currentGrade == 'F') {
		if (currentGrade == 'A') {
			cout << "\nGreat Job! You got an A in all your classes.\n";
		}
		else {
			cout << "\nOh No! You got an F in all of your classes.\n";
		}

		// Text that displays at the end of the game
	endChoice: // anchor for if user inputs the wrong characters.
		printf("\nTo play again, type restart. To quit, type quit.\n\n");
		cin >> endChoice; // Input for the endChoice variable.
		if (endChoice == "restart" || endChoice == "Restart") { // If the input is restart or Restart, then restart the game.
			printf("\n\n\n");
			goto gameStart;
		}
		if (endChoice == "quit" || endChoice == "Quit") { // If the input is quit or Quit, then quit the game.
			return 0;
		}
		else { // Otherwise restate the choices. 
			goto endChoice;
		}
	}
}

// This is the backend for the game mechanics.
void guessLength(int choice)
{
	if (occArray[choice].length() > 10) { // This compares the player's choice with the string length of the array.
		Beep(450, 1000); // Sound output for beep. Currently at 450 sound profile for 1000 milliseconds.
		// This will run if the player chose a room with a professor in it. It will increase the letter grade and then read out the previous rooms and corresponding professors.
		printf("\nThats the bell, lets see the results.\n");
		std::cout << "\nCongratulations! You found a professor. Your grade went up a letter!\n";
		profFound = true;
		currentGrade = grades[--startGrade];
		cout << "\nRoom results: \n";
		for (int j = 0; j < 20; j++)
		{
			occArray[j] = roomArray[j] + ": " + profArray[j];
			cout << "\n" << j << ". ) Room " << roomArray[j] << ", " << profArray[j];
		}
		cout << "\n\n";
		cout << "Your grade is now a " << currentGrade << ".\n\n";
		system("pause");
	}
	else {
		Beep(450, 1000); // Sound output for beep. Currently at 450 sound profile for 1000 milliseconds.
		// This will run if the player chose a room with no one in it.
		cout << "\nOh no, this room is empty! Your grade went down a letter.\n\n";
		profFound = false;
		currentGrade = grades[++startGrade];
		cout << "\nRoom results: \n";
		for (int j = 0; j < 20; j++) {
			occArray[j] = roomArray[j] + ": " + profArray[j];
			cout << "\n" << j << ". ) Room " << roomArray[j] << ", " << profArray[j];
		}
		cout << "\n\n";
		cout << "Your grade is now a " << currentGrade << ".\n\n";
		system("pause");
	}

	// Compares the new current grade with an A or an F to decide if the game will end.
	if (currentGrade == 'A' || currentGrade == 'F') {
		gameOver = true;
	}
	return;
}