#include "Forest.h"

Forest::Forest(vector<QuadTree*> forest, vector<Pointint*> points)
{
    this->forest=forest;
    this->coords=points;
}

Forest::Forest(vector<int> nboxAtDim, vector<double> minCoords, vector<double> maxCoords, int dim1, int dim2)
{
    this->N=nboxAtDim.size();
    this->minCoords=minCoords;
    this->maxCoords=maxCoords;
    this->nboxAtDim=nboxAtDim;
    for(int i=0;i<this->N;i++)
    {
        //interval
        double tot=maxCoords[i]-minCoords[i];
        //get the width of each box
        double width=tot/nboxAtDim[i];
        this->widths.push_back(width);
    }

    //total amount of boxes
    int totalNBoxes=1;
    for(int i=0;i<this->nboxAtDim.size();i++)
    {
        totalNBoxes*=nboxAtDim[i];
    }

    this->totalNBoxes=totalNBoxes;
    
//ordered as follows: (0,0,0...), (1,0,0...)....(n,0,0)...(0,1,0), (1,1,0)... (n,1,0)... etc.
    for(int i=0;i<totalNBoxes;i++)
    {
        vector<int> temp=getithCoordinate(i);
        this->coords.push_back(new Pointint(temp));
    }

    for(int i=0;i<this->coords.size();i++)
    {
        Point *tempp=new Point(getCoordi(this->coords[i]));
        
        RectangleN *temp = new RectangleN(tempp, this->N, this->widths);
        forest.push_back(new QuadTree(temp, minCoords, maxCoords, this->N, dim1, dim2));
    }
}

vector<int> Forest::getithCoordinate(int i)
{
    vector<int> index;
    //int product1=1;
    //int product2=1;
    for(int j=0;j<this->N;j++)
    {
        int product1=1;
        int product2=1;
        for(int z=0;z<=j;z++)
        {
            product1*=this->nboxAtDim[z];
            if(z!=j)
            {
                product2*=this->nboxAtDim[z];
            }
        }
        index.push_back((i%product1)/product2);
    }
    return index;
}

int Forest::index(int row, int col)
{
    //return row * this->cols + col;
    return 0;
}

/*
QuadTree *Forest::get(int r, int c)
{
    return this->forest[index(r, c)];
}
*/
/*
Point *Forest::getXYCoord(int r, int c)
{
    double x = Forest::getCoordX(c);
    double y = Forest::getCoordY(r);
    Point *temp = new Point(x, y);
    return temp;
}
*/
//first: which dimension, second: which coord in the dimension
double Forest::getCoordi(int i, int j)
{
    return (double)j * widths[i] + this->minCoords[i];
}

//returns the cartesian coordinates of the row, col coords 
vector<double> Forest::getCoordi(Pointint* point)
{
    vector<double> temp;

        for(int j=0;j<point->getDims();j++)
        {
            temp.push_back((double)point->getIthCoordinate(j) * widths[j] + this->minCoords[j]);
        }
    return temp;
}


/**
 * Divides the entire forest of trees according to the function F.
 **/
void Forest::divide(Function *F, double tol)
{

    for(int i=0;i<this->totalNBoxes;i++)
    {
        forest[i]->divideTree(F, tol, maximumLevel);
    }
}

/*
int Forest::numMinCols()
{
    return cols;
}

int Forest::numMinRows()
{
    return rows;
}
*/

//NOTE: IT RETURNS A POINT, BUT THE "POINT" CONTAINS INFORMATION ABOUT THE ROW AND COLUMN

/*
Point *Forest::getRC(double x, double y)
{
    return new Point(findC(x), findR(y));
}


int Forest::findC(double x)
{
    return binarySearchX(x, 0, cols);
}
int Forest::findR(double y)
{
    return binarySearchY(y, 0, rows);
}



bool Forest::inRangeY(double y, int r)
{
    return y >= Forest::getCoordY(r) - height && y <= Forest::getCoordY(r) ? true : false;
}

int Forest::inRangeX(double x, int c)
{
    if (x <= Forest::getCoordX(c) + width && x >= Forest::getCoordX(c))

    {
        return 0;
    }
    else if (x > Forest::getCoordX(c) + width)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}



int Forest::binarySearchX(double x, int lower, int upper)
{
    int mid = (lower / 2 + upper / 2);
    int temp = inRangeX(x, mid);
    switch (temp)
    {
    case 1:
    {
        return binarySearchX(x, mid + 1, upper);
    }
    case 0:
    {
        return mid;
    }
    case -1:
    {
        return binarySearchX(x, lower - 1, mid);
    }
    }
    return 0;
}

int Forest::binarySearchY(double y, int lower, int upper)
{
    int mid = (lower / 2 + upper / 2);
    int temp = inRangeY(y, mid);
    switch (temp)
    {
    case 1:
    {
        return binarySearchY(y, lower, mid);
    }
    case 0:
    {
        return mid;
    }
    case -1:
    {
        return binarySearchY(y, mid, upper);
    }
    }
    return 0;
}

*/

