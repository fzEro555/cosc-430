//
// Created by 肖强 on 2019/4/2.
//

#include <botan-1.10/botan/botan.h>
#include <botan-1.10/botan/bcrypt.h>
#include <iostream>
using namespace std;
using namespace Botan;

int main(int argc, char* argv[])
{
    LibraryInitializer init;
    AutoSeeded_RNG rng;
    int a=1;
    string strr="4sdfgnglkjnfkdfdfndfglgndlkgdnlkjj";
    cout<<generate_bcrypt(strr, rng,a);
    return 0;
}