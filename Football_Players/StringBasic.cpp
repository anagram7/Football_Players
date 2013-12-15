#include "Clonable.h"
#include <iostream>
#include "StringBasic.h"

#include <sstream>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <string>

#include "UtilityFunctions.h"

namespace mas {

StringBasic::StringBasic():
  capacity(defaultCapacity),
  p(new char[defaultCapacity])
{
  *p = 0;
}

StringBasic::StringBasic(const StringBasic& other):
  capacity(other.Count() + 1),
  p(new char[capacity])
{
  ::strcpy(p, other.p);
}

StringBasic::StringBasic(const std::string& s):
  capacity(static_cast<int>(s.size()+1)),
  p(new char[capacity])
{
  ::strcpy(p, s.c_str());
}

StringBasic::StringBasic(const char *s):
  capacity(static_cast<int>(::strlen(s)+1)),
  p(new char[capacity])
{
  ::strcpy(p, s);
}

/*
StringBasic::StringBasic(const char *s):
  capacity(i_strlen(s)+1),
  p(new char[capacity])
{
  i_strcpy(p, s);
}
*/

StringBasic::StringBasic(const StringBasic& other1, const StringBasic& other2):
  capacity(other1.Count() + other2.Count() + 1),
  p(new char[capacity])
{
  ::strcat(::strcpy(p, other1.p), other2.p);
}

StringBasic::StringBasic(const StringBasic& other, int startPos, int endPos):
  capacity(endPos - startPos + 2),
  p(new char[capacity])
{
  strncpy(p, other.p + startPos, capacity - 1);
  p[capacity - 1] = 0;
}

StringBasic::StringBasic(int capacity):
  capacity(capacity),
  p(new char[capacity])
{
  *p = 0;
}

StringBasic::StringBasic(const StringBasic& other, int capacity):
  capacity(capacity),
  p(new char[capacity])
{
  int count = other.Count();
  for (int i = 0; i < capacity - 1; i++)
    p[i] = other.p[i % count];
  p[capacity - 1] = 0;
}

StringBasic::StringBasic(char c):
  capacity(2),
  p(new char[2])
{
  p[0] = c;
  p[1] = 0;
}

StringBasic::StringBasic(char lowerBound, char upperBound):
  capacity(Max(0, upperBound - lowerBound + 1) + 1),
  p(new char[capacity])
{
  for (int i = 0; i < capacity - 1; i++)
    p[i] = static_cast<char>(lowerBound + i);
  p[capacity - 1] = 0;
}

StringBasic::~StringBasic()
{
//  std::cout << "Destructor for " << *this << std::endl;
  //delete [] p;
}

StringBasic& StringBasic::operator = (const StringBasic& other)
{
  Copy(other);
  return *this;
}

void StringBasic::Copy(const StringBasic& other)
{
  if (this != &other)
  {
    delete [] this->p;
    this->capacity = other.Count() + 1;
    this->p = new char[this->capacity];
    ::strcpy(this->p, other.p);
  }
}

// 2002
void StringBasic::SwapOut(StringBasic& other)
{
  std::swap(capacity, other.capacity);
  std::swap(p, other.p);
}

void StringBasic::CopySwap(const StringBasic& other)
{
  StringBasic temp(other);
  SwapOut(temp);
  //SwapOut(StringBasic(other));
}

void StringBasic::Set(const StringBasic& other)
{
  if (this != &other)
  {
    Clear();
    Append(other);
  }  
}

void StringBasic::Set(const StringBasic& other, int startPos, int endPos)
{
  Set(StringBasic(other, startPos, endPos));
}

Clonable* StringBasic::Clone() const
{
  return new StringBasic(*this);
}

int StringBasic::Capacity() const
{
  return capacity;
}

int StringBasic::Count() const
{
  return static_cast<int>(::strlen(p));
}

bool StringBasic::Empty() const
{
  return *p == 0;
}

bool StringBasic::Full() const
{
  return Count() == capacity - 1;
}

bool StringBasic::ValidIndex(int x) const
{
  return 0 <= x && x < Count();
}

bool StringBasic::ValidPosition(int x) const
{
  return 0 <= x && x <= Count();
}

bool StringBasic::ValidRange(int x, int y) const
{
  return ValidPosition(x) && ValidPosition(y + 1) && x <= y + 1;
/*
  return 0 <= x && x <= Count() &&
          -1 <= y && y < Count() &&
          y - x >= -1;
*/
}

bool StringBasic::Has(char c) const
{
  return ::strchr(p, c) != 0;
}

bool StringBasic::HasString(const StringBasic& other) const
{
  return ::strstr(this->p, other.p) != 0;
}

int StringBasic::Position(char c) const
{
  return Position(c, 0);
  //const char* q = ::strchr(p, c);
  //return static_cast<int>(q != 0 ? q - p : -1);
}

int StringBasic::Position(char c, int start) const
{
  const char* q = ::strchr(p+start, c);
  return static_cast<int>(q != 0 ? q - p : -1);
}

int StringBasic::Position(const StringBasic& other) const
{
  return Position(other, 0);
}

int StringBasic::Position(const StringBasic& other, int start) const
{
  const char* q = ::strstr(this->p+start, other.p);
  return static_cast<int>(q != 0 ? q - p : -1);
}

int StringBasic::LastPosition(char c) const
{
  const char* q = ::strrchr(p, c);
  return static_cast<int>(q != 0 ? q - p : -1);
}

int StringBasic::LastPosition(char c, int start) const
{
  for (int i = start; i >= 0; i--)
    if (p[i] == c)
      return i;
  return -1;
}

int StringBasic::LastPosition(const StringBasic& other) const
{
  return LastPosition(other, Count()-1);
}

int StringBasic::LastPosition(const StringBasic& other, int start) const
{
  for (int i = start; i >=0; i--)
//    if (::strncmp(this->p+i, other.p, otherCount) == 0)
    if (::strstr(this->p+i, other.p) != 0)
      return i;
  return -1;
}

const char& StringBasic::At(int x) const
{
  return p[x];
}

const char& StringBasic::Item() const
{
  return p[Count()-1];
}

char& StringBasic::Item()
{
  return p[Count()-1];
}

char& StringBasic::At(int x)
{
  return p[x];
}

const char& StringBasic::operator [](int x) const
{
  return p[x];
}

char& StringBasic::operator [](int x)
{
  return p[x];
}

const char& StringBasic::First() const
{
  return *p;
}

const char& StringBasic::Last() const
{
  return p[Count()-1];
}

bool StringBasic::operator == (const StringBasic& other) const
{
  return ::strcmp(this->p, other.p) == 0;
}

bool StringBasic::operator != (const StringBasic& other) const
{
  return ! operator == (other);
}

bool StringBasic::operator <= (const StringBasic& other) const
{
  return ::strcmp(this->p, other.p) <= 0;
}

bool StringBasic::operator < (const StringBasic& other) const
{
  return ::strcmp(this->p, other.p) < 0;
  //return operator <= (other) && !operator == (other);
}

bool StringBasic::operator >= (const StringBasic& other) const
{
  //return !operator <= (other) || operator == (other);
  return ! operator < (other);
}

bool StringBasic::operator > (const StringBasic& other) const
{
  return ! operator <= (other);
}

bool StringBasic::Equals(const StringBasic& other) const
{
  return ::strcmp(this->p, other.p) == 0;
}

bool StringBasic::LessThan(const StringBasic& other) const
{
  return ::strcmp(this->p, other.p) <= 0;
}

bool StringBasic::StartsBy(const StringBasic& other) const
{
  return ::strncmp(this->p, other.p, other.Count()) == 0;
}

bool StringBasic::EndsBy(const StringBasic& other) const
{
  int thisCount = this->Count();
  int otherCount = other.Count();
  return otherCount <= thisCount
      && ::strcmp(this->p + thisCount - otherCount, other.p) == 0;
}

int StringBasic::Sum() const
{
  int result = 0;
  for (int i=0; p[i] != 0; i++)
    result += static_cast<unsigned char>(p[i]);
  return result;
}

int StringBasic::HashOld() const
{
  int result = 0;
  int i = 0;
  int count = Min(Count(), 127);
  while (i < count)
  {
    int p = 0;
    for (int j = 0; j < 3 && i < count; j++)
      p += 256 * p + static_cast<unsigned char>(At(i++));
    result += p;
  }
  return result;
}

int StringBasic::Hash() const
{
  unsigned result = 0;
  for (int i = 0; p[i] != 0; i++)
  {
    result += static_cast<unsigned>(p[i]);
    result += result << 10;
    result ^= result >> 6;
  }
  result += result << 3;
  result ^= result >> 11;
  result += result << 15;
  return ::abs(static_cast<int>(result));
}

void StringBasic::Append(const StringBasic& other)
{
  if (this != &other)
  {
    GrowTo(this->Count() + other.Count() + 1);
    ::strcat(this->p, other.p);
  }
  else
    Append(StringBasic(*this));   
}

void StringBasic::Prepend(const StringBasic &other)
{
  Insert(other, 0);
}

void StringBasic::Insert(const StringBasic& other, int x)
{
  Replace(x, x-1, other);
}

void StringBasic::Select(int startPos, int endPos)
{
  Head(endPos + 1);
  Erase(0, startPos - 1);
}

void StringBasic::Replace(int startPos, int endPos, const StringBasic& other)
{
  if (this != &other)
  {
    StringBasic temp(*this, endPos+1, Count() - 1);
    Head(startPos);
    GrowTo(Count() - (endPos - startPos + 1) + other.Count() + 1);
    Append(other);
    Append(temp);
  }
  else
    Replace(startPos, endPos, StringBasic(*this));
}

void StringBasic::Put(char c)
{
  int x = Count();
  p[x] = c;
  p[x+1] = 0;
}

void StringBasic::PutAt(char c, int x)
{
  p[x] = c;
}

void StringBasic::Extend(char c)
{
  GrowTo(Count() + 2);
  Put(c);
}

void StringBasic::Precede(char c)
{
  Insert(c, 0);
}

void StringBasic::Insert(char c, int x)
{
  int count = Count();
  GrowTo(count + 2);
  ::memmove(p+x+1, p+x, count+1-x);
  p[x] = c;
}

StringBasic& StringBasic::operator += (const StringBasic& other)
{
  Append(other);
  return *this;
}

StringBasic& StringBasic::operator += (char c)
{
  Extend(c);
  return *this;
}

StringBasic& StringBasic::operator *= (int n)
{
  StringBasic temp(*this);
  Clear();
  GrowTo(n * temp.Count() + 1);
  for (int i = 0; i < n; i++)
    Append(temp);
  return *this;
}

StringBasic StringBasic::operator + (const StringBasic& other) const
{
  return StringBasic (*this, other);
}

StringBasic StringBasic::operator + (char c) const
{
  return StringBasic(*this, StringBasic(c));
}

StringBasic StringBasic::operator * (int n) const
{
  return StringBasic(*this, Count() * n + 1);
}

void StringBasic::Head(int n)
{
  if (n < Count())
    p[n] = 0;
}

void StringBasic::Tail(int n)
{
  int count = Count();
  if (n < count)
    ::memmove(p, p + count - n, n+1);
}

void StringBasic::RemoveLast()
{
  RemoveLast(1);
}

void StringBasic::RemoveLast(int n)
{
  Head(Max(0, Count() - n));
}

void StringBasic::RemoveFirst()
{
  RemoveFirst(1);
}

void StringBasic::RemoveFirst(int n)
{
  Tail(Max(0, Count() - n));
}

void StringBasic::Remove()
{
  p[Count()-1] = 0;
}

void StringBasic::RemoveAt(int x)
{
  ::memmove(p+x, p+x+1, Count() - x);
}

void StringBasic::Prune(char c)
{
  int x = Position(c);
  if (x != -1)
    RemoveAt(x);
}

void StringBasic::PruneLast(char c)
{
  int x = LastPosition(c);
  if (x != -1)
    RemoveAt(x);
}

void StringBasic::PruneAll(char c)
{
  int j = 0;
  for (int i = 0; p[i] != 0; i++)
    if (p[i] != c)
      p[j++] = p[i];
  p[j] = 0;
}

void StringBasic::Erase(int startPos, int endPos)
{
  ::memmove(p+startPos, p+endPos+1, Count() - endPos);
}

void StringBasic::Clear()
{
  *p = 0;
}

void StringBasic::GrowTo(int newCapacity)
{
  if (newCapacity > capacity)
    Reallocate(newCapacity);
}

void StringBasic::Adjust()
{
  if (!Full())
    Reallocate(Count() + 1);
}

void StringBasic::Reallocate(int newCapacity)
{
  char *q = p;
  p = new char[newCapacity];
  capacity = newCapacity;
  ::strcpy(p, q);
  delete [] q;
}

void StringBasic::Reverse()
{
  for (int i=0, j=Count() - 1; i < j; i++, j--)
    Swap(i, j);
}

void StringBasic::SendToBack()
{
  SendToBack(1);
}

void StringBasic::SendToBack(int n)
{
  StringBasic temp(*this, 0, Min(Count(), n) - 1);
  RemoveFirst(n);
  Append(temp);
}

void StringBasic::BringToFront()
{
  BringToFront(1);
}

void StringBasic::BringToFront(int n)
{
  SendToBack(Max(0, Count() - n));
}

void StringBasic::Swap(int x, int y)
{
  char m = p[x];
  p[x] = p[y];
  p[y] = m;
}

void StringBasic::ToLowercase()
{
  for (int i = 0; i < Count(); i++)
    p[i] = static_cast<char>(::tolower(p[i])); 
}

void StringBasic::ToUppercase()
{
  for (int i = 0; i < Count(); i++)
    p[i] = static_cast<char>(::toupper(p[i])); 
}

void StringBasic::Write(std::ostream& output) const
{
  output << p;
}

void StringBasic::Read(std::istream& input)
{
  Read(input, '\n');
}

void StringBasic::Read(char delimiter)
{
  Read(std::cin, delimiter);
}

void StringBasic::Read0(std::istream& input, char delimiter)  // old version
{
  Clear();
  int c;
  while (c = input.get(), input && c != delimiter)
    Extend(static_cast<char>(c));
}

void StringBasic::Read(std::istream& input, char delimiter)
{
  Clear();
  input.getline(p, capacity, delimiter);
  if (input.fail() && !input.eof())
    ReadNext(input, delimiter);
}

void StringBasic::ReadNext(std::istream& input, char delimiter)
{
  input.clear();
  GrowTo(2*capacity);
  input.getline(p + capacity / 2 - 1, capacity / 2 + 1, delimiter);
  if (input.fail() && !input.eof())
    ReadNext(input, delimiter);
}

//void StringBasic::Read(std::istream& input, char delimiter)
//{
//  Clear();
//  input.getline(p, capacity, delimiter);
//  if (input.fail() && !input.eof())
//  {
//    input.clear();
//    ReadNext(input, delimiter);
//  }
//}
//
//void StringBasic::ReadNext(std::istream& input, char delimiter)
//{
//  GrowTo(2*capacity);
//  char* q = p + capacity / 2 - 1;
//  //std::cout << p << "/" << q << std::endl;
//  input.getline(q, capacity / 2 + 1, delimiter);
//  //std::cout << p << "-" << q << std::endl;
//  if (input.fail() && !input.eof())
//  {
//    input.clear();
//    ReadNext(input, delimiter);
//  }
//}

void StringBasic::ReadUpTo(std::istream& input, const StringBasic& delimiters)
{
  Clear();
  int c;
  while (c = input.get(), input && !delimiters.Has(static_cast<char>(c)))
    Extend(static_cast<char>(c));
  if (input) 
    Extend(static_cast<char>(c));
  // the string that was read carries the actual delimiter, if there is one.
}

void StringBasic::Accept(const StringBasic& prompt)
{
  prompt.Write();
  Read(); 
}

void StringBasic::WriteLine(std::ostream& output) const
{
  Write(output);
  output << std::endl;
}

const char* StringBasic::Image() const
{
  return p;
}

int StringBasic::CountIf(const StringBasic& other) const
{
  int result = 0;
  for (int i=0; p[i] != 0; i++)
    result += other.Has(p[i]);
  return result;
}

int StringBasic::CountIfNot(const StringBasic& other) const
{
  return Count() - CountIf(other);
}

void StringBasic::PruneIf(const StringBasic& other)
{
  int j = 0;
  for (int i = 0; p[i] != 0; i++)
    if (!other.Has(p[i]))
      p[j++] = p[i];
  p[j] = 0;
}

void StringBasic::PruneIfNot(const StringBasic& other)
{
  int j = 0;
  for (int i = 0; p[i] != 0; i++)
    if (other.Has(p[i]))
      p[j++] = p[i];
  p[j] = 0;
}

int StringBasic::PositionIf(const StringBasic& other) const
{
  return PositionIf(other, 0);
}

int StringBasic::PositionIfNot(const StringBasic& other) const
{
  return PositionIfNot(other, 0);
}

int StringBasic::LastPositionIf(const StringBasic& other) const
{
  return LastPositionIf(other, Count() - 1);
}

int StringBasic::LastPositionIfNot(const StringBasic& other) const
{
  return LastPositionIfNot(other, Count() - 1);
}

int StringBasic::PositionIf(const StringBasic& other, int start) const
{
  for (int i = start; p[i] != 0; i++)
    if (other.Has(p[i]))
      return i;
  return -1;
}

int StringBasic::PositionIfNot(const StringBasic& other, int start) const
{
  for (int i = start; p[i] != 0; i++)
    if (!other.Has(p[i]))
      return i;
  return -1;
}

int StringBasic::LastPositionIf(const StringBasic& other, int start) const
{
  for (int i = start; i >= 0; i--)
    if (other.Has(p[i]))
      return i;
  return -1;
}

int StringBasic::LastPositionIfNot(const StringBasic& other, int start) const
{
  for (int i = start; i >= 0; i--)
    if (!other.Has(p[i]))
      return i;
  return -1;
}

void StringBasic::TrimLeft()
{
  int x = PositionIfNot(" ");
  if (x == -1)
    Clear();
  else
    Erase(0, x-1);
}

void StringBasic::TrimRight()
{
  Head(LastPositionIfNot(" ") + 1);
}

void StringBasic::Trim()
{
  TrimRight();
  TrimLeft();
}

StringBasic StringBasic::Numeral(int n, int base)
{
  StringBasic result(33);
  if (n < 0)
    result.Extend('-');
  result.AppendNumeral(::abs(n), base);
  return result;
}

StringBasic StringBasic::Fixed(double x, int precision)
{
  std::stringstream sst;
  sst << std::fixed << std::setprecision(precision) << x;
  return StringBasic(sst.str());
}

StringBasic StringBasic::Scientific(double x, int precision)
{
  std::stringstream sst;
  sst << std::scientific << std::setprecision(precision) << x;
  return StringBasic(sst.str());
}

bool StringBasic::IsSorted() const
{
  if (Empty()) 
    return true;
  for (int i = 1; p[i] != 0; i++)
    if (static_cast<unsigned char>(p[i-1]) > static_cast<unsigned char>(p[i]))
      return false;
  return true;
}

void StringBasic::Sort()
{
  if (!Empty())
    Quicksort(0, Count() - 1);
}

void StringBasic::Unique()
{
  int j = 0;
  int i = 0;
  while (p[i] != 0)
  {
    char c = p[i];
    do
      i++;
    while (p[i] == c);
    p[j++] = c;
  }
  p[j] = 0;
}

void StringBasic::Merge(const StringBasic& other)
{
  StringBasic result(Count()+ other.Count() + 1);
  int i = 0;
  int j = 0;
  int k = 0;
  while (p[i] != 0 && other.p[j] != 0)
    if (p[i] <= other.p[j])
      result.p[k++] = p[i++];
    else
      result.p[k++] = other.p[j++];
  while (p[i] != 0)
    result.p[k++] = p[i++];
  while (other.p[j] != 0)
    result.p[k++] = other.p[j++];
  result[k] = 0;
  SwapOut(result);
}

void StringBasic::Intersect(const StringBasic& other)
{
  StringBasic result(Min(Count(), other.Count()) + 1);
  int i = 0;
  int j = 0;
  int k = 0;
  while (p[i] != 0 && other.p[j] != 0)
    if (p[i] == other.p[j])
    {
      result.p[k++] = p[i];
      i++, j++;
    }
    else if (p[i] < other.p[j])
      i++;
    else
      j++;
  result[k] = 0;
  SwapOut(result);
}

void StringBasic::Subtract(const StringBasic& other)
{
  StringBasic result(Count() + 1);
  int i = 0;
  int j = 0;
  int k = 0;
  while (p[i] != 0 && other.p[j] != 0)
  {
    if (p[i] != other.p[j])
      result.p[k++] = p[i];
    else
      j++;
    i++;
  }
  while (p[i] != 0)
    result.p[k++] = p[i++];
  result[k] = 0;
  SwapOut(result);
}

bool StringBasic::Contains(const StringBasic& other) const
{
  int j = 0;
  for (int i = 0; p[i] != 0 && other.p[j] != 0; i++)
    if (p[i] == other.p[j])
      j++;
  return other.p[j] == 0;
}

void StringBasic::Map(const StringBasic& from, const StringBasic& to)
{
  int x;
  for(int i=0; p[i] != 0; i++)
    if ((x = from.Position(p[i])) != -1)
      p[i] = to[x];
}

StringBasic StringBasic::Applied(void (StringBasic::*F)()) const
{
  StringBasic temp(*this);
  (temp.*F)();
  return temp;
}

std::ostream& operator << (std::ostream& output, const StringBasic& s)
{
  s.Write(output);
  return output;
}

std::istream& operator >> (std::istream& input, StringBasic& s)
{
  s.Read(input);
  return input;
}

StringBasic operator + (char x, const StringBasic& y)
{
  return StringBasic(StringBasic(x), y);
}

StringBasic operator + (char* x, const StringBasic& y)
{
  return StringBasic(StringBasic(x), y);
}

void StringBasic::AppendNumeral(int n, int base)
{
  if (n >= base)
    AppendNumeral(n / base, base);
  Extend(Digit(n % base));
}

void StringBasic::Quicksort(int lowerBound, int upperBound)
{
  int i = lowerBound;
  int j = upperBound;
  char pivot = p[(i+j)/2];
  do
  {
    while (static_cast<unsigned char>(p[i]) < static_cast<unsigned char>(pivot))
      i++;
    while (static_cast<unsigned char>(p[j]) > static_cast<unsigned char>(pivot))
      j--;
    if (i <= j)
      Swap(i++, j--);
  } while (i <= j);
  if (lowerBound < j)
    Quicksort(lowerBound, j);
  if (i < upperBound)
    Quicksort(i, upperBound);
}

char StringBasic::Digit(int x)
{
  return static_cast<char>(x < 10 ? x + '0' : x - 10 + 'A');
}

int StringBasic::DigitValue(char c)
{
  return static_cast<int>(c < '0' + 10 ? c - '0' : c + 10 - 'A');
}

void StringBasic::SetDefaultCapacity(int newDefaultCapacity)
{
  defaultCapacity = newDefaultCapacity;
}

int StringBasic::defaultCapacity = 16;

const StringBasic StringBasic::uppercaseLetters('A', 'Z');
const StringBasic StringBasic::lowercaseLetters('a', 'z');
const StringBasic StringBasic::letters(uppercaseLetters, lowercaseLetters);
const StringBasic StringBasic::digits('0', '9');
const StringBasic StringBasic::null;

// ---------

void StringBasic::i_strcpy0(char *s, const char *t)
{
  int i;
  for (i = 0; t[i] != 0; i++)
    s[i] = t[i];
  s[i] = 0;
}

char *StringBasic::i_strcpy(char *s, const char *t)
{
  char *p = s;
  while ((*p++ = *t++) != 0)
    ;
  return s;
}

char *StringBasic::i_strcat(char *s, const char *t)
{
  char *p = s;
  while (*p)
    p++; 
  while ((*p++ = *t++) != 0) 
    ;
  return s;
}

int StringBasic::i_strcmp(const char *s, const char *t)
{
  for ( ; *s == *t; s++, t++)
    if (!*s)
      return 0;
  return *s - *t;
}

char *StringBasic::i_strchr(const char *s, int c)
{
  for ( ; *s; ++s)
    if (*s == c)
      return const_cast<char *>(s);
  return 0;
}

char *StringBasic::i_strstr0(const char *s, const char* t)
{
  int i;
  for ( ; *s; ++s)
    if (*s == *t)
    {
      for (i = 0; t[i]; i++)
        if (s[i] != t[i])
          break;
      if (!t[i])
        return const_cast<char *>(s);
    }
  return 0;
}

char *StringBasic::i_strstr(const char *s, const char* t)
{
  int i;
  for ( ; *s; s++)
  {
    for (i = 0; t[i] && s[i] != t[i]; i++)
      ;
    if (!t[i])
      return const_cast<char *>(s);
  }
  return 0;
}

int StringBasic::i_strlen0(const char *s)
{
  int i = 0;
  while (s[i] != 0)
    i++;
  return i;
}

int StringBasic::i_strlen(const char *s)
{
  const char *p = s;
  while (*p)
    p++;
  return static_cast<int>(p - s);
}

bool StringBasic::StartsBy0(const StringBasic& other) const
{
  StringBasic temp(*this);
  temp.Head(other.Count());
  return temp == other;
}

bool StringBasic::EndsBy0(const StringBasic& other) const
{
  StringBasic temp(*this);
  temp.Tail(other.Count());
  return temp == other;
}

int StringBasic::AsInt(int base) const
{
  int  result;
  char *endp;
  errno = 0; 
  result = ::strtol(p, &endp, base);
  if (!*p || errno || *endp)
  {
    errno = 0;
    StringBasic message("\"", *this + "\" is not a legal int value.");
    throw message;
  }
  return result;
}

double StringBasic::AsDouble() const
{
  double  result;
  char *endp;
  errno = 0;
  result = ::strtod(p, &endp);
  if (!*p || errno || *endp)
  {
    errno = 0;
    StringBasic message("\"", *this + "\" is not a legal double value.");
    throw message;
  }
  return result;
}

bool StringBasic::IsInt(int base) const
{
  bool result = true;
  try {
    AsInt(base);
  } catch (const mas::StringBasic&) {
    result = false;
  }
  return result;
}

bool StringBasic::IsDouble() const
{
  bool result = true;
  try {
    AsDouble();
  } catch (const mas::StringBasic&) {
    result = false;
  }
  return result;
}

}
