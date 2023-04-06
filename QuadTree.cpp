#include "QuadTree.h"
//A quad tree

QuadTree::QuadTree(RectangleN *s, std::vector<double> mins, std::vector<double> maxes, int N, int dim1, int dim2)
{
    this->root = new Node(s);
    double minX=mins[0];
    double minY=mins[1];
    double maxX=maxes[0];
    double maxY=maxes[1];
    root->getRekt()->createSfRectFromCartesian(minX, maxX, minY, maxY, dim1, dim2);
    this->N=N;
}
QuadTree::QuadTree()
{
    root = nullptr;
}
int QuadTree::size(Node *n)
{
    int count = 1;
    if (n->isLeaf())
    {
        return 1;
    }
    vector<Node *> children;
    children = n->getChildren();
    int temp=0;
    for(int i =0;i<this->N; i++)
    {
        temp+=size(children[i]);
    }

    return count + temp;
}
/*
    check for accuracy
    */
   //unused
   /*
vector<Node *> QuadTree::getNodes(Node *n)
{
    vector<Node *> temp;
    if (n->isLeaf())
    {
        return temp;
    }
    else
    {
        temp.push_back(n);
    }

    vector<Node *> children;
    children = n->getChildren();
    vector<Node *> t1 = asVector(children[0]);
    vector<Node *> t2 = asVector(children[1]);
    vector<Node *> t3 = asVector(children[2]);
    vector<Node *> t4 = asVector(children[3]);

    temp.insert(temp.end(), t1.begin(), t1.end());
    temp.insert(temp.end(), t2.begin(), t2.end());
    temp.insert(temp.end(), t3.begin(), t3.end());
    temp.insert(temp.end(), t4.begin(), t4.end());

    return temp;
}

vector<Node *> QuadTree::getLeaves(Node *n)
{
    vector<Node *> temp;
    if (n->isLeaf())
    {
        temp.push_back(n);
        return temp;
    }

    vector<Node *> children;
    children = n->getChildren();
    vector<Node *> t1 = asVector(children[0]);
    vector<Node *> t2 = asVector(children[1]);
    vector<Node *> t3 = asVector(children[2]);
    vector<Node *> t4 = asVector(children[3]);

    temp.insert(temp.end(), t1.begin(), t1.end());
    temp.insert(temp.end(), t2.begin(), t2.end());
    temp.insert(temp.end(), t3.begin(), t3.end());
    temp.insert(temp.end(), t4.begin(), t4.end());

    return temp;
}

vector<Node *> QuadTree::asVector(Node *n)
{
    vector<Node *> temp;
    temp.push_back(n);
    if (n->isLeaf())
    {
        return temp;
    }

    vector<Node *> children;
    children = n->getChildren();
    vector<Node *> t1 = asVector(children[0]);
    vector<Node *> t2 = asVector(children[1]);
    vector<Node *> t3 = asVector(children[2]);
    vector<Node *> t4 = asVector(children[3]);

    temp.insert(temp.end(), t1.begin(), t1.end());
    temp.insert(temp.end(), t2.begin(), t2.end());
    temp.insert(temp.end(), t3.begin(), t3.end());
    temp.insert(temp.end(), t4.begin(), t4.end());

    return temp;
}
*/

int QuadTree::thisSize()
{
    return QuadTree::size(this->getRoot());
}

Node *QuadTree::getRoot()
{
    return this->root;
}

void QuadTree::setRoot(RectangleN *s)
{
    this->root = new Node(s);
}

void QuadTree::divide(Function *F, Node *n, double tol, int maximumLevel)
{
    if (abs(n->getRekt()->integrate(F) - n->getRekt()->approx(F)) > tol && n->getLevel() <= maximumLevel)
    {
        n->createChildren();
        vector<Node *> children = n->getChildren();
        for(int i=0;i<children.size();i++)
        {
        divide(F, children[i], tol, maximumLevel);
        }
    }
    else
    {
       // n->getRekt()->createSfRectFromCartesian(minX, maxX, minY, maxY);
        return;
    }
}

void QuadTree::divideTree(Function *F, double tol, int maximumLevel)
{
    QuadTree::divide(F, this->root, tol, maximumLevel);
}

