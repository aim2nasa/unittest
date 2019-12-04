#include "gtest/gtest.h"
#include "gmock/gmock.h"

class Calc{
public:

	virtual ~Calc(){}
	virtual int Plus(int a,int b)=0;
	virtual int Minus(int a,int b)=0;
};

class MockCalc : public Calc{
public:
	MOCK_METHOD(int, Plus, (int a,int b), (override));
	MOCK_METHOD(int, Minus, (int a,int b), (override));
};

class Clerk{
	Calc *calc_;
public:
	Clerk(Calc* p):calc_(p){}

	int add(int a,int b){
		return calc_->Plus(a,b);
	}

	int orderedCall(int a,int b){
		return (calc_->Plus(a,b))*(calc_->Minus(a,b));
	}
};

using ::testing::_;
using ::testing::Return;

TEST(ClerkTest, add)
{
	MockCalc calc;
	EXPECT_CALL(calc, Plus(_,_))
		.Times(2)
		.WillRepeatedly(Return(3));

	Clerk clerk(&calc);
	EXPECT_EQ(clerk.add(1,2),3);
	EXPECT_EQ(clerk.add(5,4),3);	//WillRepeatedly(Return(3))
}

TEST(ClerkTest, exceedCall)
{
	MockCalc calc;
	EXPECT_CALL(calc, Plus(_,_))
		.Times(1)
		.WillRepeatedly(Return(3));

	Clerk clerk(&calc);
	EXPECT_EQ(clerk.add(1,2),3);
	EXPECT_EQ(clerk.add(1,2),3); //exceed call
}

TEST(ClerkTest, loopAdd)
{
	MockCalc calc;

	for(int i=0;i<10;i++){
		EXPECT_CALL(calc, Plus(i+1,i+2))
			.Times(1)
			.WillOnce(Return(i+3));
	}

	Clerk clerk(&calc);
	for(int i=0;i<10;i++){
		EXPECT_EQ(clerk.add(i+1,i+2),i+3);
	}
}

TEST(ClerkTest, multipleExpectations)
{
	MockCalc calc;
	EXPECT_CALL(calc, Plus(_,_));
	EXPECT_CALL(calc, Plus(_,_))
		.Times(2);

	Clerk clerk(&calc);
	EXPECT_EQ(clerk.add(1,2),0);	//0: default action for int
	EXPECT_EQ(clerk.add(1,2),0);
	EXPECT_EQ(clerk.add(1,2),0);
}

using ::testing::InSequence;

TEST(ClerkTest, orderedCall)
{
	MockCalc calc;

	InSequence seq;

	//Right Call sequence with Clerk::orderedCall
	EXPECT_CALL(calc,Plus);		//Plus was called first in orderdCall
	EXPECT_CALL(calc,Minus);	//Minus was called after Plus in orderdCall

	Clerk clerk(&calc);
	EXPECT_EQ(clerk.orderedCall(1,2),0);	//0: default action for int
}

TEST(ClerkTest, outOrderedCall)
{
	MockCalc calc;

	InSequence seq;

	//unmatched Call sequence with Clerk::orderedCall
	EXPECT_CALL(calc,Minus);	//Minus was called after Plus in orderdCall
	EXPECT_CALL(calc,Plus);		//Plus was called first in orderdCall

	Clerk clerk(&calc);
	EXPECT_EQ(clerk.orderedCall(1,2),0);	//0: default action for int
}

int main(int argc, char** argv)
{
	// The following line must be executed to initialize Google Mock
	// (and Google Test) before running the tests.
	::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
