#pragma once

#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <stack>
#include "ICommand.h"

using std::stack;


class Executor {
private:
	stack<ICommand> commandStack;

public:
	Executor();

	//void execute(ICommand command);

};

#endif