// 숙제로 지정하신 Attach와 Remove 함수는 85 ~ 104줄에 정의되어 있습니다
#include <stdio.h>
#include <stdlib.h>
#define MAX_DEGREE 101


//structure definition
typedef struct {
    int degree;
    float coef[MAX_DEGREE];
} polynomial;


// function definition
polynomial Zero();
int IsZero(polynomial a);
int Compare(int LeadExpA, int LeadExpB);
polynomial Attach(polynomial a, float coef_sum, int LeadExp);
polynomial Remove(polynomial a, int LeadExp);
polynomial Sum(polynomial a, polynomial b);


void main (void) {
    polynomial Ax = Zero();
    polynomial Bx = Zero();
    polynomial Result = Zero();
    
    // a assign
    Ax.degree = 6;
    Ax.coef[6] = 3;
    Ax.coef[5] = 2;
    Ax.coef[0] = 4;
    
    // b assign
    Bx.degree = 4;
    Bx.coef[4] = 1;
    Bx.coef[3] = 10;
    Bx.coef[2] = 3;
    Bx.coef[0] = 5;
    
    // sum

    
    Result = Sum(Ax, Bx);
    
    // print phase
    printf("Degree of Result Polynomial: %d\n", Result.degree);
    for (int i = Result.degree ; i >= 0 ; i--) {
        printf("coefficient of x^%d: %f\n", i, Result.coef[i]);
    }
}





// functions
polynomial Zero() { // makes empty polynomial
    polynomial empty;
    empty.degree = 0;
    for (int i = 0 ; i < MAX_DEGREE ; i++) {
        empty.coef[i] = 0;
    }
    return empty;
}

int IsZero(polynomial a) { // determines whether it is an empty polynomial
    if ((! a.degree) && (a.coef[0] == 0))
        return 1;
    else
        return 0;
}

int Compare(int LeadExpA, int LeadExpB) { // compare which has bigger exponent polynomial
    if (LeadExpA < LeadExpB)
        return -1;
    else if (LeadExpA == LeadExpB)
        return 0;
    else
        return 1;
}

polynomial Attach(polynomial a, float coef_sum, int LeadExp) {
    polynomial d = a;
    d.coef[LeadExp] = coef_sum;
    if (LeadExp > d.degree) {
        d.degree = LeadExp;
    }
    return d;
}

polynomial Remove(polynomial a, int LeadExp) { // 최고차항의 계수를 삭제하고 degree를 남은 항 중 최고자항의 degree로 변경
    polynomial d = a;
    d.coef[LeadExp] = 0;
    for (int i = LeadExp ; i >= 0 ; i--) {
        if (d.coef[i] != 0) {
            d.degree = i;
            break;
        }
    }
    return d;
}

polynomial Sum(polynomial a, polynomial b) {
    polynomial d = Zero();
    float sum_num;
    while ((!IsZero(a)) && (!IsZero(b))) {
        switch (Compare(a.degree, b.degree)) {
            case -1:
                d = Attach(d, b.coef[b.degree], b.degree);
                b = Remove(b, b.degree);
                break;
            case 0:
                sum_num = a.coef[a.degree] + b.coef[b.degree];
                if (sum_num) {
                    d = Attach(d, sum_num, a.degree);
                    a = Remove(a, a.degree);
                    b = Remove(b, b.degree);
                }
                break;
            case 1:
                d = Attach(d, a.coef[a.degree], a.degree);
                a = Remove(a, a.degree);
                break;
        }
    }
    if (!IsZero(a)) { // a에 남아있는 경우
        for (int i = b.degree ; i >= 0 ; i--) {
            d = Attach(d, a.coef[a.degree], a.degree);
            a = Remove(a, a.degree);
        }
    }
    else if (!IsZero(b)) { // b에 남아있는 경우
        for (int i = a.degree ; i >= 0 ; i--) {
            d = Attach(d, b.coef[b.degree], b.degree);
            b = Remove(b, b.degree);
        }
    }
    return d;
}