twoVects *Forest::getAllBoxes(Function *F, double cutoff)
{
    //inboxes
    vector<RectangleN *> v1;
    vector<RectangleN *> v2;
    // vector<double> v3;
    //vector<double> difArray=getDifArray(F, cutoff);
    twoVects *temp = new twoVects(v1, v2);

    //temp->v3=v3;

    for(int i=0;i<this->totalNBoxes;i++)
    {
            QuadTree *te = this->forest[i];
            twoVects *t = te->getAllBoxes(te->getRoot(), F, cutoff);
            temp->append(t);
    }
    return temp;
}

//get the lexographic coordinate from the (x,y,z...) coordinate
int Forest::getLexCoord(Pointint* coord)
{
    int temp=0;
    for(int i=0;i<this->N;i++)
    {
        int prod1=1;
        for(int j=i;i>0;i--)
        {
        prod1*=this->nboxAtDim[i];
        }
        temp+=prod1*coord->getIthCoordinate(i);
    }
    return temp;
}

/*
bool Forest::add(QuadTree *t, coords)
{
    if (r >= rows || r < 0 || c >= cols || c < 0 || forest[index(r, c)] != nullptr)
    {
        return false;
    }
    forest[index(r, c)] = t;
    return true;
}
*/

void Forest::appendOutboxesToFile(ofstream *file, double cutoff, Function *F)
{
    // *file << "{";
    twoVects *temp = getAllBoxes(F, cutoff);

    for (int i = 0; i < temp->v1.size(); i++)
    {
        if (i == temp->v1.size() - 1)
        {
            *file << temp->v1[i];
        }
        else
        {
            *file << temp->v1[i]->toStringCoord() + ", ";
            *file << "\n";
        }
    }
    // *file << "}";
    delete temp;
}

void Forest::appendInboxesToFile(ofstream *file, double cutoff, Function *F)
{
    //*file << "{";
    twoVects *temp = getAllBoxes(F, cutoff);

    for (int i = 0; i < temp->v2.size(); i++)
    {
        if (i == temp->v2.size() - 1)
        {
            *file << temp->v2[i];
        }
        else
        {
            *file << temp->v2[i]->toStringCoord();
            *file << "\n";
        }
    }
    //*file << "}";
    delete temp;
}

void Forest::draw(sf::RenderWindow *window, int dim1, int dim2)
{
    for (int i=0;i<this->totalNBoxes;i++)
    {
        std::vector<int> temp=getithCoordinate(i);
        bool te=true;
        for(int j=0;j<this->N;j++)
        {
            if(j!=dim1&&j!=dim2&&temp[j]!=this->nboxAtDim[j]/2)
            {
                te=false;
                break;
            }
        }
        if(te==true)
        {
         forest[i]->draw(window, dim1, dim2);
        }
    }
}

vector<QuadTree*> Forest::getForest()
{
    
    return this->forest;
    
}



void Forest::divideNthTimes(double minX, double maxX, double minY, double maxY, int level)
{
    for(int i=0;i<this->totalNBoxes;i++)
    {
        forest[i]->divideTreeNTimes(forest[i]->getRoot(), level);
    }
}

void Forest::divideComp(double tol, Function *F, int level, int dim1, int dim2)
{
    for(int i=0;i<this->totalNBoxes;i++)
    {
        //std::cout<<"he"<<i<<std::endl;
        this->forest[i]->divideCompMid(this->minCoords, this->maxCoords, forest[i]->getRoot(), F, tol, level, dim1, dim2);
    }
}
//v2 inboxes
//v1 outboxes
//file2 outboxes
//file inboxes
/**
     * first file is inboxes
     * second file is outboxes
     **/
