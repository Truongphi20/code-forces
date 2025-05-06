#include <iostream>
#include <vector>

class Area {

    public:
    Area() : x_coordinate(0), y_coordinate(0), pave(false) {}
    Area(int x, int y):
        x_coordinate(x),
        y_coordinate(y)
    {}

    bool pave{ false };

    void paving(int x_pave_coord, int y_pave_coord){ 
        // Paving on this area by a square flagstone, declare x,y on flagstone
        this->pave = true;
        this->x_pave_coordinate = x_pave_coord;
        this->y_pave_coordinate = y_pave_coord;
    }

    private:

    int x_coordinate;
    int y_coordinate;

    int x_pave_coordinate;
    int y_pave_coordinate;
};


class TheaterSquare {

    public:

    TheaterSquare(int w, int l):
        width(w),
        length(l)
    {
        for (int x = 0; x < width; ++x) {
            std::vector<Area> row;
            for (int y = 0; y < length; ++y) {
                row.emplace_back(x, y);  // Calls Area(x, y)
            }
            areas.emplace_back(std::move(row));
        }
    }

    void printAreas()
    {
        for (const auto& row: this->areas){
            for (const Area& area: row){
                std::cout << area.pave << ' ';
            }

            std::cout << '\n';
        }
    }

    void paving(int pave_size, int initial_x = 0, int initial_y = 0, int initial_x_coord = 0, int initial_y_coord = 0){
        this->pave_size = pave_size;
        this->recursive_pave(initial_x, initial_y, initial_x_coord, initial_y_coord);
    }

    int getUsedStoneNumber()
    {
        return this->flagstone_number;
    }

    private:

    int width;
    int length;
    std::vector<std::vector<Area>> areas;
    int pave_size;
    int flagstone_number{0};

    void paveAArea(int x_coor, int y_coor, int x_pave_coor, int y_pave_coor)
    {
        this->areas[x_coor][y_coor].paving(x_pave_coor,y_pave_coor);        
    }

    void checkNextPave(int x_pave_coord_global, int y_pave_coord_global)
    {
        // Preparing
        int next_x_point = x_pave_coord_global + this->pave_size;
        int next_y_point = y_pave_coord_global + this->pave_size;

        // lefter
        if (next_x_point < this->length)
        {
            this->recursive_pave(next_x_point, y_pave_coord_global, 0, 0);
        }
        // diagonal
        if (next_x_point < this->length && next_y_point < this->width)
        {
            this->recursive_pave(x_pave_coord_global + this->pave_size, next_y_point, 0, 0);
        }
        // below
        if (next_y_point < this->width)
        {
            this->recursive_pave(x_pave_coord_global, next_y_point, 0, 0);
        }

        return;
    }

    void recursive_pave(int x_coor, int y_coor, int x_pave_coor, int y_pave_coor)
    {
        // Exit
        if (x_coor >= this->length || y_coor >= this->width) return;

        // Paving
        int x_pave_coord_global = x_coor - x_pave_coor;
        int y_pave_coord_global = y_coor - y_pave_coor;

        if (x_pave_coor == 0 && y_pave_coor == 0)
        {
            for (int i=0; i < this->pave_size; ++i){
                for (int j=0; j < this->pave_size; ++j){
                    if (x_pave_coord_global+i >= this->length || y_pave_coord_global >= this->width){
                        continue;
                    }
                    this->paveAArea(x_pave_coord_global+i, y_pave_coord_global+j, i, j);
                }
            }
        }

        // Count pave
        this->flagstone_number += 1;

        // Pave next others
        this->checkNextPave(x_pave_coord_global, y_pave_coord_global);

        
    }
};


int main(){
    TheaterSquare ts(2,1);
    ts.printAreas();
    ts.paving(1);
    std::cout << "--------------\n"; 
    ts.printAreas();
    std::cout << "Used #stone: " << ts.getUsedStoneNumber() << "\n";

    // long long n, m, a;
    // std::cin >> n >> m >> a;
    // TheaterSquare ts(n,m);
    // ts.paving(a);
    // std::cout << ts.getUsedStoneNumber() << "\n";

    return 0;
}
