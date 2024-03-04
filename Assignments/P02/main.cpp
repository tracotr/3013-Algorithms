// Jaxon King
// 3013 - Program 2
// A modified program using the getch function and nlohmanns json library to
// read in a dictionary file and allow for searching through that json to find
// whatever the user enters (if it exists)

/**
 * This program uses a "getch" function which means "get character".
 * However, getch does not print the character to the terminal, it
 * lets you decide what to do based on what character you are pressing.
 *
 * You can test which characters are being pressed using their ascii values.
 *
 * An ascii table here should be helpful
 *      http://www.asciitable.com/
 *
 * Some integer values for some keys:
 *      LowerCase Letters   = 97(a) -> 122(z)
 *      UpperCase Letters   = 65(A) -> 90(Z)
 *      Enter Key           = 10
 *      Space Bar           = 32
 *
 *      Arrow Keys          = Have same values as some letters
 *                            so we can't distinguish between
 *                            the two (in this context).
 *
 * Code below is a basic example of using a "getch" function along with
 * searching an array of words for partial matches.
 *
 * https://repl.it/@rugbyprof/getchexample#main.cpp

 rang only depends on C++ standard library, unistd.h system header on unix and
 windows.h & io.h system headers on windows based systems. In other words, you
 don't need any 3rd party dependencies.
 */

#include "./headers/animals.hpp"
#include "./headers/console.hpp"
#include "./headers/json.hpp"
#include "./headers/rang.hpp"
#include "./loadJsonEx.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <time.h>
#include <vector>

using namespace std;
using namespace rang;

using json = nlohmann::json;

consoleSize console_size; // used to store the size of console (width=cols and
                          // height=rows)

/**
 * partialMatch
 *
 * Description:
 *      Finds partial matches in an array of strings and returns them.
 * Params:
 *      vector<string>  array       - array to search
 *      string          substring   - substring to search for in each word
 *
 * Returns:
 *      vector<string> - holding all the matches to substring
 */
vector<string> partialMatch(json input, string substring) {
  vector<string> matches; // to hold any matches
  int substringLength =
      substring.length(); // length of the substring for comparing

  // if input size = 0, then returns empty list
  if (substring.size() == 0) {
    return matches;
  }

  // I took this code from somewhere in the nlohhman json docs, i cannot find it
  // anymore :( 
  // Iterate over all key-value pairs
  for (auto &element : input.items()) {
    string key =
        element.key(); // sets the current checked key to word its looping in

    // Check if the key contains the substring, and if the substring is at the
    // start of the key
    if (key.find(substring) != string::npos &&
        key.substr(0, substringLength) == substring) {
      // Found a match, push into matches vector
      matches.push_back(key);
    }
  }

  return matches;
}

/**
* Prints a long background row of gray, with text centered.
* Not a good function since colors are hard coded, but using
* rang, I don't want to invest the time to figuere out how to
* interact with rang's enumerated class types and ostream.
* I guess you could add a switch statement to change background
* color:
* switch(color){
  "black" : cout<<bgB::black;
            break;
  "red" : cout<<bgB::red;
          break;
  ...
  ...
  ...
}
But still not a good solution.
*/
void titleBar(string title, int length = console_size.width) {
  string padding = string((length / 2) - (title.size() / 2), ' ');
  title = padding + title + padding;
  cout << bgB::black << fg::gray << title << fg::reset << bg::reset << endl;
}

/**
 * horizontalBar
 *
 * Description:
 *      Prints a horizontal bar of a given length
 * Params:
 *      int length - length of the bar
 * Returns:
 *      void
 */
void horizontalBar(int length = console_size.width) {
  string line = string(length, '_');
  cout << fg::gray << line << fg::reset << bg::reset << endl;
}

/**
 * printMatches
 *
 * Description:
 *      Prints the matches to the screen.
 * Params:
 *      vector<string> matches - vector of matches
 * Returns:
 *      void
 */
void printMenu(vector<string> options) {
  int i = 1;
  for (auto s : options) {
    cout << fg::black << style::bold << i << ". " << style::reset << fg::cyan
         << s << fg::reset << bg::reset << endl;
    i++;
  }
  cout << fg::reset << bg::reset;
}

