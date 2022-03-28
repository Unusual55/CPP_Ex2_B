#include "Notebook.hpp"
#include "Direction.hpp"
#include "page.hpp"
using ariel::Direction;

#include <iostream>
#include <stdexcept>

// int main(int argc, char const *argv[])
// {
//     string s="__________";
//     ariel::Notebook note;
//     cout<<11<<endl;
//     note.write(1, 1, 10, Direction::Horizontal, "hello world");
//     try{
//         s = note.read(0,0,0,Direction::Horizontal,100);
//     }
//     catch(const std::exception& e){
//         std::cout<<e.what();
//     }
//     return 0;
// }