#include "Executor.h"


Executor::Executor() {
	while (!undoStack.empty()) {
		undoStack.pop();
	}

	while (!redoStack.empty()) {
		redoStack.pop();
	}
}

Command* Executor::execute(Command* command) {
	command->execute();

	if (command->getIsUndoable() && command->getEvent().getID() != Command::INVALID_NUMBER) {
		undoStack.push(command);
	}

	logger.log(LogicLog::UNDOSTACK_SIZE, undoStack.size());
	return command;
}

Command* Executor::undo() {
	if(undoStack.empty()) {
		return new NullCommand;
	}
	
	//push most recently executed command from undo stack to redo stack, undo that command
	Command* commandPtr = undoStack.top();
	redoStack.push(commandPtr);
	assert(commandPtr->getIsUndoable());
	commandPtr->undo();
	undoStack.pop();

	logger.log(LogicLog::UNDOSTACK_SIZE, undoStack.size());
	logger.log(LogicLog::REDOSTACK_SIZE, redoStack.size());
	return commandPtr;
}

Command* Executor::redo() {
	if(redoStack.empty()) {
		return new NullCommand;
	}

	//push most recently undone command from redo stack to undo stack, execute that command
	Command* commandPtr = redoStack.top();
	undoStack.push(commandPtr);
	commandPtr->execute();
	redoStack.pop();

	logger.log(LogicLog::UNDOSTACK_SIZE, undoStack.size());
	logger.log(LogicLog::REDOSTACK_SIZE, redoStack.size());
	return commandPtr;
}