void Forest::appendAllBoxesToTwoFiles(ofstream *file, ofstream *file2, double cutoff, Function *F)
{
    // *file << "{";
    twoVects *temp = getAllBoxes(F, cutoff);

    for (int i = 0; i < temp->v2.size(); i++)
    {
        if (i == temp->v2.size() - 1)
        {
            *file << temp->v2[i]->toStringCoord();
        }
        else
        {
            *file << temp->v2[i]->toStringCoord();
            *file << "\n";
        }
    }
    //*file << "}";

    //*file2 << "{";

    for (int i = 0; i < temp->v1.size(); i++)
    {
        if (i == temp->v1.size() - 1)
        {
            *file2 << temp->v1[i]->toStringCoord();
        }
        else
        {
            *file2 << temp->v1[i]->toStringCoord();
            *file2 << "\n";
        }
    }
    //*file2 << "}";
    delete temp;
}

vector<double> Forest::getDifArray(Function *F, double cutoff)
{
    vector<double> temp;
    for(int i=0;i<this->totalNBoxes;i++)
    {
        vector<double> temp2;
        QuadTree *te = forest[i];
        temp2 = te->getDifArray(te->getRoot(), F, cutoff);
        temp.insert(temp.end(), temp2.begin(), temp2.end());
    }
    return temp;
}

void Forest::appendDiffarrayToFile(ofstream *file, Function *F, double cutoff)
{
    vector<double> difArray = getDifArray(F, cutoff);
    for (int i = 0; i < difArray.size(); i++)
    {
        *file << difArray[i];
        *file << "\n";
    }
}

twoVectsDoub *Forest::getSupplyDemandAmt(Function *F, double cutoff)
{
    vector<double> temp = getDifArray(F, cutoff);
    //d1 supply, d2 demand
    vector<double> d1;
    vector<double> d2;
    for (int i = 0; i < temp.size(); i++)
    {
        if (temp[i] > 0)
        {
            d1.push_back(temp[i]);
        }
        else if (temp[i] < 0)
        {
            d2.push_back(temp[i]);
        }
    }
    twoVectsDoub *temp1 = new twoVectsDoub(d1, d2);
    return temp1;
}

/**
 * first file is supply, second is demand
 * */
void Forest::appendSuppDemandAmt(ofstream *file, ofstream *file2, Function *F, double cutoff)
{
    twoVectsDoub *temp = getSupplyDemandAmt(F, cutoff);
    for (int i = 0; i < temp->v1.size(); i++)
    {
        *file << temp->v1[i];
        *file << "\n";
    }
    for (int i = 0; i < temp->v2.size(); i++)
    {
        *file2 << temp->v2[i];
        *file2 << "\n";
    }
}

void Forest::appendAllFiles(ofstream *outboxes, ofstream *inboxes, ofstream *supply, ofstream *demand, Function *F, double cutoff)
{
    appendSuppDemandAmt(supply, demand, F, cutoff);
    appendAllBoxesToTwoFiles(inboxes, outboxes, cutoff, F);
}

void Forest::appendEverythingToTwoFiles(ofstream *outbox, ofstream *inbox, Function *F, double cutoff)
{
    tripleVect *temp = getAllRelevantVects(F, cutoff);
    vector<RectangleN *> outboxes = temp->rect->v1;
    vector<RectangleN *> inboxes = temp->rect->v2;
    vector<double> supply = temp->doub->v1;
    vector<double> demand = temp->doub->v2;

    int i = 0;
    for (int i = 0; i < inboxes.size(); i++)
    {
        *inbox << inboxes[i]->toStringCoord();
        *inbox << "\t";
        *inbox << demand[i];
        *inbox << "\n";
    }
    for (int i = 0; i < outboxes.size(); i++)
    {
        *outbox << outboxes[i]->toStringCoord();
        *outbox << "\t";
        *outbox << supply[i];
        *outbox << "\n";
    }
}

void Forest::appendEverythingToTwoFilesAcc(ofstream *outbox, ofstream *inbox, Function *F, double cutoff, int accuracy, int cutoffAcc)
{
    setprecision(15);
    tripleVect *temp = getAllRelevantVectsAcc(F, cutoff, accuracy, cutoffAcc);
    vector<RectangleN *> outboxes = temp->rect->v1;
    vector<RectangleN *> inboxes = temp->rect->v2;
    vector<double> supply = temp->doub->v1;
    vector<double> demand = temp->doub->v2;

    int i = 0;
    for (int i = 0; i < inboxes.size(); i++)
    {
        *inbox << inboxes[i]->toStringCoord();
        *inbox << "\t";
        *inbox << demand[i];
        *inbox << "\n";
    }
    for (int i = 0; i < outboxes.size(); i++)
    {
        *outbox << outboxes[i]->toStringCoord();
        *outbox << "\t";
        *outbox << supply[i];
        *outbox << "\n";
    }
}

