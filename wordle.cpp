#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordFinder(const std::string &in, 
                std::string yellow, 
                std::string current_word,
                const std::set<std::string> &dict,
                std::set<std::string> &words,
                unsigned int index,
                unsigned int blanks);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    unsigned int blanks = 0;
    std::set<std::string> words;

    for (unsigned int i = 0; i < in.length(); i++){
        if (in[i] == '-'){
            blanks++;
        }
    }

    wordFinder(in, floating, in, dict, words, 0, blanks);
    return words;

}

// Define any helper functions here
void wordFinder(const std::string &in, 
                std::string yellow, 
                std::string current_word,
                const std::set<std::string> &dict,
                std::set<std::string> &words,
                unsigned int index,
                unsigned int blanks){
    
    //base case: if the word `in` is filled, then check if its real
    if (index == in.length()){
        if (yellow.empty() && dict.find(current_word) != dict.end()){
            words.insert(current_word);
        }
        return;
    }
    
    //recursive case: only change around '-' characters
    if (in[index] == '-'){
        //try every letter?
        for (char i = 'a'; i <= 'z'; i++){

            //check if `i` is a yellow char
            //if not found, yellow_index > length of
            unsigned int yellow_index = yellow.find(i);

            bool is_yellow = yellow_index < yellow.length();

            if (is_yellow == true){
              std::string next_yellow = yellow;
              next_yellow.erase(yellow_index, 1);

              //put the current char in the current_word
              current_word[index] = i;

              //go agane!!
              wordFinder(in, next_yellow, current_word, dict, words, index + 1, blanks - 1);

            } else {
              //it's not a yellow letter
              if (blanks > yellow.length()){
                current_word[index] = i;

                //move on
                wordFinder(in, yellow, current_word, dict, words, index + 1, blanks - 1);
              }
            }
        }

    } else {
        //recurse cuz current index is not a blank
        wordFinder(in, yellow, current_word, dict, words, index + 1, blanks);        
    }

}
