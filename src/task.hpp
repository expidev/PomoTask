#pragma once
#include <string>

enum class TaskStatus {
	Pending,
	Doing,
	Done
};

class Task {
	private:
		int			id;
		std::string	action;
		TaskStatus	status;
		int			pomodoroCount;
		int			passedMinutes;

	public:
		Task(int id, const std::string& action, 
			TaskStatus status = TaskStatus::Pending, 
			int pomodoroCount = 0, int passedMinutes = 0);

		int	getId() const;
		std::string getAction() const;
		TaskStatus getStatus() const;
		int getPomodoroCount() const;
		int getPassedMinutes() const;
		
		void setAction(const std::string& newAction);
		void setStatus(TaskStatus newStatus);
		void addPassedMinutes(int durationMinutes = 25);
		void addPomodoroCount();
};