// Voda Ioana Alexandra
// Grupa 131 Semigrupa1
// Tutore de laborator: Dobrovat Anca
// Code Blocks : 12.11

#include <iostream>
#include <cstring>

using namespace std;

class Pacient
{
protected:
    char *nume;
    char *prenume;
    char *risc_cardiovascular;
    int varsta;
    int colesterol;
    int tensiune;
public:
    Pacient();
    ~Pacient();
    friend istream& operator>>(istream &is, Pacient &x);
    friend ostream & operator <<(ostream &os, Pacient &x);
    virtual char *get_risc(){return risc_cardiovascular;}

};
Pacient :: ~Pacient()
{
    delete nume;
    delete prenume;
    delete risc_cardiovascular;
    varsta=0;
    colesterol=0;
    tensiune=0;
}
ostream & operator <<(ostream &os, Pacient &x)
{
    os<<x.nume<<" "<<x.prenume<<": Risc cardiovascular - "<<x.risc_cardiovascular<<" ; Colesterol: "<<x.colesterol<<" mg/dl; TA:";
    os<<x.tensiune<<endl;
    return os;
}

istream& operator>>(istream &is, Pacient &x)
{
    char aux[30];
    cout<<"Nume pacient=";
    is>>aux;
    x.nume=new char[strlen(aux)+1];
    strcpy(x.nume, aux);
    cout<<"Prenume pacient=";
    is>>aux;
    x.prenume=new char[strlen(aux)+1];
    strcpy(x.prenume, aux);
    cout<<"Varsta=";
    is>>x.varsta;
    cout<<"Colesterol=";
    is>>x.colesterol;
    cout<<"Tensiune=";
    is>>x.tensiune;
    x.risc_cardiovascular=new char[3];
    if(x.colesterol>240 || x.tensiune>139)
        strcpy(x.risc_cardiovascular, "DA");
    else
        strcpy(x.risc_cardiovascular, "NU");

    return is;
}

Pacient :: Pacient()
{
    nume=new char[1];
    strcpy(nume, "\0");
    prenume=new char[1];
    strcpy(prenume, "\0");
    varsta=0;
    colesterol=0;
    tensiune=0;
}

class Pacient40: public Pacient
{
    char *fumator;
    char *sedentarism;
public:
    Pacient40();
    ~Pacient40();
    friend istream& operator>>(istream &is, Pacient40 &x);
    friend ostream & operator <<(ostream &os, Pacient40 &x);
    char *get_risc(){return risc_cardiovascular;}
};
Pacient40 :: ~Pacient40()
{
    delete nume;
    delete prenume;
    delete risc_cardiovascular;
    delete fumator;
    delete sedentarism;
    varsta=0;
    colesterol=0;
    tensiune=0;

}
ostream & operator <<(ostream &os, Pacient40 &x)
{
    os<<x.nume<<" "<<x.prenume<<": Risc cardiovascular - "<<x.risc_cardiovascular<< "; Colesterol: "<<x.colesterol<<" mg/dl; TA :";
    os<<x.tensiune<<" ; Fumator: "<<x.fumator<<"; Sedentarism: "<<x.sedentarism<<endl;
    return os;
}

istream& operator>>(istream &is, Pacient40 &x)
{
    char aux[30];
    cout<<"Nume pacient=";
    is>>aux;
    x.nume=new char[strlen(aux)+1];
    strcpy(x.nume, aux);
    cout<<"Prenume pacient=";
    is>>aux;
    x.prenume=new char[strlen(aux)+1];
    strcpy(x.prenume, aux);
    cout<<"Varsta=";
    is>>x.varsta;
    cout<<"Colesterol=";
    is>>x.colesterol;
    cout<<"Tensiune=";
    is>>x.tensiune;
    cout<<"Este pacientul fumator? Introduceti DA sau NU:";
    is>>aux;
    x.fumator=new char[3];
    strcpy(x.fumator, aux);
    cout<<"Introduceti nivelul de sedentarism:";
    is>>aux;
    x.sedentarism=new char[strlen(aux)+1];
    strcpy(x.sedentarism,aux);
    x.risc_cardiovascular=new char[8];
    if (strcmp(x.fumator, "DA")==0 && strcmp(x.sedentarism, "ridicat")== 0)
        strcpy(x.risc_cardiovascular, "RIDICAT");
    else if(x.colesterol>240 || x.tensiune>139)
        strcpy(x.risc_cardiovascular, "DA");
    else
        strcpy(x.risc_cardiovascular, "NU");

    return is;
}

