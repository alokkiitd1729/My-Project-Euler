#include <iostream>
#include <math.h>
#include <string>
#include <set>

using namespace std;

const int N = 250; 

struct bignum {
    int a[N];
    int point; 
} num; 

bignum operator+(bignum x, bignum y) {
    bignum z;
    memset(z.a, 0, sizeof(z.a)); 
    if(x.point < y.point) {
        int diff = y.point - x.point;
        x.point = y.point;
        for(int i = N - 1 - diff; i >= 0; i--) {
            x.a[i + diff] = x.a[i];
        }
        for(int i = diff - 1; i >= 0; i--) {
            x.a[i] = 0;
        }
    } else if(y.point < x.point) {
        int diff = x.point - y.point;
        y.point = x.point;
        for(int i = N - 1 - diff; i >= 0; i--) {
            y.a[i + diff] = y.a[i];
        }
        for(int i = diff - 1; i >= 0; i--) {
            y.a[i] = 0;
        }
    }

    for(int i = 0; i < N; i++) {
        z.a[i] = x.a[i] + y.a[i];
    }
    z.point = x.point;

    int carry = 0;

    for(int i = 0; i < N; i++) {
        z.a[i] = z.a[i] + carry;
        carry = z.a[i] / 10;
        z.a[i] %= 10;
    }

    return z;
} 

bignum operator*(bignum x, int y) {
    bignum z;
    z.point = x.point;
    memset(z.a, 0, sizeof(z.a)); 

    for(int i = 0; i < N; i++) {
        z.a[i] = x.a[i] * y;
    }

    int carry = 0;

    for(int i = 0; i < N; i++) {
        z.a[i] = z.a[i] + carry;
        carry = z.a[i] / 10;
        z.a[i] %= 10;
    }

    return z;
} 

bignum operator*(bignum x, bignum y) {
    bignum z;
    z.point = x.point + y.point;
    memset(z.a, 0, sizeof(z.a)); 

    for(int i = 0; i < N; i++) {
        for(int j = 0; j <= i; j++) {
            z.a[i] += x.a[j] * y.a[i - j];
        }
    }

    int carry = 0;

    for(int i = 0; i < N; i++) {
        z.a[i] = z.a[i] + carry;
        carry = z.a[i] / 10;
        z.a[i] %= 10;
    }

    return z;
} 

bool operator>(bignum x, bignum y) {
    if(x.point < y.point) {
        int diff = y.point - x.point;
        x.point = y.point;
        for(int i = N - 1 - diff; i >= 0; i--) {
            x.a[i + diff] = x.a[i];
        }
        for(int i = diff - 1; i >= 0; i--) {
            x.a[i] = 0;
        }
    } else if(y.point < x.point) {
        int diff = x.point - y.point;
        y.point = x.point;
        for(int i = N - 1 - diff; i >= 0; i--) {
            y.a[i + diff] = y.a[i];
        }
        for(int i = diff - 1; i >= 0; i--) {
            y.a[i] = 0;
        }
    }

    for(int i = N - 1; i >= 0; i--) {
        if(x.a[i] > y.a[i]) {
            return true;
        } else if(x.a[i] < y.a[i]) {
            return false;
        }
    }

    return false;
} 

bool operator<(bignum x, bignum y) {
    return (y > x);
}

bignum square(bignum x) {
    return x * x;
}

/*
x^y
*/
bignum operator&(bignum x,int y) {
    if(y == 1) return x;
    if((y & 1) == 0) {
        return square(x & (y >> 1));
    } else {
        return x * square(x & (y >> 1));
    }
}

void printNum(bignum num) {
    for(int i = 0; i < N; i++) {
        cout<<num.a[i];
    }
    cout<<endl;
    cout<<"num.point "<<num.point<<endl;

    return;
}

int main() {
    bignum num;
    num.point = 0;
    set<bignum> s;
    int limit = 100;
    for(int a = 2; a <= limit; a++) {
        for(int b = 2; b <= limit; b++) {

            memset(num.a, 0, sizeof(num.a));
            num.a[0] = a % 10;
            num.a[1] = a / 10 % 10;
            num.a[2] = a / 100;
            num = (num & b);
            s.insert(num);
        }
    }

    cout<<s.size()<<endl;
    int wait = 0;
    cin>>wait;

    return 0; 
}
