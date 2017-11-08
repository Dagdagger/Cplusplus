#include <iostream>

using namespace std;

int main()
{

	double money_today, money_next, growth_rate, withdraw, balance, totWithdrawal;
	int year;


	cout << "Initial Investment?";
	cin >> money_today;

	cout << "Yearly growth rate?";
	cin >> growth_rate;

	cout << "Yearly withdraw amount?";
	cin >> withdraw;

	cout << "Desired balance?";
	cin >> balance;


	year = 0;


	if ((money_today > withdraw) && (growth_rate > 0)){
		while(money_today < balance)
		{
			money_next = money_today * (1 + growth_rate) - withdraw;
			money_today = money_next;
			year++;
			totWithdrawal = withdraw * year;
		}
	cout << "Years: " << year << endl;
	cout << "Balance at end: " << money_next << endl;
	cout << "Amount withdrawn over period: " << totWithdrawal <<endl;
	}

	if(growth_rate < 0) {
		while(money_today > 0)
		{
			money_next = money_today * (1 + growth_rate) - withdraw;
			money_today = money_next;
			year++;
		}

		cout<< "Years: "<< year << endl;
		cout << "Balance at end: " << 0 << endl;
		cout << "Amount withdrawn over period: " << (withdraw * year) + money_today;

	}

	if (money_today < withdraw)

	{
		cout<< "Years: "<< 1 << endl;
		cout << "Balance at end: " << 0 << endl;
		cout << "Amount withdrawn over period: " << money_today*(1+growth_rate) <<endl;
	}

	return 0;
}
