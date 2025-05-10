#include <iostream>

class Vector{

    public:
    int x_coord{0};
    int y_coord{0};
    int z_coord{0};
};


int main()
{
    int vector_number;
    std::cin >> vector_number;
    
    Vector sum_vector;
    for (int i=0; i < vector_number; i++)
    {
        int x, y, z;
        std::cin >> x >> y >> z;

        sum_vector.x_coord += x;
        sum_vector.y_coord += y;
        sum_vector.z_coord += z;
    }

    if (sum_vector.x_coord == 0 && sum_vector.y_coord == 0 && sum_vector.z_coord == 0)
    {
        std::cout << "YES" << '\n';
    }else{
        std::cout << "NO" << '\n';
    }


    return 0;
}