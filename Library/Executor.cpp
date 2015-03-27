#include "Executor.h"


Executor::Executor() {
	while (!undoStack.empty()) {
		undoStack.pop();
	}
}

ICommand* Executor::execute(ICommand* command) {
	command->execute();

	if (command->getIsUndoable()) {
		undoStack.push(command);
	}

	return command;
}

ICommand* Executor::undo() {
	if(undoStack.empty()) {
		return new NullCommand;
	}
	
	ICommand* commandPtr = undoStack.top();
	redoStack.push(commandPtr);
	commandPtr->undo();
	undoStack.pop();
	return commandPtr;
}

ICommand* Executor::redo() {
	if(redoStack.empty()) {
		return new NullCommand;
	}

	ICommand* commandPtr = redoStack.top();
	undoStack.push(commandPtr);
	commandPtr->execute();
	redoStack.pop();
	return commandPtr;
}