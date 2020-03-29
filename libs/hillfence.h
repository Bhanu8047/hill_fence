#include"source/railfence.h"
#include"source/hillcipher.h"

namespace uiuc {
    template <typename T>
class hillfence{
    int second_key,size;
    std::string pltext, citext, first_key;
    T encrypt_by_rail(){
        rail_fence<void> obj(pltext,second_key);
        obj.encrypt();
        citext = obj.get_encText();
    }
    // for userkey
    T encrypt_by_hill(std::string key){
        hillcipher<void> obj(citext,key);
        citext = obj.encrypt();
    }
    // For auto generated key
    T encrypt_by_hill(){
        hillcipher<void> obj(citext);
        citext = obj.encrypt();
        first_key = obj.getKey();
    }

    public:
        hillfence(){}
        hillfence(std::string s, std::string first_key, int second_key = 2 ){
            this->first_key = first_key;
            this->second_key = second_key;
            pltext  = s;
            encrypt_by_rail();
            encrypt_by_hill(first_key);
        }
         hillfence(std::string s, int key){
            second_key = key;
            pltext = s;
            encrypt_by_rail();
            encrypt_by_hill();
        }
        hillfence(std::string s){
            second_key = 2;
            pltext = s;
            encrypt_by_rail();
            encrypt_by_hill();
        }
        auto getCipher(){
            return citext;
        }
        auto getKey(){
            return first_key;
        }
        auto validate(const std::string s,const std::string first_key, const int second_key){
            hillfence<void> obj(s,first_key,second_key);
            return obj.getCipher() == citext;
        }
};
}