#include<iostream>
#include<bits/stdc++.h>

using namespace std;

// QS - 1 : Ninja’s Training - code studio

// memorisation - used by storing dp array - T.C : O(n*4) 

int f(int day,int last,vector<vector<int>> &points,vector<vector<int>> &dp) {
    if(day==0) {
        int maxi = 0;
        for(int task = 0; task<3; task++) {
            if(last!=task) {
                // 0 represents day
                maxi = max(maxi,points[0][task]);
            }
        }

        return maxi;
    }

    if(dp[day][last]!=-1) {
        return dp[day][last];
    }

    int maxi = 0;
    for(int task = 0; task<3; task++) {
        if(task!=last) {
            // here, f function goes to either day==0 if loop or dp[day][last]!=-1 if loop
            // according to that it gets executed.
            int point = points[day][task] + f(day-1,task,points,dp);
            maxi = max(maxi,point);
        }
    }

    return dp[day][last] = maxi;
}

int ninjaTraining(int n, vector<vector<int>> &points)
{
    vector<vector<int>> dp(n,vector<int> (4,-1));
    return f(n-1,3,points,dp);


    // space optimization 

    vector<vector<int>> dp(n,vector<int>(4,0));
    dp[0][0] = max(points[0][1],points[0][2]);
    dp[0][1] = max(points[0][0],points[0][2]);
    dp[0][2] = max(points[0][1],points[0][0]);
    dp[0][3] = max(points[0][0],max(points[0][1],points[0][2]));

    for(int day = 1; day<n; day++) {
        for(int last = 0; last<4; last++) {
            dp[day][last] = 0;
            for(int task = 0; task<3; task++) {
                if(task!=last) {
                    int point = points[day][task] + dp[day-1][task];
                    dp[day][last] = max(dp[day][last],point);
                }
            }
        }
    }

    return dp[n-1][3];

}

// problems on grids

// QS - 2 : Unique Paths in a grid from (0,0) to (m-1,n-1) - leetcode

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m+1,vector<int>(n+1,0) );

        // we are starting the traversal from bottom (m-1,n-1)
        // going towards (0,0)
        
        for(int i = 0; i<m; i++) {
            for(int j = 0; j<n; j++) {
                if(i==0 && j==0) {
                    dp[0][0] = 1;
                }

                else {
                    int left = 0;
                    int up = 0;

                    if(j>0) {
                        left = dp[i][j-1];
                    }

                    if(i>0) {
                        up = dp[i-1][j];
                    }

                    dp[i][j] = left + up;
                }
            }
        }

        return dp[m-1][n-1];
    }
};


// QS - 3 : Unique Paths in a grid from (0,0) to (m-1,n-1) 2 - leetcode
// some obstacle is present in a grid[i][j]

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();

        // edge case - when given i/p - [[anything]] return 0
        if(m==1 && n==1 && obstacleGrid[0][0] !=0) {
            return 0;
        }

        // edge case - when given i/p - [[0]] - return 1
        if(m==1 && n==1 && obstacleGrid[0][0] ==0) {
            return 1;
        }

        // we traverse from bottom (m-1,n-1) to (0,0)
        // we start counting paths from end
        vector<vector<int>> dp(m,vector<int>(n,0));

        for(int i = 0; i<m; i++) {
            for(int j = 0; j<n; j++) {
                if(i==0 && j==0) {
                    dp[0][0] = 1;
                }

                else {
                    int left = 0;
                    int up = 0;

                    // prsent grid should not be an obstacle
                    // up grid should not be an obstacle
                    if(i>0 && obstacleGrid[i][j]!=1 && obstacleGrid[i-1][j]!=1) {
                        up = dp[i-1][j];
                    }
                    
                    // prsent grid should not be an obstacle
                    // left grid should not be an obstacle
                    if(j>0 && obstacleGrid[i][j]!=1 && obstacleGrid[i][j-1]!=1) {
                        left = dp[i][j-1];
                    }

                        dp[i][j] = left + up;
                }
            }
        }

        return dp[m-1][n-1];
    }
};


// QS - 4 : Minimum path sum - leetcode
// from (0,0) to (m-1,n-1) in a (m*n) grid

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp(m+1,vector<int>(n+1,0));

        for(int i = 0; i<m; i++) {
            for(int j = 0; j<n; j++) {
                if(i==0 && j==0) {
                    dp[0][0] = grid[0][0];
                }

                else {
                    // if we assign 0 then 0 is minimum than grid[i][j]
                    //  When either i == 0 or j == oneof                valuesleft or up will remain 0, which incorrectly contributes to min(left, up).

// So for example, when i=0, up remains 0, and left is a valid sum. Then min(left, up) will wrongly select 0, which is not correct.


                    int left = INT_MAX;
                    int up = INT_MAX;
                    if(i>0) {
                        up = grid[i][j] + dp[i-1][j];
                    }

                    if(j>0) {
                        left = grid[i][j] + dp[i][j-1];
                    }

                    dp[i][j] = min(left,up);
                }
            }
        }

        return dp[m-1][n-1];
    }
};


// QS - 5 : Triangle - leetcode
// Given a triangle array, return the minimum path sum from top to bottom.
// For each step, you may move to an adjacent number of the row below. 
// More formally, if you are on index i on the current row, you may move to either index i or index i + 1 on the next row.


class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        vector<vector<int>> dp(n,vector<int>(n,-1));

        // base case
        for(int j = 0; j<n; j++) {
            dp[n-1][j] = triangle[n-1][j];
        }

        // doing it from bottom to top
        for(int i = n-2; i>=0; i--) {
            for(int j = i; j>=0; j--) {

                int d;
                int dg;

                // down of i th row and same col j
                d = triangle[i][j] + dp[i+1][j];

                // diagonal of ith row and j+1 col
                dg = triangle[i][j] + dp[i+1][j+1];

                dp[i][j] = min(d,dg);
            }
            
        }

        return dp[0][0];
    }
};


// QS - 6 : Minimum falling sum - Leetcode

// Given an n x n array of integers matrix, return the minimum sum of any falling path through matrix.
// A falling path starts at any element in the first row and chooses the element in the next row 
// that is either directly below or diagonally left/right. 
// Specifically, the next element from position (row, col) will be (row + 1, col - 1), (row + 1, col), or (row + 1, col + 1).

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        vector<vector<int>> dp(n,vector<int>(n,0)); 

        // last row dp vector is assigned with matrix[n-1][j] elements
        for(int j = 0; j<n; j++) {
            dp[n-1][j] = matrix[n-1][j];
        }

        // bottom up approach
        for(int i = n-2; i>=0; i--) {
            for(int j = n-1; j>=0; j--) {
                // same col 1 row above
                int d = matrix[i][j] + dp[i+1][j];
                // above row diagonally col+1
                int dg1 = INT_MAX;
                int dg2 = INT_MAX;
                if(j<n-1) {
                    dg1 = matrix[i][j] + dp[i+1][j+1];
                }
                
                // above row diagonally col-1
                if(j>0) {
                    dg2 = matrix[i][j] + dp[i+1][j-1];
                }

                dp[i][j] = min(d,min(dg1,dg2));
            }
        }

        // minimum sum which lies in the first row - that is the ans

        int mini = INT_MAX;
        for(int j = 0; j<n; j++) {
            mini = min(mini,dp[0][j]);
        }

        return mini;
    }
};

