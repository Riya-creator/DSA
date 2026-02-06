//Optimized  bubble sort
#include <iostream>
using namespace std;
void bubsort(int * a){
int flag=0;
    for( int i=0; i<7; i++){
        flag= 0;
        for( int j=0; j<6-i;j++){
            if(a[j]> a[j+1]){
                flag=1;
                int temp= a[j];
                a[j]= a[j+1];
                a[j+1]= temp;
            }
        }
            if( flag== 0)
                break;
    }
}
void show(int *a){
    cout<<"Array is :\n";
    for( int i=0; i< 7; i++){
        cout<<a[i]<<", ";
    }
}
int main()
{
    int a[7]={64, 34, 25, 12, 22, 11, 90};
    bubsort(a);
    show(a);
}
