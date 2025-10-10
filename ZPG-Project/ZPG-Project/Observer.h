#pragma once

enum NotifType
{
	CAMERA
};


class Observer
{
public:
	virtual void Notify(NotifType type) = 0;
};