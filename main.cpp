#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <limits.h>
#include <cmath>
using namespace std;

class BigNum
{

    vector<uint8_t> Big;

//public:
    void Converte(const string &num){

        
        for(size_t i =0;i < num.size();i++){
            
            uint16_t carry = num[i] - '0';
            for(size_t j =0;j < Big.size();j++){
            
                uint16_t s = Big[j]*10 + carry;
                Big[j] = (uint8_t)(s % 256);

                carry = s/256;
                

            }
            while(carry){
                Big.push_back((uint8_t)carry);

                carry = carry/256;

            }
            
        }

    }

    void DesCoverte(){
       unsigned long long num = 0;
        for(size_t i =0;i < Big.size();i++){
            num += Big[i] * pow(256,i);
        }
        cout << num;
    }



public:




    BigNum(const string &num){
        Big.push_back(0);
        Converte(num);
    }
    BigNum(){
        Big.push_back(0);
    }
    BigNum operator+(const BigNum &outro) const
    {
        BigNum resu;
        resu.Big.clear();

        size_t num = max(Big.size(), outro.Big.size());
        uint16_t carry = 0;

        for (size_t i = 0; i < num; i++)
        {
            uint8_t a = 0;
            uint8_t b = 0;

            if (i < Big.size())
                a = Big.at(i);
            if (i < outro.Big.size())
                b = outro.Big.at(i);

            uint16_t soma = a + b + carry;
            resu.Big.push_back(uint8_t(soma % 256));
            carry = soma / 256;
        }

        if (carry > 0)
        {
            resu.Big.push_back((uint8_t)carry);
        }
        return resu;
    }

    BigNum operator-(const BigNum &outro) const
    {
        BigNum resu;
        resu.Big.clear();
        size_t num = max(Big.size(), outro.Big.size());
        uint16_t borrow = 0;
        for (size_t i = 0; i < num; i++)
        {
            uint8_t a = 0;
            uint8_t b = 0;

            if (i < Big.size())
                a = Big.at(i);

            if (i < outro.Big.size())
                b = outro.Big.at(i);

            int16_t s = a - b - borrow;
            if (s >= 0)
            {
                resu.Big.push_back((uint8_t)s);
                borrow = 0;
            }
            else
            {
                resu.Big.push_back((uint8_t)(s + 256));
                borrow = 1;
            }
        }

        if (borrow)
        {
            cout << "Numero negativo!!";
            exit(0);
        }

        return resu;
    }

    friend istream &operator>>(istream &input, const BigNum &Num);

    void mostra_bytes ()const{

        for(uint8_t x : Big){
            cout << (int)x << " ";
        }
    }
};

istream &operator>>(istream &input, const string &Num) {






}

int main()
{   
    string num("123456789");

    BigNum teste("257");
    BigNum teste1("257");
    
    teste.mostra_bytes();

    cout << "\n";
    teste = teste + teste1;
    teste.mostra_bytes();
    cout << "\n";
    //teste.DesCoverte();

    return 0;
}
