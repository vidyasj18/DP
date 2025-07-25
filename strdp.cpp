#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// qs - 1 : Longest common subsequence
// 2 strings are given in that we need to find a longest subsequence
// return the length of the subsequence

class Solution {
// private:
    // int f(int ind1,int ind2,string text1,string text2,
    // vector<vector<int>> &dp) {

        // memorisation

    //     // base case
    //     if(ind1<0 || ind2<0) {
    //         return 0;
    //     }

    //     if(dp[ind1][ind2]!=-1) {
    //         return dp[ind1][ind2];
    //     }

    //     // match
    //     if(text1[ind1]==text2[ind2]) {
    //         return dp[ind1][ind2] = 1 + f(ind1-1,ind2-1,text1,text2,dp);
    //     }

    //     // not match
    //     return dp[ind1][ind2] = max(f(ind1-1,ind2,text1,text2,dp),
    //     f(ind1,ind2-1,text1,text2,dp));
    // }

public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size();
        int n = text2.size();

        vector<vector<int>> dp(m+1,vector<int>(n+1,0));
        // return f(m-1,n-1,text1,text2,dp);

        // tabulation 

        // base case
        for(int i = 0; i<=m; i++) {
            dp[i][0] = 0;
        }

        for(int j = 0; j<=n; j++) {
            dp[0][j] = 0;
        }

        for(int i = 1; i<=m; i++) {
            for(int j = 1; j<=n; j++) {
                if(text1[i-1]==text2[j-1]) {
                    dp[i][j] = 1 + dp[i-1][j-1];
                }

                else {
                    dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
                }
            }
        }

        return dp[m][n];

    }
};


// qs - 2 : print longest subsequence

string findLCS(int n, int m,string &s1, string &s2){
	vector<vector<int>> dp(n+1,vector<int>(m+1,0));
	for(int i = 0; i<n; i++) {
		for(int j = 0; j<m; j++) {
			dp[0][j] = 0;
			dp[i][0] = 0;
		}
	}	

	for(int i = 1; i<=n; i++) {
		for(int j = 1; j<=m; j++) {
			if(s1[i-1]==s2[j-1]) {
				dp[i][j] = 1 + dp[i-1][j-1];
			}

			else {
				dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
			}
		}
	}

    // len is the length of longest subsequence
	int len = dp[n][m];
    
    // push ans by random thing before
	string ans = "";
	for(int i = 0; i<len; i++) {
		ans += "&";
	}

    // compare from the ends of both the strings and push it inside the ans string from behind
	int ind = len-1;
	int i = n;
	int j = m;
	while(i>0 && j>0) {
		if(s1[i-1]==s2[j-1]) {
			ans[ind] = s1[i-1];
			ind--;
			i--;
			j--;
		}

		else if(dp[i][j-1]>dp[i-1][j]) {
			j--;
		}

		else {
			i--;
		}
	}

	return ans;
}