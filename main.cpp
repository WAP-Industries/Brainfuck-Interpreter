#include <iostream>
#include <fstream>
#include <optional>
#include <string>

#include "interpreter.hpp"

std::optional<std::string> GetFileContents(std::string path){
	std::ifstream File(path);
	
	auto Reverse = [](std::string string)->std::string {
		std::string fin = "";
		for (int i=string.length()-1;i>=0;i--)
			fin+=string[i];
		return fin;
	};
	
	if (!File.is_open()) {
		std::cout << "Could not locate file" << std::endl;
		return std::nullopt;
	}
	
	if (Reverse(path).find(Reverse(".bf"))!=0){
		std::cout<< "Can only interprete files with .bf extension" << std::endl;
		return std::nullopt;
	}
	
	std::string line, contents;
	while (std::getline(File, line))
		contents+=line;
		
	File.close();
	return contents;
}

int main(){
	std::cout<<"Brainfuck Interpreter\n(c) WAP Industries.\n";
	
	while (true){
		Interpreter::Init();
		
		std::string input;
		std::cout<<"\n>> ";
		std::cin>>input;
		if (input=="quit") break;
		
		std::optional<std::string> FileContents = GetFileContents(input);
		if (!FileContents.has_value()) continue;
		
		Interpreter::CURRENT_CODE = FileContents.value();
		Interpreter::Interprete();
		
		std::cout<<std::endl;
	}
	return 0;
}