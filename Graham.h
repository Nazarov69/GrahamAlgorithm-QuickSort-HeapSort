#ifndef GRAHAM_SCAN_H
#define GRAHAM_SCAN_H

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include "Point.h"
#include "List.h"
#include "Stack.h"
#include<fstream>
#include<sstream>
#include "../AACA/AACA/Heap.h"
#define DEGREE 3

class graham {
    Point p0;
    List<Point> points;
    int get_min_y(List<Point>& points) {
        int index = 0;
        int min_x = points.get_value(index).get_x();
        int min_y = points.get_value(index).get_y();
        for (int i = 1; i < points.get_size_list(); i++) {
            if ((points.get_value(i).get_y() < min_y) ||
                (points.get_value(i).get_y() == min_y && points.get_value(i).get_x() < min_x)) {
                min_x = points.get_value(i).get_x();
                min_y = points.get_value(i).get_y();
                index = i;
            }
        }
        return index;
    }
    bool compare(const Point& p1, const Point& p2) {
        if (p0.orientation(p1, p2) == collinear) {
            return (p0.sq_distance(p1) < p0.sq_distance(p2));
        }
        return (p0.orientation(p1, p2) == left);
    }
public:
    graham() { points = List<Point>(); }
    void set_list(const List<Point>& list) { points = list; }
    void add_point(const Point& pt) { points.add(pt); }
    List<Point> quick_h() {
        int min_index_y = get_min_y(points);
        points.swap(0, min_index_y);
        p0 = points.get_value(0);
        sort(points.begin() + 1, points.end(), [&](const Point& p1, const Point& p2) {
            if (p0.orientation(p1, p2) == collinear) {
                return (p0.sq_distance(p1) < p0.sq_distance(p2));
            }
            return (p0.orientation(p1, p2) == left);
            });
        List<Point> lst;
        lst.add(points.get_value(0));
        for (int i = 1; i < points.get_size_list(); i++) {
            while (i < points.get_size_list() - 1 && p0.orientation(points.get_value(i), points.get_value(i + 1)) == collinear) {
                i++;
            }
            lst.add(points.get_value(i));
        }
        points.clear();
        points = lst;
        if (points.get_size_list() < 3) {
            printf("Convex hull doesn't exist!!\n");
            return 0;
        }
        Stack st;
        st.push(0);
        st.push(1);
        st.push(2);
        for (int i = 3; i < points.get_size_list(); i++) {
            while (points.get_value(st.next_to_top()).orientation(points.get_value(st.peek()), points.get_value(i)) != left) {
                st.pop();
            }
            st.push(i);
        }
        List<Point> hull(st.get_size_stack());
        while (!st.empty()) {
            hull.add(points.get_value(st.pop()));
        }
        hull.reverse();
        return hull;
    }

    void heap_sort(List<Point>& local_points) {
        for (int i = local_points.get_size_list() / DEGREE - 1; i >= 0; i--) {
            up(local_points, local_points.get_size_list(), i);
        }
        for (int i = points.get_size_list() - 1; i >= 0; i--){
            local_points.swap(0, i);
            up(local_points, i, 0);
        }
    }

    void up(List<Point>& local_points, int size, int i) {
        int parent = i;
        int first_child = i * DEGREE + 1;
        int last_child = min((i + 1) * DEGREE, size - 1);
        for (int j = first_child; j <= last_child; j++) {
            if (compare(local_points.get_value(j), local_points.get_value(parent))) {
                parent = j;
            }
        }
        if (i != parent) {
            local_points.swap(i, parent);
            up(local_points, size, parent);
        }
    }

 /*   void heap_sort(List<Point>& local_points) {
        int size = local_points.get_size_list();
        for (int i = size - 1; i >= 0; i--) {
            down(local_points, i);
        }
        while (size > 0) {
            local_points.swap(0, size - 1);
            size--;
            down(local_points, 0);
        }
    }
    void down(List<Point>& local_points, int i) {
        int min = min_child(local_points, i);
        while (min != 0 && compare(local_points.get_value(min), local_points.get_value(i))) {
            local_points.swap(i, min);
            i = min;
            min = min_child(local_points, i);
        }
    }
    int min_child(List<Point>& local_points, int i) {
        if (i * DEGREE + 1 > points.get_size_list() - 1) {
            return 0;
        }
        int first_child = i * DEGREE + 1;
        int last_child = min((i + 1) * DEGREE, local_points.get_size_list() - 1);
        int min_child = first_child;
        for (int ind = first_child + 1; ind <= last_child; ind++) {
            if (compare(local_points.get_value(ind),local_points.get_value(min_child))) {
                min_child = ind;
            }
        }
        return min_child;
    }*/
    List<Point> heap_h() {
        int min_index_y = get_min_y(points);
        points.swap(0, min_index_y);
        p0 = points.get_value(0);
        /*std::make_heap(points.begin() + 1, points.end(), [&](const Point& p1, const Point& p2) {
            if (points.get_value(0).orientation(p1, p2) == collinear) {
                return (points.get_value(0).sq_distance(p1) < points.get_value(0).sq_distance(p2));
            }
            return (points.get_value(0).orientation(p1, p2) == left);
            });
        std::sort_heap(points.begin() + 1, points.end(), [&](const Point& p1, const Point& p2) {
            if (points.get_value(0).orientation(p1, p2) == collinear) {
                return (points.get_value(0).sq_distance(p1) < points.get_value(0).sq_distance(p2));
            }
            return (points.get_value(0).orientation(p1, p2) == left);
            });*/ // binary heap
        heap_sort(points);
        points.reverse(); // descending heap

        List<Point> lst;
        lst.add(points.get_value(0));
        for (int i = 1; i < points.get_size_list(); i++) {
            while (i < points.get_size_list() - 1 && p0.orientation(points.get_value(i), points.get_value(i + 1)) == collinear) {
                i++;
            }
            lst.add(points.get_value(i));
        }
        points.clear();
        points = lst;
        if (points.get_size_list() < 3) {
            printf("Convex hull doesn't exist!!\n");
            return 0;
        }
        Stack st;
        st.push(0);
        st.push(1);
        st.push(2);
        for (int i = 3; i < points.get_size_list(); i++) {
            while (points.get_value(st.next_to_top()).orientation(points.get_value(st.peek()), points.get_value(i)) != left) {
                st.pop();
            }
            st.push(i);
        }
        List<Point> hull(st.get_size_stack());
        while (!st.empty()) {
            hull.add(points.get_value(st.pop()));
        }
        hull.reverse();
        return hull;
    }
};
#endif
