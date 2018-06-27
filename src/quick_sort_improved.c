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
        i++;
      }
      /* 帰納的にA[l-1] < pivot ,A[l] = pivotであるから
       * swap(A[l],A[i])を行った後はA[i] = povot となるから
       * i を 1 進めても良い
       */
      else if(A[i] > pivot){
        int z = A[i];
        A[i] = A[r];
        A[r] = z;
        r--;
      }
      // A[r] > pivot とは限らないので(特に初期値) i を1つ進めてはいけない
      else{
        i++;
      }
    }
  /* 作り方から k < l のとき A[k] < pivot
   * l<= k <= r のとき, A[k] = pivot, k > r のとき A[k] > pivot なので
   * A[0], A[1],...,A[l-1] と A[r+1], A[r+2],...,A[n-1] の 2箇所をソートし直す
   */
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
