#include "Clonable.h"
#include "Date.h"
#include "StringBasic.h"
#include "UtilityFunctions.h"
#include <iostream>

#pragma once

namespace mas
{

class FootballPlayer:
	public Clonable
{
public:
	enum PositionType {GOALKEEPER, DEFENDER, MIDFIELDER, FORWARD};
private:
	StringBasic name;
	Date birthdate;
	int number;
	int position;
	int goals;
	int games;
	int rating;
	bool injured;
public:
	FootballPlayer();
	FootballPlayer(const std::string& name, const Date& birthdate,
		int number, PositionType position, int rating);
	~FootballPlayer(void);

	virtual Clonable* Clone() const;

	virtual void Play(int goals);
	virtual void Injured();
	virtual void UnInjure();
	virtual void RatingUp(int x);
	virtual void RatingDown(int x);

	virtual const StringBasic& Name() const;
	virtual const Date& Birthdate() const;
	virtual PositionType Position() const;
	virtual int Number() const;
	virtual int Games() const;
	virtual int Rating() const;
	virtual bool Injured() const;

	virtual bool operator <= (const FootballPlayer& other) const;
	virtual bool operator < (const FootballPlayer& other) const;

	virtual void Write(std::ostream& output = std::cout) const;
	virtual void WriteLine(std::ostream& output = std::cout) const;
	friend std::ostream& operator << (std::ostream& output, const FootballPlayer& p);

	virtual void Read(std::istream& input = std::cin);
	friend std::istream& operator >> (std::istream& input, FootballPlayer& p);
};

}
