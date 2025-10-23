#pragma once
#include <vector>
#include "Observer.h"

class Subject
{
protected:
	std::vector<Observer*> observers;
public:
	void attachObserver(Observer* observer);
	void detachObserver(Observer* observer);
	void notifyObservers();
};



