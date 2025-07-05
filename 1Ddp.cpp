#include<iostream>
#include<bits/stdc++.h>

using namespace std;

#include <bits/stdc++.h> 

// QS - 1: Frog Jump +1/+2 steps - code studio

// recursion approach

int f(int ind, vector<int> &heights, vector<int> &dp) {
    if(ind==0) {
        return 0;
    }

    if(dp[ind]!=-1) {
        return dp[ind];
    }

    int left = f(ind-1,heights,dp) + abs(heights[ind-1] - heights[ind]);
    int right = INT_MAX;
    if(ind>1) {
        right = f(ind-2,heights,dp) + abs(heights[ind-2] - heights[ind]);
    }

    return dp[ind] = min(left,right);
}

int frogJump(int n, vector<int> &heights)
{
    vector<int> dp(n,0);
    return f(n-1,heights,dp);

    // tabulation approach

    dp[0] = 0;
    for(int i = 1; i<n; i++) {
        int fs = dp[i-1] + abs(heights[i-1] - heights[i]);
        int ss = INT_MAX;
        if(i>1) {
            ss = dp[i-2] + abs(heights[i-2] - heights[i]);
        }

        dp[i] = min(fs,ss);
    }

    return dp[n-1];

    // space optimization

    int prev = 0;
    int prev2 = 0;

    for(int i = 1; i<n; i++) {
        int fs = prev + abs(heights[i] - heights[i-1]);

        int ss = INT_MAX;
        if(i>1) {
            ss = prev2 + abs(heights[i] - heights[i-2]);
        }

        int curr = min(fs,ss);
        prev2 = prev;
        prev = curr;
    }

    return prev;
}


//  QS - 2 : Frog Jump - k steps

class Solution {
public:
    int frogJump(vector<int>& heights, int k) {
        int n = heights.size();
        vector<int> dp(n,INT_MAX);
        dp[0] = 0;

        for(int i = 1; i<n; i++) {
            for(int j = 1; j<k+1; j++) {
                if(i-j>=0) {
                    dp[i] = min(dp[i],dp[i-j] + abs(heights[i]-heights[i-j]));
                }
            }
        }
        
        return dp[n-1];
    }
};
