//BFS and DFS using openMP

#include <iostream>
#include <queue>
#include <stack>
#include <thread>

using namespace std;

const int MAX_VERTICES = 5;

// Perform parallel Breadth-First Search
void parallelBFS(int graph[MAX_VERTICES][MAX_VERTICES], int source) {
    bool visited[MAX_VERTICES] = {false};
    visited[source] = true;

    queue<int> bfsQueue;
    bfsQueue.push(source);

    while (!bfsQueue.empty()) {
        int current = bfsQueue.front();
        bfsQueue.pop();

        cout << "Visiting vertex: " << current << endl;

        vector<thread> threads;

        for (int i = 0; i < MAX_VERTICES; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                visited[i] = true;
                bfsQueue.push(i);

                threads.emplace_back([&]() {
                    cout << "Visiting vertex: " << i << endl;
                });
            }
        }

        for (auto& thread : threads) {
            thread.join();
        }
    }
}

// Perform parallel Depth-First Search
void parallelDFS(int graph[MAX_VERTICES][MAX_VERTICES], int source) {
    bool visited[MAX_VERTICES] = {false};
    visited[source] = true;

    stack<int> dfsStack;
    dfsStack.push(source);

    while (!dfsStack.empty()) {
        int current = dfsStack.top();
        dfsStack.pop();

        cout << "Visiting vertex: " << current << endl;

        vector<thread> threads;

        for (int i = 0; i < MAX_VERTICES; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                visited[i] = true;
                dfsStack.push(i);

                threads.emplace_back([&]() {
                    parallelDFS(graph, i);
                });
            }
        }

        for (auto& thread : threads) {
            thread.join();
        }
    }
}

int main() {
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 1},
        {1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0}
    };

    cout << "Parallel BFS traversal:" << endl;
    parallelBFS(graph, 0);

    cout << "\nParallel DFS traversal:" << endl;
    parallelDFS(graph, 0);

    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////
// merge sort – 1           
#include<iostream> #include<stdlib.h>
#include<omp.h>  using namespace std;
void mergesort(int a[],int i,int j);
void merge(int a[],int i1,int j1,int i2,int j2);
void mergesort(int a[],int i,int j){
	int mid;
	if(i<j){
    	mid=(i+j)/2;
    	#pragma omp parallel sections {
	#pragma omp section {
            	mergesort(a,i,mid);  }
        // Merge Sort -2        	
#pragma omp section  {
            	mergesort(a,mid+1,j);    
       }}
    	merge(a,i,mid,mid+1,j);   } }
 
void merge(int a[],int i1,int j1,int i2,int j2){
	int temp[1000];    
	int i,j,k;
	i=i1;    
	j=i2;    
	k=0;
	while(i<=j1 && j<=j2)    {
    	if(a[i]<a[j])   {
        	temp[k++]=a[i++];  }
    	else  {
        	temp[k++]=a[j++];  } }
    while(i<=j1)    {
    	temp[k++]=a[i++];   }
	while(j<=j2)    {
    	temp[k++]=a[j++];    }
	for(i=i1,j=0;i<=j2;i++,j++)  {
    	a[i]=temp[j];  }    }
int main(){
	int *a,n,i;
	cout<<"\n enter total no of elements=>";
	cin>>n;
	a= new int[n];
	cout<<"\n enter elements=>";
	for(i=0;i<n;i++) {
    	cin>>a[i];  }
   //	 start=.......
//#pragma omp…..
	mergesort(a, 0, n-1);
//          stop…….
	cout<<"\n sorted array is=>";
	for(i=0;i<n;i++)  {
    	cout<<"\n"<<a[i];  }
  	// Cout<<Stop-Start
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////

// MIN_MAX
#include <iostream> #include <omp.h>
#include <climits>
using namespace std;
void min_reduction(int arr[], int n) {
  int min_value = INT_MAX;
  #pragma omp parallel for reduction(min: min_value)
  for (int i = 0; i < n; i++) {
	if (arr[i] < min_value) {
  	min_value = arr[i];  } } 
cout << "Minimum value: " << min_value << endl; }
void max_reduction(int arr[], int n) {
  int max_value = INT_MIN;
  #pragma omp parallel for reduction(max: max_value)
  for (int i = 0; i < n; i++) {
	if (arr[i] > max_value) {
  	max_value = arr[i]; 	}   }
cout << "Maximum value: " << max_value << endl; }
void sum_reduction(int arr[], int n) {
  int sum = 0;
   #pragma omp parallel for reduction(+: sum)
   for (int i = 0; i < n; i++) {
	sum += arr[i] ;  }
  cout << "Sum: " << sum << endl; }
void average_reduction(int arr[], int n) {
  int sum = 0;
  #pragma omp parallel for reduction(+: sum)
  for (int i = 0; i < n; i++) {
	sum += arr[i];  } 
cout << "Average: " << (double)sum / (n-1) << endl;    }
int main() {
    int *arr,n;
    cout<<"\n enter total no of elements=>";
    cin>>n;   arr=new int[n];
    cout<<"\n enter elements=>";
    for(int i=0;i<n;i++) { cin>>arr[i];  }
  min_reduction(arr, n);
  max_reduction(arr, n);
  sum_reduction(arr, n);
  average_reduction(arr, n);   }
  
  ////////////////////////////////////////////////////////////////////////////////////////////
// Parallel Bubble Sort
#include<iostream>
#include<stdlib.h>
#include<omp.h>
using namespace std;
void bubble(int *, int);
void swap(int &, int &);
void bubble(int *a, int n) {
    for(  int i = 0;  i < n;  i++ ) {  	 
   	 int first = i % 2; 	 
   	 #pragma omp parallel for shared(a,first)
   	 for(  int j = first;  j < n-1;  j += 2  ){  	  if(  a[ j ]  >  a[ j+1 ]  ) { 
          swap(  a[ j ],  a[ j+1 ]  );   }  	 
   		   }  	  }  }
void swap(int &a, int &b)
{
    int test;  test=a;
    a=b;
    b=test;
}
int main() {
    int *a,n;
    cout<<"\n enter total no of elements=>";
    cin>>n;
    a=new int[n];
    cout<<"\n enter elements=>";
    for(int i=0;i<n;i++)
    {
   	 cin>>a[i];
    }
    bubble(a,n);
    cout<<"\n sorted array is=>";
    for(int i=0;i<n;i++)
    {
   	 cout<<a[i]<<endl;
    }
return 0;
}
