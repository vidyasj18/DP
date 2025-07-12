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


// QS - 2 : partition equal sum - leetcode
// Given an integer array nums, return true if you can
// partition the array into two subsets such that the sum of the 
// elements in both subsets is equal or false otherwise.

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        
        // calculate the sum of nums array
        int sum = 0;
        for(int i = 0; i<n; i++) {
            sum += nums[i];
        }

        // if sum is odd then return false cz sum cant be divided into half
        if(sum%2!=0) {
            return false;
        }

        vector<vector<int>> dp(n,vector<int>(sum/2 + 1,0));

        for(int i = 0; i<n; i++) {
            dp[i][0] = true;
        }

        if(nums[0]==sum/2) {
            dp[0][nums[0]] = true;
        }

        // find subsequence for for sum/2 and other elements in nums 
        // are automatically form sum of sum/2
        for(int ind = 1; ind<n; ind++) {
            for(int target = 1; target<=sum/2; target++) {
                bool nottake = dp[ind-1][target];
                bool take = false;

                if(nums[ind]<=target) {
                    take = dp[ind-1][target-nums[ind]];
                }

                dp[ind][target] = take | nottake;
            }
        }

        return dp[n-1][sum/2];
    }
};