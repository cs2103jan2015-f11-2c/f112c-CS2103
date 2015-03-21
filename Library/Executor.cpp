#include "Executor.h"


Executor::Executor() {
	while (!commandPtrStack.empty()) {
		commandPtrStack.pop();
	}
}

void Executor::execute(ICommand* command) {
	command->execute();
	commandPtrStack.push(command);
}
