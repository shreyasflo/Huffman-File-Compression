#include<iostream>
#include<string.h>
#include<iomanip>
#include<stdlib.h>
#include<cctype>
#include<fstream>
#define WImaxChildCountE 5
#define HALtype 99
using namespace std;
template<class type>
class Q
{
    public:
        Q(int d=2);
        ~Q(void);
        void insertQ(type*);
        type* deleteQ(void);
        type* Start(void);
        bool Min(void) const;
        bool Max(void) const;
    private:
        int lastEle;
        type* *mutableArray;
        int currentSize;
        static const int sizeStep=10;
        int maxChildCount;
        Q(const Q &);
        const Q & operator=(const Q &);

        void buildTop(int, int);
        void buildDown(int, int);
        void exchange(type* &, type* &);
};
template<class type>
Q<type>::Q(int d)
{
    if(d<2) d=2;
    maxChildCount=d;
    lastEle=0;
    currentSize=sizeStep;
    mutableArray=new type*[currentSize];
}
template<class type>
bool Q<type>::Min(void) const
{
    return (lastEle<=0);
}
template<class type>
bool Q<type>::Max(void) const
{
    return (lastEle>=currentSize);
}
template<class type>
type* Q<type>::deleteQ(void)
{
    if(Min())
    {
        cerr<<"deleteQ error! exiting..."<<endl;
        exit(1);
    }
    type* rval=mutableArray[0];
    mutableArray[0]=mutableArray[lastEle-1];
    --lastEle;
    buildDown(0, lastEle-1);
    return rval;
}
template<class type>
type* Q<type>::Start(void)
{
    if(Min())
    {
        cerr<<"deleteQ error! exiting..."<<endl;
        exit(1);
    }
    return mutableArray[0];
}
template<class type>
void Q<type>::insertQ(type* foo)
{
    if(Max())
    {
        int ncurrentSize=currentSize+sizeStep;
        type* *nmutableArray=new type*[ncurrentSize];
        for(int i=0;i<currentSize;++i)
            nmutableArray[i]=mutableArray[i];
        delete[] mutableArray;
        mutableArray=nmutableArray;
        currentSize=ncurrentSize;
    }
    mutableArray[lastEle++]=foo;
    buildTop(0, lastEle-1);
}
template<class type>
void Q<type>::buildTop(int root, int bottom)
{
    int parent;
    if(bottom > root)
    {
        parent=(bottom-1)/maxChildCount;
        if(*mutableArray[parent] > *mutableArray[bottom])
        {
            exchange(mutableArray[parent], mutableArray[bottom]);
            buildTop(root, parent);
        }
    }
}
template<class type>
void Q<type>::buildDown(int root, int bottom)
{
    int minchild, firstchild, child;
    firstchild=root*maxChildCount+1;
    if(firstchild <= bottom)
    {
        minchild=firstchild;
        for(int i=2;i <= maxChildCount;++i)
        {
            child=root*maxChildCount+i;
            if(child <= bottom)
            {
                if(*mutableArray[child] < *mutableArray[minchild])
                {
                    minchild=child;
                }
            }
        }
        if(*mutableArray[root] > *mutableArray[minchild])
        {
            exchange(mutableArray[root], mutableArray[minchild]);
            buildDown(minchild, bottom);
        }
    }
}
template<class type>
void Q<type>::exchange(type* &a, type* &b)
{
    type* c;
    c=a;
    a=b;
    b=c;
}
template<class type>
Q<type>::~Q(void)
{
    delete[] mutableArray;
}
class typeree
{
    private:
        class Node
        {
            public:
                unsigned int freq;
                unsigned char ch;
                Node *left, *right;
                Node(void)
                    :freq(0), ch('\0'), left(NULL), right(NULL) {}
        };
        Node *root;
        typeree(const typeree &);
        const typeree & operator=(const typeree &);
        void chop(Node * N);
        void print(ostream &, Node *, int) const;
        void print(Node *, int) const;
    public:
        typeree(void);
        ~typeree(void);
        friend ostream & operator<<(ostream &, const typeree &);
        unsigned int get_freq(void) const;
        unsigned char get_char(void) const;
        void set_freq(unsigned int);
        void set_char(unsigned char);
        Node* get_left(void) const;
        Node* get_right(void) const;
        void set_left(Node *);
        void set_right(Node *);
        Node* get_root(void) const;
        bool operator==(const typeree &) const;
        bool operator!=(const typeree &) const;
        bool operator<(const typeree &) const;
        bool operator>(const typeree &) const;
        bool operator<=(const typeree &) const;
        bool operator>=(const typeree &) const;
        void HC(Node *, unsigned char, string, string &) const;
        void HClist(Node *, string) const;
        bool getChar(string, unsigned char &) const;
        string putChar(Node *) const;
};
typeree::typeree(void)
{
    Node* N=new Node;
    root=N;
}
void typeree::chop(Node *N)
{
    if(N)
    {
        chop(N->left);
        chop(N->right);
        delete N;
    }
}
typeree::~typeree(void)
{
    chop(root);
}
unsigned int typeree::get_freq(void) const
{
    return root->freq;
}
unsigned char typeree::get_char(void) const
{
    return root->ch;
}
void typeree::set_freq(unsigned int f)
{
    root->freq=f;
}
void typeree::set_char(unsigned char c)
{
    root->ch=c;
}
typeree::Node* typeree::get_left(void) const
{
    return root->left;
}
typeree::Node* typeree::get_right(void) const
{
    return root->right;
}
void typeree::set_left(Node* N)
{
    root->left=N;
}
void typeree::set_right(Node* N)
{
    root->right=N;
}
typeree::Node* typeree::get_root(void) const
{
    return root;
}
void typeree::print(ostream & ost, Node * curr, int level) const
{
    if(curr)
    {
        print(ost,curr->right,level+1);

        ost<<setw(level*WImaxChildCountE)<<putChar(curr)<<":"
           <<curr->freq<<endl;
        print(ost,curr->left,level+1);
    }
}
void typeree::print(Node * curr, int level) const
{
    if(curr)
    {
        print(curr->right,level+1);

        cout<<setw(level*WImaxChildCountE)<<putChar(curr)<<":"
            <<curr->freq<<endl;
        print(curr->left,level+1);
    }
}
ostream & operator<<(ostream &ost, const typeree &t)
{
    t.print(ost, t.root, 1);
    return ost;
}
bool typeree::operator==(const typeree & type) const
{
    return (root->freq == type.root->freq);
}
bool typeree::operator!=(const typeree & type) const
{
    return (root->freq != type.root->freq);
}
bool typeree::operator<(const typeree & type) const
{
    return (root->freq < type.root->freq);
}
bool typeree::operator>(const typeree & type) const
{
    return (root->freq > type.root->freq);
}
bool typeree::operator<=(const typeree & type) const
{
    return (root->freq <= type.root->freq);
}
bool typeree::operator>=(const typeree & type) const
{
    return (root->freq >= type.root->freq);
}
void typeree::HC(Node* N, unsigned char c, string str, string & s) const
{
    if(N)
    {

        if(!N->left && !N->right && N->ch == c)
        {
            s=str;
        }
        else
        {

            HC(N->left, c, str+"0",s);
            HC(N->right, c, str+"1",s);
        }
    }
}
void typeree::HClist(Node* N, string str) const
{
    if(N)
    {
        if(!N->left && !N->right)
            cout<<putChar(N)<<" "<<str<<endl;
        else
        {

            HClist(N->left, str+"0");
            HClist(N->right, str+"1");
        }
    }
}
bool typeree::getChar(string s, unsigned char & c) const
{
    Node * curr=root;
    for(unsigned int i=0;i<s.size();++i)
    {
        if(s[i]=='0')
            curr=curr->left;
        if(s[i]=='1')
            curr=curr->right;
    }
    bool found=false;
    if(!curr->left && !curr->right)
    {
        found=true;
        c=curr->ch;
    }
    return found;
}
string typeree::putChar(Node * N) const
{
    string s="";

    if(!N->left && !N->right)
    {
        unsigned char c=N->ch;
        if(iscntrl(c) || c==32)
        {
            char* cp=new char;
            for(int i=0;i<3;++i)
            {
                sprintf(cp,"%i",c%8);
                c-=c%8;
                c/=8;
                s=(*cp)+s;
            }
            s='/'+s;
        }
        else
            s=c;
    }
    return s;
}
void HC_write(unsigned char i, ofstream & writeTo)
{
    static int bit_pos=0;
    static unsigned char c='\0';

    if(i<2)
    {
        if(i==1)
            c=c | (i<<(7-bit_pos));
        else
            c=c & static_cast<unsigned char>(255-(1<<(7-bit_pos)));
        ++bit_pos;
        bit_pos%=8;
        if(bit_pos==0)
        {
            writeTo.put(c);
            c='\0';
        }
    }
    else
    {
        writeTo.put(c);
    }
}
unsigned char HC_read(ifstream & infile)
{
    static int bit_pos=0;
    static unsigned char c=infile.get();
    unsigned char i;
    i=(c>>(7-bit_pos))%2;
    ++bit_pos;
    bit_pos%=8;
    if(bit_pos==0)
        if(!infile.eof())
        {
            c=infile.get();
        }
        else
            i=2;
    return i;
}
void compressor(string inputFile, string outputFile, bool Work)
{
    ifstream infile(inputFile.c_str(), ios::in|ios::binary);
    if(!infile)
        cerr<<inputFile<<"ERROR"<<endl;
    if(ifstream(outputFile.c_str()))
        cerr<<outputFile<<"DUPLICATE"<<endl;
    ofstream writeTo(outputFile.c_str(), ios::out|ios::binary);
    if(!writeTo)
         cerr<<outputFile<<"ERROR";
    unsigned int frequency[256];
    for(int frequencyIndex = 0;frequencyIndex < 256;++frequencyIndex)
        frequency[frequencyIndex]=0;
    char character;
    unsigned char characterValue;
    while(infile.get(character))
    {
        characterValue=character;
        ++frequency[characterValue];
    }
    infile.clear();
    infile.seekg(0);
    Q<typeree> q(3);
    typeree* tp;
    for(int frequencyIndex = 0;frequencyIndex < 256;++frequencyIndex)
    {
        writeTo.put(static_cast<unsigned char>(frequency[frequencyIndex]>>24));
        writeTo.put(static_cast<unsigned char>((frequency[frequencyIndex]>>16)%256));
        writeTo.put(static_cast<unsigned char>((frequency[frequencyIndex]>>8)%256));
        writeTo.put(static_cast<unsigned char>(frequency[frequencyIndex]%256));
        if(frequency[frequencyIndex]>0)
        {

            tp=new typeree;
            (*tp).set_freq(frequency[frequencyIndex]);
            (*tp).set_char(static_cast<unsigned char>(frequencyIndex));
            q.insertQ(tp);
        }
    }
    typeree* tp2;
    typeree* tp3;
    do
    {
        tp=q.deleteQ();
        if(!q.Min())
        {
            tp2=q.deleteQ();
            tp3=new typeree;
            (*tp3).set_freq((*tp).get_freq()+(*tp2).get_freq());
            (*tp3).set_left((*tp).get_root());
            (*tp3).set_right((*tp2).get_root());
            q.insertQ(tp3);
        }
    }
    while(!q.Min());
    string H_table[256];
    unsigned char uc;
    for(unsigned short us=0;us<256;++us)
    {
        H_table[us]="";
        uc=static_cast<unsigned char>(us);
        (*tp).HC((*tp).get_root(), uc, "", H_table[us]);
    }
    if(Work)
    {
        cout<<*tp<<endl;
        (*tp).HClist((*tp).get_root(), "");
        cout<<"frequency table is "<<sizeof(unsigned int)*256<<" bytes"<<endl;
    }
    unsigned int allCharacters = (*tp).get_freq();
    cout<<"All Char "<<allCharacters<<endl;
    unsigned char ch2;
    while(infile.get(character))
    {
        characterValue=character;

        for(unsigned int i=0;i<H_table[characterValue].size();++i)
        {
            if(H_table[characterValue].at(i)=='0')
                ch2=0;
            if(H_table[characterValue].at(i)=='1')
                ch2=1;
            HC_write(ch2, writeTo);
        }
    }
    ch2=2;
    HC_write(ch2, writeTo);
    infile.close();
    writeTo.close();
}
void extractor(string inputFile, string outputFile, bool Work)
{
    ifstream infile(inputFile.c_str(), ios::in|ios::binary);
    if(!infile)
        cerr<<inputFile<<"ERROR";
    if(ifstream(outputFile.c_str()))
        cerr<<outputFile<<"DUPLICATE";
    ofstream writeTo(outputFile.c_str(), ios::out|ios::binary);
    if(!writeTo)
        cerr<<outputFile<<"ERROR";
    unsigned int frequency[256];
    char character;
    unsigned char characterValue;
    unsigned int j=1;
    for(int frequencyIndex=0;frequencyIndex<256;++frequencyIndex)
    {

        frequency[frequencyIndex]=0;
        for(int k=3;k>=0;--k)
        {
            infile.get(character);
            characterValue=character;
            frequency[frequencyIndex]+=characterValue*(j<<(8*k));
        }
    }
    Q<typeree> q(3);
    typeree* tp;
    for(int frequencyIndex=0;frequencyIndex<256;++frequencyIndex)
    {
        if(frequency[frequencyIndex]>0)
        {

            tp=new typeree;
            (*tp).set_freq(frequency[frequencyIndex]);
            (*tp).set_char(static_cast<unsigned char>(frequencyIndex));
            q.insertQ(tp);
        }
    }
    typeree* tp2;
    typeree* tp3;
    do
    {
        tp=q.deleteQ();
        if(!q.Min())
        {

            tp2=q.deleteQ();
            tp3=new typeree;
            (*tp3).set_freq((*tp).get_freq()+(*tp2).get_freq());
            (*tp3).set_left((*tp).get_root());
            (*tp3).set_right((*tp2).get_root());
            q.insertQ(tp3);
        }
    }
    while(!q.Min());
    if(Work)
    {
        cout<<*tp<<endl;

        (*tp).HClist((*tp).get_root(), "");
        cout<<"frequency table is "<<sizeof(unsigned int)*256<<" bytes"<<endl;
    }
    string Str;
    unsigned char character2;
    unsigned int total_chars=(*tp).get_freq();
    cout<<"All chars "<<total_chars<<endl;
    while(total_chars>0)
    {
        Str="";
        do
        {
            character=HC_read(infile);
            if(character==0)
                Str=Str+'0';
            if(character==1)
                Str=Str+'1';
        }
        while(!(*tp).getChar(Str, character2));

        writeTo.put(static_cast<char>(character2));
        --total_chars;
    }

    infile.close();
    writeTo.close();
}
void usage_msg ( const string & pname )
{
    cerr << "Path of EXE " << pname<< endl;
    cerr <<" -e  : encoding" << endl;
    cerr << " -d  : decoding" << endl;
    cerr << " -i  : input_file" << endl;
    cerr << " -o : output_file"<< endl;
    cerr << " -v  : view process " << endl;
    cerr << " -h  : help" << endl;
}

