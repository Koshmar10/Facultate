//RUSU OVIDIU-MIHAI, GRUPA 132, LAB : TEODOR CRISTIAN, C++
#include <iostream>
using namespace std;

class adult
{

      char dcol[100];
      int col;
      char dta[100];
      int ta;
      int varsta;
      char nume[10];
      char prenume[10];
      char adresa[200];
      protected:
      int risc;
      public:
             adult(){};
             virtual void calc_risc();
             void change_risc();
             virtual void afiseaza_risc();
             friend istream& operator>>(istream& in,adult &c)
             {
                    cout<<"Numele"<<endl;
                    cin>>c.nume;
                    cout<<endl<<"Prenumele"<<endl;
                    cin>>c.prenume;
                    cout<<endl<<"Adresa"<<endl;
                    cin>>c.adresa;
                    cout<<endl<<"Varsta"<<endl;
                    cin>>c.varsta;
                    cout<<endl<<"Data Colesterol"<<endl;
                    cin>>c.dcol;
                    cout<<endl<<"Colesterol"<<endl;
                    cin>>c.col;
                    cout<<endl<<"Data Tensiune arteriala"<<endl;
                    cin>>c.dta;
                    cout<<endl<<"Tensiune arteriala"<<endl;
                    cin>>c.ta;
                    c.calc_risc();
             }
             friend ostream& operator<<(ostream& out,const adult &c)
             {
                 int i;
                 cout<<c.nume<<' '<<c.prenume<<": Risc cardiovascular - ";
                 if(c.risc==0)cout<<"NU;";
                 else cout<<"DA;";
                 cout<<"Colesterol (";
                 cout<<c.dcol;
                 cout<<"):";
                 cout<<c.col;
                 cout<<";";
                 cout<<"TA (";
                 cout<<c.dta;
                 cout<<"):";
                 cout<<c.ta;
             }
};

void adult::change_risc()
{
    this->risc=1;
}

void adult::calc_risc()
{
    if(col>240&&(ta<130||ta>139))this->risc=1;

}

void adult::afiseaza_risc()
{
    if(this->risc==1)
    {
        cout<<this->nume<<' '<<this->prenume<<": Risc cardiovascular - ";
                 if(this->risc==0)cout<<"NU;";
                 else cout<<"DA;";
                 cout<<"Colesterol (";
                 cout<<this->dcol;
                 cout<<"):";
                 cout<<this->col;
                 cout<<";";
                 cout<<"TA (";
                 cout<<this->dta;
                 cout<<"):";
                 cout<<this->ta;
    }
}

class adult_040:public adult
{
    bool fum;
    int sed;
    public:
      void add();
      void afiseaza_add();
      void calc_risc();
      void afiseaza_risc();
};

void adult_040::add()
{
    cout<<"Fumeaza ? [0-DA sau 1-NU]"<<endl;
    cin>>this->fum;
    cout<<"E sedentar ? [-1-scazut , 0-mediu, 1-ridicat]"<<endl;
    cin>>this->sed;
}

void adult_040::afiseaza_add()
{
    if(this->fum==1)cout<<"Fumator:DA"<<endl;
    else cout<<"Fumator:NU"<<endl;
    if(this->sed==-1)cout<<"Sedentarism:scazut"<<endl;
    else if(this->sed==0)cout<<"Sedentarism:mediu"<<endl;
         else cout<<"Sedentarism:ridicat"<<endl;
}

void adult_040::calc_risc()
{
            if(this->fum&&this->sed==1)change_risc();

}

void adult_040::afiseaza_risc()
{
    if(this->risc==1)
    {
        cout<<this;
         if(this->fum==1)cout<<"Fumator:DA"<<endl;
    else cout<<"Fumator:NU"<<endl;
    if(this->sed==-1)cout<<"Sedentarism:scazut"<<endl;
    else if(this->sed==0)cout<<"Sedentarism:mediu"<<endl;
         else cout<<"Sedentarism:ridicat"<<endl;
    }
}
class copil:public adult
{
    char dprotc[100];
    float protc;
    char tatanume[100];
    char mamanume[100];
    char tataprenume[100];
    char mamaprenume[100];
    int antec;
    public:
    void ada();
      void afiseaza_ada();
    void calc_risc();
};

void copil::ada()
{
    cout<<endl<<"Data Proteina C"<<endl;
    cin>>this->dprotc;
    cout<<endl<<"Proteina C"<<endl;
    cin>>this->protc;
    cout<<"Antecedente ?[0-nu , 1-da]"<<endl;
    cin>>this->antec;
    if(this->antec)
    {
        cout<<"Parintii:"<<endl;
        cin>>tatanume;
        cin>>tataprenume;
        cin>>mamanume;
        cin>>mamaprenume;
    }
}

void copil::afiseaza_ada()
{
    cout<<"Proteina C reactiva (";
                 cout<<this->dprotc;
                 cout<<"):";
                 cout<<this->protc;
                 cout<<";";
    if(this->antec)
    {
        cout<<"Antecedente familie:DA"<<endl;
        cout<<tatanume<<' '<<tataprenume<<' '<<mamanume<<' '<<mamaprenume<<endl;
    }
}

void copil::calc_risc()
{
    if(this->protc>=0.60&&this->antec==1)change_risc();
}

int main()
{
    adult A[100];
    adult_040 A40[100];
    copil C[100];
    int n,m,o,i;
    cout<<"Cati adulti ?"<<endl;
    cin>>n;
    cout<<"Cati adulti peste 40 ?"<<endl;
    cin>>m;
    cout<<"Cati copii ?"<<endl;
    cin>>o;
    for(i=0;i<n;i++)
    {
      cin>>A[i];
    }
    for(i=0;i<m;i++)
    {
        cin>>A40[i];
        A40[i].add();
    }
    for(i=0;i<o;i++)
    {
        cin>>C[i];
        C[i].ada();
    }
    cout<<"1 pentru afisare toti pacienti, 2 pentru afisare pacienti cu risc"<<endl;
    cin>>i;
    if(i==1)
    {cout<<"Adulti sub 40"<<endl;
    for(i=0;i<n;i++)
    {
        cout<<A[i];
    }
    cout<<endl;
    cout<<"Adulti peste 40"<<endl;
     for(i=0;i<m;i++)
    {
        cout<<A40[i];
        A40[i].afiseaza_add();
    }
    cout<<endl;
    cout<<"Copii"<<endl;
    for(i=0;i<o;i++)
    {
        cout<<C[i];
        C[i].ada();
    }}
    if(i==2)
    {
       cout<<"Adulti sub 40"<<endl;
       for(i=0;i<n;i++)
       {
           A[i].afiseaza_risc();
       }
       cout<<endl;
    cout<<"Adulti peste 40"<<endl;
       for(i=0;i<m;i++)
       {
           A40[i].afiseaza_risc();
       }
    }
    return 0;
}
