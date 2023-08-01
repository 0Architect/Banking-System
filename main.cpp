#include <iostream>
#include <stdexcept>
#include <string>

using std::string;

class Account
{

private:
    string accountNumber;
    double balance;

public:
    Account(const string &accountNum, double amount) : accountNumber(accountNum), balance(amount) {}

    void deposit(double amount) { balance += amount; }

    void withdraw(double amount)
    {
        try
        {
            if (balance < amount)
                throw std::runtime_error("Insufficient balance");

            else
                balance -= amount;
        }

        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    double getBalance() const { return balance; }
};

class SavingsAccount : public Account
{
private:
    double interestRate;

public:
    SavingsAccount(const string &accountNum, double amount, double rate)
        : Account(accountNum, amount), interestRate(rate) {}

    void applyInterest()
    {
        double interestAmount = getBalance() * (interestRate / 100.0);
        deposit(interestAmount);
    }
};

class CheckingAccount : public Account
{
private:
    double feePerTransaction;

public:
    CheckingAccount(const string &accountNum, double amount, double fee)
        : Account(accountNum, amount), feePerTransaction(fee) {}

    void deductTransationFee()
    {
        withdraw(feePerTransaction);
    }
};

void printBalance(const string &name, double balance)
{
    std::cout << name << " has " << balance << std::endl;
}

int main()
{
    SavingsAccount account1("123943329", 6000, 5);
    CheckingAccount account2("12321232", 5000, 2);

    // SavingsAccount actions
    std::cout << "SavingsAccount actions:" << std::endl;
    printBalance("account1", account1.getBalance());
    account1.deposit(500);
    printBalance("account1", account1.getBalance());
    account1.withdraw(1000);
    printBalance("account1", account1.getBalance());
    account1.applyInterest();
    printBalance("account1", account1.getBalance());

    std::cout << '\n';

    // CheckingAccount actions
    std::cout << "CheckingAccount actions:" << std::endl;
    printBalance("account2", account2.getBalance());
    account2.deposit(500);
    printBalance("account2", account2.getBalance());
    account2.withdraw(1000);
    printBalance("account2", account2.getBalance());
    account2.deductTransationFee();
    printBalance("account2", account2.getBalance());

    return 0;
}