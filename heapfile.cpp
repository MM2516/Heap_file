# include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct Node{
    int fptr;
    vector<int> ptrs;
    vector<int> key;
};

class page{
    int psize;
    vector<Node*> f;
    public:
    page(int psize);
    void insert(int,int) ;
    void status();
    void search(int);
};

page::page(int psize){
    this->psize = psize;
}

void page::insert(int Rsize,int n){
    if(f.size()==0){
        Node* temp = new Node();
        temp->ptrs.push_back(0);
        temp->fptr = 16+Rsize+4;
        temp->key.push_back(n);
        f.push_back(temp);
        return;
    }
    for(int i=0;i<f.size();i++){
        int temp = psize-f[i]->fptr;
        if(Rsize+4<=temp){
            f[i]->key.push_back(n);
            f[i]->ptrs.push_back(f[i]->fptr-16);
            f[i]->fptr = f[i]->fptr+Rsize+4;
            return;
        }
    }
    Node* newpage = new Node();
    newpage->fptr = 16+Rsize+4;
    newpage->ptrs.push_back(0);
    newpage->key.push_back(n);
    f.push_back(newpage);
}


void page::search(int key){
    for(int i=0;i<f.size();i++){
        auto it = find(f[i]->key.begin(),f[i]->key.end(),key);
        if(it !=f[i]->key.end()){
            cout<<i<<" "<<it-f[i]->key.begin()<<endl;
            return;
        }
    }
    cout<<-1<<" "<<-1<<endl;
}

void page::status(){
    if(f.size()==0){
        cout<<0<<endl;
        return;
    }
    cout<<f.size()<<" ";
    for(int i=0;i<f.size();i++){
        cout<<f[i]->key.size()<<" ";
    }
    cout<<endl;
}



int main(){
   int c,pagesize,recordsize,primarykey;
   cin>>pagesize;
   page p(pagesize);
   cin>>c;
   while(c!=4){
     switch(c){
      case 1: //insert
              {cin>>recordsize>>primarykey;
              p.insert(recordsize,primarykey);
              break;}
      case 2: //Status
              {p.status();
              break;}
      case 3: //Search
              {cin>>primarykey;
              p.search(primarykey);
              break;}
      default: {break;}
     }
    cin>>c;
   }
return 0;
}


