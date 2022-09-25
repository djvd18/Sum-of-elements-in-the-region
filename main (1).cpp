#include <bits/stdc++.h>
using namespace std;

bool cmp(pair<int, int>&a, pair<int, int>&b){
 
    if (a.first == b.first)
        return a.second < b.second;
    return a.first < b.first;
}

int cw(pair<int, int>&a, pair<int, int>&b, pair<int, int>&c){
 
    int p = a.first * (b.second - c.second)
            + b.first * (c.second - a.second)
            + c.first * (a.second - b.second);
 
    return p < 0ll;
}

int ccw(pair<int, int>& a,pair<int, int>& b,pair<int, int>& c){
 
    int p = a.first * (b.second - c.second)+ b.first * (c.second - a.second)+ c.first * (a.second - b.second);
    return p > 0ll;
}
 
vector<pair<int, int> > convexHull(vector<pair<int, int> >& v){
    sort(v.begin(),v.end(), cmp);
 
    int n = v.size();
    if (n <= 3)
        return v;
    pair<int, int> p1 = v[0];
    pair<int, int> p2 = v[n - 1];
    vector<pair<int, int> > up, down;
    up.push_back(p1);
    down.push_back(p1);
    for (int i = 1; i < n; i++) {
 
        if (i == n - 1 || !ccw(p1, v[i], p2)) {
 
            while (up.size() > 1&& ccw(up[up.size() - 2],up[up.size() - 1],v[i])) {
                up.pop_back();
            }
            up.push_back(v[i]);
        }
 
        if (i == n - 1 || !cw(p1, v[i], p2)) {
 
            while (down.size() > 1&& cw(down[down.size() - 2],down[down.size() - 1],v[i])) {
                down.pop_back();
            }
            down.push_back(v[i]);
        }
    }
 
    for (int i = down.size() - 2;i > 0; i--){
        up.push_back(down[i]);
    }

    up.resize(unique(up.begin(),up.end())- up.begin());
 
    return up;
}

//This function is for finding which query points are inside the given points
bool isInside(vector<pair<int, int> > points,pair<int, int> query){

    points.push_back(query);

    points = convexHull(points);

    for (auto x : points) {

        if (x == query)
            return false;
    }
    return true;
}
 
// Driver Code
int main()
{
  //Generation of 25x25 2d matrix consisting of randomly generated elements
  int matrix[25][25];
  for(int i=0;i<25;i++){
    for(int j=0;j<25;j++){
        matrix[i][j]=rand()%5;
    }
  }
    
    int n = 5;
    vector<pair<int, int> > points;
    points = { { 1, 1 }, { 4, 18}, { 10, 9 },
               { 15, 3 }, { 25, 15 }};
 
    // Query Points are the points of our interest 
    //We need to find the sum of elements in between the polygon formed by this points
   int sum=0;
   for(int i=0;i<25;i++){
    for(int j=0;j<25;j++){
         pair<int, int> query = { i, j };
    if (isInside(points, query)) {
        sum+=matrix[i][j];
     }
    }
  }
  cout<<"The sum of the elements in the convex hull is: ";
  cout<<sum<<endl;
    return 0;
}
