#ifndef _H_UtilityFunctions
#define _H_UtilityFunctions

namespace mas {

template <class T>
T Min(const T& x, const T&y)
{
  return x <= y ? x : y; 
}

template <class T>
T Max(const T& x, const T&y)
{
  return x <= y ? y : x; 
}

template <class T>
T Min(const T& x, const T&y, const T& z)
{
  return Min(Min(x, y), z); 
}

template <class T>
T Max(const T& x, const T&y, const T& z)
{
  return Max(Max(x, y), z); 
}

template <class T>
bool operator != (const T& x, const T&y)
{
  return ! (x == y); 
}

template <class T>
bool operator > (const T& x, const T&y)
{
  return ! (x <= y); 
}

template <class T>
bool operator >= (const T& x, const T&y)
{
  return ! (x < y); 
}

//template <class T>
//bool operator < (const T& x, const T&y)
//{
//  return x <= y && ! (x == y); 
//}
//
template <class T>
void Sort(T& x, T&y)
{
  if (!(x <= y))
    std::swap(x, y); 
    //Swap(x, y); 
}

template <class T>
void Sort(T& x, T&y, T&z)
{
  Sort(y, z);
  Sort(x, y);
  Sort(y, z);
}

template <class T>
bool Sorted(const T& x, const T&y, const T&z)
{
  return x <= y && y <= z;
}

template <class T>
T Square(const T& x)
{
  return x * x;
}

void SkipLine(std::istream& input = std::cin, char delimiter = '\n');

template <class T>
void Swap(T& x, T&y)
{
  if (!(x <= y))
  {
    T m = x;
    x = y;
    y = m;
  }
}

template <class T>
T Result(const T& x, void (T::*f)())
{
  T result(x);
  (result.*f)();
  return result;
}

template <class T, class U>
std::ostream& operator << (std::ostream& output, const std::pair<T, U>& x)
{
  output << x.first << " " << x.second;
  return output;
}

template <class T, class U>
std::istream& operator >> (std::istream& input, std::pair<T, U>& x)
{
  input >> x.first >> x.second;
  return input;
}

//template <class T>
//std::ostream& operator << (std::ostream& output, const T& x)
//{
//  x.Write(output);
//  return output;
//}
//
//template <class T>
//std::istream& operator >> (std::istream& input, T& x)
//{
//  x.Read(input);
//  return input;
//}

}

#endif

