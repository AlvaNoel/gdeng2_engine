#pragma once
#include <string>

#include "GameObject.h"
#include "IWorkerAction.h"

class IExecutionEvent;
class ThreadLoading2 : public IWorkerAction
{
public:
	ThreadLoading2(int id, int objCount, GameObject* obj, IExecutionEvent* executionEvent);
	~ThreadLoading2();
private:
	virtual void onStartTask() override;;

	std::wstring Path;
	IExecutionEvent* exec;

	int id;
	int objCount;
	GameObject* obj;

public:
	bool isRunning;
};

