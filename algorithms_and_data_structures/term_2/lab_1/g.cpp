#include <bits/stdc++.h>

const int OFFSET = 200000;

struct X {
    int type;
    int coord;
    int y_up;
    int y_down;

    X() : type(0), coord(0), y_up(0), y_down(0) {}

    X(int coord, int type, int y_up, int y_down) : type(type), coord(coord), y_up(y_up), y_down(y_down) {}

    bool operator<(const X &a) const {
        if(coord == a.coord) {
            return type > a.type;
        }
        return coord < a.coord;
    }

    void set(int coord, int type, int y_up, int y_down) {
        this->type = type;
        this->coord = coord;
        this->y_up = y_up;
        this->y_down = y_down;
    }
};


class Segment_Tree {
    int *arr;
    int *add;
public:
    Segment_Tree() {
        add = new int[4 * 400001];
        arr = new int[4 * 400001];
        for (int i = 0; i < 4 * 400001; i++) {
            add[i] = arr[i] = 0;

        }
    }

    void push(int v, int vl, int vr) {
        if (add[v] != 0) {
            arr[v] += add[v];
            if (vl != vr) {
                add[2 * v + 1] += add[v];
                add[2 * v + 2] += add[v];
            }
            add[v] = 0;
        }
    }

    void modify(int v, int vl, int vr, int l, int r, int add) {
        push(v, vl, vr);
        if (r < vl || vr < l)
            return;
        if (l <= vl && vr <= r) {
            this->add[v] += add;
            push(v, vl, vr);
            return;
        }
        int vm = (vr + vl) / 2;
        modify(2 * v + 1, vl, vm, l, r, add);
        modify(2 * v + 2, vm + 1, vr, l, r, add);
        arr[v] = std::max(arr[2 * v + 1], arr[2 * v + 2]);
    }

    int find(int v, int vl, int vr, int max) {
        if (vl == vr)
            return vl - OFFSET;
        push(v, vl, vr);
        int vm = (vl + vr) / 2;
        if (arr[2 * v + 1] + add[2 * v + 1] == max) {
            return find(2 * v + 1, vl, vm, max);
        } else {
            return find(2 * v + 2, vm + 1, vr, max);
        }
    }

    int max(int v, int vl, int vr, int l, int r) {
        push(v, vl, vr);
        if (r < vl || vr < l) {
            return 0;
        }
        if (l <= vl && vr <= r) {
            return arr[v];
        }
        int vm = (vl + vr) / 2;
        return std::max(max(2 * v + 1, vl, vm, l, r), max(2 * v + 2, vm + 1, vr, l, r));
    }
};


int main() {
    int n, x_down, x_up, y_down, y_up;
    scanf("%d", &n);
    std::vector<X> arr(2 * n);
    for (int i = 0; i < 2 * n - 1; i += 2) {
        scanf("%d %d %d %d", &x_up, &y_up, &x_down, &y_down);
        arr[i].set(x_up, 1, y_up, y_down);
        arr[i + 1].set(x_down, -1, y_up, y_down);
    }
    std::sort(arr.begin(), arr.end());
    /*for (int i = 0; i < 2 * n ; i++) {
        printf("coord: %d (%d) \n", arr[i].coord, arr[i].type);
    }*/
    Segment_Tree s_tree;
    int max = 0, max_x, max_y;
    for (int i = 0; i < 2 * n; i++) {
        s_tree.modify(0, 0, 400000 , arr[i].y_up + OFFSET, arr[i].y_down + OFFSET, arr[i].type);
        if (max < s_tree.max(0, 0, 400000, 0, 400000 )) {
            max = s_tree.max(0, 0, 400000, 0, 400000 );
            max_x = arr[i].coord;
            max_y = s_tree.find(0, 0, 400000 , max);
        }
    }
    printf("%d\n%d %d", max, max_x, max_y);
    return 0;
}