#include <iostream>
#include <string>

using namespace std;

char getLetter(int number, int mode = 0) {
  int initial = mode == 0 ? 64 : 96;
  int value =  number % 27;
  return (initial + value);
}

char getPunc(int number) {
  int place = number % 9;
  if (place > 8) return 0;
  char chars[] = {'!', '?', ',', '.', ' ', ';', '"','\''};
  return chars[place - 1];
}

bool shouldModeChange(int mode, int number) {
  return number % (mode == 2 ? 9 : 27) == 0;
}

int getCorrectMode(int mode,int number) {
  if(!shouldModeChange(mode, number)) return mode;
  return mode == 0 ? 1 : mode == 1 ? 2 : 0;
}

string getCorrectWord(string word, int number, int mode) {
  if(mode == 2) word += getPunc(number);
  else word += getLetter(number,mode);
  return word;
}

string decodeSecretMessage(){
  string word;
  int number = 0, mode = 0;
  char digit;

  cout << "Enter a list of comma seperated integers: ";
  digit = cin.get();

  while(digit != 10) {
    int value = digit - '0';
    if(digit == ',') {
      int oldMode = mode;
      mode = getCorrectMode(mode, number); 
      if(mode != oldMode) { digit = cin.get(); number = 0; continue;}

      word = getCorrectWord(word, number, mode);
      number = 0; digit = cin.get(); 
    } 
    else {
      if(number == 0) number += value;
      else number = (number * 10) + value;
      digit = cin.get(); 
    }
  }
  return  getCorrectWord(word, number, mode);
}

int main() {
  cout << decodeSecretMessage();
} 
