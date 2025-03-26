#ifndef TETROMINOES_H
#define TETROMINOES_H
#include <windows.h>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

#define LENGTH 20
#define WIDTH 10

struct node {
    COORD p;
    node* next;
    node() {
        this->p.X = 0;
        this->p.Y = 4;
        next = nullptr;
    }
};

class tetrominoes {
private:
    vector<node*> shape;
    node* current_shape;
    char dir;
    
    public:
    node* next_shape;
    int k;
    int next_k;
    tetrominoes();
    ~tetrominoes();
    vector<string> v={"🟥","🟧","🟨","🟩","🟦","🟪","🟫"};
    node* O();
    node* I();
    node* S();
    node* Z();
    node* L();
    node* J();
    node* T();
    node* Shape();
    void change_dir(char d);
    void move(const vector<vector<int>>& grid);
    bool collision(const vector<vector<int>>& grid);
    void rotation(const vector<vector<int>>& grid);
    node*& get_current_shape();
    node*& get_next_shape();
    bool canSpawn(const vector<vector<int>>& grid);
    void freeShape(node* shape);
};

#endif