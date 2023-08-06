#include "Matrix2D.hpp" 

int main() {
    Matrix2D<int> matrix(std::string("A"), 
    {
        {1 ,2 ,3 , 4}, 
        {1, 3, 5, -1},
        {1 ,2 ,3 , 4}, 
        {1, 3, 5, 1},
        {1 ,2 ,3 , 4}, 
        {1, 3, 5, -1},
    });
    std::cout << matrix << std::endl;
    auto path = findBestPathFromSrcToDesWithDfs(matrix, Node(0,0), Node(5,2));
    std::cout << "Result" << std::endl;
    for (auto & node : path) {
        std::cout << node << " ";
    }
    std::cout << std::endl;
}