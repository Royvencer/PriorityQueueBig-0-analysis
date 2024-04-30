#pragma once

#ifndef MINPRIORITYQUEUE_H
#define MINPRIORITYQUEUE_H

#include <unordered_map>
#include <vector>
#include <utility> // Has pair and swap

using namespace std;

template <typename T>
class MinPriorityQueue
{
public:
    MinPriorityQueue() {}

    int size()
    {
        return H.size();
    }

    void push(T x, int p)
    {
        H.emplace_back(x, p);
        I[x] = H.size() - 1;
        bubble_up(H.size() - 1);
    }

    T front()
    {
        return H[0].first;
    }

    void pop()
    {
        if (H.empty())
            return;
        swap_nodes(0, H.size() - 1);
        I.erase(H.back().first);
        H.pop_back();
        if (!H.empty())
            bubble_down(0);
    }

    void decrease_key(T x, int new_p)
    {
        if (I.find(x) == I.end() || H[I[x]].second <= new_p)
            return;
        H[I[x]].second = new_p;
        bubble_up(I[x]);
    }

private:
    vector<pair<T, int>> H;     // The heap.
    unordered_map<T, int> I;    // Maps values to their indices in H.

    void bubble_up(int i)
    {
        while (i > 0 && H[parent(i)].second > H[i].second)
        {
            swap_nodes(i, parent(i));
            i = parent(i);
        }
    }

    void bubble_down(int i)
    {
        while (left_child(i) < H.size())
        {
            int min_child = left_child(i);
            if (right_child(i) < H.size() && H[right_child(i)].second < H[min_child].second)
                min_child = right_child(i);
            if (H[i].second <= H[min_child].second)
                break;
            swap_nodes(i, min_child);
            i = min_child;
        }
    }

    void swap_nodes(int i, int j)
    {
        swap(H[i], H[j]);
        I[H[i].first] = i;
        I[H[j].first] = j;
    }

    int parent(int i) { return (i - 1) / 2; }
    int left_child(int i) { return 2 * i + 1; }
    int right_child(int i) { return 2 * i + 2; }
};

#endif
