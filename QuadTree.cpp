#include "QuadTree.h"

QuadTree::QuadTree(Rectangle *s)
{
    this->root = new Node(s);
}

Node *QuadTree::get(int index)
{
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
    int t1 = size(children[0]);
    int t2 = size(children[1]);
    int t3 = size(children[2]);
    int t4 = size(children[3]);

    return count + t1 + t2 + t3 + t4;
}
/*
    check for accuracy
    */
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
void QuadTree::traverseTree()
{
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

unordered_map<int, Node *> QuadTree::asMap(Node *n)
{
}
void QuadTree::draw()
{
}
void QuadTree::traverse(Node *node)
{
}

int QuadTree::thisSize()
{
    return QuadTree::size(this->getRoot());
}

Node *QuadTree::getRoot()
{
    return this->root;
}

void QuadTree::setRoot(Rectangle *s)
{
    this->root = new Node(s);
}

void QuadTree::divide(Function *F, Node *n, double tol)
{
    if(abs(n->getRekt()->integrate(F)-n->getRekt()->approx(F))>tol)
    {
        root->createChildren();
        vector<Node*> children=root->getChildren();
        divide(F, children[0], tol);
        divide(F, children[1], tol);
        divide(F, children[2], tol);
        divide(F, children[3], tol);

    }
    else
    {
        return;
    }
}

void QuadTree::divideTree(Function *F, double tol)
{
    QuadTree::divide(F,this->root,tol);
}

vector<Rectangle *> QuadTree::getOutBoxes(Node *n, Function *F, double cutoff)
{
    vector<Rectangle *> temp;
    if (n->isLeaf())
    {
        double integral = n->integrate(F);
        if (integral != -1)
        {
            if (integral > cutoff)
            {
                temp.push_back(n->getRekt());
                return temp;
            }
        }
    }
    vector<Node *> children = n->getChildren();
    vector<Rectangle *> r1 = getOutBoxes(children[0], F, cutoff);
    vector<Rectangle *> r2 = getOutBoxes(children[1], F, cutoff);
    vector<Rectangle *> r3 = getOutBoxes(children[2], F, cutoff);
    vector<Rectangle *> r4 = getOutBoxes(children[3], F, cutoff);
    temp.insert(temp.end(), r1.begin(), r1.end());
    temp.insert(temp.end(), r2.begin(), r2.end());
    temp.insert(temp.end(), r3.begin(), r3.end());
    temp.insert(temp.end(), r4.begin(), r4.end());
    return temp;
}
vector<Rectangle *> QuadTree::getInBoxes(Node *n, Function *F, double cutoff)
{
    vector<Rectangle *> temp;
    if (n->isLeaf())
    {
        double integral = n->integrate(F);
        if (integral != -1)
        {
            if (integral < -cutoff)
            {
                temp.push_back(n->getRekt());
                return temp;
            }
        }
    }
    vector<Node *> children = n->getChildren();
    vector<Rectangle *> r1 = getInBoxes(children[0], F, cutoff);
    vector<Rectangle *> r2 = getInBoxes(children[1], F, cutoff);
    vector<Rectangle *> r3 = getInBoxes(children[2], F, cutoff);
    vector<Rectangle *> r4 = getInBoxes(children[3], F, cutoff);
    temp.insert(temp.end(), r1.begin(), r1.end());
    temp.insert(temp.end(), r2.begin(), r2.end());
    temp.insert(temp.end(), r3.begin(), r3.end());
    temp.insert(temp.end(), r4.begin(), r4.end());
    return temp;
}

//first box is outbox second is in box
 twoVects *QuadTree::getAllBoxes(Node *n, Function *F, double cutoff)
{
    vector<Rectangle *> temp1;
    vector<Rectangle *> temp2;
    twoVects *temp=new twoVects(temp1, temp2);

    if (n->isLeaf())
    {
        double integral = n->integrate(F);
        if (integral != -1)
        {
            if (integral < -cutoff)
            {
                temp2.push_back(n->getRekt());
            }
            else
            {
                temp1.push_back(n->getRekt());
            }
        }
        temp->setV1(temp1);
        temp->setV2(temp2);
        return temp;
    }
    vector<Node *> children = n->getChildren();
    twoVects* r1 = getAllBoxes(children[0], F, cutoff);
    twoVects* r2 = getAllBoxes(children[1], F, cutoff);
    twoVects* r3 = getAllBoxes(children[2], F, cutoff);
    twoVects* r4 = getAllBoxes(children[3], F, cutoff);
    
    temp->append(r1);
    temp->append(r2);
    temp->append(r3);
    temp->append(r4);

    return temp;
}