#include "MDAIndexGenerator.h"
#ifndef _WINDOWS
// Needed on Unix for getcwd() and gethostname()
#include <pwd.h>
#include <sys/types.h>
#include <unistd.h>
#else
// for _getcwd
#include <direct.h>
#include <vector>
#endif
#include <tuple>

using namespace std;

MDAIndexGenerator::MDAIndexGenerator(int rows, int cols, bool snake, bool row_wise):
    rows_(rows),
    cols_(cols),
    snake_(snake),
    row_wise_(row_wise),
    current_row_(0),
    current_col_(0)
{
    // empty constructor
}
tuple<int,int> next():
{
    if (snake_ == false){
        if (row_wise_ == true){
            if (current_col_ == cols_){
                current_col_ = 0;
                current_row_++;
            }
            else{
                current_col_++;
            }
        }
        else{
            if (current_row_ == rows_){
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
            if (current_col_ == cols_ && current_row_ % 2 == 0){
                current_col_ = cols_ - 1;
                current_row_++;
            }
            else if (current_col_ == 0 && current_row_ % 2 == 1){
                current_col_ = 0;
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
            if (current_row_ == rows_ && current_col_ % 2 == 0){
                current_row_ = rows_ - 1;
                current_col_++;
            }
            else if (current_row_ == 0 && current_col_ % 2 == 1){
                current_row_ = 0;
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
    if current_row_ >= rows_ || current_col_ >= cols_{
        return make_tuple(INT_MIN, INT_MIN );
    }

    return make_tuple(current_row_, current_col_);
}

int main()
{
// initialize the position class with a dummy example
    auto gen = MDAIndexGenerator pos(1,2,true,true);
    cout << gen.next() << endl;
    cout << gen.next() << endl;
    return 0;
}