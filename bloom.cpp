#include <bits/stdc++.h>
#include "murmur3.h"
using namespace std;

class bFilter{
    int size;
    float max_false_pos;
    int hash_count;
    int expected;
    vector<int>arr;
    int count;
    public:
    bFilter(float max_false_pos, int expected){
        this->max_false_pos = max_false_pos;
        this->expected = expected;
        float x = ((-1)*expected)*log(max_false_pos);
        x=x/(log(2)*log(2));
        this->size = x;
        float y = (1.0*this->size) / (1.0*this->expected);
        y=y*log(2);
        this->hash_count = y;
        for(int i=0;i<this->size;i++){
            arr.push_back(0);
        }
        count =0;
    }

    void insert(char* s){
        refresh();
        for(int i=0;i<this->hash_count;i++){
            int hash = (hashing(s,i) % this->size);
            this->arr[hash]=1;
        }
        count++;
    }

    bool has(char* s){
        for(int i=0;i<this->hash_count;i++){
            int hash = hashing(s,i) % this->size;
            if(this->arr[hash]==0){
                return false;
            }
        }
        return true;
    }

    void refresh(){
        if(this->count>=this->expected){
            for(int i=0;i<this->size;i++){
                this->arr[i]=0;
            }
            this->count=0;
        }
    }

    void show_bloom(){
        for(int i=0;i<this->size;i++){
            cout << this->arr[i] << " ";
        }
        cout << endl;
    }

    uint32_t hashing(char* s, int seed){
        uint32_t hash[4];
        MurmurHash3_x86_32(s,strlen(s),seed,hash);
        return hash[0];
    }

};

int main(){
    bFilter bloom(0.1,10);
    ifstream infile("./trace.txt");
    string line;
    int accurate_prefetch_bFilter=0;
    int total_prefetches_bFilter=0;
    int accurate_prefetch=0;
    int total_prefetches=0;
    int total_req=0;
    int total_dem=0;
    while(getline(infile,line)){
        istringstream iss(line);
        string word;
        iss >> word;
        string prefetch_bit;
        iss >> prefetch_bit;
        char input[word.size()+1];
        for(int i=0;i<word.size();i++){
            input[i]=word[i];
        }
        input[word.size()]='\0';
        if(prefetch_bit == "1"){
            bloom.insert(input);
            total_prefetches_bFilter++;
        }else{
            if(bloom.has(input)){
                accurate_prefetch_bFilter++;
            }
            total_dem++;
        }
        total_req++;
    }
    infile.close();
    float accuracy_bFilter = (1.0 * accurate_prefetch_bFilter)/(1.0 * total_prefetches_bFilter);
    cout << "total demand + prefetches : " << total_req << endl;
    cout << endl;
    cout << "total demand              : " << total_dem << endl;
    cout << "total prefetches          : " << (total_req-total_dem) << endl;
    cout << "accuracy                  : " << 0 << endl;
    cout << endl;
    cout << "total demand     (bFilter): " << total_dem << endl;
    cout << "total prefetches (bFilter): " << total_prefetches_bFilter << endl;
    cout << "accuracy (bFilter)        : " << accuracy_bFilter << endl;
    cout << endl;
    cout << "error                     : " << abs(accuracy_bFilter - 0) << endl;

}

