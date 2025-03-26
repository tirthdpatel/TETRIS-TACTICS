#include "tetrominoes.h"
#include<bits/stdc++.h>
using namespace std;

tetrominoes::tetrominoes() {
    current_shape = Shape();
    next_shape = Shape();
    while (k == next_k) {
        freeShape(next_shape);
        next_shape = Shape();
    }
    dir = 's';
}

tetrominoes::~tetrominoes() {
    freeShape(current_shape);
    freeShape(next_shape);
    for (auto s : shape) freeShape(s);
}

void tetrominoes::freeShape(node* shape) {
    while (shape) {
        node* temp = shape;
        shape = shape->next;
        delete temp;
    }
}

node*& tetrominoes::get_next_shape() {
    return next_shape;
}

node* tetrominoes::O() {
    node* head = new node();   
    head->p.X = 0;
    head->p.Y = 4;
    node* temp = new node();    
    temp->p.X = 0;
    temp->p.Y = 5;
    head->next = temp;
    node* temp2 = new node();   
    temp2->p.X = 1;
    temp2->p.Y = 4;
    temp->next = temp2;
    node* temp3 = new node();   
    temp3->p.X = 1;
    temp3->p.Y = 5;
    temp2->next = temp3;
    temp3->next = nullptr;
    return head;
}

node* tetrominoes::I() {
    node* head = new node();    
    head->p.X = 0;
    head->p.Y = 5;
    node* temp = new node();    
    temp->p.X = 1;
    temp->p.Y = 5;
    head->next = temp;
    node* temp2 = new node();   
    temp2->p.X = 2;
    temp2->p.Y = 5;
    temp->next = temp2;
    node* temp3 = new node();   
    temp3->p.X = 3;
    temp3->p.Y = 5;
    temp2->next = temp3;
    temp3->next = nullptr;
    return head;
}

node* tetrominoes::S() {
    node* head = new node();    
    head->p.X = 0;
    head->p.Y = 5;
    node* temp = new node();    
    temp->p.X = 0;
    temp->p.Y = 4;
    head->next = temp;
    node* temp2 = new node();   
    temp2->p.X = 1;
    temp2->p.Y = 5;
    temp->next = temp2;
    node* temp3 = new node();   
    temp3->p.X = 1;
    temp3->p.Y = 6;
    temp2->next = temp3;
    temp3->next = nullptr;
    return head;
}

node* tetrominoes::Z() {
    node* head = new node();    
    head->p.X = 0;
    head->p.Y = 5;
    node* temp = new node();    
    temp->p.X = 0;
    temp->p.Y = 6;
    head->next = temp;
    node* temp2 = new node();   
    temp2->p.X = 1;
    temp2->p.Y = 4;
    temp->next = temp2;
    node* temp3 = new node();   
    temp3->p.X = 1;
    temp3->p.Y = 5;
    temp2->next = temp3;
    temp3->next = nullptr;
    return head;
}

node* tetrominoes::L() {
    node* head = new node();    
    head->p.X = 0;
    head->p.Y = 5;
    node* temp = new node();    
    temp->p.X = 1;
    temp->p.Y = 5;
    head->next = temp;
    node* temp2 = new node();   
    temp2->p.X = 2;
    temp2->p.Y = 5;
    temp->next = temp2;
    node* temp3 = new node();   
    temp3->p.X = 2;
    temp3->p.Y = 6;
    temp2->next = temp3;
    temp3->next = nullptr;
    return head;
}

node* tetrominoes::J() {
    node* head = new node();    
    head->p.X = 0;
    head->p.Y = 5;
    node* temp = new node();    
    temp->p.X = 1;
    temp->p.Y = 5;
    head->next = temp;
    node* temp2 = new node();   
    temp2->p.X = 2;
    temp2->p.Y = 5;
    temp->next = temp2;
    node* temp3 = new node();   
    temp3->p.X = 2;
    temp3->p.Y = 4;
    temp2->next = temp3;
    temp3->next = nullptr;
    return head;
}

node* tetrominoes::T() {
    node* head = new node();    
    head->p.X = 0;
    head->p.Y = 5;
    node* temp = new node();    
    temp->p.X = 0;
    temp->p.Y = 4;
    head->next = temp;
    node* temp2 = new node();   
    temp2->p.X = 0;
    temp2->p.Y = 6;
    temp->next = temp2;
    node* temp3 = new node();   
    temp3->p.X = 1;
    temp3->p.Y = 5;
    temp2->next = temp3;
    temp3->next = nullptr;
    return head;
}

