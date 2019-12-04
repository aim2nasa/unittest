#include "gtest/gtest.h"
#include "gmock/gmock.h"

class Calc{
public:

	virtual ~Calc(){}
	virtual int Plus(int a,int b)=0;
};

class MockCalc : public Calc{
public:
	MOCK_METHOD(int, Plus, (int a,int b), (override));
};

class Clerk{
	Calc *calc_;
public:
	Clerk(Calc* p):calc_(p){}

	int add(int a,int b){
		return calc_->Plus(a,b);
	}
};

using ::testing::_;

TEST(ClerkTest, add)
{
	MockCalc calc;
	EXPECT_CALL(calc, Plus(_,_)).Times(1);
}

int main(int argc, char** argv)
{
	// The following line must be executed to initialize Google Mock
	// (and Google Test) before running the tests.
	::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
