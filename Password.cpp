#include "Password.h"
#include <String>
#include "ListArrayIterator.h"
#include <iostream>

using CSC2110::ListArrayIterator;
using namespace std;
using CSC2110::String;


namespace CSC2110
{

Password::Password() 
{
	all_words = NULL;
	viable_words = NULL;
}

Password::~Password()
{
	delete [] viable_words;
	delete [] all_words;
}

void Password::addWord(String* word)
{
	for(int i = 1; i < num_words; i++)
	{
		viable_words[i] = new String* (word);
		all_words[i] = new String* (word);
	}
}

void Password::guess(int try_password, int num_matches)
{
	all_words = bestGuess();
	for(int i = 1; i < num_words; i++)
	{
		viable_words[
	}
}

int Password::getNumberofPasswordsLeft()
{
	int counter;
	for(int i = 1; x < num_words; i++)
	{
		if(viable_words[i] == all_words[i])
			counter++;
	}
	
	return counter;
}

void Password::displayViableWords()
{
	for(int i = 1; i < num_words; i++)
	{
		cout << viable_words[i] << endl;
	}
}

String* Password::getOriginalWord(int index)
{
	return all_words[index];
}

int getNumMatches(String* curr_word, String* word_guess)
{
	int counter;
	
	for(int i = 1; i < len; i++)
	{
		if(curr_word[i] == word_guess[i])
			counter++;
	}
	
	return counter;
}

int Password::bestGuess()
{
   int best_guess_index = -1;
   int best_num_eliminated = -1;
   int num_viable_passwords = getNumberOfPasswordsLeft();

   //loop over ALL words, even if they have been eliminated as the password
   int count = 1;
   ListArrayIterator<String>* all_iter = all_words->iterator();
   while(all_iter->hasNext())
   {
      String* original_word = all_iter->next();

      //loop over only those words that could still be the password
      //count up the number of matches between a possible password and a word in the original list
      int* count_num_matches = new int[len + 1];

      for (int i = 0; i < len; i++) 
      {
         count_num_matches[i] = 0;
      }

      ListArrayIterator<String>* viable_iter = viable_words->iterator();
      while(viable_iter->hasNext())
      {
         String* viable_word = viable_iter->next();
         int num_matches = getNumMatches(viable_word, original_word);
         count_num_matches[num_matches]++;
      }
      delete viable_iter;

      //find the largest number in the count_num_matches array
      //the largest number indicates the guess that will generate the most eliminations
      int most_num_matches = 0;
      for (int j = 0; j < len; j++) 
      {
         int curr_num_matches = count_num_matches[j];
         if (curr_num_matches > most_num_matches)
         {
            most_num_matches = curr_num_matches;
         }
      }

      //compute the fewest that can possibly be eliminated by guessing the current word (original list)
      int num_eliminated = num_viable_passwords - most_num_matches;

      //select the word to guess that maximizes the minimum number of eliminations (minimax)
      if (num_eliminated > best_num_eliminated)
      {
         best_num_eliminated = num_eliminated;
         best_guess_index = count;
      }
      
      count++;
      delete[] count_num_matches;
   }

   delete all_iter;
   return best_guess_index;  //return a 1-based index into the all_words list of words (careful)
}
}