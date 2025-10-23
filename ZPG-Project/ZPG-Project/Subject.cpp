#include "Subject.h"

void Subject::attachObserver(Observer* observer)
{
	this->observers.push_back(observer);
}

void Subject::detachObserver(Observer* observer)
{
	this->observers.erase(std::remove(this->observers.begin(), this->observers.end(), observer), this->observers.end());
}

void Subject::notifyObservers()
{
	for (Observer* observer : observers)
	{
		observer->Notify();
	}
}