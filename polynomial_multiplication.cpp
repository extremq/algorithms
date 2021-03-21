/**
EXAMPLE USAGE:
Enter degree of first polynomial:
2
Enter the 3 coefficients:
1 2 1
Enter degree of second polynomial:
2 
Enter the 3 coefficients:
1 -2 1
The product is:
1 + (-2)*x^2 + x^4
**/

#include <iostream>
#include <cmath>
#include <complex>
#include <vector>

using namespace std;
using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> &a, bool invert) {
    int n = a.size();
    if (n == 1) return;

    vector<cd> a0(n/2), a1(n/2);
    for (int i = 0; 2 * i < n; ++i) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }

    fft(a0, invert);
    fft(a1, invert);

    double angle = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(angle), sin(angle));

    for (int i = 0; 2 * i < n; ++i) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) {
            a[i]       /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}

vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    
    for (int i = 0; i < n; ++i) 
        fa[i] *= fb[i];
    
    fft(fa, true);

    vector<int> result(n);

    for (int i = 0; i < n; ++i) 
        result[i] = round(fa[i].real());

    int carry = 0;
    for (int i = 0; i < n; i++) {
        result[i] += carry;
        carry = result[i] / 10;
        result[i] %= 10;
    }
    return result;
}

void reduce(vector<cd> & a) {
    for (int i = 0; i < a.size(); ++i) {
        if (abs(a[i].real()) < pow(10, -10)) a[i] = {0, a[i].imag()};
        if (abs(a[i].imag()) < pow(10, -10)) a[i] = {a[i].real(), 0}; 
    }
}

int main(){
    vector<int> a, b;
    vector<int> res;
    int size_a, size_b;
    cout << "Enter degree of first polynomial:\n";
    cin >> size_a;
    cout << "Enter the " << ++size_a << " coefficients:\n";
    for (int i = 0; i < size_a; ++i){
        int x;
        cin >> x;
        a.push_back(x);
    }
    cout << "Enter degree of second polynomial:\n";
    cin >> size_b;
    cout << "Enter the " << ++size_b << " coefficients:\n";
    for (int i = 0; i < size_b; ++i){
        int x;
        cin >> x;
        b.push_back(x);
    }
    cout << "The product is:\n";
    res = multiply(a, b);
    int lastNonZeroIndex = 0;
    for (int i = 0; i < res.size(); ++i) {
        if (res[i] != 0) lastNonZeroIndex = i;
    }
    for (int i = 0; i < res.size(); ++i) {
        if (res[i] != 0) {
            if (res[i] != 1) {
                if (res[i] < 0) cout << '(' << res[i] << ')';
                else cout << res[i];
                cout << "*";
            }
            else if (i == 0) cout << 1;
            if (i != 0) cout << "x";
            if (i > 1) cout << '^' << i;
            cout << ' ';
            if (i != res.size() - 1 && i < lastNonZeroIndex) cout << "+ ";
        }
    }
}
