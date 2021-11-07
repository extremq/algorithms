#include <iostream>

using namespace std;

int number_of_divisors(int n)
{
    int count = 1, d;
    
    // 1 has one divisor. All other numbers have at least 2 divisors.
    if (n > 1)
    {
        ++count;
    }
    
    for (d = 2; d * d < n; ++d)
    {
        if (n % d == 0)
        {
            count += 2;
        }
    }
    
    if (d * d == n)
    {
        ++count;
    }
    
    return count;
}

int main()
{
    int n;
    cin >> n;
    cout << number_of_divisors(n);

    return 0;
}
