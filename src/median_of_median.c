#include <stdio.h>

// フェルマー素数
#define N ((1<<16)+1)

int A[N];

/*
A[0], A[1], ..., A[n-1] の中でk+1番目に小さい値を返す関数
ただし、Aの中身は書き換えてしまう。
*/

int find_index(int A[],int n ,int m){
  int i;
  for(i = 0; i < n;i++){
    if(A[i] == m){
      return i;
    }
  }
  return -1;
}


int quick_select(int A[], int n, int k){
  int i, j, pivot;
  if(n <= 5){
  // 先頭の要素をピボットとする
    pivot = A[0];
    for(i = j = 0; i < n; i++){
      if(A[i] <= pivot){
        int z = A[j];
        A[j] = A[i];
        A[i] = z;
        j++;
      }
    }
    if(j == k+1) return pivot;
    else if(j < k+1) return quick_select(A+j, n-j, k-j);
    else return quick_select(A+1, j-1, k);
  }
  else{
    // 5つごとに分けた中央値を集めた新しいリストを用意する
    int newLen = (n-1)/5;
    int newA[newLen];
    int h;
    for(h = 0; (5 * h)  < n;h++){
      int a = n - (5 * h);
      if(a < 5){
        newA[h] = quick_select(A+(5*h),a,a/2);
      }
      else{
        newA[h] = quick_select(A+(5*h),5,2);
      }
    }
    pivot = quick_select(newA,newLen+1,newLen/2);
  }
  int iP = find_index(A,n,pivot);
  A[iP] = A[0];
  A[0] = pivot;
  for(i = j = 0; i < n; i++){
    if(A[i] <= pivot){
      int z = A[j];
      A[j] = A[i];
      A[i] = z;
      j++;
    }
  }
  if(j == k+1) return pivot;
  else if(j < k+1) return quick_select(A+j, n-j, k-j);
  else return quick_select(A+1, j-1, k);
}


int main(){
  int i;
  A[0] = 0;
  A[1] = 3; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }
  for(i=0;i<N;i++){
    if(quick_select(A, N, i) != i) printf("ERROR %d %d\n", i, quick_select(A, N, i));
//    printf("%d th element is %d\n", i, quick_select(A, N, i));
  }
}
