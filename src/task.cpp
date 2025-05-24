#include "task.hpp"

// Constructor

Task::Task(int id, const std::string& action, 
			TaskStatus status, 
			int pomodoroCount, int passedMinutes)
	: id(id), action(action), status(TaskStatus::Pending),
	pomodoroCount(0), passedMinutes(0)
{}

// Getter
int Task::getId() const {
	return id;
}

std::string Task::getAction() const {
	return action;
}

int Task::getPomodoroCount() const {
	return pomodoroCount;
}

int Task::getPassedMinutes() const {
	return passedMinutes;
}

TaskStatus Task::getStatus() const {
	return status;
}

// Setter
void Task::setAction(const std::string& newAction) {
	action = newAction;
}

void Task::setStatus(TaskStatus newStatus) {
	status = newStatus;
}

// Other functions
void Task::addPassedMinutes(int durationMinutes) {
	passedMinutes += durationMinutes;
}

void Task::addPomodoroCount() {
	pomodoroCount += 1;
}