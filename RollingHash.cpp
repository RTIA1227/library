#include<vector>
#include<string>

// 1-based indexing
class RollingHash{
    std::string data;
    long long int base;
    std::vector<long long int> mod;
    std::vector<std::vector<long long int>> hashVal;
    std::vector<std::vector<long long int>> powVal;

    inline void init(){
        hashVal = std::vector<std::vector<long long int>>(mod.size(),std::vector<long long int>(data.size()+1,0));
        powVal = std::vector<std::vector<long long int>>(mod.size(),std::vector<long long int>(data.size()+1,1));
        for(int i = 0; i < mod.size(); i++){
            for(int j = 0; j < data.size(); j++){
                hashVal[i][j+1] = ((hashVal[i][j]*base)%mod[i] + (long long int)data[j])%mod[i];
                powVal[i][j+1] = (powVal[i][j]*base)%mod[i];
            }
        }
    }

public:

    RollingHash(std::string s,std::vector<long long int> m = {1000000007LL,1000000009LL,999999937LL},long long int b = 10007LL):data(s),mod(m),base(b){
        init();
    }

    long long int hashCalc(const std::string &key,int modIdx){
        long long int ret = 0;
        long long int modVal = mod[modIdx];
        for(int i = 0; i < key.size(); i++){
            ret = ((ret*base)%modVal + (long long int)key[i])%modVal;
        }
        return ret;
    }

    void allHashCalc(std::vector<long long int> &keyHashVal,const std::string &key){
        keyHashVal = std::vector<long long int>(mod.size(),0);
        for(int i = 0; i < mod.size(); i++){
            keyHashVal[i] = hashCalc(key,i);
        }
        return;
    }

    long long int getHash(int l,int r,int modIdx){
        if(l > r || l <= 0 || r <= 0 || l > data.size() || r > data.size()){
            return -1;
        }
        long long int modVal = mod[modIdx];
        return (hashVal[modIdx][r] + (modVal - (hashVal[modIdx][l - 1]*powVal[modIdx][r - l + 1])%modVal ) )%modVal;
    }

    int rabinKarp(const std::string &key){
        std::vector<long long int> keyHash;

        allHashCalc(keyHash,key);

        for(int i = 0; i < data.size(); i++){
            bool flag = true;
            for(int j = 0; j < mod.size(); j++){
                if(keyHash[j] != getHash(i + 1,i + key.size(),j)){
                    flag = false;
                }
            }
            if(flag)return i+1;
        }

        return -1;
    }

    void rabinKarp(const std::string &key,std::vector<long long int> &ret){
        std::vector<long long int> keyHash;

        allHashCalc(keyHash,key);

        for(int i = 0; i < data.size(); i++){
            bool flag = true;
            for(int j = 0; j < mod.size(); j++){
                if(keyHash[j] != getHash(i + 1,i + key.size(),j)){
                    flag = false;
                }
            }
            if(flag)ret.push_back(i+1);
        }

        return;
    }
};