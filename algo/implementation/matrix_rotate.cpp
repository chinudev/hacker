#include <iostream>
#include <assert.h>
#include <vector>
#include <stdio.h>

using namespace std;

class RotateCounter
{
public:
        RotateCounter(int arrayRows_, int arrayCols_, 
                      int subRows_, int subCols_) 
                : arrayRows(arrayRows_),
                  arrayCols(arrayCols_),
                  subRows(subRows_),
                  subCols(subCols_)
        {
                // compute startRow,startCol assuming sub-array is in middle
                assert(((arrayRows - subRows) % 2) == 0); 
                startRow = (arrayRows - subRows) / 2;
                endRow = startRow+subRows-1;

                assert(((arrayCols - subCols) % 2) == 0); 
                startCol = (arrayCols - subCols) / 2;
                endCol = startCol+subCols-1;

                // Start with top-left 
                Row = startRow;
                Col = startCol;
                NumElements = (2*subRows + 2*subCols - 4);
        }

        // move Row,Col anti-clockwise by one step 
        void advance()
        {
                if (Col == startCol) {
                        if (Row < endRow) Row++;
                        else Col++; 
                } else if (Col == endCol) {
                        if (Row > startRow) Row--;
                        else Col--; 
                } else {
                        if (Row == startRow) Col--;
                        else if (Row == endRow) Col++;
                        else assert(false);
                }
        }

        void advance(int numSteps)
        {
                numSteps = numSteps % NumElements;
                cout << "advancing " << numSteps << endl;
                for (int i=0;i<numSteps;i++) {
                        advance();
                }
        }


        int Row;
        int Col;
        int NumElements;

private:
        int arrayRows;
        int arrayCols; 
        int subRows; 
        int subCols; 

        // left-top element of sub-array is at this index
        int startRow;
        int startCol;
        int endRow;
        int endCol;

};


void testCounter() 
{
        RotateCounter count(6,4,4,2);
        cout << "start : " << count.Row << " " << count.Col << endl;
        for (int i=0;i<10;i++) { 
                count.advance();
                cout << " " << count.Row << " " << count.Col << endl;
        }

        RotateCounter count2(6,4,4,2);
        count2.advance(10);
        cout << "advance 10 " << count2.Row << " " << count2.Col << endl;
}

void rotateMatrix(vector< vector<long> > &inArray,     // Input array
                  vector< vector<long> > &outArray,    // copy rotate array to out Array
                  long numSteps)                      // number of rotate steps
{
        long numRows = inArray.size();
        long numCols = inArray[0].size();

        long subRows = numRows;
        long subCols = numCols;

        while (subRows > 1 && subCols > 1) {
                RotateCounter src(numRows, numCols, subRows, subCols);
                RotateCounter dest(numRows, numCols, subRows, subCols);
                dest.advance(numSteps);

                for (int elem=0; elem < src.NumElements; elem++) {
                        outArray[dest.Row][dest.Col] = inArray[src.Row][src.Col];
                        src.advance();
                        dest.advance();
                }

                subRows -= 2;
                subCols -= 2;
        }
       

}

void printMatrix(vector <vector<long> > array) 
{
        for (int i=0; i < array.size() ;i++) {
                for (int j=0; j < array[i].size(); j++) {
                        //printf("%3ld ", array[i][j]);
                        printf("%ld ", array[i][j]);
                }
                printf("\n");
        }

}

int main()
{
        long rows, cols, steps;

        cin >> rows >> cols >> steps;

        vector< vector<long>> inArray(rows, vector<long>(cols,0));
        vector< vector<long>> outArray(rows, vector<long>(cols,0));

        for (int i=0; i<rows;i++) {
                for (int j=0; j<cols; j++) {
                        cin >> inArray[i][j];
                }
        }


        //printMatrix(inArray);
        rotateMatrix(inArray, outArray, 7);
        printMatrix(outArray);

}