int main( int argc, char * argv[] )
{
    string in;
    string out;
    bool cmprss = true;
    bool Work = false;

    for ( int i = 1 ; i < argc ; ++i )
    {
        if ( !strcmp( "-h", argv[i] ) || !strcmp( "--help", argv[i] ) )
        {
            usage_msg( argv[0] );
            exit( HALtype );
        }
        else if ( !strcmp( "-i", argv[i] ) )
        {
            cerr << "input file is '" << argv[++i] << "'" << endl;
            in = argv[i];
        }
        else if ( !strcmp( "-o", argv[i] ) )
        {
            cerr << "output file is '" << argv[++i] << "'" << endl;
            out = argv[i];
        }
        else if ( !strcmp( "-d", argv[i] ) )
            cmprss = false;
        else if ( !strcmp( "-e", argv[i] ) )
            cmprss = true;
        else if ( !strcmp( "-v", argv[i] ) )
            Work = true;
    }
    if ( !in.size() || !out.size() )
    {
        cerr << "Enter in format given in readMe" << endl;
        usage_msg( argv[0] );
        exit( HALtype );
    }
    if ( cmprss )
    {
        cerr << "Compress ...." << endl;
        compressor( in, out, Work );
    }
    else
    {
        cerr << "Extract ...." << endl;
        extractor( in, out, Work );
    }
    cerr << "Finishing up .... " << endl;
    return 0;
}
