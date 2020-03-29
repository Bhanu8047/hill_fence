#include<iostream>
#include"libs/hillfence.h"
#define fast std::ios_base::sync_with_stdio(false);std::cin.tie(NULL);

int main()
{
	fast;
    freopen("output.txt","w",stdout);

	// uiuc::rail_fence<void> obj("wiirsenehrte", 4);
	// obj.decrypt();
    // std::cout<<obj.get_decText()<<"\n";

	// uiuc::rail_fence<void> obj1("WINTER IS HERE", 3);
	// obj1.encrypt();
    // std::cout<<obj1.get_encText()<<"\n";

    // uiuc::rail_fence<void> obj4(obj1.get_encText(),3);
    // obj4.decrypt();
    // std::cout<<obj4.get_decText()<<"\n";
	// // std::cout<<obj2.get_encText()<<"\n";

   
    uiuc::rail_fence<void> obj5("HELLO",4);
    obj5.encrypt();
    std::cout<<obj5.get_encText()<<"\n";
    uiuc::hillcipher<void> my(obj5.get_encText(),"WRNCPPMVH");
    std::cout<<my.encrypt()<<" \n";
    std::cout<<my.getKey()<<"\n";

    uiuc::hillfence<void> mast("HELLO",4);
    std::cout<<mast.getCipher()<<"\n";
    std::cout<<mast.getKey()<<"\n";
    // std::cout<<mast.validate("HELL0");

	return 0;
}
// BFLOWC   