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

    void DesConverteSimples()const{
       unsigned long long num = 0;
        for(size_t i =0;i < Big.size();i++){
            num += Big[i] * pow(256,i);
        }
        cout << num;
    }

    string soma_base_10(string num_string1,string num_string2)const{
        size_t tam = max(num_string1.size(),num_string2.size());
        reverse(num_string1.begin(),num_string1.end());
        reverse(num_string2.begin(),num_string2.end());
        string resu;
        uint8_t carry =0;
        for(size_t i = 0;i < tam;i++){

            uint8_t a = 0;
            uint8_t b = 0;

            if(i < num_string1.size())
                a = num_string1.at(i) - '0';
            if(i < num_string2.size())
                b = num_string2.at(i) - '0';




            uint8_t s = a + b + carry;

            if(s > 9){
                carry = s/10;
            }else{
                carry = 0;
            }
            resu.push_back(s%10 + '0');
        }
        if(carry)
            resu.push_back(carry + '0');


        reverse(resu.begin(),resu.end());
        return resu;
    }

    string multiplica(string &num_string,unsigned num)const{
        string resu = num_string;
        for(size_t i =0;i < num;i++){
            resu = soma_base_10(resu,num_string);
        }

        return resu;
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

    string DesConverte()const{       
        string num = "0";
        for(size_t i=0;i < Big.size();i++){
            num = multiplica(num,(unsigned)256);
            num = soma_base_10(num,to_string(Big.at(i) ) );
        }
        return num;
    }

};

istream &operator>>(istream &input, const string &Num) {






}

/*
    string soma_base_10(string num_string1,string num_string2){
        size_t tam = max(num_string1.size(),num_string2.size());
        reverse(num_string1.begin(),num_string1.end());
        reverse(num_string2.begin(),num_string2.end());
        string resu;
        uint8_t carry =0;
        for(size_t i = 0;i < tam;i++){

            uint8_t a = 0;
            uint8_t b = 0;

            if(i < num_string1.size())
                a = num_string1.at(i) - '0';
            if(i < num_string2.size())
                b = num_string2.at(i) - '0';




            uint8_t s = a + b + carry;

            if(s > 9){
                carry = s/10;
            }else{
                carry = 0;
            }
            resu.push_back(s%10 + '0');
        }
        if(carry)
            resu.push_back(carry + '0');


        reverse(resu.begin(),resu.end());
        return resu;
    }

    string multiplica(string &num_string,unsigned num){
        string resu = num_string;
        for(size_t i =0;i < num;i++){
            resu = soma_base_10(resu,num_string);
        }

        return resu;
    }

*/
int main()
{   /*
    string num("123456789");

    BigNum teste("257");
    BigNum teste1("257");
    
    teste.mostra_bytes();

    cout << "\n";
    teste = teste + teste1;
    teste.mostra_bytes();
    cout << "\n";
    //teste.DesCoverte();
    */
    //string num = "10";
    //cout << (soma_base_10(num,"1234321")) << "\n";

    //cout << multiplica(num,2);
    BigNum teste;
    BigNum teste1;

    teste1.Converte("0");
    teste.Converte("267");
    //arrumar 
    //tem erro na coversao esta convetendo ao contrario 
    //esta 1*256^0 + 11*256^1
    //mas era pra estar 1*256^1 + 11*256^0
    //e pararece que esta somando algo a mais em algum lugar 


    //teste = teste1 + teste;
    teste.mostra_bytes();
    cout  << "\n" << "valor em int: ";
    cout << teste.DesConverte();

    return 0;
}