tripleVect *Forest::getAllRelevantVects(Function *F, double cutoff)
{
    vector<RectangleN *> t1;
    vector<RectangleN *> t2;
    vector<double> t3;
    vector<double> t4;
    twoVects *temp1 = new twoVects(t1, t2);
    twoVectsDoub *temp2 = new twoVectsDoub(t3, t4);
    tripleVect *temp = new tripleVect(temp1, temp2);

    for(int i=0;i<this->totalNBoxes;i++)
    {
            QuadTree *a = forest[i];
            tripleVect *t = a->getAllRelevantVects(a->getRoot(), F, cutoff);
            temp->append(t);
    }

    return temp;
}

void Forest::normalize(Function *F)
{
    double value = 0;

    for(int i=0;i<this->totalNBoxes;i++)
    {
            value += forest[i]->normalize(forest[i]->getRoot(), F);
    }

    F->normalize(1 / value);
}

void Forest::divideCompAcc(double tol, Function *F, int level, int accuracy)
{
    for(int i=0;i<this->totalNBoxes;i++)
    {
        forest[i]->divideCompMidAcc(forest[i]->getRoot(), F, tol, level, accuracy);
    }
}

tripleVect *Forest::getAllRelevantVectsAcc(Function *F, double cutoff, int accuracy, int cutoffAcc)
{
    vector<RectangleN *> t1;
    vector<RectangleN *> t2;
    vector<double> t3;
    vector<double> t4;
    twoVects *temp1 = new twoVects(t1, t2);
    twoVectsDoub *temp2 = new twoVectsDoub(t3, t4);
    tripleVect *temp = new tripleVect(temp1, temp2);
    for(int i=0;i<this->totalNBoxes;i++)
    {
        QuadTree *a = forest[i];
        tripleVect *t = a->getAllRelevantVectsAcc(a->getRoot(), F, cutoff, accuracy, cutoffAcc);
        temp->append(t);
    }

    return temp;
}
void Forest::normalizeAcc(Function *F, int accuracy)
{
    double value = 0;
    for(int i=0;i<this->totalNBoxes;i++)
    {
        value += forest[i]->normalizeAcc(forest[i]->getRoot(), F, accuracy);
    }
    F->normalize(1 / value);
}

//check
double Forest::getScaledCutoff(double cutoff)
{

    double vol=1;
    for(int i=0;i<this->N;i++)
    {
        vol*=this->widths[i];
    }
    vector<double> intervals;
    for(int i=0;i<this->N;i++)
    {
        intervals.push_back(this->maxCoords[i]-this->minCoords[i]);
    }
    double areaComp =  1;

    for(int i=0;i<this->N;i++)
    {
        areaComp*=intervals[i]/20;
    }
    //double difx=this->rows-20;
    //double dify=this->rows-20;
    return cutoff / pow(areaComp / vol, this->N);
}

double Forest::getScaledCutOffMinSizeDif(int nboxes, double cutoff)
{
        std::cout << "in CUTOFF:" << cutoff << std::endl;
        std::cout << "NBOX:" << nboxes << std::endl;
        std::cout<<((nboxes/20)*(nboxes/20)) <<std::endl;
    std::cout << "THE CUTOFF:" << cutoff / ((((double)nboxes)/20)*(((double)nboxes)/20)) << std::endl;

    return cutoff / (((double)nboxes/20)*((double)nboxes/20));
}

void Forest::appendCoordsCellsToFiles(ofstream *coords, int PRECISION)
{
    vector<std::string> c=getAllCoords();
    for(int i=0;i<c.size();i++)
    {
        *coords<<setprecision(PRECISION)<<c[i];
        *coords<<"\t";
        if(i%2!=0)
        {
            *coords<<"\n";
        }
    }
}

vector<std::string> Forest::getAllCoords()
{
    vector<std::string> allCoords;
    int count=0;

    for(int i=0;i<this->totalNBoxes;i++)
    {
        QuadTree *a = forest[i];
        vector<std::string> temp=a->getStringCoordOfAllCells(a->getRoot());
            allCoords.insert(allCoords.end(), temp.begin(),temp.end());
            count++;
    }
     
    return allCoords;
}

int Forest::getNumLeaves()
{
    int sum=0;
    for(int i=0;i<this->totalNBoxes;i++)
    {
        sum+=this->forest[i]->getNumLeaves();
    }
    return sum;
}