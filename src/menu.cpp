#include <iostream>
#include <string>
#include <filesystem>
#include "project.hpp"
#include "timer.hpp"

namespace fs = std::filesystem;

void listProjects()
{
	std::cout << "Listing all projects..." << std::endl;
	std::string path = "data/";

	bool hasProjects = false;
	for (const auto &entry : fs::directory_iterator(path))
	{
		std::cout << "- " << entry.path().filename().string() << std::endl;
		hasProjects = true;
	}

	if (!hasProjects)
	{
		std::cout << "No project" << std::endl;
	}
	std::cout << std::endl;
}

void addTask(Project& project)
{
	std::string taskName;
	std::cout << "Enter the task: ";
	std::getline(std::cin, taskName);
    if (taskName == "cancel")
    {
        return;
    }
	project.addTask(taskName, TaskStatus::Pending, 0, 0);
	project.saveFile(project.getProjectName());
	std::cout << "\033[32mTask added: " << taskName << "\033[0m" << std::endl;
	std::cout << std::endl;
}

void updateTask(Project& project)
{
	int id;
	std::string newAction;

	std::cout << "Enter the ID of the task to update: ";
	std::cin >> id;
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input. Please enter a valid integer ID." << std::endl;
		return;
	}

	std::cin.ignore();
	std::cout << "Enter the new action: ";
	std::getline(std::cin, newAction);
	if (project.updateTask(id, newAction) == 0)
	{
		std::cout << "\033[32mTask updated: " << id << "- TASK " 
			<< newAction << "\033[0m" << std::endl;
		project.saveFile(project.getProjectName());
	}
	else
		std::cout << "Task not found." << std::endl;
}

void removeTask(Project& project)
{
	int id;

	std::cout << "Enter the ID of the task to remove: ";
	std::cin >> id;
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input. Please enter a valid integer ID." << std::endl;
		return;
	}

	std::cin.ignore();
	if (project.removeTask(id) == 0)
	{
		std::cout << "\033[32mTask removed: " << id << "\033[0m" << std::endl;
		project.saveFile(project.getProjectName());
	}
	else
		std::cout << "Task not found." << std::endl;
}
void startPomodoro(Project& project)
{
	int id;
	std::cout << "Enter the id of the task to start Pomodoro: ";
	std::cin >> id;

	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input. Please enter a valid integer ID." << std::endl;
		return;
	}

	std::cin.ignore();
	Task* task = project.getTaskById(id);
	if (task)
	{
		Timer timer;
		timer.startPomodoro(*task, 30);
		project.saveFile(project.getProjectName());
	}
	else
		std::cout << "Task not found.\n" << std::endl;
}

void printProjectMenu()
{
	std::cout << std::endl;
	std::cout << "\033[35mProject Menu!\033[0m" << std::endl;
	std::cout << "1. Add a task" << std::endl;
	std::cout << "2. Remove a task" << std::endl;
	std::cout << "3. Update a task" << std::endl;
	std::cout << "4. List all tasks" << std::endl;
	std::cout << "5. Start Pomodoro" << std::endl;
	std::cout << "6. Back" << std::endl;
}

void loadProjectMenu(Project& project)
{
	int choice = -1;

	while (true)
	{
		printProjectMenu();
		std::cout << "Enter your choice: ";
		std::cin >> choice;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please enter a valid integer ID." << std::endl;
			continue;
		}

		std::cin.ignore();
		switch (choice)
		{
			case 1: {
				addTask(project);
				break;
			}
			case 2: {
				removeTask(project);
				break;
			}
			case 3: {
				updateTask(project);
				break;
			}
			case 4: {
				project.listTasks();
				break;
			}
			case 5: {
				startPomodoro(project);
				break;
			}
			case 6: {
				std::cout << "Exiting project menu..." << std::endl;
				return;
			}
			default: {
				std::cout << "Invalid choice. Try again with a correct number." << std::endl;
				break;
			}
		}
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please enter a valid integer ID." << std::endl;
		}
	}
}

bool loadProject(std::string& projectName)
{
	Project project(projectName);

	if (projectName == "cancel")
	{
		return true;
	}

	if (!project.loadFile(projectName))
		return false;
	std::cout << "\033[32mProject loaded: " << project.getProjectName() << "\033[0m" << std::endl;
	loadProjectMenu(project);
	return true;
}

void createNewProject(std::string& projectName)
{
	Project project(projectName);
	std::cout << "\033[32mProject created: " << projectName << "\033[0m" << std::endl << std::endl;
	if (fs::exists("data/" + projectName)) {
		std::cout << "Project already exists." 
			<< std::endl;
		return;
	}
	project.saveFile(projectName);
	loadProjectMenu(project);
}
