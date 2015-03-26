#pragma once

#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <stack>
#include "ICommand.h"

using std::stack;


class Executor {
private:
	stack<ICommand*> undoStack, redoStack;

public:
	Executor();

	ICommand* execute(ICommand* command);
	ICommand* undo();
	ICommand* redo();
};

#endif