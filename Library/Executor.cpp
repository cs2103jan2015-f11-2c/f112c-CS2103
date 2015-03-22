#include "Executor.h"


Executor::Executor() {
	while (!undoStack.empty()) {
		undoStack.pop();
	}
}

void Executor::execute(ICommand* command) {
	command->execute();
	undoStack.push(command);
}
