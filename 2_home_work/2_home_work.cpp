

#include <iostream>
#include <vector>
#include <string>
#include <utility>
class big_integer {
private:
	std::string str;
	int count = 0;
	std::string sum_string(std::string s1, std::string s2) {
		auto it = s1.rbegin();
		auto it_2 = s2.rbegin();
		std::string res;


		while ((it != s1.rend()) || (it_2 != s2.rend())) {
			int num = 0;
			int num_2 = 0;

			if (it != s1.rend()) {
				num = *it - '0';
				++it;
			}
			if (it_2 != s2.rend()) {
				num_2 = *it_2 - '0';
				++it_2;
			}

			int sum = num + num_2 + count;

			if (sum >= 10) {
				count = sum / 10;
				sum = sum % 10;
			}
			else {
				count = 0;
			}

			res.push_back(static_cast<char>(sum + '0'));
		}
		if (count > 0) {
			res.push_back(static_cast<char>(count + '0'));
		}
		std::reverse(res.begin(), res.end());
		
		return res;
	}
public:
	big_integer(std::string str_) : str(str_) {};
	big_integer(big_integer&& other)noexcept : str(std::exchange(other.str, "0")) {};
	big_integer& operator= (big_integer&& other) noexcept {
		other.str.swap(str);
		return *this;
	}; 
	big_integer& operator= (const big_integer& other)  {
		str = other.str;
	};
	big_integer(const big_integer& other) : str(other.str) {};

	friend std::ostream& operator<<(std::ostream& os, big_integer& other) {
		os << other.str;
		return os;
	};
		
	big_integer operator+ (big_integer &other) {
		return sum_string(str, other.str);
	};

	big_integer operator* (big_integer& other) {  
		std::string res = "";
		std::string sum_res = "";
		
		int var = 0;
		for (auto it = str.rbegin(); it != str.rend(); ++it) {
			int num = *it - '0';
			int num_2 = 0;
			int sum = 0;
			sum_res = "";
			int var2 = var;
			for (auto it_2 = other.str.rbegin(); it_2 != other.str.rend(); ++it_2) {
				num_2 = *it_2 - '0';
				sum = (num * num_2) + count;

				if (sum >= 10) {
					count = sum / 10;
					sum %= 10;
				}
				else { count = 0; }
				sum_res.insert(sum_res.begin(), static_cast<char>(sum + '0'));
			}
			if (count > 0) {
				sum_res.insert(sum_res.begin(), static_cast<char>(count + '0'));
			}
			count = 0;
			if (res.size() == 0){
				res = sum_res;
			}
			else {
				if (var2 > 0) {
					while (var2 > 0) {
						sum_res.push_back('0');
						--var2;
					}
				}
				res = sum_string(res, sum_res);
			}
			++var;
		 }

		return big_integer(res);
	};




};

int main()
{
	auto number1 = big_integer("355");
	auto number2 = big_integer(std::move(number1));
	auto number3 = big_integer("355");
	auto result = number3 + number2;
	auto mult = number2 * number3;
	std::cout << "sum: " << result; 
	std::cout << std::endl;
	std::cout << "mult: " << mult;
	//std::cout << number1 << "\t" << number2 << "\t" << number3;

	std::cout << std::endl;

	

}
