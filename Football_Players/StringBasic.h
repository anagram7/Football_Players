#ifndef _H_StringBasic
#define _H_StringBasic

namespace mas {

class StringBasic: public Clonable {
private:
  int capacity;
  char *p;
private: // static
  static int defaultCapacity;
public:
  StringBasic();
  StringBasic(const StringBasic& other);
  StringBasic(const std::string& s);
  StringBasic(const char *s);
  StringBasic(const StringBasic& other1, const StringBasic& other2);
  StringBasic(const StringBasic& other, int startPos, int endPos);
                                                       // pre other.ValidRange(startPos, endPos);
  explicit StringBasic(char c);
  StringBasic(char lowerBound, char upperBound);
  explicit StringBasic(int capacity);  // pre capacity >= 1;
  StringBasic(const StringBasic& other, int capacity); 
                                                      // pre !other.Empty() && capacity >= 1;
                                                      // post Full();
   
  virtual ~StringBasic();

  virtual Clonable* Clone() const;
  virtual void Copy(const StringBasic& other);
  virtual StringBasic& operator = (const StringBasic& other);
  virtual void SwapOut(StringBasic& other);
  virtual void CopySwap(const StringBasic& other);

  virtual void Set(const StringBasic& other);
  virtual void Set(const StringBasic& other, int startPos, int endPos);
                                             // pre other.ValidRange(startPos, endPos);

  virtual int Capacity() const;
  virtual int Count() const;
  virtual bool Empty() const;
  virtual bool Full() const;

  virtual void Append(const StringBasic& other);
  virtual void Select(int startPos, int endPos);   // pre ValidRange(startPos, endPos);
  virtual void Insert(const StringBasic& other, int x);   // pre ValidPosition(x);
  virtual void Replace(int startPos, int endPos, const StringBasic& other);
                                                                  // pre ValidRange(startPos, endPos)
  virtual void Erase(int startPos, int endPos);  // pre ValidRange(startPos, endPos);
  virtual void Clear();                                   // post Empty();
  virtual int Position(const StringBasic& other) const;
  virtual int LastPosition(const StringBasic& other) const;
  virtual const char& At(int x) const;              // pre ValidIndex(x);
  virtual void PutAt(char c, int x);                  // pre ValidIndex(x);

  virtual bool ValidIndex(int x) const;
  virtual bool ValidPosition(int x) const;
  virtual bool ValidRange(int x, int y) const;
  
  virtual bool operator == (const StringBasic& other) const;
  virtual bool operator != (const StringBasic& other) const;
  virtual bool operator <= (const StringBasic& other) const;
  virtual bool operator <  (const StringBasic& other) const;
  virtual bool operator >= (const StringBasic& other) const;
  virtual bool operator >  (const StringBasic& other) const;

  virtual bool Equals(const StringBasic& other) const;        // do not redefine.
  virtual bool LessThan(const StringBasic& other) const;   // do not redefine.

  virtual void Read(std::istream& input = std::cin);
  virtual void Read(std::istream& input, char delimiter);
  virtual void Read(char delimiter);
  virtual void Write(std::ostream& output = std::cout) const;
  virtual void WriteLine(std::ostream& output= std::cout) const;

  virtual void GrowTo(int n);
  virtual void Adjust();   // post Full();

  virtual bool Has(char c) const;
  virtual bool HasString(const StringBasic& other) const;
  virtual int Position(char c) const;
  virtual int Position(char c, int start) const;   // pre ValidPosition(start);
  virtual int Position(const StringBasic& other, int start) const;
                                                                // pre ValidPosition(start);
  virtual int LastPosition(char c) const;
  virtual int LastPosition(char c, int start) const;   // pre start < Count();
  virtual int LastPosition(const StringBasic& other, int start) const;
                                                               //  pre start < Count();

  virtual char& At(int x);  // pre ValidIndex(x);
  virtual const char& operator [](int x) const; // pre ValidIndex(x);
  virtual char& operator [](int x);    // pre ValidIndex(x);
  virtual const char& First() const;   // pre !Empty();
  virtual const char& Last() const;   // pre !Empty();
  virtual const char& Item() const;  // pre !Empty();
  virtual char& Item();                   // pre !Empty();
  
  virtual void Prepend(const StringBasic &other);
  virtual void Insert(char c, int x);   // pre ValidPosition(x);

  virtual void Put(char c);   // pre !Full();
  virtual void Extend(char c);
  virtual void Precede(char c);

  virtual StringBasic& operator += (const StringBasic& other);
  virtual StringBasic& operator += (char c);
  virtual StringBasic& operator *= (int n);  // pre n >= 0;
  virtual StringBasic operator + (const StringBasic& other) const;
  virtual StringBasic operator + (char c) const;
  virtual StringBasic operator * (int n) const;   // pre n >= 0;

