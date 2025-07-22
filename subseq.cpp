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

// QS - 3 : count subsets with sum k

// recursion approach

int f(int ind,int sum,vector<int> &arr) {
	if(sum==0) return 1;
	if(ind==0) return arr[0]==sum;

	int notake = f(ind-1,sum,arr);
	int take = 0;
	if(arr[ind]<=sum) {
		take = f(ind-1,sum-arr[ind],arr);
	}

	return notake + take;
}

// better approach - memorisation

int f(int ind, int sum,vector<int> &arr,vector<vector<int>> &dp) {
	if(sum==0) return 1;

	if(ind==0) return arr[0]==sum;

	if(dp[ind][sum]!=-1) return dp[ind][sum];

	int notake = f(ind-1,sum,arr,dp);

	int take = 0;
	if(arr[ind]<=sum) {
		take = f(ind-1,sum-arr[ind],arr,dp);
	}

	return dp[ind][sum] = take + notake;
}

int findWays(vector<int>& arr, int k)
{
	// recursion 
	int n = arr.size();
	return f(n-1,k,arr);

	// better app - memorisation

	vector<vector<int>> dp(n,vector<int>(k+1,-1));
	return f(n-1,k,arr,dp);

	// optimised approach - tabulation

	int n = arr.size();
	vector<vector<int>> dp(n,vector<int>(k+1,0));

	for(int i = 0; i<n; i++) {
		dp[i][0] = 1;
	}

	if(arr[0]<=k) {
		dp[0][arr[0]] = 1;
	}

	for(int ind = 1; ind<n; ind++) {
		for(int sum = 0; sum<=k; sum++) {
			int notake = dp[ind-1][sum];
			int take = 0;

			if(arr[ind]<=sum) {
				take = dp[ind-1][sum-arr[ind]];
			}

			dp[ind][sum] = take + notake;
		}
	}

	return dp[n-1][k];
}


// QS - 4 : Assign Cookies - Leetcode
// greedily assign cookies

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(),g.end());
        int m = g.size();
        int n = s.size();
        sort(s.begin(),s.end());

        int cnt = 0;
        int i = 0;
        int j = 0;

        while(i<m && j<n) {
            if(s[j]>=g[i]) {
                cnt++;
                i++;
            }

            j++;
            
        }

        return cnt;
    }
};


// QS - 5 : minimum coins or change coin - Leetcode

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        // coins size(), target
        vector<vector<int>> dp(n,vector<int>(amount+1));

        // base case 
        // when the 0th index is divisible by the target
        // then no. of coins needed will be equal to coins[0]/target
        // assign the no. of coins needed in dp array

        for(int t = 0; t<=amount; t++) {
            if(t%coins[0]==0) {
                dp[0][t] = t/coins[0];
            }

            else {
                dp[0][t] = 1e9;
            }
        }

        // recursive relation

        for(int ind = 1; ind<n; ind++) {
            for(int tar = 0; tar<=amount; tar++) {
                // if we dont take, ind will get decreased
                int nottake = 0 + dp[ind-1][tar];
                int take = INT_MAX;
                
                if(tar>=coins[ind]) {
                    // if we take we will see, can we take
                    // the same coin thats why ind remains same
                    take = 1 + dp[ind][tar-coins[ind]];
                }

                // assign which is min in take and nottake
                dp[ind][tar] = min(nottake,take);
            }       
        }

        // ans lies in the last ind of dp table
        int ans = dp[n-1][amount];
        // if ans is INT_MAX or not defined then return -1
        if(ans>=1e9) {
            return -1;
        }

        // return ans if ans is defined
        return ans;
    }
};