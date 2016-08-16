#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <unordered_set>

// http://pastebin.com/ugAQjABX

using namespace std;

int main() {
  ofstream output;
  output.open("emoji.hpp");
  	
  string line;
  ifstream inputFile("emoji-data.txt");
  // http://unicode.org/Public/emoji/1.0/emoji-data.txt
  
  if(inputFile.is_open()) {
    output << "#ifndef EMOJI_HPP_\n";
    output << "#define EMOJI_HPP_\n";
    output << "\n";
    output << "template <class CharT> bool isEmoji(CharT c) {\n";
    output << "\n";
    output << "\tstatic const unordered_set<CharT> emojis = {\n";	
    
    while(getline(inputFile, line)) {
      if (line.at(0) == '#') {
	continue;
      }
      
      string symbol = line.substr(0, line.find(";", 1)) + ",";
      
      int spaces = 0;
      for(char& c : symbol) {
	if (c == ' ') {
	  spaces++;
	}
      }
	  
      if (spaces >= 2) {
	continue;
      }
	  
      symbol.insert(0, "0x");
      
      string comment = " //" + line.substr(line.find(")") + 1);
      
      line = symbol + comment;
      
      output << "\t";
      output << "\t";
      output << line;
      output << "\n";
      cout   << line;
	  
    }
    inputFile.close();
	
	
    // Flags
    // A through Z
    for(int charNum = 0; charNum < 26; charNum++) {

      stringstream stream_ascii;
      stringstream stream_unicode;
		
      string symbol;
      string comment;
      char ascii = 'A'+charNum;
      int unicode = 0x1F1E6+charNum;
		
      stream_ascii << ascii;
      stream_ascii >>  comment;
		
      stream_unicode << hex << unicode;
      stream_unicode >> symbol;
		
      if (charNum != 25) {
	symbol += " ,";
      }
      else {
	symbol += "  ";
      }
		
      symbol.insert(0, "0x");
      
      comment.insert(0, " // ");
		
		
      string line = symbol + comment;
		
      output << "\t";
      output << "\t";
      output << line;
      output << "\n";
      cout   << line;
    }
	
    output << "\n\t};";
    output << "\n\n";
    output << "\treturn emojis.count(c);";
    output << "\n}\n";
    output << "\n#endif";
	
    output.close();
	
  }
  else {
    cout << "Unable to open file"; 
  }

  return 0;
}
