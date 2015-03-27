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

	Command* execute(Command* command);
	Command* undo();
	Command* redo();
};

#endif