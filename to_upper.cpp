#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <cctype>
#include <mutex>
#include <fstream> 
using namespace std;
std::string S = "";
bool flag = true;
bool stop = false;
mutex mtx;

void schit(ifstream &fin){
    while(1){
        if(flag){
        mtx.lock();
        getline(fin, S);
        flag = false;
        mtx.unlock();
        }
        if(fin.eof()==true){
            stop = true;
            break;
        }
    }

}

void zapis(ofstream &fout){
    while(1){
        if(flag == false){
        mtx.lock();
        for(int i = 0; i<S.size(); ++i){
            S[i] = toupper(S[i]);
        }
        fout << S << endl;
        flag = true;
        mtx.unlock();
        }
        if(stop){
            break;
        }
    }

}

int main() {
    ifstream Fin("invisible_man.txt"); // Открытие файла для чтения
    ofstream Fout("output.txt"); // Открытие файла для записи
    

    thread read ([&]() { schit(Fin); });

    thread write ([&]() { zapis(Fout); });
    read.join();
    write.join();
    Fin.close(); // Закрытие файла
    Fout.close(); // Закрытие файла

    return 0;
}