Pacient40 :: Pacient40():Pacient()
{
    fumator=false;
    sedentarism =new char[6];
    strcpy(sedentarism, "mediu");
}

class Copil : public Pacient
{
    char *precedent;
    char *nume_mama;
    char *prenume_mama;
    char *nume_tata;
    char *prenume_tata;
    float proteina_C;
public:
    Copil();
    ~Copil();
    friend istream& operator>>(istream &is, Copil &x);
    friend ostream & operator <<(ostream &os, Copil &x);
    char *get_risc(){return risc_cardiovascular;}

};
Copil :: ~Copil()
{
    delete nume;
    delete prenume;
    delete risc_cardiovascular;
    delete precedent;
    delete nume_mama;
    delete prenume_mama;
    delete nume_tata;
    delete prenume_tata;
    proteina_C=0;
    varsta=0;
    colesterol=0;
    tensiune=0;
}
ostream & operator <<(ostream &os, Copil &x)
{
    os<<x.nume<<" "<<x.prenume<<": Risc cardiovascular - "<<x.risc_cardiovascular<< "; Colesterol: "<<x.colesterol<<" mg/dl; TA :";
    os<<x.tensiune<<" Proteina C reactiva: "<<x.proteina_C<<" mg/dl; Antecedente familie: "<<x.precedent<<endl;
    return os;
}

istream& operator>>(istream &is, Copil &x)
{
    char aux[30];
    cout<<"Nume pacient=";
    is>>aux;
    x.nume=new char[strlen(aux)+1];
    strcpy(x.nume, aux);
    cout<<"Prenume pacient=";
    is>>aux;
    x.prenume=new char[strlen(aux)+1];
    strcpy(x.prenume, aux);
    cout<<"Varsta=";
    is>>x.varsta;
    cout<<"Colesterol=";
    is>>x.colesterol;
    cout<<"Tensiune=";
    is>>x.tensiune;
    cout<<"Nume tata=";
    is>>aux;
    x.nume_tata=new char[strlen(aux)+1];
    strcpy(x.nume_tata, aux);
    cout<<"Preume tata=";
    is>>aux;
    x.prenume_tata=new char[strlen(aux)+1];
    strcpy(x.prenume_tata, aux);
    cout<<"Nume mama=";
    is>>aux;
    x.nume_mama=new char[strlen(aux)+1];
    strcpy(x.nume_mama, aux);
    cout<<"Preume mama=";
    is>>aux;
    x.prenume_mama=new char[strlen(aux)+1];
    strcpy(x.prenume_mama, aux);
    cout<<"Exista antecedente in familie? Introduceti Da sau Nu";
    is>>aux;
    x.precedent=new char[strlen(aux)+1];
    strcpy(x.precedent, aux);
    cout<<"Proteina C reactiva=";
    is>>x.proteina_C;
    x.risc_cardiovascular=new char[3];
    if(x.colesterol>240 || x.tensiune>139 ||strcmp(x.precedent, "Da")==0 || x.proteina_C<0.60)
        strcpy(x.risc_cardiovascular, "DA");
    else
        strcpy(x.risc_cardiovascular, "NU");

    return is;
}

Copil :: Copil():Pacient()
{
    precedent = new char[3];
    strcpy(precedent, "NU");
    nume_mama = new char[1];
    strcpy(nume_mama, "\0");
    nume_tata = new char[1];
    strcpy(nume_tata, "\0");
    prenume_tata = new char[1];
    strcpy(prenume_tata, "\0");
    prenume_mama= new char[1];
    strcpy(prenume_mama, "\0");
    proteina_C=0.60;
}

