#pragma once
#include "line1.h"
#include "line2.h"
#include <random>
#include <functional>
#include <ctime>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class body {
public:
    body(double neck_x, double neck_y, double seg_length);

    void seg_rotate();
    void seg_rotate(int index);
    void rotate(int steps, void (*method_ptr)(body*) = nullptr);
    void print(int highlight);

    shared_ptr<point> neck_ptr, back_ptr;
    unique_ptr<base_line> segs[6];

    friend void print(body* ptr);
    friend void save(body* ptr);
    friend class object;

private:
    random_device seeder;
    mt19937 engine;
    uniform_int_distribution<int> choose_seg;
    uniform_real_distribution<double> choose_ang;

    void save(ofstream& file);
};

void print(body* ptr);
void save(body* ptr);