vector<RectangleN *> QuadTree::getOutBoxes(Node *n, Function *F, double cutoff)
{
    vector<RectangleN *> temp;
    if (n->isLeaf())
    {
        double integral = n->integrate(F);
        if (integral != -1)
        {
            if (integral > scaleCutoff(cutoff, n->getLevel()))
            {
                temp.push_back(n->getRekt());
                return temp;
            }
        }
    }
    for(int i=0;i<n->getChildren().size();i++)
    {
        vector<RectangleN *> r1 = getOutBoxes(n->getChildren()[i], F, cutoff);
        temp.insert(temp.end(), r1.begin(), r1.end());
    }
    return temp;
}
vector<RectangleN *> QuadTree::getInBoxes(Node *n, Function *F, double cutoff)
{
    vector<RectangleN *> temp;
    if (n->isLeaf())
    {
        double integral = n->integrate(F);
        if (integral != -1)
        {
            if (integral < -scaleCutoff(cutoff, n->getLevel()))
            {
                temp.push_back(n->getRekt());
                return temp;
            }
        }
    }
    for(int i=0;i<n->getChildren().size();i++)
    {
        vector<RectangleN *> r1 = getInBoxes(n->getChildren()[i], F, cutoff);
        temp.insert(temp.end(), r1.begin(), r1.end());
    }
    return temp;
}

//first box is outbox second is in box
twoVects *QuadTree::getAllBoxes(Node *n, Function *F, double cutoff)
{
    vector<RectangleN *> temp1;
    vector<RectangleN *> temp2;
    twoVects *temp = new twoVects(temp1, temp2);

    if (n->isLeaf())
    {
        double integral = n->getRekt()->approx(F);
        if (integral < -scaleCutoff(cutoff, n->getLevel()))
        {
            //inboxes
            temp2.push_back(n->getRekt());
        }
        else if (integral > scaleCutoff(cutoff, n->getLevel()))
        {
            //outboxes
            temp1.push_back(n->getRekt());
        }
        temp->setV1(temp1);
        temp->setV2(temp2);
        return temp;
    }
    vector<Node *> children = n->getChildren();

    for(int i=0;i<children.size();i++)
    {
    twoVects *r1 = getAllBoxes(children[i], F, cutoff);
    temp->append(r1);
    }
    return temp;
}

void QuadTree::draw(sf::RenderWindow *window, int dim1, int dim2)
{
    QuadTree::drawRoot(root, window, dim1, dim2);
}

void QuadTree::drawRoot(Node *n, sf::RenderWindow *window, int dim1, int dim2)
{
    if (n->isLeaf())
    {
        n->getRekt()->draw(window, dim1, dim2);
        return;
    }
    else
    {
        vector<Node *> children = n->getChildren();
        for(int i=0;i<children.size();i++)
        {
        drawRoot(children[i], window, dim1, dim2);
        }
    }
}

// F, tol, level
void QuadTree::divideTreeNTimes(Node *n, int level)
{
    if (level == 0)
    {
        //n->getRekt()->createSfRectFromCartesian(mins, maxes);
        return;
    }
    else
    {
        n->createChildren();
        vector<Node *> children = n->getChildren();
        //for(int i=0;i<children.size();i++)
        {
        //children[i]->getRekt()->createSfRectFromCartesian(mins, maxes);
        }
        
        for(int i=0;i<children.size();i++)
        {
        divideTreeNTimes(children[i], level - 1);
        }
    }
}

//main division function
//dim1 and dim2 are drawing dimensions
void QuadTree::divideCompMid(std::vector<double> mins, std::vector<double> maxes, Node *n, Function *F, double tol, int maximumLevel, int dim1, int dim2)
{
    vector<Node *> fakeChildren = n->createFakeChildren();
    double sum=0;
    for(int i=0;i<fakeChildren.size();i++)
    {
        sum+=abs(fakeChildren[i]->getRekt()->approx(F));
    }
    double temp=fakeChildren[0]->getRekt()->approx(F);
    if (abs(sum-abs(n->getRekt()->approx(F))) > tol && n->getLevel() < maximumLevel)
    {
        //std::cout<<"dividing"<<std::endl;
        n->createChildren(fakeChildren);
        vector<Node *> children = n->getChildren();
        for(int i=0;i<children.size();i++)
        {
        divideCompMid(mins, maxes, children[i], F, tol, maximumLevel, dim1, dim2);
        }
    }
    else
    {
        n->getRekt()->createSfRectFromCartesian(mins[0], maxes[0], mins[0], maxes[0], dim1, dim2);
        if(temp<-0.00001/pow(4,n->getLevel()))
        {
            n->getRekt()->setColor("inbox");
        }
        else if(temp>0.00001/pow(4,n->getLevel()))
        {
            n->getRekt()->setColor("outbox");
        }
        return;
    }
}

