#include <vector>

class Interpreter{
	private:
		static const int MEMORY_SIZE = 3e4;
		static unsigned char CELLS[MEMORY_SIZE];
		static int IPOINTER, MPOINTER;
		
	public: 
		static bool ENDED;
		static std::string CURRENT_CODE;
		static std::vector<int> QUEUE;
		static void Init();
		static bool CheckIndex();
		static void Error(std::string s);
		static void Interprete();
};
unsigned char Interpreter::CELLS[Interpreter::MEMORY_SIZE];
std::string Interpreter::CURRENT_CODE = "";
int Interpreter::IPOINTER = 0;
int Interpreter::MPOINTER = 0;
std::vector<int> Interpreter::QUEUE;
bool Interpreter::ENDED = false;


void Interpreter::Init(){
	std::fill(std::begin(Interpreter::CELLS), std::end(Interpreter::CELLS), 0);
	
	Interpreter::IPOINTER = Interpreter::MPOINTER = 0;
	Interpreter::QUEUE.clear();
	Interpreter::CURRENT_CODE = "";
	Interpreter::ENDED = false;
}


void Interpreter::Error(std::string ERRMSG){
	std::cout<< ERRMSG;
	Interpreter::ENDED = true;
}


bool Interpreter::CheckIndex(){
	return (
		Interpreter::IPOINTER>=0 &&
		Interpreter::IPOINTER<Interpreter::CURRENT_CODE.length()
	);
}


void Interpreter::Interprete(){
	while (!Interpreter::ENDED){
		switch (Interpreter::CURRENT_CODE[Interpreter::IPOINTER]){
			case '>':
				Interpreter::MPOINTER++;
				if (Interpreter::MPOINTER>=Interpreter::MEMORY_SIZE)
					Interpreter::Error("Out of bounds memory access with index " + std::to_string(Interpreter::MPOINTER));
				break;
			case '<':
				Interpreter::MPOINTER--;
				if (Interpreter::MPOINTER<0)
					Interpreter::Error("Out of bounds memory access with index " + std::to_string(Interpreter::MPOINTER));
				break;
				
			case '+':
				Interpreter::CELLS[Interpreter::MPOINTER]++;
				break;
			case '-':
				Interpreter::CELLS[Interpreter::MPOINTER]--;
				break;
			
			case '[':
				if ((bool)Interpreter::CELLS[Interpreter::MPOINTER])
					Interpreter::QUEUE.push_back(Interpreter::IPOINTER);
				else{
					int count = 0;
					while (true) {
						Interpreter::IPOINTER++;
						if (!Interpreter::CheckIndex()) break;
						if (Interpreter::CURRENT_CODE[Interpreter::IPOINTER] == '[') count++;
						else if (Interpreter::CURRENT_CODE[Interpreter::IPOINTER] == ']') {
							if (count) count--;
							else break;
						}
					}
				}
				break;
			case ']':
				if (Interpreter::QUEUE.size()==0)
					Interpreter::Error("'[' expected");
				else
					Interpreter::IPOINTER = Interpreter::QUEUE.back()-1;
				break;
				
			case ',':
				char input;
				std::cin >> input;
				Interpreter::CELLS[Interpreter::MPOINTER] = (int)input;
				break;

			case '.':
				char c = Interpreter::CELLS[Interpreter::MPOINTER];
				std::cout<< (((int)c)<20 ? '?' : c);
				break;
		}
		Interpreter::IPOINTER++;

		if (!Interpreter::CheckIndex()) break;
	}
}