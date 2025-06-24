#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// fibonacci series - returning a fib(n) - given n.

// using recursion
int f(int n,vector<int> &dp) {
    if(n<=1) return n;

    if(dp[n] != -1) return dp[n];

    return dp[n] = f(n-1,dp) + f(n-2,dp);
}

int main() {
    int n;
    cin >> n;

    // recursion
    // T.C : O(N) S.C : O(N) + O(N) --> RECURSION + ARRAY USED
    vector<int> dp(n+1,-1);
    cout << f(n,dp);

    // using prev or prev1 pointers
    // T.C : O(N) S.C : O(1)
    int prev2 = 0;
    int prev = 1;

    for(int i = 2; i<=n; i++) {
        int curr = prev + prev2;
        prev2 = prev;
        prev = curr;
    }

    cout << prev;
    return 0;
}