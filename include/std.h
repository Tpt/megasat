#ifndef std_h
#define std_h

//Quelques ajouts à la lib standard C++11

#include<cstddef>
#include<functional>

namespace std
{
    template<> struct hash<pair<int,int>>
    {
        size_t operator()(const pair<int,int>& pair) const
        {
            hash<int> hasher;
            return hasher(pair.first) + hasher(pair.second);
        }
    };
}

#endif
