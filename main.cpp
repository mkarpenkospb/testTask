#include "triangle.hpp"

#include <iostream>
#include <cassert>


using namespace figures;
using namespace std;

void test_third() {
    {
        point p1(1,1);
        point p2(2,3);
        point p3 = third(p1,p2);
        assert(dblEq(dist(p1,p3), dist(p2,p3), 0.0001) && "Wrong point");
        assert(dblEq(dist(p1,p3), dist(p1,p2), 0.0001) && "Wrong point");
        cout << "Test 1 passed." << endl;
    }

    {
        point p1(1,1);
        point p2(1,2);
        point p3 = third(p1,p2);
        assert(dblEq(dist(p1,p3), dist(p2,p3), 0.0001) && "Wrong point");
        assert(dblEq(dist(p1,p3), dist(p1,p2), 0.0001) && "Wrong point");
        cout << "Test 2 passed." << endl;
    }

    {
        point p1(1,1);
        point p2(2,1);
        point p3 = third(p1,p2);
        assert(dblEq(dist(p1,p3), dist(p2,p3), 0.0001) && "Wrong point");
        assert(dblEq(dist(p1,p3), dist(p1,p2), 0.0001) && "Wrong point");
        cout << "Test 3 passed." << endl;
    }
}

void simple_case () {
    point p1(1,1);
    point p2(2,2);
    point p3 = third(p1,p2);
    triangle t(p1,p2,p3);
    vector<line> res = cutWall(t, 1);
    vector<line> ans = {line(point(0.9797799427, 1.686886724), point(1.686886724, 0.9797799427)),
                        line(point(1.639045555, 1.415248676), point(2.604971381, 1.674067721)),
                        line(point(1.781274080, 0.2730201510), point(2.040093125, 1.238945977))};
    assert(res == ans && "Wrong cut");
    cout << "Test 4 passed." << endl;
}

void almost_max() {
    point p1(1,1);
    point p2(2,2);
    point p3 = third(p1,p2);
    triangle t(p1,p2,p3);
    vector<line> res = cutWall(t, maxL(p1, p2) - 0.001);
    vector<line> ans = {line(point(0.7563366175, 1.910330049), point(1.910330049, 0.7563366175)),
                        line(point(1.333816296, 1.333462743), point(2.910200640, 1.755853655)),
                        line(point(1.699488147, -0.03220910754), point(2.121879058, 1.544175236))};
    assert(res == ans && "Wrong cut");
    cout << "Test 5 passed." << endl;
}

void test_max() {
    point p1(1,1);
    point p2(2,2);
    point p3 = third(p1,p2);
    triangle t(p1,p2,p3);
    vector<line> res = cutWall(t, maxL(p1, p2) + 0.0001);
    vector<line> ans = {};
    assert(res == ans && "Wrong cut");
    cout << "Test 6 passed." << endl;
}

void test_x1_eq_x2() {
    point p1(1,1);
    point p2(1,3);
    point p3 = third(p1,p2);
    triangle t(p1,p2,p3);
    vector<line> res = cutWall(t, maxL(p1, p2) - 0.3);
    vector<line> ans = {line(point(-0.004700538379, 1.666666667), point(2.004700538, 1.666666667)),
                        line(point(1.075000000, 1.796570477), point(2.079700538, 3.536762856)),
                        line(point(1.652350269, 2.536762856), point(2.657050808, 0.7965704772))};
    assert(res == ans && "Wrong cut");
    cout << "Test 7 passed." << endl;
}

void test_y1_eq_y2() {
    point p1(3,1);
    point p2(1,1);
    point p3 = third(p1,p2);
    triangle t(p1,p2,p3);
    vector<line> res = cutWall(t, maxL(p1, p2) - 0.8);
    vector<line> ans = {line(point(0.6797434948, 1.954700538), point(1.986923172, 1.200000000)),
                        line(point(1.679743495, 1.777350269), point(2.986923172, 2.532050808)),
                        line(point(2.333333333, 1.754700538), point(2.333333333, 0.2452994616))};
    assert(res == ans && "Wrong cut");
    cout << "Test 8 passed." << endl;
}


int main() {
    test_third();
    simple_case();
    almost_max();
    test_max();
    test_x1_eq_x2();
    test_y1_eq_y2();
    return 0;
}
