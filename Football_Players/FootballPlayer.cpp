#include "FootballPlayer.h"

using namespace mas;

FootballPlayer::FootballPlayer()
{
}

FootballPlayer::FootballPlayer(const std::string& name, const Date& birthdate, 
	int number, PositionType position, int rating):
	name(name), 
	birthdate(birthdate), 
	number(number),
	position(position),
	goals(0),
	games(0), 
	rating(rating), 
	injured(false)
{
}

FootballPlayer::~FootballPlayer(void)
{
}

Clonable* FootballPlayer::Clone() const
{
	return new FootballPlayer(*this);
}

void FootballPlayer::Play(int goals)
{
	this->goals += goals;
	this->games++;
}

void FootballPlayer::Injured()
{
	injured = true;
}

void FootballPlayer::UnInjure()
{
	injured = false;
}

void FootballPlayer::RatingUp(int x)
{
	rating += x;
}

void FootballPlayer::RatingDown(int x)
{
	rating -= x;
}

const StringBasic& FootballPlayer::Name() const
{
	return name;
}

const Date& FootballPlayer::Birthdate() const
{
	return birthdate;
}

FootballPlayer::PositionType FootballPlayer::Position() const
{
	return static_cast<PositionType>(position);
}

int FootballPlayer::Number() const
{
	return number;
}

int FootballPlayer::Games() const
{
	return games;
}

int FootballPlayer::Rating() const
{
	return rating;
}

bool FootballPlayer::Injured() const
{
	return injured;
}

/*Read like player x is less bad than player y -> done
in this way to easier the task of ordering the vector*/
bool FootballPlayer::operator <= (const FootballPlayer& other) const
{
	return rating > other.rating
		|| rating == other.rating && birthdate >= other.birthdate; 
}

/*Read this operator as the previous one*/
bool FootballPlayer::operator < (const FootballPlayer& other) const
{
	return rating >= other.rating
		&& (rating != other.rating || birthdate > other.birthdate);
}

void FootballPlayer::Write(std::ostream& output) const
{
	output << name << ";" << birthdate << ";" << number << ";"
		<< position << ";" << goals << ";" << games << ";" << rating << ";"
		<< injured << ";";
}

void FootballPlayer::WriteLine(std::ostream& output) const
{
	Write(output);
	output << std::endl;
}

std::ostream& operator << (std::ostream& output, const FootballPlayer& p)
{
	p.Write(output);
	return output;
}

void FootballPlayer::Read(std::istream& input)
{
	name.Read(input, ';');
	if (!input)
		return;
	char c;
	birthdate.Read(input);
	input >> c >> number >> c >> position >> goals >> c >> games >> c >> rating >> c >> injured >> c;
	mas::SkipLine(input);
}

std::istream& operator >> (std::istream& input, FootballPlayer& p)
{
	p.Read(input);
	return input;
}