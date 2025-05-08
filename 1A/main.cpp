#include <iostream>
#include <vector>

class TheaterSquare {

    public:

    TheaterSquare(int l, int w):
        length(l),
        width(w)
    {}

    void paving(int pave_size, int initial_x = 0, int initial_y = 0){
        this->pave_size = pave_size;

        int* p_initial_x = new int(initial_x);
        int* p_initial_y = new int(initial_y);

        // Preparing
        int* p_initial_next_x = new int(*p_initial_x + this->pave_size);
        int* p_initial_next_y = new int(*p_initial_y);

        this->recursive_pave(p_initial_x, p_initial_y, p_initial_next_x, p_initial_next_y);
    }

    int getUsedStoneNumber()
    {
        return this->flagstone_number;
    }

    private:

    int width;
    int length;
    int pave_size;
    int flagstone_number{0};

    void recursive_pave(int* p_x_coor, int* p_y_coor, int* p_next_x, int* p_next_y)
    {
        while (*p_x_coor < this->length && *p_y_coor < this->width)
        {
            // Count pave
            this->flagstone_number += 1;


            // lefter
            if (*p_next_x < this->length)
            {
                // Re set pointer
                int* p_tem_x = new int(*p_x_coor);
                int* p_tem_y = new int(*p_y_coor);

                *p_x_coor = *p_next_x;

                *p_next_x = *p_x_coor + this->pave_size;
                *p_next_y = *p_y_coor;

                delete p_tem_x;
                delete p_tem_y;

                continue;
            }
            // below
            else if (*p_next_y < this->width)
            {
                // Re set pointer
                *p_x_coor = 0;
                *p_y_coor = *p_next_y + this->pave_size;

                *p_next_x = this->pave_size;
                *p_next_y = *p_y_coor;

                continue;
            }
        }
        
    }
};


int main(){
    // TheaterSquare ts(1000000000,1000000000);
    // ts.paving(1);
    // std::cout << "Used #stone: " << ts.getUsedStoneNumber() << "\n";

    long long n, m, a;
    std::cin >> n >> m >> a;
    TheaterSquare ts(n,m);
    ts.paving(a);
    std::cout << ts.getUsedStoneNumber() << "\n";

    return 0;
}