/**
 * printHighlightedSubstr
 *
 * Description:
 *      Given a word, print the substr underlined and red vs blue for the rest
 * of the word.
 * Params:
 *      string word - word to print
 *      string substr - substring to highlight in red
 *      int loc - location of substr in word
 * Returns:
 *      void
 */
void printHighlightedSubstr(string word, string substr, int loc) {
  for (int j = 0; j < word.size(); j++) {
    // if we are printing the substring turn it red
    if (j >= loc && j <= loc + substr.size() - 1) {
      cout << fg::red << style::underline << word[j] << fg::blue
           << style::reset;
    } else {
      cout << fg::blue << word[j] << fg::reset << style::reset;
    }
  }
}

/**
 * printCurrent
 *
 * Description:
 *      Prints the current key pressed and the current substr to the screen.
 * Params:
 *      char k - last character pressed.
 *      string word - current substring being printed.
 * Returns:
 *      void
 */
void printCurrent(char k, string word) {
  cout << fg::green << style::bold << "KeyPressed: \t\t" << style::reset
       << fgB::yellow;
  if (int(k) == 127) {
    cout << "del";
  } else {
    cout << k;
  }
  cout << " = " << (int)k << fg::reset << endl;
  cout << fg::green << style::bold << "Current Substr: \t" << fg::reset
       << fgB::blue << word << fg::reset << style::reset << endl;
  cout << endl;
}

/**
 * errorMessage
 *
 * Description:
 *      Prints an error message to the screen.
 * Params:
 *      string message - message to print
 * Returns:
 *      void
 */
void errorMessage(string message) {
  cout << bgB::red << fgB::gray << message << fg::reset << bg::reset << endl;
  sleep(1);
}

int main() {
  console_size = getConsoleSize(); // get width and height of console
  char k;                          // holder for character being typed
  string key;                      // string version of char for printing
  string substr = "";              // var to concatenate letters to
  json dictionary =
      loadJsonFile("data/dictionary.json"); // array of dictionary words
  vector<string> matches; // any matches found in vector of animals
  int loc;                // location of substring to change its color
  bool deleting = false;
  string str = "";
  vector<string> mainMenu;
  mainMenu.push_back("Type letters and watch the results change.");
  mainMenu.push_back(
      "Hit the DEL key to erase a letter from your search string.");
  mainMenu.push_back(
      "When a single word is found, hit enter. (this is for real assignment.)");

  clearConsole();
  titleBar("Getch Example", console_size.width);
  printMenu(mainMenu);

  // While capital Z is not typed keep looping

  while ((k = getch()) != 'Z') {

    clearConsole();
    titleBar("Getch Example", console_size.width);
    printMenu(mainMenu);

    // Tests for a backspace and if pressed deletes
    // last letter from "substr".
    if ((int)k == 127) {
      if (substr.size() > 0) {
        substr = substr.substr(0, substr.size() - 1);
        deleting = true;
      }
    } else {
      deleting = false;
      // Make sure a letter was pressed and only letter
      if (!isalpha(k)) {
        errorMessage("Letters only!");
        continue;
      }

      // We know its a letter, lets make sure its lowercase.
      // Any letter with ascii value < 97 is capital so we
      // lower it.
      if ((int)k < 97) {
        k += 32;
      }
      substr += k; // append char to substr
    }

    // Print current letters pressed
    printCurrent(k, substr);

    // Find any words in the array that partially match
    // our substr word
    matches = partialMatch(dictionary, substr);

    if ((int)k != 32) { // if k is not a space print it

      key = to_string(k);

      horizontalBar();

      cout << style::bold << style::underline << fg::black
           << "MATCHES: " << fg::green << matches.size() << style::reset
           << fg::reset << endl
           << endl;

      for (auto &c : substr)
        c = tolower(c);
      // This prints out all found matches
      for (int i = 0; i < matches.size(); i++) {
        // find the substring in the substr
        loc = matches[i].find(substr);
        // if its found
        if (loc != string::npos) {
          printHighlightedSubstr(matches[i], substr, loc);
        }
        cout << ", ";

        // if it prints 10 things, break the for loop
        if (i == 10) {
          break;
        }
      }
      cout << fg::reset << endl << endl << endl;

      if (matches.size() == 1) {
        // prints definition if only one match
        cout << dictionary.at(matches[0]);
      }
    }
  }
  return 0;
}
