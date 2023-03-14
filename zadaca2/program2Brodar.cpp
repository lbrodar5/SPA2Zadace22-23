#include<iostream>
#include<vector>
#include<string>
#include<math.h>

using namespace std;

class UsernameTable
{
    private:
        int m;
        vector<bool> container;

        int h1(const string& username)
        {
            unsigned long long sum = 0;
            int n = username.length();;

            for(int i = 0; i < n; i++) 
            {
            sum += username[i] % m;
            }

            return sum % m;
        }

        int h2(const string& username)
        {
            unsigned long long sum = 1;
            int n = username.length();
            for(int i = 0; i < n; i++)
            {
                sum +=(unsigned)(username[i] * pow(19, i)) % m;
            }

            return sum % m;
        }
        int h3(const string& username)
        {
            unsigned long long sum = 7;
            int n = username.length();
            for(int i = 0; i < n; i++)
            {
                sum += (unsigned)(username[i] * pow(30, i)) % m;
            }
            return sum % m;
        }
        int h4(const string& username)
        {
            unsigned long long sum = 3;
            int n = username.length();
            for(int i = 0; i < n; i++)
            {
                sum +=(unsigned)(username[i] * pow(3, i) * pow(7,i)) % m;
            }
            return sum % m;
        }
    
    public:

    UsernameTable(int m)
    {
        this->m = m;
        for(int i = 0; i < m; i++)
        {
            container.push_back(false);
        }
    }

    void insert(const string& s)
    {

    int t1 = h1(s);
    int t2 = h2(s);
    int t3 = h3(s);
    int t4 = h4(s);

    container[t1] = true;
    container[t2] = true;
    container[t3] = true;
    container[t4] = true;

    }

string search(const string& s) {
    string naso = "element je vjerojatno u tablici";
    string nije_naso = "element nije u tablici";
    
    if(container[h1(s)] == false) {
        return nije_naso;
    }
    if(container[h2(s)] == false) {
        return nije_naso;
    }
    if(container[h3(s)] == false) {
        return nije_naso;
    }
    if(container[h4(s)] == false) {
        return nije_naso;
    }
    return naso;
}
    
        
};

int main()
{
    UsernameTable table(100);
    vector<string> names = {
        "jopis107", "hstranput", "Matej293", "MateaCucman", "JosipCestar", 
        "lanamak", "DanijelaValjak", "filipuranjek", "domagojziros", "lsanic",
        "TomislavVinkovic", "IvoSusac", "matej2810", "KresimirSecan", 
        "inespejic", "InesSimunovic", "IvanFrantal", "Frle001", "inesstrapac", 
        "mkolak", "Dpritisa", "istvavk", "mtoldi", "lbrodar5", "mkristic", 
        "andreamatasovic", "balentovicanja", "IvanaVinkovic", "prakidzija", 
        "DMV1204", "JMesaric", "KarloKampic", "jurick1910", "LarisaDarojkovic"
    };

    for(auto name : names) {
        table.insert(name);
    }



    cout << table.search("lbrodar5") << endl;
    cout << table.search("KresimirSecan") << endl;
    cout << table.search("nekag lupostt") << endl;
    
    cout << table.search("lol") << endl;

    cout << table.search("IvanFrantal") << endl;
    cout << table.search("Joža") << endl;
    return 0;
}