struct Fise
{
    Pacient p;
    Pacient40 p40;
    Copil c;
    char tip_obiect[10];
};

int main()
{
    int nr, i=0;
    cout<<"Inserati numarul de pacienti a caror fise doriti sa le cititi:";
    cin>>nr;
    Fise f[nr];
    cout<<" 1. Citire fisa pacient obisnuit \n 2. Citire fisier pacient peste 40 de ani \n 3. Citire fisa copil \n 4. Afisare toate referintele citite \n";
    cout<<" 5. Afisare pacienti adulti cu risc vascular ridicat\n 6. Afisare pacient cu risc cardiovascular \n 7.Iesire";
    int optiune =-1;

    while(optiune!=7 && i!=nr+1)
    {
        cout<<"\nIntroduceti optiune";
        cin>>optiune;
        switch(optiune){
            case 1:{i++;
                    strcpy(f[i].tip_obiect, "pacient");
                    cin>>f[i].p;
                    break;
                    }
            case 2:{i++;
                    strcpy(f[i].tip_obiect, "pacient40");
                    cin>>f[i].p40;
                    break;
                    }
            case 3:{i++;
                    strcpy(f[i].tip_obiect, "copil");
                    cin>>f[i].c;
                    break;
                    }
            case 4:{cout<<"\nAdulti:";
                    cout<<"\nAdulti peste 40 de ani:";
                    for(int indice=1;indice<=nr;indice++)
                        {if(strcmp(f[indice].tip_obiect, "pacient40")==0)
                                cout<<f[indice].p40;
                        cout<<endl;}
                    cout<<"\nAdulti sub 40 de ani:";
                    for(int indice=1;indice<=nr;indice++)
                        {if(strcmp(f[indice].tip_obiect, "pacient")==0)
                                cout<<f[indice].p;
                        cout<<endl;}
                    cout<<"\nCopii:";
                    for(int indice=1;indice<=nr;indice++)
                        {if(strcmp(f[indice].tip_obiect, "copil")==0)
                                cout<<f[indice].c;
                        cout<<endl;}
                    break;
                    }
            case 5:{
                    cout<<"\nAdulti:";
                    cout<<"\nAdulti peste 40 de ani:";
                    for(int indice=1;indice<=nr;indice++)
                        {if(strcmp(f[indice].tip_obiect, "pacient40")==0 && strcmp(f[indice].p40.get_risc(), "ridicat")==0)
                                cout<<f[indice].p40;
                        cout<<endl;}
                    cout<<"\nAdulti sub 40 de ani:";
                    for(int indice=1;indice<=nr;indice++)
                        {if(strcmp(f[indice].tip_obiect, "pacient")==0 && strcmp(f[indice].p.get_risc(), "ridicat")==0)
                                cout<<f[indice].p;
                        cout<<endl;}
                    break;
            }
        case 6: {
                    cout<<"\nAdulti:";
                    cout<<"\nAdulti peste 40 de ani:";
                    for(int indice=1;indice<=nr;indice++)
                        {if(strcmp(f[indice].tip_obiect, "pacient40")==0 &&( strcmp(f[indice].p40.get_risc(), "ridicat")==0 || strcmp(f[indice].p40.get_risc(), "da")==0 ))
                                cout<<f[indice].p40;
                        cout<<endl;}
                    cout<<"\nAdulti sub 40 de ani:";
                    for(int indice=1;indice<=nr;indice++)
                        {if(strcmp(f[indice].tip_obiect, "pacient")==0 && (strcmp(f[indice].p.get_risc(), "ridicat")==0 || strcmp(f[indice].p.get_risc(), "da")==0))
                                cout<<f[indice].p;
                        cout<<endl;}
                    cout<<"\nCopii";
                    for(int indice=1;indice<=nr;indice++)
                        {if(strcmp(f[indice].tip_obiect, "copil")==0 && (strcmp(f[indice].c.get_risc(), "ridicat")==0 || strcmp(f[indice].c.get_risc(), "da")==0))
                                cout<<f[indice].c;
                        cout<<endl;}
                    break;

        }
        }
    }
    return 0;
}
