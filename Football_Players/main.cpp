#include "FootballPlayer.h"

void TestFootballPlayer()
{
	mas::FootballPlayer p1("Miguel", mas::Date(1977, 12, 6), 8, mas::FootballPlayer::FORWARD, 13000);
	p1.WriteLine();
	p1.RatingDown(2000);
	p1.Play(2);
	p1.Injured();
	p1.RatingUp(1000);
	p1.WriteLine();
	mas::FootballPlayer p2("Nuno", mas::Date(1980, 6, 8), 25, mas::FootballPlayer::FORWARD, 11000);
	std::cout << (p1 <= p2) <<(p2 <= p1) << std::endl;
	getchar();
}


void main ()
{
	TestFootballPlayer();
}