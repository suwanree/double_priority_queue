#include <iostream>

#define SIZE 1000001


using namespace std;


int heap[SIZE];
int counter = 1;

// 홀수 : min heap
// 짝수 : max heap
bool isMAXheap(int x){
    int index = 1;

    while(x > 1){
        x >>= 1;
        index++;
    }

    return index%2 == 0 ? true : false;
}

void swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}

void pushUpMin(int cur){
    int pparent = cur/4;
    if(cur >= 4 && heap[pparent] > heap[cur]){
        swap(heap[pparent], heap[cur]);
        pushUpMin(pparent);
    }
}

void pushUpMax(int cur){
    int pparent = cur/4;
    if(cur >= 4 && heap[pparent] < heap[cur]){
        swap(heap[pparent], heap[cur]);
        pushUpMax(pparent);
    }
}



void pushUp(int value){
    heap[counter] = value;

    if(counter==1){
        counter++;
        return;
    }

    int parent = counter/2;

    if(isMAXheap(parent)){
        if(heap[parent] < heap[counter]){
            swap(heap[parent], heap[counter]);
            pushUpMax(parent);
        }
        else{
            pushUpMin(counter);
        }
    }
    else{
        if(heap[parent] > heap[counter]){
            swap(heap[parent], heap[counter]);
            pushUpMin(parent);
        }
        else{
            pushUpMax(counter);
        }
    }
    counter++;
}

int getMinimumOrMaximumIndex(int cur, bool* isChild, bool Minimum){
    if(cur*2 >= counter)       
        return -1;

    int dn[6] = {       cur*2, cur*2+1,
                 cur*4, cur*4+1, cur*4+2, cur*4+3};
    
    int index = dn[0];
    int value = heap[index];

    for(int i = 1; i<6; i++){
        if(Minimum && dn[i] < counter && value > heap[dn[i]]){
            value = heap[dn[i]];
            index = dn[i];
        }
        else if(!Minimum && dn[i] < counter && value < heap[dn[i]]){
            value = heap[dn[i]];
            index = dn[i];
        }
    }

    if(index == dn[0] || index == dn[1])
        *isChild = true;
    else
        *isChild = false;
    return index;
}

void pushDownMaxLevel(int cur){
    bool isChild;
    int index = getMinimumOrMaximumIndex(cur, &isChild, false);

    if(index == -1){
        return;
    }

    if(heap[index] > heap[cur])
        swap(heap[index], heap[cur]);

    if(!isChild){
        if(heap[index/2] > heap[index]){
            swap(heap[index/2], heap[index]);
        }
        pushDownMaxLevel(index);
    }
}
void pushDownMinLevel(int cur){
    bool isChild;
    int index = getMinimumOrMaximumIndex(cur, &isChild, true);
    if(index == -1){
        return;
    }

    if(heap[index] < heap[cur])
        swap(heap[index], heap[cur]);

    if(!isChild){
        if(heap[index/2] < heap[index]){
            swap(heap[index/2], heap[index]);
        }
        pushDownMinLevel(index);
    }

}


void pushDown(bool max){
    if(counter == 1){
        return;
    }

    if(max){
        int index;
        if(counter == 2)
            index = 1;
        else if(counter == 3)
            index = 2;
        else
            index = heap[2] > heap[3] ? 2 : 3;

        heap[index] = heap[--counter];
        pushDownMaxLevel(index);
    }
    else{
        heap[1] = heap[--counter];
        pushDownMinLevel(1);
    }
}


int getMAX(){
    if(counter == 2){
        return heap[1];
    }
    else if(counter == 3){
        return heap[2];
    }
    else
    return max(heap[2], heap[3]);
}

int getMIN(){
    return heap[1];
}

void print(){
    cout << "\nprint ";
    for(int i = 1; i<counter; i++)
        cout << heap[i] << " ";
    cout << endl;
}

int main(void){

    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int m;

    char command;
    cin >> m;
    for(int i = 0; i<m; i++){
        int n, value;
        cin >> n;
        for(int j = 0; j<n; j++){
            cin >> command >> value;
            if(command == 'I'){
                pushUp(value);
            }
            else if(command == 'D'){
                if(value == -1){
                    pushDown(false);
                }
                else if(value == 1){
                    pushDown(true);
                }
            }

            //print();
        }

        
        if(counter == 1){
            cout << "EMPTY\n";
        }
        else{
            cout << getMAX() << ' ' << getMIN() << '\n';
        }

        counter = 1;
    }

    return 0;
}