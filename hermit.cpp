#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


int main()
{
    srand (time(0));

// Sieve loop
int sievecounter = 0;
int miningcounter = 0;
int million = 1000000;
int randomone;
int randomtwo;
int randomthree;
int moneycounter = 0;


while (sievecounter < million){
        randomone = rand() % 101;
        randomtwo = rand() % 101;
        randomthree = rand() % 101;

        if(randomone < 5){
            moneycounter = moneycounter + 500;
        }
        if(randomtwo < 5){
            moneycounter = moneycounter + 500;
        }
        if(randomthree < 5){
            moneycounter = moneycounter + 500;
        }
        sievecounter++;
}

double supermillion = 1000000;

supermillion = moneycounter/supermillion;

cout << supermillion << endl;

moneycounter = 0;


while (miningcounter < million){
    randomone = rand() % 101;

 if (randomone == 1){
    moneycounter = moneycounter + 2000;
 }
 if (randomone < 19){
    moneycounter = moneycounter + 200;
 }
 if (randomone < 20){
    moneycounter = moneycounter + 50;
 }
 miningcounter++;
 }


supermillion = 1000000;

supermillion = moneycounter/supermillion;

cout << supermillion << endl;

}





