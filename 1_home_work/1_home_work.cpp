
#include <iostream>
#include <vector>
template<class T>
void move_vectors(std::vector<T>& one_, std::vector<T>& two_) {
    two_.swap(one_);

};



int main()
{
    std::vector <std::string> one = { "test_string1", "test_string2" };
    std::vector <std::string> two;
    move_vectors(one, two);

    for (const auto& it : two) {
        std::cout << it << " ";
    }
}
