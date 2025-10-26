#pragma once
#include <vector>
#include "Observer.h"

enum SubjectType
{
	CAMERA,
	LIGHT,
	INPUT
};

class Subject
{
protected:
	std::vector<Observer*> observers;
public:
	void attachObserver(Observer* observer);
	void detachObserver(Observer* observer);
	void notifyObservers(enum SubjectType type);
};



