#include <iostream>
#include <windows.h>
#include <locale.h>
#include <fstream>

using namespace std;

template<typename T>
class simple_array {
private:
    T* array;      
    int length;   
    
public:
    simple_array(int size) : length(size) {
        array = new T[length];
    }
    
    ~simple_array() {
        delete[] array;
    }
    
    T& operator[](int index) {
        return array[index];
    }

    void insertSort(long& comparisons, long& swaps) {
        T x;
        long i, j;
        
        comparisons = 0;
        swaps = 0;
        
        for (i = 0; i < length; i++) {
            x = array[i];
            
            for (j = i-1; j >= 0; j--) {
                comparisons++; 
                if (array[j] > x) {
                    array[j+1] = array[j];
                    swaps++;
                } else {
                    break;
                }
            }
            array[j+1] = x;
            if (j+1 != i) {
                swaps++; 
            }
        }
    }

    void print_array() {
        for (int i = 0; i < 10; i++) {
            cout << array[i] << endl;
        }
    }

    int increment(long inc[], long size) {
        int p1, p2, p3, s;

        p1 = p2 = p3 = 1;
        s = -1;
        do {
            if (++s % 2) {
                inc[s] = 8*p1 - 6*p2 + 1;
            } else {
                inc[s] = 9*p1 - 9*p3 + 1;
                p2 *= 2;
                p3 *= 2;
            }
            p1 *= 2;
        } while(3*inc[s] < size);  

        return s > 0 ? --s : 0;
    }

    void shellSort(long& comparisons, long& swaps) {
        long inc, i, j, seq[40];
        int s;

        comparisons = 0;
        swaps = 0;

        s = increment(seq, length);
        while (s >= 0) {
            inc = seq[s--];

            for (i = inc; i < length; i++) {
                T temp = array[i];
                
                for (j = i-inc; j >= 0; j -= inc) {
                    comparisons++; 
                    if (array[j] > temp) {
                        array[j+inc] = array[j];
                        swaps++; 
                    } else {
                        break;
                    }
                }
                
                array[j+inc] = temp;
                if (j+inc != i) {
                    swaps++; 
                }
            }
        }
    }
};