#include<bits/stdc++.h>
using namespace std;

// Declaring the structure for each node
struct node {
	char symbol;
	int freq;
	node *leftNode, *rightNode;
	node(char symbol, int freq, node* leftNode, node* rightNode) {
		this->freq = freq;
		this->symbol = symbol;
		this->leftNode = leftNode;
		this->rightNode = rightNode;
	}
};

// To compare between 2 structure objects
class cmp {
public:
	bool operator()(node* left, node* right){
		return (left->freq > right->freq);
	}
};

// Assigning the o/1 bits to the paths of the huffman tree generated - recursive function
void genHuffCodes(node* root, string str, map<char, string> &codes)
{
    if(root != NULL) {
		if (!(root->leftNode) && !(root->rightNode))    
			codes[root->symbol] = (str != "") ? str : "0";
		genHuffCodes(root->leftNode, str + "1", codes);
		genHuffCodes(root->rightNode, str + "0", codes); 
	}
}

float calculate_average_no_of_bits(map<char,int> freqMap,map<char,string> compCode){
	vector<char> c;
    for(auto& i:freqMap){
        c.push_back(i.first);
    }
    int n=0;
    int sum = 0;
    int nc = 0;
    cout<<"Table for the Calculation of average number of bits"<<endl;
    cout<<"----------------------------------------------------------------------"<<endl;
    cout << "Symbol\t\t" << "Frequency\t\t" << "Huffman Code\t\t" << "Code Length\t\t" <<endl;
    cout<<"----------------------------------------------------------------------"<<endl;
    for(int i=0;i<c.size();i++){
        sum += freqMap[c[i]] * compCode[c[i]].length();
        nc += freqMap[c[i]];
        if(compCode[c[i]].length() >= 8)
            cout << c[i] << "\t\t\t\t" << freqMap[c[i]] << "\t\t\t\t" << compCode[c[i]] << "\t\t\t\t" << compCode[c[i]].length() <<endl;
        else
            cout << c[i] << "\t\t\t\t" << freqMap[c[i]] << "\t\t\t\t" << compCode[c[i]] << "\t\t\t\t" << compCode[c[i]].length() <<endl;
    cout<<"----------------------------------------------------------------------"<<endl;
    }
    cout<<"Total number of bits : "<<sum<<endl;
    cout<<"Total number of characters : "<<nc<<endl;
	cout<<"----------------------------------------------------------------------"<<endl;
	return float(sum)/nc;
}

void displayStats(string &text, map<char,int> &freqMap, string codedText, map<char, string> &compCode) {
	//---------------------------------------------------------------------
	cout<<"Total number of characters in the text are : "<<text.length()<<endl<<endl;	
	
	//---------------------------------------------------------------------
	//Printing the generated frequency table
	cout<<"----------------Frequncey Table----------------"<<endl<<endl;
    cout<<"Character\t"<<"Frequency\t"<<"\tASCII Value\t"<<endl;
    cout<<"----------------------------------------------"<<endl;
    for (auto &it : freqMap){
        cout <<it.first << "\t\t\t\t" << it.second<< "\t\t\t\t" << int(it.first) << endl;
        cout<<"-----------------------------------------"<<endl;
    }
	cout<<endl<<endl;
    
	//---------------------------------------------------------------------
	cout<<"Average no. of bits : "<<calculate_average_no_of_bits(freqMap,compCode)<<endl<<endl;	

	//---------------------------------------------------------------------
	// Printing the huffman codes
	cout<<endl<<endl<<"\nOutput from Huffman Coding is as follows"<<endl;
    cout<<"========================================="<<endl;
    cout<<"Character"<<"\t"<<"Huffman Code"<<endl;
    cout<<"========================================="<<endl;
    for (auto& it : compCode){
        cout<<it.first<<"\t\t"<<it.second<<endl;
        cout<<"-----------------------------------------"<<endl;
    }
	cout<<endl<<endl;

	//---------------------------------------------------------------------
	cout<<"Huffman coding output for input text file will be : \n"<<codedText<<endl;
}

int main(){
    string text_file = "Assignment_1_input.txt";
    ifstream input_file(text_file);

    if (!input_file.is_open()) {
        cout << "File cannot open" << endl;
        return 0;
    }

    //Opening the file
    char character;
    string text ="";
    map<char, int> freqMap;
	map<char,string> huffCode;
	priority_queue<node*, vector<node*>, cmp> symbols;
	struct node *temp, *left;

	// Generating frequency table of characters
    while (input_file.get(character)) {
      	if(character != ' ' && character != '\n') {
            text = text + character;
			freqMap[character]++;
		}
	}
	//Closing the file
	input_file.close();

	//Applying huffman coding algorithm	
	for (auto i : freqMap)
		symbols.push(new node(i.first,i.second, NULL, NULL));
	
    while (symbols.size() != 1){
        left = symbols.top(); 
		symbols.pop();	
		temp = new node(' ', left->freq + symbols.top()->freq, left, symbols.top());
		symbols.pop();
		symbols.push(temp);
	}
	// Assigning codes to each path on the tree
	genHuffCodes(symbols.top(), "", huffCode);

    //Generating the encoded string for given input text
    string codedText;
    for (char ch: text)
        codedText += huffCode[ch];

	// displaying the statistics
	displayStats(text, freqMap, codedText, huffCode);
	
	return 1;
}
