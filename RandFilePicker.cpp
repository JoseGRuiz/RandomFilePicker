#include <Windows.h>
#include <filesystem>
#include <random>
//#include <iostream>

namespace fs = std::filesystem;

int main() {
	//std::cout << fs::current_path() << std::endl; prints current path where program is located

	auto currDir = fs::current_path();

	unsigned int i = 0;
	// prints all folders and subfolders in current directory
	for (auto& f : fs::recursive_directory_iterator(currDir)) {
		//std::cout << f << std::endl;
		i++;
	}

	//std::cout << "number of files " << i << std::endl;

	//seed generation
	std::random_device rd;

	//create an engine and chose distribution for random num gen
	std::default_random_engine el(rd());
	std::uniform_int_distribution<int> uniform_dist(1, i);
	fs::directory_entry theChosen;

	int pick;
	unsigned int j = 0;
	bool foundRegular = false;
	int numTries = 3; 

	for(int i = 0; i < numTries && !foundRegular; i++) {
		//make a random pick 
		pick = uniform_dist(el);
		//std::cout << "pick chosen " << pick << std::endl;
		j = 0;
		for (auto& f : fs::recursive_directory_iterator(currDir)) {
			if (j == pick) {
				if (fs::is_regular_file(f)) {
					theChosen = f;
					foundRegular = true;
					break;
				}
				else {
					//try the next files after the randomly picked one 
					//still somewhat random
					for(auto& g : fs::recursive_directory_iterator(f)) {
						if (fs::is_regular_file(g)) {
							theChosen = g; 
							foundRegular = true; 
							break;
						}
					}
				}
			}
			j++;
		}
	}
	//std::cout << theChosen << std::endl;

	fs::path finalFile = theChosen.path();
	std::string fName = finalFile.string();
	ShellExecute(0, 0, fName.c_str(), 0, 0, SW_SHOWNORMAL);
	//system("pause");
	return 0;
}