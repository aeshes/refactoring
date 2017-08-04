#include <iostream>
#include <string>
#include <memory>
#include <vector>


class movie
{
public:
	static const int CHILDREN = 2;
	static const int REGULAR = 0;
	static const int NEW_RELEASE = 1;

public:
	movie() = default;
	movie(const std::string& title, const int price_code)
		:_title(title), _price_code(price_code)
	{
	}

	const  int get_price_code() const
	{
		return _price_code;
	}

	void set_price_code(int new_price_code)
	{
		_price_code = new_price_code;
	}

	const std::string get_title() const
	{
		return _title;
	}

private:
	std::string _title;
	int _price_code;
};

const int movie::CHILDREN;
const int movie::REGULAR;
const int movie::NEW_RELEASE;


class rental
{
	movie _movie;
	int _days_rented;

public:
	rental() = default;
	rental(const movie& m, const int days_rented)
		:_movie(m), _days_rented(days_rented)
	{

	}
	const int get_days_rented() const
	{
		return _days_rented;
	}
	const movie get_movie() const
	{
		return _movie;
	}
};

class customer
{
	std::string _name;
	std::shared_ptr<std::vector<rental>> _rentals;

public:
	customer() = default;
	customer(const std::string& name)
		:_name(name), _rentals(new std::vector<rental>()) {}
	void add_rental(const rental& r)
	{
		_rentals->push_back(r);
	}
	const std::string get_name() const
	{
		return _name;
	}
	const std::string statement() const;
};

const std::string customer::statement() const
{
	double total_amount = 0;
	int frequent_renter_points = 0;
	std::string result = "rent statement for: " + _name + "\n";

	for (const auto& entry : *_rentals)
	{
		double this_amount = 0;

		switch (entry.get_movie().get_price_code())
		{
		case movie::REGULAR:
			this_amount += 2;
			if (entry.get_days_rented() > 2)
			{
				this_amount += (entry.get_days_rented() - 2) * 1.5;
			}
			break;
		case movie::NEW_RELEASE:
			this_amount += entry.get_days_rented() * 3;
			break;
		case movie::CHILDREN:
			this_amount += 15;
			if (entry.get_days_rented() > 3)
			{
				this_amount += (entry.get_days_rented() - 3) * 1.5;
			}
			break;
		}

		++frequent_renter_points;

		if (entry.get_movie().get_price_code() == movie::NEW_RELEASE
			&& entry.get_days_rented() > 1)
		{
			++frequent_renter_points;
		}

		result += "\t" + entry.get_movie().get_title() + "\t" + std::to_string(this_amount) + "\n";
		total_amount += this_amount;
	}

	result += "sum is " + std::to_string(total_amount) + "\n";
	result += "you gained: " + std::to_string(frequent_renter_points) + "points \n";

	return result;
}

int main()
{

}