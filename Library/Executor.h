#pragma once

#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <stack>
#include "Command.h"

using std::stack;


class Executor {
private:
	stack<Command*> undoStack, redoStack;

public:
	Executor();

	//getters
	stack<Command*> getUndoStack();
	stack<Command*> getRedoStack();

	//methods for executing commands
	Command* execute(Command* command);
	Command* undo();
	Command* redo();
};

#endif