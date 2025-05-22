#pragma once
#include <string>
#include <vector>

#include "task.hpp"

class Project {
	private:
		std::string name;
		std::vector<Task> tasks;
		int lastTaskId = 0;

	public:
		Project(const std::string& name);

		std::string& getProjectName() const;
		std::vector<Task>& getTasks() const;

		Task*	getTaskById(int id);
		int		addTask()


}