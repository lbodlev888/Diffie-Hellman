#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

bool prime(unsigned nr)
{
  for(int i = 2; i <= sqrt(nr); i++)
    if(nr % i == 0) return false;
  return true;
}

string multiply(string num1, string num2) {
   if (num1 == "0" || num2 == "0") {
      return "0";
   }
   string product(num1.size() + num2.size(), 0);
   for (int i = num1.size() - 1; i >= 0; i--) {
      for (int j = num2.size() - 1; j >= 0; j--) {
            int n = (num1[i] - '0') * (num2[j] - '0') + product[i + j + 1];
            product[i + j + 1] = n % 10;
            product[i + j] += n / 10;
      }
   }
   for (int i = 0; i < product.size(); i++) {
      product[i] += '0';
   }
   if (product[0] == '0') {
      return product.substr(1);
   }
   return product;
}

string intToStr(int nr)
{
  string ret = "";
  while(nr > 0)
  {
    ret += (nr % 10) + '0';
    nr /= 10;
  }
  unsigned n = ret.length();
  for (int i = 0; i < n / 2; i++)
    swap(ret[i], ret[n - i - 1]);
  return ret;
}

string power(string base, int exponent)
{
  string base1 = base;
  for(int i = 1; i < exponent; i++) base = multiply(base, base1);
  return base;
}

int mod(string num, int a)
{
  int res = 0;
  for (int i = 0; i < num.length(); i++)
    res = (res * 10 + num[i] - '0') % a;
  return res;
}

int main()
{
  srand(time(NULL));
  int n = 5000000 + rand() % (100000000 - 5000000 + 1);
  while(!prime(n)) n++;
  int intOfG = 1 + rand() % 1000000;
  string G = intToStr(intOfG);
  cout << n << " " << G << "\n";
  int a = 100 + rand() % (999-100+1), b = 100 + rand() % (999-100+1);
  cout << "First private key: " << a << "\nSecond private key: " << b << "\n";
  string pub1 = intToStr(mod(power(G, a), n)), pub2 = intToStr(mod(power(G, b), n));
  cout << "First public key: " << pub1;
  cout << "\nSecond public key: " << pub2;
  cout << "\nComputing shared secret";
  int shared_a = mod(power(pub2, a), n), shared_b = mod(power(pub1, b), n);
  cout << "\nAlice: " << shared_a;
  cout << "\nBob: " << shared_b;
  return 0;
}
