//====================================================================
// John Fernow
// project4.cpp
// February 22, 2017
// This project reads a wordsearch and solves for the given words
//====================================================================

#define N 6000
#include <iostream> 	// used to have cin and cout
#include <stdio.h> 		// used to handle keyboard/terminal input/output
#include <stdlib.h>		// used to use atoi(), to convert str to int
#include <vector>		// used to store container of strings
#include <string>		// used to save current words 
using namespace std;

// function templates
bool searchCrossword (char puzzle[14][14], vector<string> words, int currentLen, string currentWord);

//====================================================================
// main
//====================================================================
int main ( void )
{
	char puzzle[14][14];	 // puzzle text as read in
	vector<string> words (N);// words to search for, as read in
	char numOfWords[1];		 // number of words to look for
	int totalWords;			 // count of how many words to search
	string currentWord; 	 // current word to search for
	int currentLen;			 // length of current word
	bool wordFound; 		 // determines whether word was found

	/*----------------------- PART 1 ---------------------------------
    The purpose of part 1 is to read in puzzle text and save it to
    multi-dimensional array. It also reads in words to search for.
    ----------------------------------------------------------------*/

    /* This block of code will read a character of input at a time
     until it hits the end-of-file.   
     The characters are stored in the 2D character array 'puzzle'.  */
    
	// read in puzzle
    for (int i = 0; i < 14; i++){
        for (int j = 0; j < 14; j++)
            cin >> puzzle[i][j];
    }
    

    // prints puzzle
    for (int i = 0; i < 14; i++){
    	for (int j = 0; j < 14; j++)
    		cout << puzzle[i][j];
    	cout << endl;
    }
    
	
    // finds number of words to search for
    cin >> numOfWords;
    totalWords = atoi(numOfWords); 	// converts str to int
    //cout << "Searching for " << totalWords << " words." << endl; // comment out later

    // find words that are to be searched for
    for (int i = 0; i < totalWords; i++)
    	cin >> words[i];

	/*
    // prints words to be searched for -- comment out later
    for (int i = 0; i < totalWords; i++)
    	cout << words[i] << endl;
	*/

	/*----------------------- PART 2 ---------------------------------
    This part of the program calls searchCrossword
    ----------------------------------------------------------------*/
	for (int n = 0; n < totalWords; n++){	// for every word,
		currentWord = words[n]; 			// save current word
		currentLen = currentWord.length();	// find length of it
    	wordFound = searchCrossword(puzzle, words, currentLen, currentWord);// call function
		if (wordFound == false)
			cout << currentWord << " not found" << endl;

    }

  return 0;
}
//====================================================================
// searchCrossword
// This part of the program reads the puzzle array left to right,
// right to left, top to bottom, bottom to top, and the four diagonal
// directions in search for the desired words. 
// Parameters:
// - puzzle		: 2D char array used to save contents of puzzle
// - words 		: vector of strings used to save words to be searched for
// - currentLen	: int used to pass through length of word currently being searched for
// - currentWord: word to be searched for
// Return Value:
// - bool saved as wordFound: used to determine if word was found
// Side Effects:
// - prints words found and their positions
//====================================================================
bool searchCrossword ( char puzzle[14][14], vector<string> words, int currentLen, string currentWord )
{
	string currentStr;
	for ( int i = 0; i < 14; i++){ 					// for every row,
		for ( int j = 0; j < 14; j++){ 				// for every column,
			currentStr = ""; 						// clear string

			// search left to right
			if (j + currentLen - 1 <= 14){ 			// if inside grid
				for (int k = 0; k < currentLen; k++)
					currentStr += puzzle[i][j+k]; 	// save characters as str
				if (currentWord == currentStr){
					cout << currentWord << " found at (" << int(i) << ", " << int(j) <<
					") going right" << endl;
					return true;
				}
				else								
					currentStr = ""; 				
			}
			
			// search right to left
			if (j - currentLen + 1 >= 0){ 			// if inside grid
				for (int k = 0; k < currentLen; k++)
					currentStr += puzzle[i][j-k];	// save characters as str
				if (currentWord == currentStr){
					cout << currentWord << " found at (" << int(i) << ", " << int(j) << 
					") going left" << endl;
					return true;
				}
				else
					currentStr = "";
			}

			// search top to bottom
			if (i + currentLen - 1 <= 14){ 			// if inside grid
				for (int k = 0; k < currentLen; k++)
					currentStr += puzzle[i+k][j];	// save characters as str
				if (currentWord == currentStr){
					cout << currentWord << " found at (" << int(i) << ", " << int(j) << 
					") going down" << endl;
					return true;
				}
				else
					currentStr = "";
			}

			// search bottom to top
			if (i - currentLen + 1 >= 0){ 			// if inside grid
				for (int k = 0; k < currentLen; k++)
					currentStr += puzzle[i-k][j];	// save characters as str
				if (currentWord == currentStr){
					cout << currentWord << " found at (" << int(i) << ", " << int(j) << 
					") going up" << endl;
					return true;
				}
				else
					currentStr = "";
			}

			// search down right diagonally
			if (i + currentLen - 1 <= 14 && j + currentLen - 1 <= 14){ // if inside grid
				for (int k = 0; k < currentLen; k++)
					currentStr += puzzle[i+k][j+k];	// save characters as str
				if (currentWord == currentStr){
					cout << currentWord << " found at (" << int(i) << ", " << int(j) << 
					") going down right" << endl;
					return true;
				}
				else
					currentStr = "";
			}

			// search down left diagonally
			if (i + currentLen - 1 <= 14 && j - currentLen + 1 >= 0){ // if inside grid
				for (int k = 0; k < currentLen; k++)
					currentStr += puzzle[i+k][j-k];	// save characters as str
				if (currentWord == currentStr){
					cout << currentWord << " found at (" << int(i) << ", " << int(j) << 
					") going down left" << endl;
					return true;
				}
				else
					currentStr = "";
			}

			// search up right diagonally
			if (i - currentLen + 1 >= 0 && j + currentLen - 1 <= 14){ // if inside grid
				for (int k = 0; k < currentLen; k++)
					currentStr += puzzle[i-k][j+k];	// save characters as str
				if (currentWord == currentStr){
					cout << currentWord << " found at (" << int(i) << ", " << int(j) << 
					") going up right" << endl;
					return true;
				}
				else
					currentStr = "";
			}

			// search up left diagonally
			if (i - currentLen + 1 >= 0 && j - currentLen + 1 >= 0){ // if inside grid
				for (int k = 0; k < currentLen; k++)
					currentStr += puzzle[i-k][j-k];	// save characters as str
				if (currentWord == currentStr){
					cout << currentWord << " found at (" << int(i) << ", " << int(j) << 
					") going up left" << endl;
					return true;
				}
				else
					currentStr = "";
			}
		}
	}
	return false; // occurs only when word was not found in any of the eight directions
}
