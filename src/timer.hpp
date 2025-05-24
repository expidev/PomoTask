#pragma once
#include "task.hpp"

class Timer {
	public:
		void startPomodoro(Task& task, int duration);
	private:
		void runSession(const std::string &label, int duration);
		bool askBeforeSession(const std::string& label);
};