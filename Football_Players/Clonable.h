#pragma once

namespace mas
{
class Clonable
{
public:
	virtual Clonable* Clone() const = 0;
	~Clonable(void){};
};
}