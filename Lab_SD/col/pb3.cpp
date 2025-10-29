#include<iostream>
using namespace std;
int mat[2001][2001];
int ilumimat[2001][2001];
int main()
{
    int n, m, k;
    cin>>n>>m>>k;
    for(int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            cin>>mat[j][i];
        }
    }
    for(int i =0; i< n; i ++){
        for(int j=0; j<m; j++){
            for(int x=1; x<=k; x++){
                if(i + x < n){
                    if(mat[i][j] > mat[i+x][j]){
                        ilumimat[i+x][j]+=1;
                    }else{
                        break;
                    }
                }
            } for(int x=1; x<=k; x++){

                if(i - x >= 0){
                    if(mat[i][j] > mat[i-x][j]){
                        ilumimat[i-x][j]+=1;
                    }else{
                        break;
                    }
                }
            }
            for(int x=1; x<=k; x++){
                if(j - x >= 0){
                    if(mat[i][j] > mat[i][j-x]){
                        ilumimat[i][j-x]+=1;
                    }else{
                        break;
                    }
                }} for(int x=1; x<=k; x++){
                if(j + x < m){
                    if(mat[i][j] > mat[i][j+x]){
                        ilumimat[i][j+x]+=1;
                    }else {
                        break;
                    }
                }}

            }
        }
    

    int count = 0;
    for(int i =0; i<n; i++){
        for(int j=0; j<m; j++){
            if (ilumimat[i][j] == 1){
                count+=1;
            };
        }
    }
    cout<<count;
    
}