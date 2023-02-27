//RectangleN
#include "RectangleN.h"

 RectangleN::RectangleN(Point *corner, int N, std::vector<double> dims)
{
    //corner is the bottom most corner
    this->point=corner;
    this->N=N;
    this->dims=dims;
}


double RectangleN::getVol()
{
    double prod=1;
    for(int i=0;i<this->N;i++)
    {
        prod*=this->dims[i];
    }
    return prod;
}
double RectangleN::getithInterval(int i)
{
    return this->dims[i];
}
    double RectangleN::getithCoord(int i)
    {
        return this->point->getIthCoordinate(i);
    }

    double RectangleN::getCenterI(int i)
    {
        return this->point->getIthCoordinate(i)+this->dims[i]/2;
    }

    Point* RectangleN::getPoint()
    {
        return this->point;
    }

//integrate the function
double RectangleN::integrate(Function *F)
{
    return 0;
}

//gives a mid point riemann sum approximation of F on this interval

double RectangleN::approx(Function *F)
{
    return getVol()*F->value(this->getMidPoint()->getCoords());
}


double RectangleN::approx(double **F)
{
    return 0;
}

void RectangleN::draw(sf::RenderWindow *window, int dim1, int dim2)
{

    window->draw(*rect);
    /*
    bool temp=true;
    std::cout<<"WAWAWAWAWA"<<std::endl;
    this->getPoint()->print();
    std::cout<<"fWAWAWAWAWA"<<std::endl;
    for(int i=0;i<this->N;i++)
    {
        if(i!=dim1&&i!=dim2&&this->getithCoord(i)!=0)
        {
            temp=false;
            break;
        }
    }
    if(temp==true)
    {
        std::cout<<"FUCCCCCK"<<std::endl;
    window->draw(*rect);
    }

    */

}

std::string RectangleN::toStringCoord()
{
    std::string x="";
    for(int i=0;i<this->getN();i++)
    {
        x+=std::to_string(getCenterI(i));
        if(i!=this->N-1)
        {
            x+="\t";
        }
    }
    return x;
}


void RectangleN::createSfRectFromCartesian(double minX, double maxX, double minY, double maxY, int dim1, int dim2)
{
    Point *te=new Point(this->point->getCoords());
    //std::cout<<this->point->getIthCoordinate(dim2)+this->dims[dim2]<<std::endl;
    te->setCoord(dim2, this->point->getIthCoordinate(dim2)+this->dims[dim2]);
    Point *temp=GraphicsMechanics::convertFromCartesian(minX, maxX, minY, maxY, te, dim1, dim2);
    this->rect=new sf::RectangleShape();
    rect->setPosition(temp->getIthCoordinate(0),temp->getIthCoordinate(1));
    double width=this->dims[dim1];
    //std::cout<<width<<std::endl;
    double height=this->dims[dim2];

    rect->setSize(sf::Vector2f(width*GraphicsMechanics::getXScale(minX, maxX),height*GraphicsMechanics::getYScale(minY, maxY)));
    rect->setFillColor(sf::Color(100, 250, 50));
    rect->setOutlineColor(sf::Color(0, 0, 0));
    rect->setOutlineThickness(1);
}

void RectangleN::setColor(std::string s)
{
    if(s.compare("inbox")==0)
    {
        rect->setFillColor(sf::Color(169, 179, 255));
    }
    if(s.compare("outbox")==0)
    {
        rect->setFillColor(sf::Color(255, 169, 169));
    }

}


double RectangleN::getAccurateApprox(Function *F, int accuracy)
{
    
    if(accuracy==0)
    {
        return approx(F);
    }
    double intervalX=this->dims[0]/accuracy;
    double intervalY=this->dims[1]/accuracy;
    double total=0;
    for(int r=0;r<accuracy;r++)
    {
        for(int c=0;c<accuracy;c++)
        {
            std::vector<double> temp;
            temp.push_back(c*intervalX+point->getIthCoordinate(0)+intervalX/2);
            temp.push_back(point->getIthCoordinate(1)+r*intervalY+intervalY/2);
            double te=intervalX*intervalY*F->value(temp);
            total+=te;
        }
    }
    //std::cout<<total<<std::endl;
    return total;
    
   return 0;
}

    std::string RectangleN::toStringCoordBottomRight()
    {
        std::string temp="";
        for(int i=0;i<this->N;i++)
        {
            temp+=std::to_string(this->getithCoord(i)+this->dims[i]);
            if(i!=this->N-1)
            {
                temp+=+"\t";
            }
        }
        return temp;
    }


    std::string RectangleN::toStringCoordTopLeft()
    {
        std::string temp="";
        //std::cout<<"theeee n"<<this->getN()<<std::endl;
        for(int i=0;i<this->N;i++)
        {
            temp+=std::to_string(this->getithCoord(i));
            if(i!=this->N-1)
            {
                temp+=+"\t";
            }
        }
        return temp;
    }



int RectangleN::getN()
{
    return this->N;
}


Point* RectangleN::getMidPoint()
{
    std::vector<double> temp;
    for(int i=0;i<this->N;i++)
    {
        temp.push_back(this->getPoint()->getIthCoordinate(i)+(double)this->dims[i]/2);
    }
    return new Point(temp);
}