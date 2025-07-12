#include<iostream>
#include<bits/stdc++.h>

using namespace std;

// QS - 1 : Subset Sum Equal To K - codestudio
// return true if any pair exists and false if not

bool subsetSumToK(int n, int k, vector<int> &arr) {
    vector<vector<int>> dp(n,vector<int>(k+1,0));

    for(int i = 0; i<n; i++) {
        dp[i][0] = true;
    }

    if(arr[0]==k) {
        dp[0][arr[0]] = true;
    }

    for(int ind = 1; ind<n; ind++) {
        for(int target = 1; target<=k; target++) {
            bool notTake = dp[ind-1][target];
            bool take = false;
            if(arr[ind]<=target) {
                take = dp[ind-1][target - arr[ind]];
            }

            dp[ind][target] = take | notTake;
        }
    }

    return dp[n-1][k];


}