#include "project.hpp"
#include "task.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Constructor
Project::Project(const std::string& name) : name(name) {}

// Getter
const std::string& Project::getProjectName() const {
	return name;
}

// CRUD
const std::vector<Task>& Project::getTasks() const {
	return tasks;
}

void	Project::listTasks() {
	std::cout << std::endl;
	std::cout << "\033[35m";
	std::cout << "####################################################### "<< std::endl;
	std::cout << "#                                                     #" << std::endl;
	std::cout << "       Project:" << getProjectName() << std::endl;
	std::cout << "#                                                     #" << std::endl;
	std::cout << "####################################################### "<< std::endl;
	std::cout << "\033[0m";

	if (tasks.empty()) {
		std::cout << "No tasks available." << std::endl;
		std::cout << std::endl;
		return;
	}
	for (const auto& task : tasks) {
		std::cout << 
			"ID: " << task.getId() << " TASK: " << task.getAction() << std::endl << std::endl;
	}
}

Task* Project::getTaskById(int id) {
	for (auto& task : tasks) {
		if (task.getId() == id) {
			return &task;
		}
	}
	return nullptr;
}

int Project::addTask(const std::string& action, 
	TaskStatus status, int pomodoroCount, int passedMinutes) {
	Task newTask(++lastTaskId, action, status, pomodoroCount, passedMinutes);
	tasks.push_back(newTask);
	return lastTaskId;
}

int Project::removeTask(int id) {
	for (size_t i = 0; i < tasks.size(); ++i) {
		if (tasks[i].getId() == id) {
			tasks.erase(tasks.begin() + i);
			return 0;
		}
	}
	return -1;
}

int Project::updateTask(int id, const std::string& newAction) {
	Task* task = getTaskById(id);
	if (task) {
		task->setAction(newAction);
		return 0;
	}
	return -1;
}

// Storage Method
bool Project::loadFile(const std::string& filename) {
	std::string path = "data/" + filename;
	std::ifstream file(path);
	std::string line;

	if (!file.is_open()) {
		std::cerr << "Error opening file: " << path << std::endl;
		return false;
	}
	while (std::getline(file, line)) {

		std::string content = line.substr(0, line.size());
		std::istringstream stream(content);
		TaskStatus e_status;
		std::string action, status, count, duration;

		std::getline(stream, action, ',');
		std::getline(stream, status, ',');
		std::getline(stream, count, ',');
		std::getline(stream, duration, ',');

		if (action.empty() || count.empty() || duration.empty()) {
			std::cerr << "Invalid line format: " << line << std::endl;
			std::cerr << action << count << duration << std::endl;
			return false;
		}
		if (status == "Pending") {
			e_status = TaskStatus::Pending;
		} else if (status == "Doing") {
			e_status = TaskStatus::Doing;
		} else if (status == "Done") {
			e_status = TaskStatus::Done;
		} else {
			std::cerr << "Invalid status: " << status << std::endl;
			return false;
		}
		addTask(action, e_status,
			std::stoi(count), std::stoi(duration));
	}
	file.close();
	return true;
}

void Project::saveFile(const std::string& filename) {
	std::string path = "data/" + filename;
	TaskStatus e_status;
	std::string status;
	std::ofstream file(path);

	if (!file.is_open()) {
		std::cerr << "Error opening file: " << path << std::endl;
		return;
	}
	for (const auto& task : tasks) {
		e_status = task.getStatus();
		switch (e_status) {
			case TaskStatus::Pending:
				status = "Pending";
				break;
			case TaskStatus::Doing:
				status = "Doing";
				break;
			case TaskStatus::Done:
				status = "Done";
				break;
		}
		file << task.getAction() << "," << status << ","
			 << task.getPomodoroCount() << "," 
			 << task.getPassedMinutes() << "\n";
	}
	file.close();
}