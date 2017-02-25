//
//  main.cpp
//  copy_vs_move
//
//  Created by Kio on 2/25/17.
//  Copyright © 2017 Kio. All rights reserved.
//

#include <iostream>
#include <vector>
#include <chrono>

class Unmobable
{
    int *a;
public:
    Unmobable(int k){ a = new int(k);} ;
    ~Unmobable(){delete[] a;};
    Unmobable(const Unmobable &co){ a = new int; *a = *co.a;};
    Unmobable& operator = (const Unmobable &co) { std::swap(*a,*co.a); return *this;};
};

class Mobable
{
    int *a;
public:
    Mobable(int k){ a = new int(k);} ;
    ~Mobable(){delete[] a;};
    Mobable(const Mobable &co){ a = new int; *a = *co.a;};
    Mobable& operator = (const Mobable &co) { std::swap(*a,*co.a); return *this;};
    Mobable(Mobable&& mov){ a = mov.a; mov.a = nullptr; }
    Mobable& operator= (Mobable&& mo){a = mo.a; mo.a = nullptr; return *this; };
};


void  moves(int n)
{
    std::vector<Mobable> moving;

    auto move_start = std::chrono::system_clock::now();
    
    for (int i=0; i<n ; ++i)
    {
        
        moving.push_back(Mobable(2));
        
    }
    
    auto move_end = std::chrono::system_clock::now();
    auto move_dur = move_end - move_start;
    auto move_msec = std::chrono::duration_cast<std::chrono::milliseconds>(move_dur).count();
    
    std::cout<< "move takes: " <<move_msec <<std::endl;
}

void copies(int n)
{
    std::vector<Unmobable>copying;
    
    auto copy_start = std::chrono::system_clock::now();
    
    for (int i=0; i<n ; ++i)
    {
        
        copying.push_back(Unmobable(3));
        
    }
    
    auto copy_end = std::chrono::system_clock::now();
    auto copy_dur = copy_end - copy_start;
    auto copy_msec = std::chrono::duration_cast<std::chrono::milliseconds>(copy_dur).count();
    
    std::cout<< "copy takes: " << copy_msec <<std::endl;
}

int main(int argc, const char * argv[]) {

    int n = 10000000;
    
    moves(n);
    copies(n);
    
    return 0;
}
