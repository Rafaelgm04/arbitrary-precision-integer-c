#include "BigNum.h"

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <limits.h>
#include <cmath>

using namespace std;


string soma_base_10N(string num_string1,string num_string2){
    size_t tam = max(num_string1.size(),num_string2.size());
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
    return resu;
}


auto multiplica = [](const string &num_string,const string &num_string1){

    size_t tam =  min(num_string.size(),num_string1.size());
    string resu;
    vector<string> mult;

    //no caso da menor que fica por baixo e nao varia e a string1
    if(num_string1.size() == tam){
        
        for(size_t n = num_string1.size();n > 0;n--){
            uint16_t carry =0;
            string  soma;
             for(size_t i = num_string.size(); i > 0; i--){
                uint16_t s = ((num_string1[n-1]-'0') * (num_string[i-1]-'0')) + carry;
                carry = s / 10;
                soma.push_back(s % 10 + '0');
            }
            while(carry){
                soma.push_back(carry % 10 + '0');
                carry /= 10;
            }
            mult.push_back(soma); 
        }
    }else{
        for(size_t n = num_string.size();n > 0;n--){
            uint16_t carry =0;
            string  soma;
            for(size_t i = num_string1.size(); i > 0; i--){
                uint16_t s = ((num_string1[i-1]-'0') * (num_string[n-1]-'0')) + carry;
                carry = s / 10;
                soma.push_back(s % 10 + '0');
            }
            while(carry){
                soma.push_back(carry % 10 + '0');
                carry /= 10;
            }
            mult.push_back(soma); 
        }
    }

    string zero ="";
    for(string x : mult){
        x.insert(0,zero);
        zero.push_back('0');
        resu = soma_base_10N(resu,x);
    }
    reverse(resu.begin(),resu.end());
    return resu;
};



//fazer como funcao lambida
//arrumar para nao usar o reverse tantas vezes
string BigNum::soma_base_10(string num_string1,string num_string2)const{
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
    
    
BigNum::BigNum(const string &num){
    Big.push_back(0);
    Converte(num);
}
BigNum::BigNum(){
    Big.push_back(0);
}
 
    

BigNum BigNum::operator+(const BigNum &outro) const
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

BigNum BigNum::operator+(const string &outro1) const
{
    BigNum outro(outro1);
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

BigNum BigNum::operator-(const BigNum &outro) const
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

BigNum BigNum::operator-(const string &outro1) const
{
    BigNum outro(outro1);
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

bool BigNum::operator==(const BigNum &outro) const{
    size_t i=0;
    while(i < Big.size() && Big[i] == 0) 
        i++;
    size_t n=0;
    while(n < outro.Big.size() && outro.Big[n] == 0) 
        n++;
    if(outro.Big.size() -n != Big.size() - i){
        return false;
    }
    size_t tam = max(Big.size() - i,outro.Big.size() -n);
    for(size_t k =0;k < tam;k++){
        if(Big.at(k+i) != outro.Big.at(k+n))
            return false;
        
    }
    return true;
}

bool BigNum::operator==(const string &outro1) const{
    BigNum outro(outro1);
    size_t i=0;
    while(i < Big.size() && Big[i] == 0) 
        i++;
    size_t n=0;
    while(n < outro.Big.size() && outro.Big[n] == 0) 
        n++;
    if(outro.Big.size() -n != Big.size() - i){
        return false;
    }
    size_t tam = max(Big.size() - i,outro.Big.size() -n);
    for(size_t k =0;k < tam;k++){
        if(Big.at(k+i) != outro.Big.at(k+n))
            return false;
        
    }
    return true;
}



/*  
//implementar ainda 
bool BigNum::operator>(const BigNum &outro) const{
    size_t i=0;
    while(Big[i] == 0) 
        i++;
    size_t n=0;
    while(outro.Big[n] == 0) 
        n++;
    if(outro.Big.size() -n < Big.size() - i){
        return true;
    }
    //comparar byte por byte
    size_t tam = max(outro.Big.size() -n,Big.size() - i);
    for(size_t i =0;i < tam;i++){
    }
}
*/
/*BigNum BigNum::operator*(BigNum outro)const {
    BigNum resu("0");
    while(outro > "0"){
        resu =  resu + *this;
        outro = (outro - "1");
    }
    return resu;
}
*/

void BigNum::mostra_bytes ()const{
    for(uint8_t x : Big){
        cout << (int)x << " ";
    }
}

void BigNum::Converte(const string &num){
    for(size_t i =0;i < num.size();i++){
        
        uint16_t carry = num[i] - '0';
        for(size_t j =0;j < Big.size();j++){
        
            uint16_t s = Big[j]*10 + carry;
            Big[j] = (uint8_t)(s % 256);
            carry = s/256;
            
        }
        while(carry){
            Big.push_back((uint8_t)(carry % 256));
            carry = carry/256;
        }
        
    }
}

string BigNum::DesConverte()const{       
    //num = num * 256 + digito;
    string num = "0";
    for(int i = Big.size() -1;i >= 0;i--){
        num = multiplica(num,"256");
        num = soma_base_10(num,to_string(Big.at(i) ) );
    }
    return num;
}

//nao funciona para numeros muitos grandes 
void BigNum::DesConverteSimples()const{
    unsigned long long num = 0;
    for(size_t i =0;i < Big.size();i++){
        num += Big[i] * pow(256,i);
    }
    cout << num;
}

//implementar ainda 
void BigNum::fatorial(unsigned num){
    for(size_t i =0;i < num;i++){
        
    }
}


//istream &operator>>(istream &input, BigNum &Num){

//}