double QuadTree::scaleCutoff(double cutoff, int level)
{
    return cutoff / pow(this->N, level);
}

vector<double> QuadTree::getDifArray(Node *n, Function *F, double cutoff)
{
    vector<double> temp;
    if (n->isLeaf())
    {
        double integral = n->getRekt()->approx(F);
        if (abs(integral) > abs(scaleCutoff(cutoff, n->getLevel())))
            temp.push_back(integral);
        return temp;
    }
    else
    {
        vector<Node *> children = n->getChildren();
        for(int i=0;i<children.size();i++)
        {
        vector<double> r1 = getDifArray(children[i], F, cutoff);
        temp.insert(temp.end(), r1.begin(), r1.end());
        }
    }
    return temp;
}
tripleVect *QuadTree::getAllRelevantVects(Node *n, Function *F, double cutoff)
{
    vector<RectangleN *> temp1;
    vector<RectangleN *> temp2;

    vector<double> supply;
    vector<double> demand;
    twoVects *t1 = new twoVects(temp1, temp2);
    twoVectsDoub *t2 = new twoVectsDoub(supply, demand);
    tripleVect *temp = new tripleVect(t1, t2);
    if (n->isLeaf())
    {
        double integral = n->getRekt()->approx(F);
        if (integral < -abs(scaleCutoff(cutoff, n->getLevel())))
        {
            //inboxes
            //std::cout<<"inbox"<<std::endl;
            t1->v2.push_back(n->getRekt());
            n->getRekt()->setColor("inbox");
            //demand
            t2->v2.push_back(integral);
        }
        else if (integral > scaleCutoff(cutoff, n->getLevel()))
        {
            //outboxes
            t1->v1.push_back(n->getRekt());
            //supply
            n->getRekt()->setColor("outbox");
            t2->v1.push_back(integral);
        }
        temp->setDoub(t2);
        temp->setRect(t1);
        return temp;
    }
    vector<Node *> children = n->getChildren();
    for(int i=0;i<children.size();i++)
    {
    tripleVect *r1 = getAllRelevantVects(children[i], F, cutoff);
    temp->append(r1);
    }

    return temp;
}

double QuadTree::normalize(Node *n, Function *F)
{
    double temp = 0;
    if (n->isLeaf())
    {
        temp += n->getRekt()->approx(F);
    }
    else
    {
        vector<Node *> children = n->getChildren();
        for(int i=0;i<children.size();i++)
        {
        double t1 = normalize(children[0], F);
        temp += t1;
        }
    }
    return temp;
}

void QuadTree::divideCompMidAcc(Node *n, Function *F, double tol, int maximumLevel, int accuracy)
{
    vector<Node *> fakeChildren = n->createFakeChildren();
    if (abs(fakeChildren[0]->getRekt()->approx(F) - n->getRekt()->approx(F)) > tol)
    {
        n->createChildren(fakeChildren);
        for(int i=0;i<fakeChildren.size();i++)
        {
        divideCompMidAcc(fakeChildren[i], F, tol, maximumLevel, accuracy);
        }
    }
    else
    {
        //n->getRekt()->createSfRectFromCartesian(minX, maxX, minY, maxY);
        return;
    }
}

