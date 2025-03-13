#include<iostream>
#include <vector>
#include <cstdint>
#include <fstream>
#include <bitset>
using namespace std;

ofstream outputFile("/home/petru/Facultate/Lab_LFA/kolakoski/output.txt");

const long algorithmIterations = 0;

vector<bool> k={0, 1, 1};


void generateKolakoskiSequence(long iterations){
    long i=2;
    while( i < 64*iterations && k.size()<64*iterations){
        if (k[i]){
            bool aux = !k.back();
            k.push_back(aux);
            k.push_back(aux);
        }else{
            k.push_back(!k.back());
        }
        i++;
    }
    int n = k.size();
    outputFile <<n << "\n";
    for(int i = 0; i < n; i++){
        if (k[i]==1)
        outputFile << 2 << "";
        else
        outputFile << 1 << "";
        if (!( (i+1)%64 )){outputFile<<"\n";}
    }
    size_t memoryUsedBytes = k.size() * sizeof(bool);

    // Convert bytes to MB
    double memoryUsedMB = static_cast<double>(memoryUsedBytes) / (1024 * 1024);
    cout<<memoryUsedMB<<" MBs Used"<<"\n";

}

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

void genKolakoski(int numberOfBuffers /*sirul generat va vea size*32 elemente */){
    outputFile<<64*numberOfBuffers<<"\n";
    sequence.push_back(bitset<64>("110"));
    bitset<64> overflowBuffer;
    bool overflow = false;
    int bufferPointer = 2;
    int globalBufferSize = 3;
    int localBufferSize = 3;
    int sector = 0;
    int workingSector = 0;
    int pointerSector = 0;
    int bufferSector = 0;
    bool nextValue = 0;

    for(int i = 0; i < numberOfBuffers; i++){
        if (i > 0){
            if (overflow){
                overflow = false;
                sequence.push_back(overflowBuffer);
                localBufferSize = 1;
                globalBufferSize += 1;
                overflowBuffer.reset();
            } else {
                sequence.push_back(bitset<64>());
                localBufferSize = 0;
            }
            workingSector = i;
        }
        while(localBufferSize < 64){
            pointerSector = bufferPointer / 64;
            bufferSector = globalBufferSize / 64;

            bool currentBit = sequence[pointerSector][bufferPointer % 64];
            if (currentBit){
                sequence[workingSector][localBufferSize] = nextValue;
                localBufferSize += 1;
                globalBufferSize += 1;
                if (localBufferSize == 64){
                    overflowBuffer[0] = nextValue;
                    nextValue = !sequence[bufferSector][(globalBufferSize - 1) % 64];
                    overflow = true;
                    bufferPointer++;
                    break;
                }
                sequence[workingSector][localBufferSize] = nextValue;
                localBufferSize += 1;
                globalBufferSize += 1;
            } else {
                sequence[workingSector][localBufferSize] = nextValue;
                localBufferSize += 1;
                globalBufferSize += 1;
            }
            bufferPointer++;
            nextValue = !sequence[bufferSector][(globalBufferSize - 1) % 64];
        }
        //outputFile << reverseBits(sequence[workingSector]) << "\n";
    }
    size_t memoryUsedBytes = sequence.size() * sizeof(std::bitset<64>);

    // Convert bytes to MB
    double memoryUsedMB = static_cast<double>(memoryUsedBytes) / (1024 * 1024);
    //outputFile<<memoryUsedMB<<" MBs Used"<<"\n";

}

int main()
{   
    //generateKolakoskiSequence(algorithmIterations);
    //printKolakoskiSequence();
    //outputFile << "\n";
    generateKolakoskiSequence(30);
    genKolakoski(30);   
    printGeneratedSequence(sequence.size());
    return 0;
}
