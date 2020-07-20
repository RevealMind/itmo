#include <iostream>
#include <vector>

class Segment_tree {
private:
    static const int SIZE = (4 * 1000000 + 1);
    std::pair<long long, long long> *arr;
    char *flag;// n , l, r ,b
    int *update;

    void union_tree(int v, int v1, int v2) {
        switch (flag[v1]) {
            case 'n':
                switch (flag[v2]) {
                    case 'n':
                        flag[v] = 'n';
                        break;
                    case 'l':
                        flag[v] = 'n';
                        break;
                    case 'r':
                        flag[v] = 'r';
                        break;
                    case 'b':
                        flag[v] = 'r';
                        break;
                }
                arr[v].first = arr[v1].first + arr[v2].first;
                break;
            case 'l':
                switch (flag[v2]) {
                    case 'n':
                        flag[v] = 'l';
                        break;
                    case 'l':
                        flag[v] = 'l';
                        break;
                    case 'r':
                        flag[v] = 'b';
                        break;
                    case 'b':
                        flag[v] = 'b';
                        break;
                }
                arr[v].first = arr[v1].first + arr[v2].first;
                break;
            case 'r':
                switch (flag[v2]) {
                    case 'n':
                        flag[v] = 'n';
                        arr[v].first = arr[v1].first + arr[v2].first;
                        break;
                    case 'l':
                        flag[v] = 'n';
                        arr[v].first = arr[v1].first + arr[v2].first - 1;
                        break;
                    case 'r':
                        flag[v] = 'r';
                        arr[v].first = arr[v1].first + arr[v2].first;
                        break;
                    case 'b':
                        flag[v] = 'r';
                        arr[v].first = arr[v1].first + arr[v2].first - 1;
                        break;
                }
                break;
            case 'b':
                switch (flag[v2]) {
                    case 'n':
                        flag[v] = 'l';
                        arr[v].first = arr[v1].first + arr[v2].first;
                        break;
                    case 'l':
                        flag[v] = 'l';
                        arr[v].first = arr[v1].first + arr[v2].first - 1;
                        break;
                    case 'r':
                        flag[v] = 'b';
                        arr[v].first = arr[v1].first + arr[v2].first;
                        break;
                    case 'b':
                        flag[v] = 'b';
                        arr[v].first = arr[v1].first + arr[v2].first - 1;
                        break;
                }
                break;
        }
        arr[v].second = arr[v1].second + arr[v2].second;
        return;
    }

    void push(int v, int vl, int vr) {
        if (update[v] != -1) {
            switch (update[v]) {
                case 0:
                    arr[v].first = arr[v].second = 0;
                    flag[v] = 'n';
                    break;
                case 1:
                    arr[v].first = 1;
                    arr[v].second = vr - vl + 1;
                    flag[v] = 'b';
                    break;
            }
            if (vr != vl) {
                update[2 * v + 1] = update[v];
                update[2 * v + 2] = update[v];
            }
            update[v] = -1;
        }
    }

public:
    Segment_tree() {
        flag = new char[SIZE];
        update = new int[SIZE];
        arr = new std::pair<long long, long long>[SIZE];

        for (int i = 0; i < SIZE; i++) {
            flag[i] = 'n';
            arr[i].first = arr[i].second = 0;
            update[i] = -1;
        }
    }

    void paint(int v, int vl, int vr, int l, int r, char col) {
        push(v, vl, vr);
        if (r < vl || vr < l)
            return;
        if (l <= vl && vr <= r) {
            update[v] = col != 'W';
            push(v, vl, vr);
            return;
        }
        int vm = (vl + vr) / 2;
        paint(2 * v + 1, vl, vm, l, r, col);
        paint(2 * v + 2, vm + 1, vr, l, r, col);
        union_tree(v, 2 * v + 1, 2 * v + 2);
    }

    long long get_first() {
        return arr[0].first;
    }

    long long get_second() {
        return arr[0].second;
    }
};

int main() {
    freopen("painter.in", "r", stdin);
    freopen("painter.out", "w", stdout);
    Segment_tree s_tree;
    int n, x, l;
    char col;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> col >> x >> l;
        s_tree.paint(0, 0, 1000000 - 1, 500000 + x, 500000 + x + l - 1, col);
        std::cout << s_tree.get_first() << " " << s_tree.get_second() << "\n";
    }
    return 0;
}