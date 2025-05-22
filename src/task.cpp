#include "task.hpp"

// Constructor

Task::Task(int id, const std::string& action)
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

// Setter
void Task::setAction(const std::string& newAction) {
	action = newAction;
}

void Task::setStatus(TaskStatus newStatus) {
	status = newStatus;
}

// Other functions
void Task::addPomodoro(int durationMinutes) {
	pomodoroCount++;
	passedMinutes += durationMinutes;
}