  virtual void Head(int n);  // pre n >= 0;
  virtual void Tail(int n);     // pre n >= 0;
  virtual void RemoveLast();
  virtual void RemoveLast(int n); // pre n >= 0;
  virtual void RemoveFirst();
  virtual void RemoveFirst(int n);  // pre n >= 0;
  virtual void Remove(); // pre !Empty();
  virtual void RemoveAt(int x); // pre ValidIndex(x);
  virtual void Prune(char c);
  virtual void PruneLast(char c);
  virtual void PruneAll(char c);

  virtual int CountIf(const StringBasic& other) const;
  virtual int CountIfNot(const StringBasic& other) const;
  virtual void PruneIf(const StringBasic& other);
  virtual void PruneIfNot(const StringBasic& other);

  virtual int PositionIf(const StringBasic& other) const;
  virtual int PositionIfNot(const StringBasic& other) const;
  virtual int LastPositionIf(const StringBasic& other) const;
  virtual int LastPositionIfNot(const StringBasic& other) const;
  virtual int PositionIf(const StringBasic& other, int start) const;      //  pre start >= 0;
  virtual int PositionIfNot(const StringBasic& other, int start) const; //  pre start >= 0;
  virtual int LastPositionIf(const StringBasic& other, int start) const;
                                                                                         //  pre start < Count();
  virtual int LastPositionIfNot(const StringBasic& other, int start) const;
                                                                                         //  pre start < Count();
  virtual void Trim(); 
  virtual void TrimLeft(); 
  virtual void TrimRight(); 

  virtual bool StartsBy(const StringBasic& other) const;
  virtual bool EndsBy(const StringBasic& other) const;

  virtual void Reverse();
  virtual void Swap(int x, int y);  // pre ValidIndex(x) && ValidIndex(y);
  virtual void SendToBack();
  virtual void SendToBack(int n); // pre n >= 0;
  virtual void BringToFront();
  virtual void BringToFront(int n); // pre n >= 0;
  
  virtual void ToLowercase();
  virtual void ToUppercase();

  virtual int Sum() const;
  virtual int HashOld() const;   // obsolete, kept for illustration.
  virtual int Hash() const;

  virtual bool IsSorted() const;
  virtual void Sort();  // post IsSorted();
  virtual void Unique();
  virtual void Merge(const StringBasic& other);
  virtual void Intersect(const StringBasic& other);
  virtual void Subtract(const StringBasic& other);
  virtual bool Contains(const StringBasic& other) const;

  virtual void ReadUpTo(std::istream& input, const StringBasic& delimiters);
  virtual void Accept(const StringBasic& prompt);
  virtual const char *Image() const;

  virtual void Map(const StringBasic& from, const StringBasic& to);
                                      //pre from.Count() <= to.Count();

public: // general function
  virtual StringBasic Applied(void (StringBasic::*F)()) const;

public: // static pseudo-constructors
  static StringBasic Numeral(int n, int base = 10);  // pre 2 <= base && base <= 36;
  static StringBasic Fixed(double x, int precision = 6);
  static StringBasic Scientific(double x, int precision = 6);

public: // conversion to number
  virtual int AsInt(int base = 10) const;  // pre 2 <= base && base <= 36;
  virtual double AsDouble() const;
// 2003
  virtual bool IsInt(int base = 10) const;  // pre 2 <= base && base <= 36;
  virtual bool IsDouble() const;

public: // static
  static char Digit(int x);  // pre 0 <= x && x < 36;
  static int DigitValue(char c);  // pre '0' <= c && c < '9' || 'A' <= c && c < 'Z';
  static void SetDefaultCapacity(int newDefaultCapacity);

public: // friend
  friend std::ostream& operator << (std::ostream& output, const StringBasic& s);
  friend std::istream& operator >> (std::istream& input, StringBasic& s);
  friend StringBasic operator + (char x, const StringBasic& y);
  friend StringBasic operator + (char* x, const StringBasic& y);

public: // static constants
  static const StringBasic uppercaseLetters;
  static const StringBasic lowercaseLetters;
  static const StringBasic letters;
  static const StringBasic digits;
  static const StringBasic null;

private:
  virtual void AppendNumeral(int n, int base);  
                                                         // pre n >= 0 && 2 <= base && base <= 36;
  virtual void ReadNext(std::istream& input, char delimiter);
  virtual void Reallocate(int newCapacity);  // pre newCapacity >= Count() + 1;
  virtual void Quicksort(int lowerBound, int upperBound);

public: // static basic char* functions programmed here for illustration
  static void i_strcpy0(char *s, const char *t);
  static char *i_strcpy(char *s, const char *t);
  static char *i_strcat(char *s, const char *t);
  static int i_strcmp(const char *s, const char *t);
  static char *i_strchr(const char *s, int c);
  static char *i_strstr(const char *s, const char *t);
  static int i_strlen0(const char *s);
  static int i_strlen(const char *s);

  static char *i_strstr0(const char *s, const char *t);
public: // for illustration
  virtual bool StartsBy0(const StringBasic& other) const;
  virtual bool EndsBy0(const StringBasic& other) const;
  virtual void Read0(std::istream& input, char delimiter);
};

}

#endif
