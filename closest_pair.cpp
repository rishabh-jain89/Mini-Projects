#include <bits/stdc++.h>
using namespace std;

void merge(vector<vector<int>>& points,int left,int mid,int right,int x){
    int n1=mid-left+1;
    int n2=right-mid;
    vector<vector<int>> L(n1),R(n2);
    for(int i=0;i<n1;i++){
        L[i].push_back(points[left+i][0]);
        L[i].push_back(points[left+i][1]);
    }
    for(int i=0;i<n2;i++){
        R[i].push_back(points[mid+i+1][0]);
        R[i].push_back(points[mid+i+1][1]);
    }
    int i=0,j=0,k=left;
    while(i<n1&&j<n2){
        if(L[i][x]<=R[j][x]){
            points[k][0]=L[i][0];
            points[k][1]=L[i][1];
            i++;
        }
        else{
            points[k][0]=R[j][0];
            points[k][1]=R[j][1];
            j++;
        }
        k++;
    }
    while(i<n1){
        points[k][0]=L[i][0];
        points[k][1]=L[i][1];
        i++;
        k++;
    }
    while(j<n2){
        points[k][0]=R[j][0];
        points[k][1]=R[j][1];
        j++;
        k++;
    }
}

void mergeSort(vector<vector<int>>& points,int left,int right,int x){
    if(left>=right){
        return ;
    }
    int mid=left+(right-left)/2;
    mergeSort(points,left,mid,x);
    mergeSort(points,mid+1,right,x);
    merge(points,left,mid,right,x);
}

double distance(vector<int> p1,vector<int> p2){
    return sqrt(pow(p2[0]-p1[0],2)+pow(p2[1]-p1[1],2));
}

double min(double x,double y){
    return x<y?x:y;
}

vector<vector<int>> partition(vector<vector<int>>& points,int left,int right,vector<vector<int>> y_points){
    if(right-left+1==2){
        vector<vector<int>> arr(2,vector<int>(2));
        arr[0]=points[left];
        arr[1]=points[left+1];
        return arr;
    }
    if(right-left+1==3){
        vector<vector<int>> arr(2,vector<int>(2));
        double d1,d2,d3;
        d1=distance(points[left],points[left+1]);
        d2=distance(points[left+1],points[left+2]);
        d3=distance(points[left],points[left+2]);
        double mi=min(d1,(min(d2,d3)));
        if(mi==d1){
            arr[0]=points[left];
            arr[1]=points[left+1];
        }
        else if (mi==d2){
            arr[0]=points[left+1];
            arr[1]=points[left+2];
        }
        else{
            arr[0]=points[left];
            arr[1]=points[left+2];
        }
        return arr;
    }
    int mid=left+(right-left)/2;
    vector<vector<int>> arrl(2,vector<int>(2));
    vector<vector<int>> arrr(2,vector<int>(2));
    arrl=partition(points,left,mid,y_points);
    arrr=partition(points,mid+1,right,y_points);
    double d_min=min(distance(arrl[0],arrl[1]),distance(arrr[0],arrr[1]));
    double line = points[points.size()/2][0];
    vector<vector<int>> result = (distance(arrl[0], arrl[1]) < distance(arrr[0], arrr[1])) ? arrl : arrr;
    vector<vector<int>> Strip_points;
    for(int i=0;i<points.size();i++){
        if(y_points[i][0]>=line-d_min&&y_points[i][0]<=line+d_min){
            Strip_points.push_back(y_points[i]);
        }
    }
    for(int i=0;i<Strip_points.size();i++){
        for(int j=i+1;j<Strip_points.size();j++){
            if(distance(points[i],points[j])<d_min){
                result[0]=Strip_points[i];
                result[1]=Strip_points[j];
            }
            else{
                break;
            }
        }
    }
    return result;
}

void print(vector<vector<int>> points){
    for(int i=0;i<points.size();i++){
        cout<<points[i][0]<<" "<<points[i][1]<<endl;
    }
}

int main(){
    int n;
    cout<<"Enter the no of elements:";
    cin>>n;
    vector<vector<int>> points(n);
    for(int i=0;i<n;i++){
        cout<<"Enter "<<i+1<<" point";
        int x,y;
        cin>>x>>y;
        points[i].push_back(x);
        points[i].push_back(y);
    }
    vector<vector<int>> x_points(n,vector<int>(2)),y_points(n,vector<int>(2));
    vector<vector<int>> arr(2,vector<int>(2));
    for(int i=0;i<n;i++){
        x_points[i]=points[i];
        y_points[i]=points[i];
    }

    mergeSort(x_points,0,n-1,0);
    mergeSort(y_points,0,n-1,1);
    arr=partition(x_points,0,n-1,y_points);
    print(arr);
    return 0;
}
