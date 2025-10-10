#pragma once

#include "Observer.h"

class CameraObserver : public Observer
{
public:
	void Notify(NotifType type);
};

