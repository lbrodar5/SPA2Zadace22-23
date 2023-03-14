#include<iostream>
#include<list>
#include<vector>
#include<random>
#include<time.h>

using namespace std;


int random_a()
{
    int a  = 0;
    srand((unsigned)time(NULL));
    for(int i = 0; i < 7; i++)
    {
        a += (rand() % 7)*pow(10,i);
    }
    return a;
}


class HashTable
{
    private:
    int a;
    vector<list<pair<int,float>>> container{7};

    int f(int x)
    {
        int t = a;
        int s = 0;
        while(x > 0)
        {
            s += ((x%10)*(t%10));
            x = x/10;
            t = t/10;
        }
        return s%7;
    }

    public:

    HashTable()
    {
        a = random_a();
    }

    void insert(int key, float value)
    {
        container[f(key)].push_back({key,value});
    }

    pair<int,float> search(int key)
    {
        for(auto p : container[f(key)])
        {
            if(key == p.first)
            {
                return p;
            }
        }
        return {};
    }

    void print()
    {
        for(auto l : container)
        {
            for( pair<int,float> p : l)
            {
                cout << "k:" << p.first << " "  << "v:" << p.second << " -> ";
            }
            cout << "" << endl;
        }
    }

};

int main()
{
    HashTable hash;

    vector<int> keys = {123343,2133,6541,32440,230312,132342,213,400,21365,534120,40612};
    vector<float> values;

    for(float i = 0; i < 1.1; i += 0.1)
    {
        values.push_back(i);
    }

    for(int i = 0; i < 11; i++)
    {
        hash.insert(keys[i],values[i]);
    }

    hash.print();  

    cout << hash.search(400).first << " " <<  hash.search(400).second << endl;

    return 0;
}

