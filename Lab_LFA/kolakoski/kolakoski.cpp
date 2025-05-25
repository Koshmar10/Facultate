#include<iostream>
#include <vector>
#include <cstdint>
#include <fstream>
#include <bitset>

using namespace std;

//ABORDARE
/*
Ideea din spatele acestui algoritm  este de a genera o secventa Kolakoski cat mai lunga
folosind cat mai putin spatiu.
Prima idee a fost sa folosesc un vector dinamic ce tine valori booleene, dar s-a dovedit
a fi ineficient atat de vedere a timpului(la generarea unei secvente mai mari de 1 000 000 de elemente)
dar si a spatiului(din cauza algoritmului de alocare de memorie a vectorului din stl)

Metoda pe care am ales sa o folosesc in schimb este urmatoarea.
Folosesc un vector de bitset<64>, astfel fiecare element al vecotrului va corespunde unei
scvente de 64 de elemnte(bit 1 reprezinta valoarea 2 bit 0 reprezinta valoarea 1)

*/



ofstream outputFile("./output.txt"); //fisierul de output

/*
Prima metoda, simpla de implementat dar ineficienta, 
am folosit-o ca sa verific corectitudinea celei de a doua

const long algorithmIterations = 0;

vector<bool> k={0, 1, 1}; //vectorul de  inceput


void generateKolakoskiSequence(long iterations){
    long i=2; //primele 2 elemente exista deja in sir deci incep de la 2
    while( i < 64*iterations && k.size()<64*iterations){ se genereaza $iterations secvente de 64 de elemente
        if (k[i]){
            // daca elementul curent este 1 vom adauga 2 elemente la coada sirului
            // cu valoarea opusa ultimului element
            bool aux = !k.back();
            k.push_back(aux);
            k.push_back(aux);
        }else{
            k.push_back(!k.back());
        }
        i++;
    }
    
    int n = k.size(); //marimea secventei generate
    outputFile <<n << "\n"; 
    
    //Afisarea secventei

    for(int i = 0; i < n; i++){
        //parcurg toata secventa generata si
        //pentru k[i]==1 afisez 2 pentru k[i]==0 afisez 1
        if (k[i]==1)
        outputFile << 2 << ""; 
        else
        outputFile << 1 << "";
        if (!( (i+1)%64 )){outputFile<<"\n";}
    }
    //calculez ati bytes foloseste vectorul meu de    
    size_t memoryUsedBytes = k.size() * sizeof(bool);

    // convertesc bytes in MB si afisez memoria folosita
    double memoryUsedMB = static_cast<double>(memoryUsedBytes) / (1024 * 1024);
    cout<<memoryUsedMB<<" MBs Used"<<"\n";
    
    }
    
*/
bitset<64> reverseBits(const bitset<64>& b) {
    bitset<64> reversed;
    for (size_t i = 0; i < 64; ++i) {
        reversed[i] = b[63 - i];
    }
    return reversed;
}

vector<bitset<64>> sequence;

void printGeneratedSequence(int numberOfBuffers){
    for (int i = 0; i < numberOfBuffers; i++) {
        bitset<64> buffer = sequence[i];
        for (int j = 0; j < 64; j++) {
            if (buffer[j] == 0) {
                outputFile << 1;
            } else {
                outputFile << 2;
            }
        }
        outputFile << "\n";
    }
}

void genKolakoski(int numberOfBuffers, bool showSize=true, bool printSeq=false){
    // can zic buffer ma refer la secventa curenta de 64 de elemente 
    outputFile<<64*numberOfBuffers<<"\n"; //numarul de elemente generate este intotdeauna afist

    sequence.push_back(bitset<64>("110")); //primul buffer este adaugat in vector

    bitset<64> overflowBuffer; // buffer pentru oerflow

    bool overflow = false; //daca s-a produs overflow in timpul adaugarii de elemente

    int bufferPointer = 2; //indicele elementului curent
    
    int globalBufferSize = 3; //cate elemente exista in lista

    int localBufferSize = 3; //cate elemente are bufferul curent

    int workingSector = 0; //elementul din lista in care fac modificari
    int pointerSector = 0; //locul din lista unde se afla elementul care dicteaza generarea

    int bufferSector = 0; // indicele bufferului curent 
    bool nextValue = 0; // urmatoarea valoare de adaugat in buffer

    for(int i = 0; i < numberOfBuffers; i++){
        // pentru a evita posibile segfault-uri am ales sa dau push
        // la buffere si sa lucrez pe ele atunci cand sunt  deja in lista
        // can i=0 primul buffer e adaugat deja si sar peste verificarea de overflow
        if (i > 0){
            if (overflow){ 
                //daca s-a produs overflow in iteratia precedenta, urmatorul buffer nu va mai fi gol
                //va fi egal vu valoare lui overflow buffer
                overflow = false;
                sequence.push_back(overflowBuffer);
                localBufferSize = 1; // pentru ca a fost overflow bufferul deja are o valoare deci incepem de la 1 constrctia
                globalBufferSize += 1; 
                overflowBuffer.reset(); //resetam overflowBuffer-ul 
            } else {
                //altfel adaugam un buffer gol
                sequence.push_back(bitset<64>());
                localBufferSize = 0;
            }
            workingSector = i; // working sector devine indicele elementului curent din lista
        }
        while(localBufferSize < 64){ //cat timp bufferul curent nu este umplut 

            pointerSector = bufferPointer / 64; //calculam in ce buffer este lementul curent
            bufferSector = globalBufferSize / 64; // calculam in ce buffer se afla ultima valoare

            bool currentBit = sequence[pointerSector][bufferPointer % 64]; //luam elementul curent
            if (currentBit){
                //daca este 1 adaugam 2 elemente la finalul bufferului curent
                sequence[workingSector][localBufferSize] = nextValue;
                
                //marim variabile care tin cont de lungimea bufferului local / global
                localBufferSize += 1;
                globalBufferSize += 1;
                
                //verificam daca limita bufferului a fost atinsa si setam overflow daca e necesar
                if (localBufferSize == 64){
                    overflowBuffer[0] = nextValue;
                    nextValue = !sequence[bufferSector][(globalBufferSize - 1) % 64];
                    overflow = true;
                    bufferPointer++;
                    break;
                }
                sequence[workingSector][localBufferSize] = nextValue;
                
                //marim variabile care tin cont de lungimea bufferului local / global
                localBufferSize += 1;
                globalBufferSize += 1;
            } else {
                //aici nu este nevoie sa verificam overflow-ul deoarece avem o singura adaugare
                sequence[workingSector][localBufferSize] = nextValue;
                localBufferSize += 1;
                globalBufferSize += 1;
            }
            bufferPointer++;
            
            //se calculeaza urmatoarea valoare
            nextValue = !sequence[bufferSector][(globalBufferSize - 1) % 64];
        }
        //outputFile << reverseBits(sequence[workingSector]) << "\n";
    }
    //afisarea memoriei folosite
    if (showSize){
    size_t memoryUsedBytes = sequence.size() * sizeof(std::bitset<64>);

    // Convertire bytes la MB
    double memoryUsedMB = static_cast<double>(memoryUsedBytes) / (1024 * 1024);
    outputFile<<memoryUsedMB<<" MBs Used"<<"\n";
    }
    if (printSeq){
        printGeneratedSequence(sequence.size());
    }
}

int main()
{   
    //ca parametri dam numarul de elemente pe care vrem sa le avem in lista
    //un element contine 64 de termenti ai secventei kolakoski
    genKolakoski(1000000, true/*afisare MB*/, false /*afisare intreazga secventa*/);   
    return 0;
}