tripleVect *QuadTree::getAllRelevantVectsAcc(Node *n, Function *F, double cutoff, int accuracy, int cutoffAcc)
{
    vector<RectangleN *> temp1;
    vector<RectangleN *> temp2;

    vector<double> supply;
    vector<double> demand;
    twoVects *t1 = new twoVects(temp1, temp2);
    twoVectsDoub *t2 = new twoVectsDoub(supply, demand);
    tripleVect *temp = new tripleVect(t1, t2);
    if (n->isLeaf())
    {
        double integral = n->getRekt()->getAccurateApprox(F, cutoffAcc);
        if (integral < -(scaleCutoff(cutoff, n->getLevel())))
        {
            integral = n->getRekt()->getAccurateApprox(F, accuracy);
            // cout<<"inbox: "<<integral<<endl;
            //inboxes
            t1->v2.push_back(n->getRekt());
            //demand
            //std::cout<<"inbox"<<std::endl;
            n->getRekt()->setColor("inbox");
            t2->v2.push_back(integral);
        }
        else if (integral > scaleCutoff(cutoff, n->getLevel()))
        {
            integral = n->getRekt()->getAccurateApprox(F, accuracy);
            // cout<<"outbox: "<<integral<<endl;
            //outboxes
            t1->v1.push_back(n->getRekt());
            //supply
            n->getRekt()->setColor("outbox");
            t2->v1.push_back(integral);
        }
        temp->setDoub(t2);
        temp->setRect(t1);
        return temp;
    }
    vector<Node *> children = n->getChildren();

    for(int i=0;i<children.size();i++)
    {
    tripleVect *r1 = getAllRelevantVectsAcc(children[i], F, cutoff, accuracy, cutoffAcc);
    temp->append(r1);
    }

    return temp;
}

double QuadTree::normalizeAcc(Node *n, Function *F, int accuracy)
{
    double temp = 0;
    if (n->isLeaf())
    {
        temp += n->getRekt()->getAccurateApprox(F, accuracy);
    }
    else
    {
        vector<Node *> children = n->getChildren();
        double t1 = normalizeAcc(children[0], F, accuracy);
        double t2 = normalizeAcc(children[0], F, accuracy);
        double t3 = normalizeAcc(children[0], F, accuracy);
        double t4 = normalizeAcc(children[0], F, accuracy);
        temp += t1;
        temp += t2;
        temp += t3;
        temp += t4;
    }
    return temp;
}

/*
tripleVect *QuadTree::getAllRelevantVectsGaussQuad(Node *n, Function *F, double cutoff, int MAX_ITERATIONS, GaussianQuadrature *gaussQuad)
{
    vector<RectangleN *> temp1;
    vector<RectangleN *> temp2;

    vector<double> supply;
    vector<double> demand;
    twoVects *t1 = new twoVects(temp1, temp2);
    twoVectsDoub *t2 = new twoVectsDoub(supply, demand);
    tripleVect *temp = new tripleVect(t1, t2);
    if (n->isLeaf())
    {

        double integral = n->getRekt()->integralGaussApprox(MAX_ITERATIONS, F, gaussQuad);
        //cout << "integral: " << integral << endl;
        if (integral < -(scaleCutoff(cutoff, n->getLevel())))
        {
            t1->v2.push_back(n->getRekt());
            n->getRekt()->setColor("inbox");
            t2->v2.push_back(integral);
        }
        else if (integral > scaleCutoff(cutoff, n->getLevel()))
        {
            t1->v1.push_back(n->getRekt());
            n->getRekt()->setColor("outbox");
            t2->v1.push_back(integral);
        }
        temp->setDoub(t2);
        temp->setRect(t1);
        return temp;
    }
    vector<Node *> children = n->getChildren();
    for(int i=0;i<children.size();i++)
    {
    tripleVect *r1 = getAllRelevantVectsGaussQuad(children[i], F, cutoff, MAX_ITERATIONS, gaussQuad);
    temp->append(r1);
    }

    return temp;
}
*/

vector<std::string> QuadTree::getStringCoordOfAllCells(Node *n)
{
    vector<std::string> temp;
    if (n->isLeaf())
    {
        temp.push_back(n->getRekt()->toStringCoordTopLeft());

        temp.push_back(n->getRekt()->toStringCoordBottomRight());
        return temp;
    }
    vector<Node *> children = n->getChildren();

    for(int i=0;i<children.size();i++)
    {
        vector<std::string> r1 = getStringCoordOfAllCells(children[i]);
        temp.insert(temp.end(), r1.begin(), r1.end());
    }
    return temp;
    /*

void twoVectsDoub::appendToV1(std::vector<double> t)
{
    v1.insert(v1.end(), t.begin(), t.end());
}
    */
}

int QuadTree::getNumLeaves()
{
    return this->root->getNumLeaves(this->root, 0);
}