#include<bits/stdc++.h>

using namespace std;

int n , m;
bool visit[50][50][50][50][2];
#define cap 2

struct Node{
    int x , y , x1 , y1;
    char ch;
    Node(){}
    Node(int _x , int _y , int _x1 , int _y1 , char _ch){
        x = _x ; y = _y; x1 = _x1; y1 = _y1; ch = _ch;
    }
};

vector < Node > ans;

bool solve(int nl , int ml , int nouka , int nr , int mr){
    if(nr == n and mr == m){
        return true;
    }
    visit[nl][ml][nr][mr][nouka] = true;
    bool pos = false;
    if(nouka == 0){
        for(int i = 0; i<=cap; i++){
            for(int j = 0; j<=cap; j++){
                if( (i + j) <= cap and nl >= i and ml >= j and (i+j) > 0){
                    int tn = nl - i;
                    int tm = ml - j;
                    if( ( tn >= tm || tn == 0 ) and ( (nr + i) >= (mr + j) || (nr + i) == 0) and visit[tn][tm][nr+i][mr+j][1] == false){
                        pos |= solve(tn , tm , 1 , nr + i , mr + j);
                        if(pos == true){
                            ans.push_back(Node(tn, tm , nr + i , mr + j , 'R'));
                            return true;
                        }
                    }
                }
            }
        }
    }
    else{
        for(int i = 0; i<=cap; i++){
            for(int j = 0; j<=cap; j++){
                if((i + j) <= cap and nr >= i and mr >= j){
                    int tn = nr - i;
                    int tm = mr - j;
                    if(( tn >= tm || tn == 0) and ( (nl + i) >= (ml + j) || (nl + i) == 0 ) and (i+j) > 0 and visit[nl+i][ml+j][tn][tm][0] == false){
                        pos |= solve(nl + i , ml + j , 0 , tn , tm);
                        if(pos == true){
                            ans.push_back(Node(nl+i, ml+j , tn , tm , 'L'));
                            return true;
                        }
                    }
                }
            }
        }
    }
    return pos;
}


int main()
{
    cin >> n >> m;
    if(solve(n,m,0,0,0)){
        ans.push_back(Node(n,m,0,0,'L'));
        reverse(ans.begin(),ans.end());
        cout << "Yes\n";
        for(auto v : ans){
            cout << v.x << " " << v.y << " " << v.x1 << " " << v.y1 << " " << v.ch << endl;
        }
    }
    else cout << "No\n";
    return 0;
}
