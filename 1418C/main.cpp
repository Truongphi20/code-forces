#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <algorithm>

class BossHandle
{
    public:
    BossHandle(int boss_number, std::vector<std::bitset<1>> boss_list):
    boss_number(boss_number),
    boss_list(boss_list)
    {
        std::reverse(this->boss_list.begin(), this->boss_list.end());
    }

    void SessionFighting(int killed_boss_num, std::string fighter)
    {
        if (fighter == "me"){
            me_frighting += 1;
        }else if (fighter == "myfriend")
        {
            for (int counter = 0; counter < killed_boss_num; ++counter)
            {
                std::bitset<1> boss_level { boss_list[boss_list.size() - 1 - counter] };
                if (boss_level == 0b0){
                    friend_frighting += 1;
                }
                else{
                    skipper_frighting += 1;
                }
            }
        }

        boss_list.resize(boss_list.size() - killed_boss_num);
    }

    std::vector<std::bitset<1>> getBossList(){
        return boss_list;
    }

    int getSkipper(){
        return skipper_frighting;
    }
    
    int getFriendFighting(){
        return friend_frighting;
    }



    private:
    int boss_number;
    std::vector<std::bitset<1>> boss_list;
    int me_frighting{0};
    int friend_frighting{0};
    int skipper_frighting{0};
    std::string turn_marker[2] = {"me", "myfriend"};


};







int main()
{
    // int test_case_num;
    // std::cin >> test_case_num;

    // for (int i=0; i<test_case_num; i++)
    // {
    //     // Read boss number
    //     int boss_number;
    //     std::cin >> boss_number;
        
    //     // Read list of boss
    //     std::vector<std::bitset<1>> boss_list;
    //     for (int i=0; i < boss_number; i++)
    //     {
    //         std::bitset<1> bit;
    //         std::cin >> bit;
    //         boss_list.push_back(bit);
    //     }

    //     // Handle bosses
    //     BossHandle(boss_number, boss_list);
    // }

    //// Testing
    int boss_number {4};
    std::vector<std::bitset<1>> boss_list{ 1, 1, 1, 1 };
    // for (const std::bitset<1> bit: boss_list) std::cout << bit << '\n'; 
    BossHandle bh(boss_number, boss_list);
    // for (const std::bitset<1> bit: bh.getBossList()) std::cout << bit << '\n'; 

    // bh.SessionFighting(2, "me");
    // for (const std::bitset<1> bit: bh.getBossList()) std::cout << bit << '\n'; 
    
    bh.SessionFighting(2, "myfriend");
    for (const std::bitset<1> bit: bh.getBossList()) std::cout << bit << '\n'; 
    std::cout << bh.getSkipper() << '\n';
    std::cout << bh.getFriendFighting() << '\n';

    return 0;
}