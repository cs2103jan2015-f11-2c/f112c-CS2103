#pragma once

#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <stack>
#include "ICommand.h"

using std::stack;


class Executor {
private:
	stack<ICommand*> commandPtrStack;

public:
	Executor();

	void execute(ICommand* command);

};

#endif