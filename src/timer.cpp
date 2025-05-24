#include <chrono>
#include <thread>
#include <iostream>
#include <cstdlib>
#include "timer.hpp"
#include "task.hpp"

// run a session for the given label and duration
void Timer::runSession(const std::string &label, int duration) {
	std::cout << "Starting " << label << " session for " << duration << " minutes." << std::endl;

	for (int i = duration; i > 0; i--) {
		std::cout << "Time left: " 
			<< "\033[31m" << i << " minute(s)\033[0m" << std::endl;
		std::this_thread::sleep_for(std::chrono::minutes(1));
	}

	std::cout << label << " session completed!" << std::endl;
	std::cout << "\a" << std::flush;
	std::system("aplay music/triskelion.wav > /dev/null 2>&1");
}

// ask the user before starting a session
bool Timer::askBeforeSession(const std::string& label) {
	std::string choice;
	std::cout << label;
	std::cin >> choice;

	if (choice == "y") {
		return true;
	} else if (choice == "n") {
		return false;
	} else {
		std::cout << "Invalid input. Please enter 'y' or 'n'." << std::endl;
		return askBeforeSession(label);
	}
}

// start a Pomodoro cycle for the given task
void Timer::startPomodoro(Task& task, int duration = 30) {
	int sessionCount = 0;

	std::cout << "Starting Pomodoro for task: " << task.getAction() << std::endl;
	if (task.getStatus() != TaskStatus::Doing) {
		task.setStatus(TaskStatus::Doing);
		std::cout << "Task status set to Doing." << std::endl;
	}
	while (true) {
		std::cout << "\nSession " << (sessionCount + 1) << ": Work\n";
		runSession("Deep Work", duration - (duration / 6));
		task.addPassedMinutes(duration - (duration / 6));
		task.addPomodoroCount();

		if (askBeforeSession("Take a break? (y/n): ")) {
			sessionCount++;
			if (sessionCount >= 4) {
				std::cout << "You have completed 4 sessions. Take a longer break!" << std::endl;
				runSession("Long Break", duration);
				task.addPassedMinutes(duration / 2);
				sessionCount = 0;
			} else {
				std::cout << "You have completed " 
					<< sessionCount << " sessions. Take a short break!" << std::endl;
				runSession("Break", duration / 6);
				task.addPassedMinutes(duration / 6);
			}
		} else {
			break;
		}

		if (!askBeforeSession("Continue with the next session? (y/n): ")) {
			std::cout << "Pomodoro session ended." << std::endl;
			break;
		} 
	}

	if (askBeforeSession("Do you want to mark this task as done? (y/n): ")) {
		task.setStatus(TaskStatus::Done);
		std::cout << "Task marked as done successfully!" << std::endl;
	}
}