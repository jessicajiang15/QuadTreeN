
#include "GaussianN.h"

GaussianN::GaussianN(double a,double rho, double p, double theta, std::vector<double> displacements, int N, int dummy)
{
    std::cout<<"TYPE 1 CONSTRUCTOR"<<std::endl;
    //constructs a gaussian of the form A*exp(-(x-b)^2/(2c^2)+-(y-d)^2/(2e^2))
    this->a=a;
    this->rho=rho;
    this->p=p;
    this->theta=theta;
    this->displacements=displacements;
    this->N=N;
    this->type=1;
    this->normConst = 1;
}

GaussianN::GaussianN(double a, double rho, double p, double theta, std::vector<double> displacements, int N)
{
    std::cout<<"TYPE 2 CONSTRUCTOR"<<std::endl;
    this->type = 2;

    this->N=N;

    //sus
    this->rho=rho;
    this->p=p;
    this->theta=theta;

    this->a=a;
    this->aa = ((cos(theta) * cos(theta)) / (p * p)) + (p * p * sin(theta) * sin(theta)) / (rho * rho);
    this->bb = 2 * sin(theta) * cos(theta) * (1 / (p * p) - p * p / (rho * rho));
    this->cc = (sin(theta) * sin(theta)) / (p * p) + (p * p * cos(theta) * cos(theta) / (rho * rho));
    /**
     * constructs a gaussian of the form A*exp(-(x-b)^2/(2c^2)+-(y-d)^2/(2e^2))
    **/
    this->normConst = 1;
    this->displacements=displacements;
}


double GaussianN::value(std::vector<double> inputs)
{
    //std::cout<<"size"<<inputs.size()<<std::endl;
    if(this->type==1)
    {
     double temp=1;
     for(int i=0;i<this->N;i++)
     {
        double prod=i==1?(this->rho*this->rho):1;
        //std::cout<<i<<" rho: "<<rho<<std::endl;
        //std::cout<<i<<" prod: "<<prod<<std::endl;
        //std::cout<<i<<" exp: "<<-(inputs[i]-this->displacements[i])*(inputs[i]-this->displacements[i])/prod<<std::endl;
        temp*=exp(-(inputs[i]-this->displacements[i])*(inputs[i]-this->displacements[i])/prod);
     }
     //std::cout<<temp<<std::endl;
     return this->a*temp;
    }
    else if(this->type==2)
    {
        double temp=1;
        for(int i=2;i<this->N;i++)
        {
            temp*=exp(-(inputs[i]-this->displacements[i])*(inputs[i]-this->displacements[i]));
        }
        temp*=this->a * this->normConst * exp(-(this->aa * (inputs[0]-this->displacements[0]) * (inputs[0]-this->displacements[0]) + bb * (inputs[0]-this->displacements[0]) * (inputs[1]-this->displacements[1]) + cc * (inputs[1]-this->displacements[1]) * (inputs[1]-this->displacements[1])));
        return temp;
    }
    std::cout<<"undefined type"<<std::endl;
    return 0;
}


void GaussianN::setNormConstant(double norm)
{
    this->normConst=norm;
}


double GaussianN::getNormConstant()
{
    return this->normConst;
}
