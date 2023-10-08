#include<stdio.h>
#include<stdlib.h>
#include<stack>
using namespace std;
#define CUP 6
struct State{
    int Glass[CUP];
    // Định nghĩa cấu trúc State
};
void Makenullstate(State *State){
    for(int i=0;i<6;i++){
        if(i%2==0){
            State->Glass[i] = 1;
        }else{
            State->Glass[i] = -1;
        }
        // Thiết lập trạng thái ban đầu của bài toán
    }
}
struct Node{
    State State;
    Node *Dad;
    int Order;
    // Định nghĩa cấu trúc Node
};
int Comparestate(State S1, State S2){
    for(int i=0;i<6;i++){
        if(S1.Glass[i]!=S2.Glass[i]){
            return 0;
        }
        // Kiểm tra hai trạng thái có giống nhau hay không
    }
    return 1;
}
int Findstate(State State, stack<Node*> Openstack){
    while(!Openstack.empty()){
        if(Comparestate(Openstack.top()->State,State)){
            return 1;
        }
        Openstack.pop();
        // Tìm kiếm trạng thái trong ngăn xếp bằng cách sử dụng vòng lặp while
    }
    return 0;
}
int Goal(State State){
    for(int i=0;i<6;i++){
        if(State.Glass[i]==-1){
            return 0;
        }
        // Kiểm tra trạng thái hiện tại có phải là trạng thái kết thúc hay không
    }
    return 1;
}
void Upsidedown(State Current, State *Result, int Index){
    int i;
    for(i=0;i<6;i++){
        Result->Glass[i] = Current.Glass[i];
    }
    for(i = Index;i<=Index+2;i++){
        Result->Glass[i] *= -1;
    }
    // Đảo ngược các ly trong trạng thái hiện tại tại vị trí được chỉ định
}
void Printstate(State State){
    printf("State: ");
    for(int i=0;i<6;i++){
        printf("%2d ",State.Glass[i]);
    }
    printf("\n");
    // In trạng thái hiện tại ra màn hình console
}
Node *DFS(State S){
    stack<Node*> Open, Closed;
    Node *Root = (Node*)malloc(sizeof(Node));
    Root->State = S;
    Root->Dad = NULL;
    Root->Order = 0;
    Open.push(Root);
    // Khởi tạo ngăn xếp Open với nút gốc là Root
    while(!Open.empty()){
        Node *NODE = Open.top();
        Open.pop();
        Closed.push(NODE);
        // Lấy nút NODE ra khỏi ngăn xếp Open và đưa nó vào ngăn xếp Closed
        if(Goal(NODE->State)){
            return NODE;
            // Nếu NODE là trạng thái kết thúc, trả về NODE
        }
        for(int Index=0;Index<4;Index++){
            State Newstate;
            Makenullstate(&Newstate);
            Upsidedown(NODE->State,&Newstate,Index);
            if(Findstate(Newstate,Open)||Findstate(Newstate,Closed)){
                continue;
                // Kiểm tra xem Newstate đã nằm trong ngăn xếp Open hoặc Closed chưa. Nếu đúng, bỏ qua và tiếp tục với các Newstate khác
            }
            Node *Newnode = (Node*)malloc(sizeof(Node));
            Newnode->State = Newstate;
            Newnode->Dad = NODE;
            Newnode->Order = Index;
            Open.push(Newnode);
            // Tạo một nút mới tương ứng với Newstate, thêm nút mới này vào ngăn xếp Open
        }
    }
    return NULL;
}

void Print_TheWayToGetGoal(Node *N){
    stack<Node*> Stackprint; // Khai báo ngăn xếp để lưu các node trên đường đi
    while(N->Dad!=NULL){ // Duyệt qua các node cha của node đích
        Stackprint.push(N); // Thêm node cha vào ngăn xếp
        N = N->Dad; // Xét tiếp node cha
        // Thêm các nút vào ngăn xếp để in ra các bước cần thực hiện để đạt đến trạng thái kết thúc
    }
    Stackprint.push(N); // Thêm node đích vào ngăn xếp
    while(!Stackprint.empty()){ // Duyệt qua từng node trong ngăn xếp
        int Position = Stackprint.top()->Order+1; // Lấy vị trí cần đảo ngược các ly
        printf("Lật ngược các ly ở các vị trí: %d - %d - %d.\n",Position,Position+1,Position+2); // In ra bước cần thực hiện để tới trạng thái hiện tại
        Printstate(Stackprint.top()->State); // In ra trạng thái hiện tại
        Stackprint.pop(); // Xóa node khỏi ngăn xếp
    }
}
int main(int argc, char const *argv[]){
    State Current; // Khai báo biến Current để lưu trữ trạng thái hiện tại
    Makenullstate(&Current); // Thiết lập trạng thái ban đầu
    Node *P = DFS(Current); // Tìm kiếm đường đi từ trạng thái ban đầu đến trạng thái kết thúc
    Print_TheWayToGetGoal(P); // In ra các bước cần thực hiện để tới được trạng thái kết thúc
}