node* tetrominoes::Shape() {
    shape.clear();
    shape.push_back(O());
    shape.push_back(I());
    shape.push_back(S());
    shape.push_back(Z());
    shape.push_back(L());
    shape.push_back(J());
    shape.push_back(T());
    int index = rand() % 7; 
    node* newShape = shape[index];
    if (newShape == current_shape) k = index;
    else next_k = index;
    shape.clear();
    return newShape;
}

void tetrominoes::change_dir(char d) {
    dir = d;
}

bool tetrominoes::collision(const vector<vector<int>>& grid) {
    node* temp = current_shape;
    while (temp) {
        int nextX = temp->p.X + 1;
        int y = temp->p.Y;
        if (nextX >= LENGTH + 3 || y < 1 || y > WIDTH - 1) return true; 
        if (nextX >= 3 && grid[nextX - 3][y] == 1) return true;
        temp = temp->next;
    }
    return false;
}

void tetrominoes::move(const vector<vector<int>>& grid) {
    if (!current_shape) return;

    node* temp = current_shape;
    if (dir == 'd') { 
        while (temp) {
            if (temp->p.Y + 1 > WIDTH - 1 || 
                (temp->p.X >= 3 && grid[temp->p.X - 3][temp->p.Y + 1] == 1)) {
                dir = 's';
                return;
            }
            temp = temp->next;
        }
        temp = current_shape;
        while (temp) {
            temp->p.Y += 1;
            temp = temp->next;
        }
    } else if (dir == 'a') { 
        while (temp) {
            if (temp->p.Y - 1 < 1 || 
                (temp->p.X >= 3 && grid[temp->p.X - 3][temp->p.Y - 1] == 1)) {
                dir = 's';
                return;
            }
            temp = temp->next;
        }
        temp = current_shape;
        while (temp) {
            temp->p.Y -= 1;
            temp = temp->next;
        }
    } else if (dir == ' ') { 
        int dropDistance = LENGTH + 3;
        while (temp) {
            int maxDrop = LENGTH + 2 - temp->p.X;
            for (int y = temp->p.Y; y <= WIDTH - 1; y++) {
                for (int x = temp->p.X + 1; x <= LENGTH + 2; x++) {
                    if (x >= 3 && grid[x - 3][temp->p.Y] == 1) {
                        maxDrop = min(maxDrop, x - temp->p.X - 1);
                        break;
                    }
                }
            }
            dropDistance = min(dropDistance, maxDrop);
            temp = temp->next;
        }
        temp = current_shape;
        while (temp) {
            temp->p.X += dropDistance;
            temp = temp->next;
        }
    } else { 
        while (temp) {
            if (temp->p.X + 1 >= LENGTH + 3 || 
                (temp->p.X + 1 >= 3 && grid[temp->p.X + 1 - 3][temp->p.Y] == 1)) {
                return;
            }
            temp = temp->next;
        }
        temp = current_shape;
        while (temp) {
            temp->p.X += 1;
            temp = temp->next;
        }
    }
    dir = 's';
}

void tetrominoes::rotation(const vector<vector<int>>& grid) {
    if (!current_shape || !current_shape->next) return;

    node* pivot = current_shape;
    vector<node> old_positions;
    node* temp = current_shape;
    while (temp) {
        old_positions.push_back(*temp);
        temp = temp->next;
    }

    temp = current_shape->next;
    while (temp) {
        int dx = temp->p.Y - pivot->p.Y;
        int dy = -(temp->p.X - pivot->p.X);
        temp->p.X = pivot->p.X + dx;
        temp->p.Y = pivot->p.Y + dy;
        temp = temp->next;
    }

    temp = current_shape;
    while (temp) {
        if (temp->p.Y < 1 || temp->p.Y > WIDTH - 1 || temp->p.X >= LENGTH + 3 ||
            (temp->p.X >= 3 && grid[temp->p.X - 3][temp->p.Y] == 1)) {
            temp = current_shape;
            int i = 0;
            while (temp) {
                temp->p = old_positions[i++].p;
                temp = temp->next;
            }
            return;
        }
        temp = temp->next;
    }
}

node*& tetrominoes::get_current_shape() {
    return current_shape;
}

bool tetrominoes::canSpawn(const vector<vector<int>>& grid) {
    node* temp = current_shape;
    while (temp) {
        if (temp->p.Y < 1 || temp->p.Y > WIDTH - 1 ||
            (temp->p.X >= 3 && temp->p.X < LENGTH + 3 && 
             grid[temp->p.X - 3][temp->p.Y] == 1)) {
            return false;
        }
        temp = temp->next;
    }
    return true;
}