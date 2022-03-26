#include<bits/stdc++.h>
using namespace std;

// class min_heap_node {
// public:
// 	char symbol;
// 	int frequency;
// 	min_heap_node *left, *right;
// 	min_heap_node(char symbol, int frequency){
// 		left = right = NULL;
// 		this->symbol = symbol;
// 		this->frequency = frequency;
// 	}
// };

struct node {
	char symbol;
	int freq;
	node *leftNode, *rightNode;
	node(char symbol, int freq) {
		this->freq = freq;
		this->symbol = symbol;
		leftNode = rightNode = NULL;
	}
};

class compare {
public:
	bool operator()(node* left1, node* right1){
		return (left1->freq > right1->freq);
	}
};

void print_frequency_table(map<char,int> M){
    cout<<"Frequncey Table"<<endl;
    cout<<"========================================="<<endl;
    cout<<"Character"<<"\t"<<"ASCII Value\t"<<"Frequency"<<endl;
    cout<<"========================================="<<endl;
    for (auto& it : M){
        cout <<it.first << "\t\t" << int(it.first) << "\t\t" << it.second<< endl;
        cout<<"-----------------------------------------"<<endl;
    }
}

void generate_huffman_codes(node* root, string str, map<char, string> &huffman_codes)
{
    if(!root)   return;
    if (!(root->leftNode) && !(root->rightNode))    
		huffman_codes[root->symbol] = (str != "") ? str : "1";
	generate_huffman_codes(root->leftNode, str + "0", huffman_codes);
    generate_huffman_codes(root->rightNode, str + "1", huffman_codes);
}

void generated_codes_message(map<char, string> huffman_codes){
    cout<<"\nOutput from Huffman Coding is as follows"<<endl;
    cout<<"========================================="<<endl;
    cout<<"Character"<<"\t"<<"Huffman Code"<<endl;
    cout<<"========================================="<<endl;
    for (auto& it : huffman_codes){
        cout<<it.first<<"\t\t"<<it.second<<endl;
        cout<<"-----------------------------------------"<<endl;
    }
}

map<char, string> Huffman_Coding(map<char,int> M)
{
    map<char, string> huffman_codes;
	priority_queue<node*, vector<node*>, compare> heap_of_symbols;
	struct node *top, *left, *right;
	for (auto i : M)
		heap_of_symbols.push(new node(i.first,i.second));
    while (heap_of_symbols.size() != 1){
        left = heap_of_symbols.top();
        heap_of_symbols.pop();
		right = heap_of_symbols.top();
		heap_of_symbols.pop();
		top = new node('$', left->freq + right->freq);
		top->leftNode = left;
		top->rightNode = right;
		heap_of_symbols.push(top);
	}
	generate_huffman_codes(heap_of_symbols.top(), "", huffman_codes);
    generated_codes_message(huffman_codes);
    return huffman_codes;
}

string get_huffman_string(string text, map<char, string> huffman_codes){
    string str;
    for (char ch: text)
        str += huffman_codes[ch];
    //cout << str << endl;
    return str;
}

float calculate_average_no_of_bits(map<char,int> m1,map<char,string> m2,vector<char> c){
    int n=0;
    int sum = 0;
    int nc = 0;
    cout<<"\nTable for the Calculation of average number of bits"<<endl;
    cout<<"==================================================="<<endl;
    cout << "Symbol" << "\t" << "Frequency" << "\t" << "Huffman Code" << "\t" << "Code Length" <<endl;
    cout<<"==================================================="<<endl;
    for(int i=0;i<c.size();i++){
        sum = sum + m1[c[i]]*m2[c[i]].length();
        nc = nc + m1[c[i]];
        if(m2[c[i]].length()>=8)
            cout << c[i] << "\t" << m1[c[i]] << "\t\t" << m2[c[i]] << "\t" << m2[c[i]].length() <<endl;
        else
            cout << c[i] << "\t" << m1[c[i]] << "\t\t" << m2[c[i]] << "\t\t" << m2[c[i]].length() <<endl;
        cout<<"---------------------------------------------------"<<endl;
    }
    cout<<"Total number of bits : "<<sum<<endl;
    cout<<"Total number of characters : "<<nc<<endl;
    float ab = float(sum)/nc;
    return ab;
}

int main(){
    string text_file = "Assignment_1_input.txt";
    ifstream input_file(text_file);

    if (!input_file.is_open()) {
        cerr << "File cannot open" << endl;
        return EXIT_FAILURE;
    }

    //Opening the file
    char character;
    string text ="";
    map<char, int> freqMap;
    while (input_file.get(character)) {
      	if(character != ' ' && character != '\n') {
            text = text + character;
			freqMap[character]++;
		}
	}
	//Closing the file
	input_file.close();

    // cout<<"Total characters in the text are : "<<total<<endl<<endl;

	//Printing the generated frequency table
    print_frequency_table(freqMap);

    //Applying huffman coding algorithm
    map<char, string> huffman_codes = Huffman_Coding(freqMap);

    //Generating the encoded string for given input text
    string huffman_string;
    huffman_string = get_huffman_string(text,huffman_codes);
    cout<<"Huffman coding output for input text file will be : \n"<<huffman_string<<endl;

    //Calculation of average number of bits
    vector<char> chars;
    for(auto& i:freqMap){
        chars.push_back(i.first);
    }
    float ab = calculate_average_no_of_bits(freqMap,huffman_codes,chars);
    cout<<"Average no. of bits : "<<ab<<endl<<endl;
    return EXIT_SUCCESS;
}
