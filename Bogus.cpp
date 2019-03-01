/*

vagitable , goat and nekre problem of machine learning.

*/

#include<bits/stdc++.h>

using namespace std;

bool visit[1<<5][1<<5][2];

bool look(int mask , int pos){
    if(mask & (1 << pos))return true;
    else return false;
}

bool currect(int mask){
    if(look(mask , 1) and look(mask , 2))return false;
    else if(look(mask , 1) and look(mask , 3))return false;
    else return true;
}

int get_Next(int mask , int pos){
    mask ^= (1 << pos);
    mask ^= (1);
    return mask;
}


string Pair(int j){
    if(j == 0)return "Man ";
    if(j == 1)return "Goat ";
    else if(j == 2)return "Vegitable ";
    else if(j == 3)return "Nekre ";
    else return "Nothing ";
}
vector< pair < pair < int , int > , string >  > ans;

/*
Represent Something here. I prefer Dynamic programming. <3 : Nice D p.
11111
0 for man
1 for goat
2 for vag
3 for nek
4 for bogus

Goat destroy with nekre
Vegitable destroy with Goat.

*/

bool solve(int mask1 , int mask2 , int nouka){
    if(mask2 == (1<<5)-1 and nouka == 1)return true;
    visit[mask1][mask2][nouka] = true;
    bool posi = false;
    if(nouka == 0){
        int newMask = 1;
        for(int i = 1; i<=4; i++){
            newMask = 1;
            if(mask1 & (1 << i)){
                newMask |= (1 << i);
                newMask |= (1 << 4);
                int Next = get_Next(mask1 , i);
                newMask |= mask2;
                if(currect(Next) == true and visit[Next][newMask][1] == false){
                    posi |= solve(Next , newMask , 1);
                    if(posi == true){
                        ans.push_back({{(Next) , (newMask)} , "L to R"});
                        return true;
                    }
                }
            }
        }
    }
    else{
        int newMask = 1;
        for(int i = 1; i<=4; i++){
            newMask = 1;
            if(mask2 & (1 << i)){
                newMask |= (1 << i);
                newMask |= (1 << 4);
                int Next = get_Next(mask2 , i);
                newMask |= mask1;
                if(currect(Next) == true and visit[newMask][Next][0] == false){
                    posi |= solve(newMask , Next , 0);
                    if(posi == true){
                        ans.push_back({{(newMask) , (Next)}, "R to L"});
                        return true;
                    }
                }
            }
        }
    }
    return posi;
}


int main()
{
    if(solve((1<<5)-1 , (1<<4) , 0)){
        cout << "YES\n\n";
        ans.push_back({{(1<<5)-1 , 0} , "Starting....."});
        reverse(ans.begin(),ans.end());
        for(auto v : ans){
            for(int i = 0; i<4; i++){
                if(v.first.first & (1 << i))cout << Pair(i);
            }

            if(v.second[0] == 'L')cout <<  "  (" << v.second << ") ---> " ;
            else cout <<  "  <---(" << v.second << ") " ;
            for(int i = 0; i<4; i++){
                if(v.first.second & (1 << i)){
                    cout << Pair(i);
                }
            }
            cout << endl << endl;
        }
    }
    else cout << "No Solution\n";
    return 0;
}
