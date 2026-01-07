#include <iostream>
#include "clsCurrency.h"
#include "clsLoginScreen.h"

template <typename Type> Type MyMax(Type Num1, Type Num2)
{
    return (Num1 > Num2) ? Num1 : Num2;
}

template<class T> class Calculator
{
private:
    T Number1, Number2, Result;

public:
    Calculator(T n1, T n2)
    {
        Number1 = n1;
        Number2 = n2;
    }

    T Add()
    {
        return Result = Number1 + Number2;
    }
     
    T Sub()
    {
        return Result = Number1 - Number2;
    }

    T Mul()
    {
        return Result = Number1 * Number2;
    }

    void Print()
    {
        cout << "\nthe result of nums (" << Number1 << ") and (" << Number2 << ") is : "<<Result << endl;
    }
};

int main()

{
    while (true)
    {
        if (!clsLoginScreen::ShowLoginScreen())
        {
            break;
        }

    }

    return 0;

}



