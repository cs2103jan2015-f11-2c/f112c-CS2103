//@author A0111089L
#pragma once

#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <stack>
#include "Command.h"

using std::stack;


class Executor {
private:
	stack<Command*> undoStack, redoStack;
	LogicLog logger;

public:
	//constructor, destructor
	Executor();
	~Executor();

	//api
	Command* execute(Command* command);
	Command* undo();
	Command* redo();

	void clearRedo();
};

#endif