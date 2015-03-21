#include "Executor.h"


Executor::Executor() {
	while (!commandStack.empty()) {
		commandStack.pop();
	}
}

/*
void Executor::execute(ICommand command) {
	command.execute();
	commandStack.push(command);
}
*/