##string
iterator:begin(), end(), rbegin(), rend(), cbegin(), crbegin(), crend().
###构造函数:constructor
```
int main ()
{
  std::string s0 ("Initial string");

  // constructors used in the same order as described above:
  std::string s1;
  std::string s2 (s0);
  std::string s3 (s0, 8, 3);
  std::string s4 ("A character sequence");
  std::string s5 ("Another character sequence", 12);
  std::string s6a (10, 'x');
  std::string s6b (10, 42);      // 42 is the ASCII code for '*'
  std::string s7 (s0.begin(), s0.begin()+7);

  std::cout << "s1: " << s1 << "\ns2: " << s2 << "\ns3: " << s3;
  std::cout << "\ns4: " << s4 << "\ns5: " << s5 << "\ns6a: " << s6a;
  std::cout << "\ns6b: " << s6b << "\ns7: " << s7 << '\n';
  return 0;
}
```
###capacity
size()==length() 注意，这两个函数的反之值是一样的，而且是value in bytes，比如“中国”对应的长度是6.
capacity():目前string 可以存下的字符数目（不新增内存空间）
clear(), empty(), reverse()
###element access
[], back(), front(), at
###modifier
+=, append(), push_back(), assign(), erase(), replace, swap(), pop_back().
replace:
```
int main ()
{
  std::string base="this is a test string.";
  std::string str2="n example";
  std::string str3="sample phrase";
  std::string str4="useful.";

  // replace signatures used in the same order as described above:

  // Using positions:                 0123456789*123456789*12345
  std::string str=base;           // "this is a test string."
  str.replace(9,5,str2);          // "this is an example string." (1)
  str.replace(19,6,str3,7,6);     // "this is an example phrase." (2)
  str.replace(8,10,"just a");     // "this is just a phrase."     (3)
  str.replace(8,6,"a shorty",7);  // "this is a short phrase."    (4)
  str.replace(22,1,3,'!');        // "this is a short phrase!!!"  (5)

  // Using iterators:                                               0123456789*123456789*
  str.replace(str.begin(),str.end()-3,str3);                    // "sample phrase!!!"      (1)
  str.replace(str.begin(),str.begin()+6,"replace");             // "replace phrase!!!"     (3)
  str.replace(str.begin()+8,str.begin()+14,"is coolness",7);    // "replace is cool!!!"    (4)
  str.replace(str.begin()+12,str.end()-4,4,'o');                // "replace is cooool!!!"  (5)
  str.replace(str.begin()+11,str.end(),str4.begin(),str4.end());// "replace is useful."    (6)
  std::cout << str << '\n';
  return 0;
}
```
类似replace的函数，表示位置，我们用的是pos，表示子串，我们用的是<pos, length>

###string operation.
c_str() == data.
find(). find参数为子串和搜索位置，注意，我们不能指定搜索的长度
```
size_t find (const string& str, size_t pos = 0) const noexcept;
size_t find (const char* s, size_t pos = 0) const;
size_t find (const char* s, size_t pos, size_type n) const;
size_t find (char c, size_t pos = 0) const noexcept;
```
find_first_of(substr, pos): 和上面函数最大的不同，这个函数的要求是任意匹配.
find_first_not_of(substr, pos).
string substr (size_t pos = 0, size_t len = npos) const;
compare(pos, len1, str2, pos2, len2)
```
  std::string str1 ("green apple");
  std::string str2 ("red apple");

  if (str1.compare(str2) != 0)
    std::cout << str1 << " is not " << str2 << '\n';

  if (str1.compare(6,5,"apple") == 0)
    std::cout << "still, " << str1 << " is an apple\n";

  if (str2.compare(str2.size()-5,5,"apple") == 0)
    std::cout << "and " << str2 << " is also an apple\n";

  if (str1.compare(6,5,str2,4,5) == 0)
    std::cout << "therefore, both are apples\n";
```
##vector
vector的成员和string类似
###constructor.
```
  std::vector<int> first;                                // empty vector of ints
  std::vector<int> second (4,100);                       // four ints with value 100
  std::vector<int> third (second.begin(),second.end());  // iterating through second
  std::vector<int> fourth (third);                       // a copy of third
```
##set
###constructor.
```
// constructing sets
#include <iostream>
#include <set>

bool fncomp (int lhs, int rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const int& lhs, const int& rhs) const
  {return lhs<rhs;}
};

int main ()
{
  std::set<int> first;                           // empty set of ints

  int myints[]= {10,20,30,40,50};
  std::set<int> second (myints,myints+5);        // range

  std::set<int> third (second);                  // a copy of second

  std::set<int> fourth (second.begin(), second.end());  // iterator ctor.

  std::set<int,classcomp> fifth;                 // class as Compare

  bool(*fn_pt)(int,int) = fncomp;
  std::set<int,bool(*)(int,int)> sixth (fn_pt);  // function pointer as Compare

  return 0;
}
```

### others
key_comp();
>Returns a copy of the comparison object used by the container.
By default, this is a less object, which returns the same as operator<.
This object determines the order of the elements in the container: it is a function pointer or a function object that takes two arguments of the same type as the container elements, and returns true if the first argument is considered to go before the second in the strict weak ordering it defines, and false otherwise.
Two elements of a set are considered equivalent if key_comp returns false reflexively (i.e., no matter the order in which the elements are passed as arguments).
In set containers, the keys to sort the elements are the values themselves, therefore key_comp and its sibling member function value_comp are equivalent.

lower_bound() && uppper_bound().
这是一个前闭后开的区间, lower_bound(3) && uppper_bound(3)入下图所示。
1, 2, 3, 3, 4, 6, 7, 7, 7, 7, 9
	  ^     ^	  ^
	  l.3   u.3   l(6.5) 如果找不到这个元素，lower_bound == uppper_bound。
##map
同set类似


##queue
##list
##int,double,string
cstdlib:atoi(), atol(), atof().
strtod, strtof, strtol, strtold, strtoll, strtoul, strtoull
```
/* strtod example */
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* strtod */

int main ()
{
  char szOrbits[] = "365.24 29.53";
  char* pEnd;
  double d1, d2;
  d1 = strtod (szOrbits, &pEnd);
  d2 = strtod (pEnd, NULL);
  printf ("The moon completes %.2f orbits per Earth year.\n", d1/d2);
  return 0;
}
```

整数到字符串:
```
char *  itoa ( int value, char * str, int base );
This function is not defined in ANSI-C and is not part of C++, but is supported by some compilers.

A standard-compliant alternative for some cases may be sprintf:
sprintf(str,"%d",value) converts to decimal base.
sprintf(str,"%x",value) converts to hexadecimal base.
sprintf(str,"%o",value) converts to octal base.
```
这个函数的陷阱在于，缓冲区溢出。
