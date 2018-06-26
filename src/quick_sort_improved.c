#include <stdio.h>

//フェルマー素数
#define N ((1<<16)+1)

int A[N];

/*
A[0], A[1], ..., A[n-1] をソートして昇順に書き換える関数
*/
void quick_sort(int A[], int n){
  if(n <= 1){
    return;
  }
  else{
    int l, r, i,pivot;
    pivot = A[0];
    l = 0;
    r = n-1;
    i = 1;
    while(i <= r){
      if(A[i] < pivot){
        int z = A[i];
        A[i] = A[l];
        A[l] = z;
        l++;
      }
      else if(A[i] > pivot){
        int z = A[i];
        A[i] = A[r];
        A[r] = z;
        r--;
      }
      else{
        i++;
      }
    }
  quick_sort(A,l);
  quick_sort(A+r+1,n-r-1);
  return;
  }
}

int main(){
  int i;
  A[0] = 0;
  A[1] = 3; //原始元
  for(i=2;i<N;i++){
    A[i] = (long long int) A[i-1] * A[1] % N;
  }

// すべての要素が同じ場合でも計算が早く終わるか確認する

  quick_sort(A, N);
  for(i=0;i<N;i++){
    if(A[i] != i) printf("ERROR %dth element is %d\n", i, A[i]);
  }
}
