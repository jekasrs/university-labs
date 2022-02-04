#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

const int N = 900;

float** a = new float *[N];
float** b = new float *[N];
float** r = new float *[N];

int main() {
    
    srand(static_cast<unsigned int>(time(0)));

    for(int i = 0; i<N; i++){
        a[i]= new float[N];
    }

    for(int i = 0; i<N; i++){
        b[i]= new float[N];
    }

    for(int i = 0; i<N; i++){
        r[i]= new float[N];
    }
    
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            a[i][j] = rand() % 10;
            b[i][j] = rand() % 10;
            r[i][j] = 0;
        }
    }

    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            for(int k = 0; k < N; k++){
                r[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    std::ofstream fout("wtf.txt");
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            fout << r[i][j];
        }
    }
    fout.close();
    return 0;
}
