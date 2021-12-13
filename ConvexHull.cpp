#include<iostream>
#include "List.h"
#include "Point.h"
#include "Graham.h"
#include <random>

int main() {
    graham quick_hull, heap_hull;
    time_t time1, time2, time3, time4;
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_real_distribution<> urd(-1000, 1000);
    List<Point> points;
    List<Point> cop;
    Point pt;
    for (int i = 0; i < SIZE; i++) {
        pt.set_x(urd(gen));
        pt.set_y(urd(gen));
        points.add(pt);
        cop.add(pt);
    }
    quick_hull.set_list(points);
    time1 = clock();
    List<Point> quick = quick_hull.quick_h();
    time2 = clock();
    quick.print(); printf("\n");
    printf("quick time : %d\n\n", time2 - time1);
    heap_hull.set_list(cop);
    time3 = clock();
    List<Point> heap = heap_hull.heap_h();
    time4 = clock();
    heap.print(); printf("\n");
    printf("heap time : %d\n\n", time4 - time3);
}
