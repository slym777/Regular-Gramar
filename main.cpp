/// Gramatica Regulata implementata cu clase
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

ifstream fin("input.in");
string buffer[100];
int n, nr, k, nr_buffer = -1;

class Gr_Reg;

class productie
{
protected:
    string t;
    vector < vector <string> > v;
public:
    friend class Gr_Reg;
    productie newProd(string s);
    productie& operator= (const productie& x)
    {
        if (this != &x)
        {
            t = x.t;
            for (int r = 0; r < (int)x.v.size(); r++)
            for (int j =0; j < (int)x.v[r].size(); j++)
                 v[r][j] = x.v[r][j];
        }
        return *this;
    }
    friend ostream& operator<< (ostream&, const productie&);
    friend void Afisare_cuv(int r,Gr_Reg);
};


class Gr_Reg
{
    static int nr_cuv;
    int lung;
    vector <productie> gram;
public:
    Gr_Reg();
    void get_nr_cuv() { cout << "Nr de cuvinte generate de lungimea " << lung << " este " << endl << nr;}
    void Afisare_cuv(int r);
    friend ostream& operator<< (ostream&, const Gr_Reg&);
};

int Gr_Reg::nr_cuv = 0;

productie productie::newProd(string s)
{
    k = 0;
    //cout << " ! " << endl;
    productie p;
    p.v.resize(1);
    p.t = s[0];
    for (int i = 3; i < (int)s.size(); i++)
    {
        if (s[i] == '|')
            {k++;
            p.v.resize(k+1);}
            //cout << " $ " << endl;}
        else
        {
            p.v[k].push_back(s.substr(i,1));
            //cout << " ? " << endl;
        }
    }
    return p;
}

Gr_Reg::Gr_Reg()
{
    fin >> lung >> n;
    for (int i = 0; i<n; i++)
        {
            string s;
            fin >> s;
            productie p;
            gram.push_back(p.newProd(s));
        }
}


void Gr_Reg::Afisare_cuv(int r)
{
    string ch,temp;
    nr_buffer++;
    buffer[nr_buffer] = "";
    if (nr_buffer > 0)
        buffer[nr_buffer]= buffer[nr_buffer-1];
    //cout << "buffer[nr_buffer]:" << buffer[nr_buffer] << endl;
    //cout << "lung: " << (int)buffer[nr_buffer].size() << endl;
                if (lung == (int)buffer[nr_buffer].size())
                {
                     cout << buffer[nr_buffer] << endl;
                     nr++;
                    return;
                }
    temp = buffer[nr_buffer];
    for (int i = 0; i < (int)gram[r].v.size(); i++)
    {
       // cout << "(int)gram[r].v[i].size(): " << (int)gram[r].v[i].size() << endl;
        for (int j = 0; j < (int)gram[r].v[i].size(); j++)
        {
            ch = gram[r].v[i][j];
            //cout << ch << endl;
            if (ch != "S" && ch != "B" && ch != "C" && ch !="A")
            {
                buffer[nr_buffer] = buffer[nr_buffer] + gram[r].v[i][j];
            }
            else
            {
                for ( int k = 0 ; k < (int)gram.size(); k++)
                {
                    if (gram[k].t == ch)
                    {
                       // cout << "am asjuns" << endl;
                        Afisare_cuv(k);
                        nr_buffer--;
                    }
                }
            }
            if (j+1 == (int)gram[r].v[i].size() && ch!= "S" && ch != "B" && ch != "C" && ch !="A")
                {
                    cout << buffer[nr_buffer] << endl;
                    nr++;
                }
            //cout << c << "!";
        }
        buffer[nr_buffer] = temp;
    }
}

ostream& operator<< (ostream& out, const productie& x)
{
        out << x.t << " -> ";
        for (int r = 0; r < (int)x.v.size(); r++)
        {
            for (int j =0; j < (int)x.v[r].size(); j++)
                out << x.v[r][j];
            out << " | ";
        }
    return out;
}


ostream& operator<< (ostream& out, const Gr_Reg& x)
{
    for (int i = 0; i < n; i++)
    {
        out << x.gram[i];
        out << endl;
    }
    out << "Lungimea maxima admisibila a cuvintelor este : " << x.lung << endl;
    return out;
}

int main()
{
    Gr_Reg c;
    cout << c;
    cout << "Cuvintele generate de Gramatica Regulata sunt :" << endl;
    c.Afisare_cuv(0);
    c.get_nr_cuv();
    fin.close();
    return 0;
}

