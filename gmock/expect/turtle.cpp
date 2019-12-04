#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../turtle/mock_turtle.h"

class Painter
{
	Turtle * turtle_;
public:
	Painter( Turtle * turtle): turtle_(turtle){}

	int GetX()
	{
		return turtle_->GetX();
    }
};

using ::testing::Return;

TEST(Painter, sticky_1)
{
	MockTurtle turtle;

	int n=1;
	for(int i=n;i>0;i--) {
		EXPECT_CALL(turtle, GetX())
			.WillOnce(Return(10*i));
	}

	Painter painter(&turtle);
	EXPECT_EQ(painter.GetX(),10);
}

TEST(Painter, sticky_2)
{
	MockTurtle turtle;

	int n=2;
	for(int i=n;i>0;i--) {
		EXPECT_CALL(turtle, GetX())
			.WillOnce(Return(10*i))
			.RetiresOnSaturation();
	}

	Painter painter(&turtle);
	EXPECT_EQ(painter.GetX(),10);
	EXPECT_EQ(painter.GetX(),20);
}

TEST(Painter, uninteresting_call)
{
	MockTurtle turtle;

	//No expectations are given to generate "uninteresting call" warning message

	Painter painter(&turtle);
	EXPECT_EQ(painter.GetX(),0);	//0: default action for int
}
