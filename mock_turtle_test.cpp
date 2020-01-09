#include <gmock/gmock.h>

class Turtle
{
public:
    virtual ~Turtle() {};
    virtual void PenUp() = 0;
    virtual void PenDown() = 0;
    virtual void Forward(int distance) = 0;
    virtual void Turn(int degrees) = 0;
    virtual void GoTo(int x, int y) = 0;
    virtual int GetX() const = 0;
    virtual int GetY() const = 0;
};

class MockTurtle : public Turtle
{
public:
    MOCK_METHOD0(PenUp, void());
    MOCK_METHOD0(PenDown, void());
    MOCK_METHOD1(Forward, void(int distance));
    MOCK_METHOD1(Turn, void(int degrees));
    MOCK_METHOD2(GoTo, void(int x, int y));
    MOCK_CONST_METHOD0(GetX, int());
    MOCK_CONST_METHOD0(GetY, int());
};

class Painter
{
    Turtle* turtle;
public:
    Painter(Turtle* turtle) : turtle(turtle)
    {
    }

    bool DrawCircle(int x, int y, int)
    {
        turtle->GoTo(x, y);
        turtle->PenDown();

        return true;
    }
};

TEST(PainterTest, CanDrawSomething)
{
    MockTurtle turtle;

    // Set expectations
    EXPECT_CALL(turtle, GoTo(100, 50));
    EXPECT_CALL(turtle, PenDown());

    // Call sequence
    Painter painter(&turtle);

    EXPECT_TRUE(painter.DrawCircle(100, 50, 10));
}

int main(int argc, char** argv)
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
