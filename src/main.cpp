#include "menu.hpp"
#include "project.hpp"
#include <string>
#include <cstdlib>
#include <iostream>

// execute the action from the main menu based on the given choice
bool executeChoice()
{
	int choice = -1;
	std::string projectName;

	std::cout <<  std::endl << "Enter your choice: ";
	std::cin >> choice;
	std::cin.ignore();

	switch (choice) {
		case 1: {
			std::cout << "Enter your new project name or type (cancel): ";
			std::getline(std::cin, projectName);
			if (projectName == "cancel") {
				return true;
			}
			createNewProject(projectName);
			break;
		}
		case 2:
		{
			listProjects();
			break;
		}
		case 3:
		{
			std::cout << "Enter the name of the project to load or type (cancel): ";
			std::getline(std::cin, projectName);
			if (projectName == "cancel") {
				return true;
			}
			if (!loadProject(projectName)) {
				std::cout << "Failed to load project." << std::endl;
			}
			break;
		}
		case 4:
		{
			std::cout << "Exiting..." << std::endl;
			return false;
		}
		default:
		{
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore();
			}
			std::cout << "\033[31mPlease enter a valid number.\033[0m" << std::endl << std::endl;
			break;
		}
	}
	return true;
}
// load the main menu and execute the appropriate action based on the choice
int	main(int argc, char **argv) {
	int choice = -1;

	while (true) {
		std::cout << std::endl;
		std::cout << "\033[35mWelcome to the Pomodoro Timer!\033[0m" << std::endl;
		std::cout << "Please select an option:" << std::endl << std::endl;
		std::cout << "1. Start a new project" << std::endl;
		std::cout << "2. List all projects" << std::endl;
		std::cout << "3. Load a project" << std::endl;
		std::cout << "4. Exit" << std::endl;
		if (!executeChoice()) {
			break;
		}
	}
	return 0;
}