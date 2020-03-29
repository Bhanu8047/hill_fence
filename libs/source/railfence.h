#include<string>
#include<vector>
#include<algorithm>

namespace uiuc{
    template<typename T>
class rail_fence{
private:
	int key,size;
	std::string plText,encText,decText;
	std::vector< std::vector<char> > matrix;
	T fillMatrix(){
		for(int i=0;i<key;i++){
			std::vector<char> v(size);
			std::fill(begin(v),end(v),'_');
			matrix.push_back(v);
		}
	}

	T fillText(){
		bool down = false;
		int row = 0;
		for(int i=0;i<size;i++){
			if(row == 0 || row == key-1)
				down = !down;
			matrix[row].at(i) = plText[i];
			down?row++:row--;
		}
	}
	// While decrypting
	T fillText(char ch){
		bool down = false;
		int row = 0;
		for(int i=0;i<size;i++){
			if(row == 0 || row == key-1)
				down = !down;
			matrix[row].at(i) = ch;
			down?row++:row--;
		}
	}
	std::string readText(){
		std::string s;
		bool down = false;
		int row = 0;
		for(int i=0;i<size;i++){
			if(row == 0 || row == key-1)
				down = !down;
			s.push_back(matrix[row].at(i));
			down?row++:row--;
		}
		return s;
	}

	T getEncrypted(){
		std::string s;
		for(int i=0;i<matrix.size();i++)
			for(int j=0;j<matrix[i].size();j++)
				if(matrix[i][j] != '_')
					s += matrix[i][j];
		encText = s;
	}
	
	T getDecrypted(){
		fillText('*');
		int index = 0;
		for(int i=0;i<matrix.size();i++)
			for(int j=0;j<matrix[i].size();j++)
				if(matrix[i][j] == '*' && index < size)
					matrix[i][j] = plText[index++];
		decText = readText();
	}
    

public:
	rail_fence(){};
	rail_fence(std::string s, int key = 2){
		this->key = key;
        s.erase(std::remove(begin(s), end(s),' '), end(s));
        std::transform(begin(s),end(s),begin(s),[](auto i){
            return i = tolower(i);
        });
        plText = s;
        size = s.size();
		fillMatrix();
		fillText();
	}
    
	auto getText(){return plText;}
    auto getKey(){return key;}
    auto get_encText(){if(!encText.empty())return encText; return std::string("{-undefined-}");}
    auto get_decText(){if(!decText.empty())return decText; return std::string("{-undefined-}");}
	T encrypt(){getEncrypted();}
	T decrypt(){getDecrypted();}

};

}