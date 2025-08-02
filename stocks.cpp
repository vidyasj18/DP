#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// qs - 1 : best time to buy and sell stock 2

class Solution {
private:
    int f(vector<int> &prices,int ind,bool buy,int profit) {

        // recursive approach

        int n = prices.size();

        // base case
        if(ind==n) {
            return 0;
        }

        if(buy) {
            profit = max((-prices[ind]+f(prices,ind+1,0,profit)),
            (0+f(prices,ind+1,1,profit)));
        }

        else {
            profit = max((prices[ind] + f(prices,ind+1,1,profit)),
            (0+f(prices,ind+1,0,profit))); 
        }

        return profit;
    }

    int f(vector<int> &prices, int ind,int buy,int profit) {

        // memorisation

        int n = prices.size();
        vector<vector<int>> dp(n+1,vector<int>(2,-1));

        // base case
        if(ind==n) {
            return 0;
        }

        if(dp[ind][buy]!=-1) {
            return dp[ind][buy];
        }

        if(buy) {
            profit = max(-prices[ind]+f(prices,ind+1,0,profit),
            0+f(prices,ind+1,1,profit));
        }

        else {
            profit = max(prices[ind]+f(prices,ind+1,1,profit),
            0+f(prices,ind+1,0,profit));
        }

        return dp[ind][buy] = profit;
    }

public:
    int maxProfit(vector<int>& prices) {
        // recursive approach

        int ind = 0;
        bool buy = 1;
        int profit = 0;
        int ans = f(prices,ind,buy,profit);
        return ans;

        // memorisation approach

        int ind = 0; 
        bool buy = 1;
        int profit = 0;
        
        return f(prices,ind,buy,profit);

        // Tabulation

        int n = prices.size();
        vector<vector<int>> dp(n+1,vector<int>(2,0));

        // base case
        dp[n][0] = dp[n][1] = 0;
        int profit = 0;

        for(int ind = n-1; ind>=0; ind--) {
            for(int buy = 0; buy<=1; buy++) {
                // if buy is 1
                if(buy) {
                    profit = max(-prices[ind]+dp[ind+1][0],
                    0+dp[ind+1][1]);
                }

                else {
                    profit = max(prices[ind]+dp[ind+1][1],
                    0+dp[ind+1][0]);
                }

                dp[ind][buy] = profit;
            }

        }

        return dp[0][1];


        // space optimisation

        // ahead[0] = buy
        // ahead[1] = dont buy
        // curr[0] = saves bought 
        // curr[1] = saves sold

        vector<int> ahead(2,0),curr(2,0);
        ahead[0] = ahead[1] = 0;
        int profit = 0;
        int n = prices.size();

        for(int ind = n-1; ind>=0; ind--) {
            for(int buy = 0; buy<=1; buy++) {
                int profit = 0;

                // when buy is 1
                if(buy) {
                    profit = max(-prices[ind] + ahead[0],
                    0+ahead[1]);
                }

                else {
                    profit = max(prices[ind]+ahead[1],
                    0+ahead[0]);
                }

                curr[buy] = profit;
            }

            ahead = curr;
        }

        return ahead[1];
    }
};


// qs - 2 : best time to buy and sell stock 1

class Solution {
public:
    int maxProfit(vector<int>& prices) {

        // brute force approach
        long long ans = 0;

        for(long long i = 0; i<prices.size(); i++) {
            for(long long j = i+1; j<prices.size(); j++) {
                if(prices[j]-prices[i] > ans) {
                    ans = prices[j] - prices[i];
                }
            }
        }

        return ans;

        // optimised approach - using kadane's algo.

        int buy = prices[0];
        int profit = 0;

        // iterate from after the buy function. buy = 0 so start from 1.
        for(int i = 1; i<prices.size(); i++) {
            if(prices[i]<buy) {
                buy = prices[i];
            }

            else if(profit < prices[i] - buy) {
                profit = prices[i] - buy;
            }
        }

        // return profit;

        // another approach

        int maxProfit = 0;
        int mini = prices[0];
        int n = prices.size();

        for(int i = 0; i<n; i++) {
            int cost = prices[i];

            maxProfit = max(maxProfit,cost-mini);
            mini = min(mini,cost);
        }

        return maxProfit;
    }
};
