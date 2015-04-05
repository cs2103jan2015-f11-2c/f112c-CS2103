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
		logger.log(LogicLog::UNDOSTACK_SIZE, undoStack.size());
		return new NullCommand;
	}
	
	//push most recently executed command from undo stack to redo stack, undo that command
	Command* commandPtr = undoStack.top();
	assert(commandPtr->getIsUndoable());
	redoStack.push(commandPtr);
	commandPtr->undo();
	undoStack.pop();

	logger.log(LogicLog::UNDOSTACK_SIZE, undoStack.size());
	logger.log(LogicLog::REDOSTACK_SIZE, redoStack.size());
	return commandPtr;
}

Command* Executor::redo() {
	if(redoStack.empty()) {
		logger.log(LogicLog::REDOSTACK_SIZE, redoStack.size());
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