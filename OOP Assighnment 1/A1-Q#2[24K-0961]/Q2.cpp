#include <iostream>
#include <string>
#include <tuple>

using namespace std;

class Ball
{
private:
    int x, y;

public:
    Ball(int startX = 0, int startY = 0) : x(startX), y(startY) {}

    int getX() const
    {
        return x;
    }

    int getY() const
    {
        return y;
    }

    void move(int dx, int dy)
    {
        x += dx;
        y += dy;
    }

    std::tuple<int, int> getPosition() const
    {
        return std::make_tuple(x, y);
    }
};

class Robot
{
private:
    std::string name;
    int hits;

public:
    Robot(std::string n) : name(n), hits(0) {}

    void hitBall(int &ballX, int &ballY, const std::string &direction)
    {
        if (direction == "up")
        {
            ballY += 1;
        }
        else if (direction == "down")
        {
            ballY -= 1;
        }
        else if (direction == "left")
        {
            ballX -= 1;
        }
        else if (direction == "right")
        {
            ballX += 1;
        }
        else
        {
            std::cout << "Invalid direction! Ball not moved.\n";
            return;
        }
        hits++;
    }

    int getHits() const
    {
        return hits;
    }

    std::string getName() const
    {
        return name;
    }
};

class Goal
{
private:
    int x, y;

public:
    Goal(int goalX = 3, int goalY = 3) : x(goalX), y(goalY) {}

    bool isGoalReached(int ballX, int ballY) const
    {
        return (ballX == x && ballY == y);
    }
};

class Team
{
private:
    std::string teamName;
    Robot *robot;

public:
    Team(std::string name, Robot *r) : teamName(name), robot(r) {}

    std::string getTeamName() const
    {
        return teamName;
    }

    Robot *getRobot() const
    {
        return robot;
    }
};

class Game
{
private:
    Team *teamOne;
    Team *teamTwo;
    Ball ball;
    Goal goal;

public:
    Game(Team *t1, Team *t2) : teamOne(t1), teamTwo(t2) {}

    void play(Team *team)
    {
        std::cout << "\n"
                  << team->getTeamName() << "'s turn:\n";
        Robot *robot = team->getRobot();
        std::string direction;

        ball.move(-ball.getX(), -ball.getY());

        while (true)
        {

            int ballX = ball.getX();
            int ballY = ball.getY();

            if (goal.isGoalReached(ballX, ballY))
            {
                std::cout << "Goal reached by " << team->getTeamName() << "!\n";
                break;
            }

            std::cout << "Current ball position: (" << ballX << ", " << ballY << ")\n";
            std::cout << "Enter direction (up, down, left, right): ";
            std::cin >> direction;

            robot->hitBall(ballX, ballY, direction);
            ball.move(ballX - ball.getX(), ballY - ball.getY());

            std::cout << "Ball moved to (" << ball.getX() << ", " << ball.getY() << ")\n";
        }
    }

    void startGame()
    {
        std::cout << "Starting the game!\n";
        play(teamOne);
        play(teamTwo);
        declareWinner();
    }

    void declareWinner()
    {
        int hitsTeamOne = teamOne->getRobot()->getHits();
        int hitsTeamTwo = teamTwo->getRobot()->getHits();

        std::cout << "\nGame Over!\n";
        std::cout << teamOne->getTeamName() << " hits: " << hitsTeamOne << "\n";
        std::cout << teamTwo->getTeamName() << " hits: " << hitsTeamTwo << "\n";

        if (hitsTeamOne < hitsTeamTwo)
        {
            std::cout << teamOne->getTeamName() << " wins!\n";
        }
        else if (hitsTeamOne > hitsTeamTwo)
        {
            std::cout << teamTwo->getTeamName() << " wins!\n";
        }
        else
        {
            std::cout << "It's a tie!\n";
        }
    }
};

int main()
{
    string name = "M.MAHAD KHAN";
    string Rollnum = "24K-0961";
    string sec = "BCS-2C";

    cout << "Name: " << name << endl
         << "Roll NUmber: " << Rollnum << endl
         << "Section: " << sec << endl;

    Robot robot1("Robot1");
    Robot robot2("Robot2");

    Team teamOne("Team A", &robot1);
    Team teamTwo("Team B", &robot2);

    Game game(&teamOne, &teamTwo);
    game.startGame();

    return 0;
}