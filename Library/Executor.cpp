#include "Executor.h"


Executor::Executor() {
	while (!undoStack.empty()) {
		undoStack.pop();
	}
}

Command* Executor::execute(Command* command) {
	command->execute();

	if (command->getIsUndoable()) {
		undoStack.push(command);
	}

	return command;
}

Command* Executor::undo() {
	if(undoStack.empty()) {
		return new NullCommand;
	}
	
	Command* commandPtr = undoStack.top();
	redoStack.push(commandPtr);
	commandPtr->undo();
	undoStack.pop();
	return commandPtr;
}

Command* Executor::redo() {
	if(redoStack.empty()) {
		return new NullCommand;
	}

	Command* commandPtr = redoStack.top();
	undoStack.push(commandPtr);
	commandPtr->execute();
	redoStack.pop();
	return commandPtr;
}