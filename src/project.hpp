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

		const std::string& getProjectName() const;
		const std::vector<Task>& getTasks() const;

		Task*	getTaskById(int id);
		int		addTask(const std::string& description, 
			TaskStatus status = TaskStatus::Pending, 
			int pomodoroCount = 0, int passedMinutes = 0);
		int		removeTask(int id);
		int		updateTask(int id, const std::string& description);
		bool	loadFile(const std::string& filename);
		void	saveFile(const std::string& filename);
		void	listTasks();
};