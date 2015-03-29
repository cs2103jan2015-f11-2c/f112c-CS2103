#include "Executor.h"


Executor::Executor() {
	while (!undoStack.empty()) {
		undoStack.pop();
	}

	while (!redoStack.empty()) {
		redoStack.pop();
	}
}


//GETTERS
stack<Command*> Executor::getUndoStack() {
	return undoStack;
}

stack<Command*> Executor::getRedoStack() {
	return redoStack;
}


//FOR EXECUTING COMMANDS
Command* Executor::execute(Command* command) {
	command->execute();

	//only push command into undoStack if it is undoable and it has been executed thoroughly
	if (command->getIsUndoable() && command->getEvent().getID() != Command::INVALID_NUMBER) {
		undoStack.push(command);
	}

	return command;
}

Command* Executor::undo() {
	if(undoStack.empty()) {
		return new NullCommand;
	}
	
	//push most recently executed command from undo stack to redo stack, undo that command
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

	//push most recently undone command from redo stack to undo stack, execute that command
	Command* commandPtr = redoStack.top();
	undoStack.push(commandPtr);
	commandPtr->execute();
	redoStack.pop();
	return commandPtr;
}