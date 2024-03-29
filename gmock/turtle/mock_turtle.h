#ifndef __MOCK_TURTLE_H__
#define __MOCK_TURTLE_H__

#include "gmock/gmock.h"
#include "turtle.h"

class MockTurtle : public Turtle
{
public:
	MOCK_METHOD(void, PenUp, (), (override));
	MOCK_METHOD(void, PenDown, (), (override));

	MOCK_METHOD(void, Forward, (int distance), (override));
	MOCK_METHOD(void, Turn, (int degrees), (override));
	MOCK_METHOD(void, GoTo, (int x, int y), (override));
	MOCK_METHOD(int, GetX, (), (const, override));
	MOCK_METHOD(int, GetY, (), (const, override));
};

#endif
