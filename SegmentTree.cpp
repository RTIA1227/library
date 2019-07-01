#include<vector>
#include<functional>

template<typename dataType>
class SegmentTree{
    int dataSize;
    dataType initialVal;
    std::vector<dataType> tree;
    std::function<dataType(dataType,dataType)> addFunc;
    std::function<dataType(dataType,dataType)> extFunc;

    void internalUpdate(int pointedIndex){
        while(pointedIndex > 1){
            pointedIndex >>= 1;
            tree[pointedIndex] = extFunc(tree[pointedIndex*2],tree[pointedIndex*2+1]);
        }
    }

public:

    SegmentTree(int N, dataType init,
                function<dataType(dataType,dataType)> f1 = [](dataType a,dataType b)->dataType{return a+b;},
                function<dataType(dataType,dataType)> f2 = [](dataType a,dataType b)->dataType{return a+b;})
                :initialVal(init),addFunc(f1),extFunc(f2){
                    dataSize = 1;
                    while(dataSize < N){
                        dataSize *= 2;
                    }
                    tree = std::vector<dataType>(dataSize*2,initialVal);
                }

    void initialize(vector<dataType> data){
        for(int i = dataSize; i < dataSize*2 && i - dataSize < data.size(); i++){
            tree[i] = data[i - dataSize];
        }
        for(int i = dataSize - 1; i > 0; i--){
            tree[i] = extFunc(tree[i*2],tree[i*2+1]);
        }
    }

    bool updateQuery(int index,dataType newVal){
        if(index < 1 || index > dataSize){
            return false;
        }
        int pointedIndex = dataSize + index - 1;
        tree[pointedIndex] = newVal;
        internalUpdate(pointedIndex);
        return true;
    }

    bool addQuery(int index,dataType newVal){
        if(index < 1 || index > dataSize){
            return false;
        }
        int pointedIndex = dataSize + index - 1;
        tree[pointedIndex] = addFunc(tree[pointedIndex],newVal);
        internalUpdate(pointedIndex);
        return true;
    }

    dataType getQuery(int leftIndex , int rightIndex){
        if(leftIndex > rightIndex || leftIndex < 1 || rightIndex > dataSize){
            return initialVal;
        }else if(leftIndex == rightIndex){
            return tree[dataSize + leftIndex - 1];
        }

        int leftPointedIndex = dataSize + leftIndex - 1;
        int rightPointedIndex = dataSize + rightIndex - 1;

        dataType leftVal = tree[leftPointedIndex];
        dataType rightVal = tree[rightPointedIndex];
        
        while(true){
            bool wasLeftEven = (leftPointedIndex % 2 == 0);
            bool wasRightEven = (rightPointedIndex % 2 == 0);

            leftPointedIndex >>= 1;
            rightPointedIndex >>= 1;

            if(leftPointedIndex == rightPointedIndex){
                return extFunc(leftVal,rightVal);
            }

            if(wasLeftEven){
                leftVal = extFunc(leftVal,tree[leftPointedIndex*2 + 1]);
            }

            if(!wasRightEven){
                rightVal = extFunc(rightVal,tree[rightPointedIndex*2]);
            }
        }

        return initialVal;
    }
};