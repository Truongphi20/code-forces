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
        std::reverse(boss_list.begin(), boss_list.end());
    }

    void SessionFighting(int killed_boss_num, std::string fighter)
    {
        if (fighter == "me"){
            me_frighting += 1;
        }else if (fighter == "myfriend")
        {
            for (int counter = 0; counter < killed_boss_num; ++counter)
            {
                std::bitset<1> boss_level { boss_list.size() - counter };
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
    int test_case_num;
    std::cin >> test_case_num;

    for (int i=0; i<test_case_num; i++)
    {
        // Read boss number
        int boss_number;
        std::cin >> boss_number;
        
        // Read list of boss
        std::vector<std::bitset<1>> boss_list;
        for (int i=0; i < boss_number; i++)
        {
            std::bitset<1> bit;
            std::cin >> bit;
            boss_list.push_back(bit);
        }

        // Handle bosses
        BossHandle(boss_number, boss_list);
    }

    return 0;
}