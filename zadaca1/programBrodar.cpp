#include<iostream>
#include<vector>

using namespace std;

class Hash
{
    private:
    vector<pair<int,float>*> table;
    int size;
    
    int h(int k, int i){
        return (k%size + i*(1 + (k%(size-1)))) % size;
    }

    public:
    Hash(int size): size(size)
    {
        for(int i = 0; i < size; i++)
        {
            table.push_back(nullptr);
        }

    }

    void insert(int k, float v){
        int i = 0;
        while (table[h(k,i)] != nullptr)
        {
            if(k == (*table[h(k,i)]).first)
            {
                table[h(k,i)] =  new pair<int,float>(k,v);
                return;
            }
            i++;
        }
        table[h(k,i)] =  new pair<int,float>(k,v);
    }

    pair<int,float>* search(int k)
    {
        for(int i = 0; i < size; i++)
        {
            if((*table[h(k,i)]).first == k)
            {
                return table[h(k,i)];
            }
        }
        return nullptr;
    }

    void remove(int k)
    {
        for(int i = 0; i < size; i++)
        {
            if((*table[h(k,i)]).first == k)
            {
                table[h(k,i)] = nullptr;
                return;
            }
        }
    }

    void print()
    {
        for(pair<int,float>* p : table)
        {
            if(p == nullptr)
            {
                cout << "nil" << " ";
            }
            else
            {
                cout << "K:" << (*p).first << " " << "V:" << (*p).second << " ";
            }
        }
    }

    ~Hash()
    {
        for(pair<int,float>* p: table)
        {
            delete p;
        }
    }
};

int main()
{  
    Hash hash(19);
    vector<int> keys(10);
    vector<float> values {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.f};

    for (int i = 0; i < 10; i++) 
    {
        cin >> keys[i];
    }

    for (int i = 0; i < 10; i++) 
    {
        hash.insert(keys[i], values[i]);
    }


    hash.remove(keys[6]);
    hash.insert(keys[2], 1.1f);

    hash.print();

    return 0;
}