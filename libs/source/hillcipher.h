#include<iostream>
#include<math.h>
#include<vector>
#include<string>
#include<time.h>
#include<algorithm>
namespace uiuc{
    template <typename T>
class hillcipher{
private:
	int rows;
	int columns;
	std::vector< std::vector<int> > arr;
	std::string plText,key,encText;
	std::vector< std::vector<int> > keyArray, encArray;

	T setDimension(int len){
		rows = floor(sqrt(len));
		columns = len/rows;
		if(len % columns > 0)
			columns++;
	}
	T setMatrix(){
		if(rows*columns % plText.size() > 0 ){
			int extraChar = rows*columns % plText.size();
			for(int i=0;i<extraChar;i++)plText += 'z';
		}
		int x = 0;
		for(int i=0;i<rows;i++){
			std::vector<int> v;
			for(int j=0;j<columns;j++){
				v.push_back(plText[x]-97);
				x++;
			}
			arr.push_back(v);
		}
	}
	// If key is set to the object
	T setKeyMatrix(){
		int x = 0;
		for(int i=0;i<columns;i++){
			std::vector<int> v;
			for(int j=0;j<columns;j++){
				v.push_back(tolower(key[x])-97);
				x++;
			}
			keyArray.push_back(v);
		}
	}

	T keyGen(){//Generating key
		srand(time(0));
		for(int i=0;i<columns;i++)
		{

			std::vector<int> v;
			for(int j=0;j<columns;j++)
				v.push_back(rand()%26);

			keyArray.push_back(v);	
		}
	}

	// Matrix Multiplication
	int sumVector(std::vector<int> A, std::vector<int> B){
		int sum=0;
		for(int i=0;i<A.size();i++){
			sum+= A[i]*B[i];
		}
		return sum % 26;
	}

	T matrixMultiply(){
		for(int i=0;i<arr.size();i++){
			std::vector<int> v;
			for(int j=0;j<keyArray.size();j++){
				v.push_back( sumVector(arr[i], keyArray[j]) );
			}
			encArray.push_back(v);
		}
	}

	//  Assingning encrypted value to the cipher variable i.e. EncText
	T setText(){
		for(int i=0;i<encArray.size();i++){
			for(int j=0;j<encArray[i].size();j++){
				encText += toupper((char)encArray[i][j]+97);
			}
		}
	}

public:
	hillcipher(std::string s){
		s.erase(std::remove(begin(s), end(s),' '), end(s));
        std::transform(begin(s),end(s),begin(plText),[](auto i){
            return i = tolower(i);
        });
        plText = s;
		setDimension(this->plText.size());
		setMatrix();
		keyGen();
		matrixMultiply();
		setText();
	}

	hillcipher(std::string s, std::string key){
		s.erase(std::remove(begin(s), end(s),' '), end(s));
        std::transform(begin(s),end(s),begin(plText),[](auto i){
            return i = tolower(i);
        });
        plText = s;
		this->key = key;
		setDimension(this->plText.size());
		setMatrix();
		// keyGen();
		setKeyMatrix();
		// transposeMatrix();
		matrixMultiply();
		setText();
	}
	auto getKey(){
		std::string s = "";
		for(int i=0;i<keyArray.size();i++){
			for(int j=0;j<keyArray[i].size();j++){
				s += toupper((char)keyArray[i][j]+97);
			}
		}
		return s;
	}

	auto encrypt(){
		return encText;
	}
};
}