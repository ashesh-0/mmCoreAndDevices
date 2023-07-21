#include "MDAIndexGenerator.h"
#include "limits.h"
#include <iostream>
#include <tuple>


#ifndef _WINDOWS
// Needed on Unix for getcwd() and gethostname()
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#else
// for _getcwd
#include <direct.h>
#endif

using namespace std;

MDAIndexGenerator::MDAIndexGenerator(int rows, int cols, bool snake, bool row_wise):
    rows_(rows),
    cols_(cols),
    snake_(snake),
    row_wise_(row_wise),
    total_positions_(-1)
{
    reset();
}

tuple<int,int> MDAIndexGenerator::next()
{
    if (current_row_ == -1 || current_col_ == -1){
        assert(current_col_ ==-1 && current_row_ == -1);
        current_row_ = 0;
        current_col_ = 0;
    }
    else if (snake_ == false){
        if (row_wise_ == true){
            if (current_col_ == cols_-1){
                current_col_ = 0;
                current_row_++;
            }
            else{
                current_col_++;
            }
        }
        else{
            if (current_row_ == rows_-1){
                current_row_ = 0;
                current_col_++;
            }
            else{
                current_row_++;
            }
        }
    }
    else{
        if (row_wise_ == true){
            if (current_col_ == cols_-1 && current_row_ % 2 == 0){
                current_row_++;
            }
            else if (current_col_ == 0 && current_row_ % 2 == 1){
                current_row_++;
            }
            else{
                if (current_row_ % 2 == 0)
                    current_col_++;
                else
                    current_col_--;
            }
        }
        else{
            if (current_row_ == rows_-1 && current_col_ % 2 == 0){
                current_col_++;
            }
            else if (current_row_ == 0 && current_col_ % 2 == 1){
                current_col_++;
            }
            else{
                if (current_col_ % 2 == 0)
                    current_row_++;
                else
                    current_row_--;
            }
        }
    }
    if (current_row_ >= rows_ || current_col_ >= cols_)
    {
        return make_tuple(INT_MIN, INT_MIN );
    }

    return make_tuple(current_row_, current_col_);
}

void MDAIndexGenerator::reset()
{
    current_row_ = -1;
    current_col_ = -1;
}

unsigned int MDAIndexGenerator::totalPositions()
{
    if (total_positions_ != -1)
        return total_positions_;

    // For spiral index generator, this logic is necesasary. Otherwise, we could simply return rows_*cols_.
    auto old_row = current_row_;
    auto old_col = current_col_;
    reset();
    auto total_positions_ = 0;
    
    while (true){
        auto loc = next();
        if (std::get<0>(loc) == INT_MIN && std::get<1>(loc) == INT_MIN)
            break;
        total_positions_++;
    }

    current_row_ = old_row;
    current_col_ = old_col;
    return total_positions_;
}

// int main()
// {
// // initialize the position class with a dummy example
//     int rows = 4;
//     int cols= 5;
//     auto gen = MDAIndexGenerator(rows,cols,true,false);
//     for (auto i = 0; i <rows*cols; i++){
//         auto loc = gen.next();
//         cout << std::get<0>(loc) << std::get<1>(loc) << endl;
//     }
//     return 0;
// }