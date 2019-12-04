#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../turtle/mock_turtle.h"
#include "../turtle/painter.h"

using ::testing::AtLeast;

TEST(PainterTest, CanDrawSomething)
{
	MockTurtle turtle;
	EXPECT_CALL(turtle, PenDown()).Times(AtLeast(1));
	Painter painter(&turtle);

	EXPECT_TRUE(painter.DrawCircle(0,0,10));
}
