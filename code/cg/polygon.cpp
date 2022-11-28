#define nxt(x) ((x + 1) >= n ? x + 1 - n : x + 1)
struct polygon {    
    vector<vec> s;
    polygon () {s.clear();}
    ld circ () const { // 多边形的周长
        if (s.size() <= 1) return 0.0;
        ld ans = 0.0;
        for (int i = 0, n = s.size(); i < n; ++i) 
            ans += s[i].dis(s[nxt(i)]);
        return ans;
    }
    ld area () const { // 多边形的面积
        if (s.size() <= 1) return 0.0;
        ld ans = 0.0;
        for (int i = 0, n = s.size(); i < n; ++i)
            ans += s[i].cross(s[nxt(i)]);
        return ans / 2;
    }
    void polar_angle_sort_origin() { // 关于原点极角排序
        auto cmp = [&](const vec &a, const vec &b) {
            if (a.up() != b.up()) return a.up() > b.up(); 
            ld d = a.cross(b); // 叉积判断方向
            return d == 0 ? a.norm() < b.norm() : d > 0;
        };
        sort(s.begin(), s.end(), cmp);
    }
    void polar_angle_sort() { // 极角排序
        auto cmp = [&](const vec &a, const vec &b) {
            double d = (a - s[0]).cross(b - s[0]);
            return d == 0 ? a.dis2(s[0]) < b.dis2(s[0]) : d > 0;
        };
        for (int i = 1, n = s.size(); i < n; ++i)
            if (s[i] < s[0]) swap(s[0], s[i]);
        sort(s.begin() + 1, s.end(), cmp); // 注意不要把 s[0] 排进去
    }
    void convex_hull () { // 求凸包
        if (s.size() <= 1) return;
        polar_angle_sort(); // 先进行极角排序
        vector<vec> t; t.clear(); swap(s, t); 
        s.push_back(t[0]); s.push_back(t[1]); 
        for (int top = 1, i = 2, n = t.size(); i < n; ++i) {
            while ((s[top] - s[top - 1]).cross(t[i] - s[top - 1]) <= 0) {
                s.pop_back(); if ((--top) < 1) break;
            }
            s.push_back(t[i]); ++top;
        }
    }
    void convex_hull_maxcnt() { // 上下凸壳合并版写法
        auto cmp = [&](const vec &a, const vec &b) {
            return a.y == b.y ? a.x < b.x : a.y < b.y;
        };
        sort(s.begin(), s.end(), cmp);
        vector<vec> t; t.clear(); swap(s, t);
        s.push_back(t[0]); s.push_back(t[1]);
        int top = 1;
        for (int i = 2, n = t.size(); i < n; ++i) { // 保留最多的点
            while ((s[top] - s[top - 1]).cross(t[i] - s[top - 1]) < 0) {
                s.pop_back(); if ((--top) < 1) break;
            }
            s.push_back(t[i]); ++top;
        }
        int lim = top;
        for (int i = t.size() - 2; i >= 0; --i) {
            while ((s[top] - s[top - 1]).cross(t[i] - s[top - 1]) < 0) {
                s.pop_back(); if ((--top) < lim) break;
            }
            s.push_back(t[i]); ++top;
        }
        s.pop_back();
    }
    ld convex_diam () const { // 凸包的直径
        if (s.size() <= 1) return 0.0;
        ld ans = 0;
        for (int i = 0, ptr = 1, n = s.size(); i < n; ++i) {
            while (s[i].dis(s[ptr]) <= s[i].dis(s[nxt(ptr)])) 
                ptr = nxt(ptr);
            ans = max(ans, s[i].dis(s[ptr]));
        }
        return ans;
    }
};