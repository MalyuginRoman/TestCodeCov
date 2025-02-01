const double e = 1E-07;

struct root
{
        double x1;
        double x2;
};

double discr(double a, double b, double c)
{
    return b * b - 4.0 * a * c;
}

root solve(double a, double b, double c)
{
    root x;
    x.x1 = 0;
    x.x2 = 0;
    if(abs(a) < e)
        std::cout << "The equation is not quadratic." << std::endl;
    else
    {
        double d = discr(a, b, c);
        std::cout << "d = " << d << std::endl;
        if(d < 0.0)
            std::cout << "The equation has no real roots." << std::endl;
        else
        {
            if(abs(d) < e)
            {
                std::cout << "The equation has one real roots:";
                x.x1 = -b + sqrt(d) / (2 * a);
                std::cout << x.x1;
            }
            else
            {
                std::cout << "The equation has two real roots:";
                x.x1 = -b + sqrt(d) / (2 * a);
                std::cout << x.x1 << ", ";
                x.x2 = -b - sqrt(d) / (2 * a);
                std::cout << x.x2;
            }
        }
    }
    return x;
}
