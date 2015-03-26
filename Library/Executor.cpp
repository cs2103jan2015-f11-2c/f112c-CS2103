#include "Executor.h"


Executor::Executor() {
	while (!undoStack.empty()) {
		undoStack.pop();
	}
}

ICommand* Executor::execute(ICommand* command) {
	command->execute();
	undoStack.push(command);
	return undoStack.top();
}

ICommand* Executor::undo() {
	ICommand* commandPtr = undoStack.top();
	redoStack.push(commandPtr);
	commandPtr->undo();
	undoStack.pop();
	return commandPtr;
}