#ifndef _H_Date
#define _H_Date

// Note: all int arguments must be non-negative.

#include <iostream>

namespace mas {

class Date {
private:
  int count;  // number of days since first.
  // invariant count >= 0;
public:
  enum WeekdayType {MONDAY, TUESDAY, WEDNESDAY, THURSDAY, 
                                     FRIDAY, SATURDAY, SUNDAY};
  
  Date();
  Date(const Date& other);
  Date(int year, int month, int day);   // pre Valid(year, month, day);
  Date(int year, int dayNumber);
                      // pre Valid(year) && dayNumber <= DaysInYear(year);
  Date(int year, int week, WeekdayType weekday);  //pre Valid(year) && week >= 1;
  virtual ~Date();

  virtual void Copy(const Date& other);
  virtual Date& operator = (const Date& other);

  virtual bool IsValid() const;
  
  virtual int Year() const;
  virtual int Month() const;
  virtual int Day() const;
  virtual int Century() const;
  virtual int DayNumber() const;
  virtual int Count() const;

  virtual void Set(int year, int month, int day);  // pre Valid(year, month, day);
  virtual void Set(int year, int dayNumber);
                       // pre Valid(year) && dayNumber <= DaysInYear(year);
  virtual void Forth();
  virtual void Back();               // pre operator > (First());
  virtual void Add(int x);
  virtual void Subtract(int x);  // DaysSince(First()) >= x;
  
  virtual int DaysTo(const Date& other) const;         // pre operator <= (other);
  virtual int DaysSince(const Date& other) const;    // pre operator >= (other);

  virtual int Age(const Date& other) const; // pre operator >= (other);

  virtual bool operator == (const Date& other) const;
  virtual bool operator != (const Date& other) const;
  virtual bool operator <= (const Date& other) const;
  virtual bool operator <  (const Date& other) const;
  virtual bool operator >= (const Date& other) const;
  virtual bool operator >  (const Date& other) const;

  virtual const Date& operator ++  (int);
  virtual const Date& operator --  (int);    // pre operator > (First());

  virtual Date& operator +=(int x);
  virtual Date& operator -=(int x);      // pre x <= Count();
  virtual Date operator +(int x) const;
  virtual Date operator -(int x) const; // pre x <= Count();
  virtual int operator - (const Date& other) const;
   
  virtual void Write(std::ostream& output = std::cout) const;
  virtual void WriteLine(std::ostream& output = std::cout) const;
  virtual void Read(std::istream& input = std::cin);
  virtual void Accept(const std::string& prompt, const std::string& errorMessage);
  friend std::ostream& operator << (std::ostream& output, const Date& d);
    
  virtual int MonthSize() const;
  virtual int YearSize() const;
  virtual int CenturySize() const;
  virtual bool InLeapYear() const;
  
  virtual WeekdayType Weekday() const;
  virtual int WeekNumber() const;
  virtual int WeekYear() const;
  
  virtual void Set(int year, int week, WeekdayType weekday);
  virtual void AddWeek(int x = 1);
  virtual void SubtractWeek(int x = 1);   // pre Count() >= 7 * x;
  
  virtual void ReachForward(WeekdayType weekday);
  virtual void ReachBackward(WeekdayType weekday); // pre Count() >= 7;

  virtual bool Weekend() const;
  virtual bool WorkingDay() const;
  virtual bool Holiday() const;

public: // static

  static const Date& First();

  static bool Valid(int y, int m, int d);
  static bool Valid(int y, int m);
  static bool Valid(int y);

  static int Count(int y, int m, int d);   // pre Valid(y, m, d);
  static bool LeapYear(int y);      // pre Valid(y);
  static int DaysInMonth(int y, int m);  // pre Valid(y, m);
  static int DaysInYear(int y);               // pre Valid(y);
  static int CenturyOf(int y);                 // pre y >= 1;
  static int DaysInCentury(int c);         // pre c >= Century(first.Year());
  static int WeeksInYear(int y);           // pre Valid(y - 1);

  static int FirstYearOfCentury(int c);
  static int FirstDayOfCentury(int c);
  static int FirstDayOfYear(int y);
  static int FirstDayOfMonth(int y, int m);
  static int YearsInCentury(int d);       // d < 365 * 100 + 25;

private:  // static data members
  static const int firstYear;
  static const int firstCentury;
  static const Date first;
  static const WeekdayType firstWeekday;
  static const int daysInMonth[2][12];
  static const int accumulated[2][12];
  static const int fourYears;
  static const int oneCentury;
  static const int fourCenturies;

public:  // for illustration only
  virtual int Century2() const;
  virtual int WeekYear0() const;        // pre First().Year() < Year();
  virtual void SetFirstMonday0(int year);   // pre Valid(year);
  static int Centuries2(int d);
  static int FirstDayOfCentury2(int c);
};

}

#endif
