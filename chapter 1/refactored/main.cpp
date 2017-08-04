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
	int get_days_rented() const
	{ return _days_rented; }

	movie get_movie() const
	{ return _movie; }

	double get_charge() const;
	int get_renter_points() const;
};

double rental::get_charge() const
{
	double result = 0;

	switch (get_movie().get_price_code())
	{
	case movie::REGULAR:
		result += 2;
		if (get_days_rented() > 2)
		{
			result += (get_days_rented() - 2) * 15;
		}
		break;
	case movie::NEW_RELEASE:
		result += get_days_rented() * 3;
		break;
	case movie::CHILDREN:
		result += 15;
		if (get_days_rented() > 3)
		{
			result += (get_days_rented() - 3) * 15;
		}
		break;
	}

	return result;
}

int rental::get_renter_points() const
{
	if (get_movie().get_price_code() == movie::NEW_RELEASE
		&& get_days_rented() > 1)
	{
		return 2;
	}
	else return 1;
}

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
	std::string get_name() const
	{
		return _name;
	}
	double get_total_charge() const;
	int get_total_renter_points() const;
	std::string statement() const;
	std::string html_statement() const;
};

double customer::get_total_charge() const
{
	double result = 0;
	for (const auto& entry : *_rentals)
		result += entry.get_charge();
	return result;
}

int customer::get_total_renter_points() const
{
	int result = 0;
	for (const auto& entry : *_rentals)
		result += entry.get_renter_points();
	return result;
}

std::string customer::statement() const
{
	double total_amount = 0;
	std::string result = "rent statement for: " + _name + "\n";

	for (const auto& entry : *_rentals)
	{
		result += "\t" + entry.get_movie().get_title() + "\t" + std::to_string(entry.get_charge()) + "\n";
	}

	result += "sum is " + std::to_string(get_total_charge()) + "\n";
	result += "you gained: " + std::to_string(get_total_renter_points()) + " points \n";

	return result;
}

std::string customer::html_statement() const
{
	std::string result = "<H1>Rent operations for <EM>" + get_name() + "</EM></H1><P>\n";

	for (const auto& entry : *_rentals)
	{
		result += entry.get_movie().get_title()
			+ std::to_string(entry.get_charge()) + "<BR>\n";
	}

	result += "<P>Total: <EM>"
		+ std::to_string(get_total_charge()) + "</EM>\n";
	result += "You gained: <EM>"
		+ std::to_string(get_total_charge()) + "</EM> points for activity</P>";

	return result;
}


int main()
{
	movie m1("movie 1", 0);
	movie m2("movie 2", 1);
	movie m3("movie 3", 2);

	rental r1(m1, 1);
	rental r2(m2, 2);
	rental r3(m3, 3);

	customer c("cust name");
	c.add_rental(r1);
	c.add_rental(r2);
	c.add_rental(r3);

	std::cout << c.statement() << std::endl;
}