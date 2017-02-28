// Auther: Huan Wang
// This is a tree implementation designed for this game only. Incable of making this a general purpose tree for my own use.

#pragma once

#include<vector>

using namespace std;

class tree {
public:
    tree();
    ~tree();

    void destory_parents_and_relatives();

    // data
    tree *parent;
    vector<tree*> children;
};

