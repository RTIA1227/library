#include<vector>

class SquareMatrix{
    size_t size;
    std::vector<std::vector<long long int>> matrix;
    long long int identifyElement;
    long long int zeroElement;
    unsigned long long int moduloValue;
    long long int determinant;
    bool isCalculatedDet;

    long long int cofactorExpansion(size_t subMatrixSize,std::vector<std::vector<long long int>> subMatrix){
        if(subMatrixSize == 2){
            return subMatrix[0][0] * subMatrix[1][1] - subMatrix[0][1] * subMatrix[1][0];
        }else if(subMatrixSize == 1){
            return subMatrix[0][0];
        }else{
            long long int subDeterminant = 0;
            for(int i = 0; i < subMatrixSize; i++){
                std::vector<std::vector<long long int>> nextSubMatrix(subMatrixSize - 1,std::vector<long long int>(subMatrixSize - 1));
                for(int j = 1; j < subMatrixSize; j++){
                    for(int k = 0; k < subMatrixSize; k++){
                        if(k == i){
                            continue;
                        }
                        if(k < i){
                            nextSubMatrix[j-1][k] = subMatrix[j][k];
                        }else{
                            nextSubMatrix[j-1][k-1] = subMatrix[j][k];
                        }
                    }
                }
                long long int sig = 1;
                if(i % 2 != 0){
                    sig = -1;
                }
                subDeterminant += sig * subMatrix[0][i] * cofactorExpansion(subMatrixSize - 1,nextSubMatrix);
            }
            return subDeterminant;
        }
    }

    // Unimplemented;
    long long int calculateDeterminant(){
        isCalculatedDet = true;
        return cofactorExpansion(size,matrix);
    }

public:
    SquareMatrix(int n,long long int initialIdentify = 1,long long int initialZero = 0,unsigned long long int initialMod = (1LL << 63)):size((size_t)n),identifyElement(initialIdentify),zeroElement(initialZero),moduloValue(initialMod){
        matrix = std::vector<std::vector<long long int>>(size,std::vector<long long int>(size,zeroElement));
        isCalculatedDet = false;
    }

    void initializeIdentifyMatrix(){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                matrix[i][j] = (i == j ? identifyElement : zeroElement);
            }
        }
    }

    long long int getDeterminant(){
        if(isCalculatedDet){
            return determinant;
        }else{
            return calculateDeterminant();
        }
    }

    void setValue(long long int value,int i,int j){
        matrix[i][j] = value;
        isCalculatedDet = false;
    }

    const SquareMatrix operator +(const SquareMatrix &right)const{
        SquareMatrix returnValue(size,identifyElement,zeroElement,moduloValue);
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                returnValue.matrix[i][j] = this->matrix[i][j] + right.matrix[i][j];
                returnValue.matrix[i][j] %= moduloValue;
            }
        }
        return returnValue;
    }

    const SquareMatrix operator *(const SquareMatrix &right)const{
        SquareMatrix returnValue(size,identifyElement,zeroElement,moduloValue);
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                for(int k = 0; k < size; k++){
                    returnValue.matrix[i][j] += (this->matrix[i][k]*right.matrix[k][j])%moduloValue;
                    returnValue.matrix[i][j] %= moduloValue;
                }
            }
        }
        return returnValue;
    }
};