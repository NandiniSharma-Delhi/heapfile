#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int sizpage;

class data{
    public:
    int pk;
    int datasize;
    vector<int> *p;
    data(){
        datasize=0;
        p=nullptr;

    }
};

class direc{
    public:
    data * recstart;
    direc(){
        //recsize=0;
        recstart = nullptr;
    }
};


class page{
    public:
    vector<data> rec;
    vector<direc> directory;
    int coun;
    //int * freespace;
    page * left;
    page * right;
    int sizetally;
    page(){
        coun=0;
       // freespace = nullptr;
        left = nullptr;
        right = nullptr;
        sizetally = 16;
    }
    int searchrecord(int pk){
        for(int i=0;i<coun;i++){
            if(rec[i].pk == pk){
                return i;
            }
        }
        return -1;
    }


};

class file{
    public:
    page * start;
    int numofpages;
    file(){
        start = nullptr;
        numofpages=0;
    }
    void addrecord(int sizeofrec,int pk){
        page * ptr=start;

        data data1;
        data1.datasize = sizeofrec;
        data1.pk = pk;



        for(int i=0;i<numofpages;i++){
            if((ptr->sizetally)+sizeofrec+4 < sizpage){
                (ptr->rec).push_back(data1);
                direc direc1;
                direc1.recstart = &(ptr->rec[ptr->coun]);
                (ptr->directory).push_back(direc1);
                (ptr->coun)++;
                (ptr->sizetally) = (ptr->sizetally) + sizeofrec+4;
                return;


            }
            else{
                    ptr = ptr->right;
            }

        }
        if(ptr==nullptr && start!=nullptr){
                ptr = start;
            while(ptr->right!=nullptr){
                ptr = ptr->right;
            }

        }
        numofpages++;

        page * page1 = new page;
        if(numofpages==1){

            start = page1;
        }
        else{
            ptr->right = page1;
        page1->left = ptr;

        }
        ptr = page1;
        (ptr->rec).push_back(data1);
        direc direc1;
        direc1.recstart = &(ptr->rec[ptr->coun]);
        (ptr->directory).push_back(direc1);
        (ptr->coun)++;
        (ptr->sizetally) = (ptr->sizetally) + sizeofrec+4;
        return;



    }
    void searchrecord(int pk){
        page * ptr = start;
        for(int i=0;i<numofpages;i++){
            int ans = ptr->searchrecord(pk);
            if(ans!=-1){
                cout<<i<<" "<<ans<<endl;
                return;

            }
            else{

                ptr = ptr->right;
            }
        }
        cout<<"-1 -1"<<endl;
        return;

    }

    void status(){
        cout<<numofpages;
        page * ptr = start;
        for(int i=0;i<numofpages;i++){
            cout<<" "<<ptr->coun;
            ptr = ptr->right;
        }
        cout<<endl;
    }
};

int main()
{   file file1;

    cin>>sizpage;
    int opcode;
    cin>>opcode;
    while(opcode!=4){
        if(opcode ==1){
            int sizeofrec;
            int pk;
            cin>>sizeofrec;
            cin>>pk;
            file1.addrecord(sizeofrec,pk);
        }
        else if(opcode ==3){
            int pk;
            cin>>pk;
            file1.searchrecord(pk);
        }
        else if(opcode ==2){
            file1.status();
        }
        cin>>opcode;
    }
}
