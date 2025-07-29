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


// qs - 3 : Longest palindromic subsequence
// 1 string s is given in the question

class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.length();
        vector<vector<int>> dp(n+1,vector<int>(n+1,0));
        // create a new string s1 and store the reverse of s into it
        string s1 = s;
        reverse(s1.begin(),s1.end());
        
        // rest is same as longest common subsequence problem qs
        // base case
        for(int i = 0; i<n; i++) {
            dp[i][0] = 0;
            dp[0][i] = 0;
        } 

        for(int ind1 = 1; ind1<=n; ind1++) {
            for(int ind2 = 1; ind2<=n; ind2++) {
                if(s[ind1-1]==s1[ind2-1]) {
                    dp[ind1][ind2] = 1 + dp[ind1-1][ind2-1];
                }

                else {
                    dp[ind1][ind2] = max(dp[ind1-1][ind2],dp[ind1][ind2-1]);
                }
            }
        }

        return dp[n][n];
    }
};


// qs - 4 : delete operation for 2 strings

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        
        vector<vector<int>> dp(m+1,(vector<int>(n+1,0)));

        // base case
        for(int i = 0; i<m; i++) {
            dp[i][0] = 0;
        }

        for(int i = 0; i<n; i++) {
            dp[0][i] = 0;
        }

        int ans = 0;

        for(int ind1 = 1; ind1<=m; ind1++) {
            for(int ind2 = 1; ind2<=n; ind2++) {
                if(word1[ind1-1]==word2[ind2-1]) {
                    dp[ind1][ind2] = 1 + dp[ind1-1][ind2-1];
                }

                else {
                    dp[ind1][ind2] = max(dp[ind1-1][ind2],dp[ind1][ind2-1]);
                }
            }
        }

        ans = dp[m][n];
        // no. of elements which are not similar in both the words 
        int ans1 = m - ans + n - ans;
        return ans1;
    }
};


// qs - 6 : shortest common supersequence
// Input: str1 = "abac", str2 = "cab"     Output: "cabac"

class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        int m = str1.size();
        int n = str2.size();
        vector<vector<int>> dp(m+1,vector<int>(n+1,0));

        for(int i = 0; i<=m; i++)  {
            dp[i][0] = 0;
        }

        for(int i = 0; i<=n; i++) {
            dp[0][i] = 0;
        }

        for(int ind1 = 1; ind1<=m; ind1++) {
            for(int ind2 = 1; ind2<=n; ind2++) {
                if(str1[ind1-1]==str2[ind2-1]) {
                    dp[ind1][ind2] = 1 + dp[ind1-1][ind2-1];
                }

                else {
                    dp[ind1][ind2] = max(dp[ind1-1][ind2],dp[ind1][ind2-1]);
                }
            }
        }
        
        string temp = "";

        int i = m; 
        int j = n;
        while(i>0 && j>0) {
            if(str1[i-1]==str2[j-1]) {
                temp += str1[i-1];
                i--;
                j--;
            }

            else if(dp[i-1][j]>dp[i][j-1]) {
                temp += str1[i-1];
                i--;
            }

            else {
                temp += str2[j-1];
                j--;
            }
        }

        // if j becomes lesser than or equal to 0
        // push remaining str1 elements inside res
        while(i>0) {
            temp += str1[i-1];
            i--;
        }

        // if i becomes lesser than or equal to 0
        // push remaining str2 elements inside res
        while(j>0) {
            temp += str2[j-1];
            j--;
        }
        
        // reverse the string as we built backwards
        reverse(temp.begin(),temp.end());
        return temp;

    }
};


// qs - 7 : Edit distance
// word1 should be made similar to word2 by inserting,deleting or replacing
// in how many counts of these insert,delete,replace are required return those many counts

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();

        if(m==0 && n!=0) {
            return n;
        } 

        vector<vector<int>> dp(m+1,vector<int>(n+1,0));

        // base case
        for(int i = 0; i<=m; i++) {
            dp[i][0] = i;
        }

        for(int j = 0; j<=n; j++) {
            dp[0][j] = j;
        }

        for(int i = 1; i<=m; i++) {
            for(int j = 1; j<=n; j++) {
                if(word1[i-1]==word2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                }

                else {
                    dp[i][j] = 1 + min(
                    {dp[i-1][j], // delete
                    dp[i][j-1], // insert
                    dp[i-1][j-1]}); // replace
                }
            }
        }

        return dp[m][n];
    }
};


// qs - 8 : Minimum inseertion steps to make a string palindrome - Leetcode
// ans : total length of the string - length of the longest palindromic sequence
// create a new string same as given string and reverse that string and compare both the strings from 
// indexes behind and calculate the length of the longest palindromic subsequence

class Solution {
public:
    int minInsertions(string s) {
        int n = s.size();
        
        // create string s1 and reverse it
        // so that it is easier to compare from the last indexes
        string s1 = s;
        reverse(s1.begin(),s1.end());

        // dp array
        vector<vector<int>> dp(n+1,vector<int>(n+1,0));

        // find the length of the longest palindromic sequence 
        // given in the s string
        // base case
        for(int i = 0; i<n; i++) {
            dp[i][0] = 0;
            dp[0][i] = 0;
        }

        for(int i = 1; i<=n; i++) {
            for(int j = 1; j<=n; j++) {
                if(s[i-1]==s1[j-1]) {
                    dp[i][j] = 1 + dp[i-1][j-1];
                }

                else {
                    dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
                }
            }
        }

        return n-dp[n][n];
    }
};