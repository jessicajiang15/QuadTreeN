#include "Node.h"
//Node of a tree, .cpp
Node::Node(RectangleN *s)
{
    this->orientation=0;
    this->square = s;
    Node::allNullESq();
    level = 0;
    this->hasChildren=false;
    this->N=this->square->getN();
    this->numChildren=pow(2, N);
}

Node::Node(Point *corner, Node *parent, std::vector<double> widths, int orientation, int level, int N)
{
    RectangleN *temp = new RectangleN(corner, N, widths);
    this->square = temp;
    this->orientation=orientation;
    this->level = level;
    this->hasChildren=false;
    this->numChildren=pow(2, N);
    this->N=N;
}

bool Node::isLeaf()
{
    return !hasChildren;
}

Node *Node::getParent()
{
    return p;
}

void Node::createChildren()
{
    //double x, double y, Node *parent, vector<Node *> siblings, double width, double height

    for(int i=0;i<this->numChildren;i++)
    {
        std::vector<double> temp;
        std::vector<double> lengths;
        for(int j=0;j<this->N;j++)
        {
            double coord=this->square->getPoint()->getIthCoordinate(j);
            temp.push_back(i&pow(2,j)==1?coord+this->square->getithInterval(j)/2: coord);
            lengths[j]=this->square->getithInterval(j)/2;
        }
        Point* corner=new Point(temp);
        children[i]=new Node(corner, this, lengths, 1, this->level + 1, this->N);
    }
    this->square = nullptr;
    this->hasChildren=true;
}

vector<Node *> Node::getChildren()
{
    return children;
}

int Node::getRelativeOrientation()
{
    return this->orientation;
}

void Node::allNullESq()
{
    this->p = nullptr;
    for(int i=0;i<this->N;i++)
    {
        this->children[i]=nullptr;
    }
}


double Node::integrate(Function *F)
{
    if (square == nullptr)
    {
        return -1;
    }
    return square->integrate(F);
}

RectangleN *Node::getRekt()
{
    return square;
}

int Node::getLevel()
{
    return level;
}

vector<Node*> Node::createFakeChildren()
{
    std::vector<Node*> temp1;
    for(int i=0;i<this->numChildren;i++)
    {
        //creating one child
        std::vector<double> temp;
        std::vector<double> lengths;
        for(int j=0;j<this->N;j++)
        {
            double coord=this->square->getPoint()->getIthCoordinate(j);
            //i is the 0000 0001 etc
            //2^j is 0001 0010
            int t=(i&(int)pow(2,j))>>j;
            temp.push_back((t==1)?coord+this->square->getithInterval(j)/2: coord);
            lengths.push_back(this->square->getithInterval(j)/2);
        }
        Point* corner=new Point(temp);
        Node* tee=new Node(corner, this, lengths, i, this->level + 1, this->N);
        temp1.push_back(tee);
    }
    return temp1;
}

//    void createChildren(vector<Node*> children);
void Node::createChildren(vector<Node*> children)
{
    this->children=children;
    this->hasChildren=true;
    this->square=nullptr;
}

bool Node::hasChildrenf()
{
    return this->hasChildren;
}
int Node::getNumLeaves(Node* temp, int i)
{
    if(temp->isLeaf())
    {
        return 1;
    }
    else
    {
        int sum=0;
        for(int i=0;i<this->getChildren().size();i++)
        {
            sum+=getNumLeaves(this->getChildren()[i], i);
        }
        return sum;
    }
}