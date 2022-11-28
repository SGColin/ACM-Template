 typedef double T;
typedef long double ld;

#define let  const auto
#define lett const T
#define letp const P // P for Point
#define lets const S // S for Segment
#define letl const L // L for Line
#define letc const C // C for Convex

const T eps = 1e-8;
const double PI = 3.1415926535897932384;
#define z(x) (abs((x)) <= eps) // is zero

const ld a90 = atan(1) * 2;
const ld a180 = a90 * 2, a270 = a90 * 3, a360 = a90 * 4;
const ld dlt[2][2] = {0, a180, a360, a180};

struct P {
    T x, y;
    P (T x = 0, T y = 0) : x(x), y(y) {}
    P operator + (letp &p) const {return {x + p.x, y + p.y};} 
    P operator - (letp &p) const {return {x - p.x, y - p.y};} 
    P operator * (lett &d) const {return {x * d, y * d};}
    P operator / (lett &d) const {return {x / d, y / d};}
    P operator - () const {return {-x, -y};}

    T operator | (letp &p) const {return x * p.x + y * p.y;} // dot
    T operator ^ (letp &p) const {return x * p.y - y * p.x;} // cross
    
    P rot(double ang) const { // counterclockwise rotation (ang) angle
        double cosa = cos(ang), sina = sin(ang);
        return {x * cosa - y * sina, x * sina + y * cosa};
    }
    P rot(double cosa, double sina) const { 
        return {x * cosa - y * sina, x * sina + y * cosa};
    }
    ld angle() const { // counterclockwise, start from (1, 0)
        if (fabs(x) < 1e-15) return a90 * (1 + 2 * (y < 0));
        else return atan(y / x) + dlt[y < 0][x < 0];
    }

    bool operator == (letp &p) const {return z(x - p.x) && z(y - p.y);}
    bool operator != (letp &p) const {return ! operator == (p);}
    bool operator < (letp &p) const {return z(x - p.x) ? y < p.y : x < p.x;}
    bool operator > (letp &p) const {return !(*this < p || *this == p);}
   
    // left(counterclockwise) = 1 | on = 0 | right(clockwise) = -1
    int ori(letp &p) const {T t = (*this) ^ p; return (t > eps) - (t < -eps);}

    T norm() const {return x * x + y * y;}
    T dis(letp &p) const {return sqrt(((*this) - p).norm());}
    P proj (letp &p) const {return (*this) * (((*this) | p) / norm());}
    P refl (letp &p) const {return proj(p) * 2 - p;}
} zero;

double abs(letp &p) {return sqrt(p.norm());}
P unit(letp &p) {return p / abs(p);}
P perp(letp &p) {return {-p.y, p.x};} // turn pi / 2 left(counterclockwise)
P perpr(letp &p) {return {p.y, -p.x};} // turn pi / 2 right(clockwise)

bool orth(letp &p, letp &q) {return z(p | q);} // orthogonal
bool para(letp &p, letp &q) {return z(p ^ q);} // parallel

struct argcmp { // compared by polar angle
    bool operator() (letp &a, letp &b) const {
        const auto quad = [](letp &a) {
            if (a.y < -eps) return 1; // halfplane with negative y
            if (a.y > eps) return 4;  // halfplane with positive y
            if (a.x < -eps) return 5; // negative x-axis
            if (a.x > eps) return 3;  // positive x-axis
            return 2; // origin
        };
        const int qa = quad(a), qb = quad(b);
        if (qa != qb) return qa < qb; 
        const auto t = (a ^ b); //in the same quad
        /* sorted by length in increasing order when parallel
        if (z(t)) return norm(a) < norm(b) - eps; */
        return t > eps;
    }    
};

struct L {
    P p, v;
    int ori (letp &a) const {return v.ori(a - p);} 
    P inter(letl &l) const {return p + v * ((l.v ^ (p - l.p)) / (v ^ l.v));} 
    L shift(letp &d) const {return {p + d, v};}
    L shiftl(double d) const {return {p + perp(v) * d / abs(v), v};}
    P proj(letp &a) const {return p + v.proj(a - p);}
    P refl(letp &a) const {return p + v.refl(a - p);} 
    double dis(letp &a) const {return abs(v ^ (a - p)) / abs(v);} 
};

bool orth(letl &p, letl &q) {return z(p.v | q.v);} // orthogonal
bool para(letl &p, letl &q) {return z(p.v ^ q.v);} // parallel


struct S {
    P a, b;

    // on endPs = -1 | out = 0 | in = 1
    int is_on(letp &p) const {
        if (p == a || p == b) return -1;
        return (p - a).ori(p - b) == 0 && ((p - a) | (p - b)) < -eps;
    }

    // inter on endPs = -1 | not inter = 0 | inter inside = 1
    int is_inter(letl &l) const {
        if (l.ori(a) == 0 || l.ori(b) == 0) return -1;
        return l.ori(a) != l.ori(b);
    }

    // inter on endPs = -1 | not inter = 0 | inter inside = 1
    int is_inter(lets &s) const {
        if (is_on(s.a) || is_on(s.b) || s.is_on(a) || s.is_on(b)) return -1;
        letl &l{a, b - a}, ls{s.a, s.b - s.a};
        return l.ori(s.a) * l.ori(s.b) == -1 && ls.ori(a) * ls.ori(b) == -1;
    }

    double dis(letp &p) const {
        if (((p - a) | (b - a)) < -eps || ((p - b) | (a - b)) < -eps) 
            return min(abs(a - p), abs(b - p));
        return L{a, b - a}.dis(p);
    }

    double dis(lets &s) const {
        if (is_inter(s)) return 0.0;
        return min({dis(s.a), dis(s.b), s.dis(a), s.dis(b)});
    }
};

struct Polygon {
    vector<P> p; // counterclockwise
    Polygon(const vector<P> p = {}) : p(p) {}
    size_t nxt(const size_t i) const {return i == p.size() - 1 ? 0 : i + 1;}
    size_t pre(const size_t i) const {return i == 0 ? p.size() - 1 : i - 1;}
    T double_area() const {
        T sum = 0;
        for (size_t i = 0; i < p.size(); ++i) sum += (p[i] ^ p[nxt(i)]);
        return abs(sum);
    }
    ld area() const {return double_area() / 2.0;}
    ld circ() const {
        ld sum = 0;
        for (size_t i = 0; i < p.size(); ++i) sum += abs(p[i] - p[nxt(i)]);
        return sum;
    }

    // pair<is_on_edge, winding number> , out = [winding number = 0]
    pair<bool,int> winding(letp &a) const {
        int cnt = 0;
        for (size_t i = 0; i < p.size(); ++i) {
            letp u = p[i], v = p[nxt(i)];
            if (z((a - u) ^ (a - v)) && ((a - u) | (a - v)) <= eps) return {true, 0};
            if (z(u.y - v.y)) continue;
            letl uv{u, v - u};
            if (u.y < v.y - eps && uv.ori(a) <= 0) continue;
            if (u.y > v.y + eps && uv.ori(a) >= 0) continue;
            if (u.y < a.y - eps && v.y >= a.y - eps) cnt++;
            if (u.y >= a.y - eps && v.y < a.y - eps) cnt--;
        }
        return {false, cnt};
    }

    bool is_convex() const {
        bool pos = false, neg = false;
        for (size_t i = 0; i < p.size(); ++i) {
            int o = (p[i] - p[pre(i)]).ori(p[nxt(i)] - p[i]);
            if (o == 1) pos = true;
            if (o == -1) neg = true;
        }
        return !(pos && neg);
    }
};

struct C : Polygon {
    C (const vector<P> &p = {}) : Polygon(p) {}
    C operator + (letc &c) const { // Minkowski Sum
        const auto &p = this -> p;
        vector<S> e1(p.size()), e2(c.p.size());
        vector<S> edge(p.size() + c.p.size());
        vector<P> res; res.reserve(p.size() + c.p.size());
        
        const auto cmp = [](lets &u, lets &v) {
            return argcmp()(u.b - u.a, v.b - v.a);
        };

        for (size_t i = 0; i < p.size(); ++i) e1[i] = {p[i], p[this -> nxt(i)]};
        for (size_t i = 0; i < c.p.size(); ++i) e2[i] = {c.p[i], c.p[c.nxt(i)]};
        rotate(e1.begin(), min_element(e1.begin(), e1.end(), cmp), e1.end());
        rotate(e2.begin(), min_element(e2.begin(), e2.end(), cmp), e2.end());
        merge(e1.begin(), e1.end(), e2.begin(), e2.end(), edge.begin(), cmp);

        const auto check = [](const vector<P> &res, letp &u) {
            const auto b1 = res.back(), b2 = *prev(res.end(), 2);
            return (b1 - b2).ori(u - b1) == 0 && ((b1 - b2) | (u - b1)) >= -eps;
        };
        
        auto u = e1[0].a + e2[0].a;
        for (const auto &v : edge) {
            while (res.size() > 1 && check(res, u)) res.pop_back();
            res.push_back(u); u = u + v.b - v.a;
        }
        if (res.size() > 1 && check(res, res[0])) res.pop_back();
        return {res};
    }

    // O(log n) : on = -1 | out = 0 | in = 1
    int is_in(letp &a) const {
        const auto &p = this -> p;
        if (p.size() == 1) return a == p[0] ? -1 : 0;
        if (p.size() == 2) return S{p[0], p[1]}.is_on(a) ? -1 : 0; 
        if (a == p[0]) return -1;
        if ((p[1] - p[0]).ori(a - p[0]) == -1) return 0;
        if ((p.back() - p[0]).ori(a - p[0]) == 1) return 0;
        let cmp = [&](letp &u, letp &v) {return (u - p[0]).ori(v - p[0]) == 1;};
        const size_t i = lower_bound(p.begin() + 1, p.end(), a, cmp) - p.begin();
        if (i == 1) return S{p[0], p[i]}.is_on(a) ? -1 : 0;
        if (i == p.size() - 1 && S{p[0], p[i]}.is_on(a)) return -1;
        if (S{p[i - 1], p[i]}.is_on(a)) return -1;
        return (p[i] - p[i - 1]).ori(a - p[i - 1]) > 0;
    }

    template<typename F> size_t extreme(const F &dir) const {
        let &p = this -> p;
        let check = [&](const size_t i) {return dir(p[i]).ori(p[nxt(i)] - p[i]) >= 0;};
        let dir0 = dir(p[0]); 
        let check0 = check(0);
        if (!check0 && check(p.size() - 1)) return 0;
        const auto cmp = [&](letp &v) {
            const size_t vi = &v - p.data();
            if (vi == 0) return 1;
            let checkv = check(vi);
            let t = dir0.ori(v - p[0]);
            if (vi == 1 && checkv == check0 && dir0.ori(v - p[0]) == 0) return 1;
            return checkv ^ (checkv == check0 && t <= 0);
        };
        return partition_point(p.begin(), p.end(), cmp) - p.begin();
    }

    pair<size_t,size_t> tangent(letp &a) const {
        const size_t i = extreme([&](letp &u){return u - a;});
        const size_t j = extreme([&](letp &u){return a - u;});
        return {i, j};
    }

    pair<size_t,size_t> tangent(letl &a) const {
        const size_t i = extreme([&](...){return a.v;});
        const size_t j = extreme([&](...){return -a.v;});
        return {i, j};
    }

};

C convexHull(vector<P> p) {
    vector<P> st;
    sort(p.begin(), p.end());
    const auto check = [](const vector<P> &st, letp &u) {
        const auto back1 = st.back(), back2 = *prev(st.end(), 2);
        return (back1 - back2).ori(u - back2) <= 0;
    };
    for (letp &u : p) {
        while (st.size() > 1 && check(st, u)) st.pop_back();
        st.push_back(u);
    }
    size_t k=st.size();
    p.pop_back(); reverse(p.begin(),p.end());
    for (letp &u : p) {
        while (st.size() > k && check(st, u)) st.pop_back();
        st.push_back(u);
    }
    st.pop_back();
    return {st};
}

vector<L> halfInter(vector<L> l, lett lim = 1e9) { // O(n log n)
    const auto check = [](letl &a, letl &b, letl &c) { return a.ori(b.inter(c)) < 0;};
    /* // no precision error, but the number will become x^3
    const auto check = [](letl &a, letl &b, letl &c) {
        letp t = (b.v ^ c.v);
        letp p = (a.v | t), q = (b.p | t) + (b.v | (c.v ^ (b.p - c.p))) - (a.p | t);
        return p.ori(q) < 0;
    }; */
    const auto cmp = [] (letl &a, letl &b) {
        if (abs(a.v ^ b.v) <= eps && (a.v | b.v) >= -eps) return a.ori(b.p) == -1;
        return argcmp()(a.v, b.v);
    };
    l.push_back({{-lim, 0}, {0, -1}}); l.push_back({{0, -lim}, {1, 0}});
    l.push_back({{lim, 0}, {0, 1}});   l.push_back({{0, lim}, {-1, 0}});
    sort(l.begin(), l.end(), cmp);
    deque<L> q;
    for (size_t i=0;i<l.size();i++) {
        if (i && l[i - 1].v.ori(l[i].v) == 0 && (l[i - 1].v | l[i].v) > eps) continue;
        while (q.size() > 1 && check(l[i], q.back(), q[q.size() - 2])) q.pop_back();
        while (q.size() > 1 && check(l[i], q[0], q[1])) q.pop_front();
        if (!q.empty() && q.back().v.ori(l[i].v) <= 0) return vector<L>();
        q.push_back(l[i]);
    }
    while (q.size() > 1 && check(q[0], q.back(), q[q.size() - 2])) q.pop_back();
    while (q.size() > 1 && check(q.back(), q[0], q[1])) q.pop_front();
    return vector<L>(q.begin(), q.end());
}

C halfInterConvex(vector<L> l, lett lim = 1e9) {
    l = halfInter(l, lim);
    if (l.size() <= 1) return vector<P>();
    vector<P> res; res.resize(l.size());
    for (size_t i = 0; i < l.size(); ++i) 
        res[i] = l[i].inter(l[i == l.size() - 1 ? 0 : i + 1]);
    return res;
}

struct Circle {
    P c; ld r;
    Circle(letp &c = zero, double r = 0.0) : c(c), r(r) {}
    Circle(letp &A = zero, letp &B = zero, letp &C = zero) {
        double x1 = A.x - B.x, y1 = A.y - B.y;
        double x2 = A.x - C.x, y2 = A.y - C.y;
        double e = ((A.x * A.x - B.x * B.x) - (B.y * B.y - A.y * A.y)) / 2.0;
        double f = ((A.x * A.x - C.x * C.x) - (C.y * C.y - A.y * A.y)) / 2.0; 
        c.x = (e * y2 - y1 * f) / (x1 * y2 - y1 * x2);
        c.y = (x1 * f - e * x2) / (x1 * y2 - y1 * x2);
        r = A.dis(c);
    }
    bool operator == (const Circle &a) const {return c == a.c && z(r - a.r);}
    ld circ() const {return 2 * PI * r;}  // 周长
    ld area() const {return PI * r * r;}  // 面积
    // 点与圆的关系 : -1 圆上 | 0 圆外 | 1 圆内
    int is_in(letp &p) const {ld d = p.dis(c); return z(d-r) ? -1 : d < r - eps;}
    // 直线与圆关系 : 0 相离 | 1 相切 | 2 相交
    int relation(letl &l) const {
        ld d = l.dis(c);
        return (z(d - r) ? 1 : (d > r + eps ? 0 : 2));
    }
    // 圆与圆关系 : -1 相同 | 0 相离 | 1 外切 | 2 相交 | 3 内切 | 4 内含
    int relation(const Circle &a) const {
        if (*this == a) return -1;
        ld d = c.dis(a.c);
        if (d > r + a.r + eps) return 0;
        if (z(d - r - a.r)) return 1;
        if (z(d - abs(r - a.r))) return 3;
        if (d < abs(r - a.r) - eps) return 4;
        return 2;
    }
    // 直线与圆的交点
    vector<P> inter(letl &l) const {
        const ld d = l.dis(c);
        const P p = l.proj(c);
        const int t = relation(l);
        if (t == 0) return vector<P>();
        if (t == 1) return vector<P>{p};
        const ld k = sqrt(r * r - d * d);
        return vector<P>{p - unit(l.v) * k, p + unit(l.v) * k};
    }
    // 圆与圆交点
    vector<P> inter(const Circle &a) const {
        const ld d = c.dis(a.c);
        const int t = relation(a);
        if (t == -1 || t == 0 || t == 4) return vector<P>();
        P e = a.c - c; e = unit(e) * r;
        if (t == 1 || t == 3) {
            if (r * r + d * d - a.r * a.r >= -eps) return vector<P>{c + e};
            return vector<P>{c - e};
        }
        const ld costh = (r * r + d * d - a.r * a.r) / (2 * r * d);
        const ld sinth = sqrt(1 - costh * costh);
        return vector<P>{c + e.rot(costh, -sinth), c + e.rot(costh, sinth)};
    }
    // 圆与圆交面积
    ld inter_area(const Circle &a) const {
        const ld d = c.dis(a.c);
        const int t = relation(a);
        if (t == -1) return area();
        if (t < 2) return 0;
        if (t > 2) return min(area(), a.area());
        const ld costh1 = (r * r + d * d - a.r * a.r) / (2 * r * d);
        const ld costh2 = (a.r * a.r + d * d - r * r) / (2 * a.r * d);
        const ld sinth1 = sqrt(1 - costh1 * costh1);
        const ld sinth2 = sqrt(1 - costh2 * costh2);
        const ld th1 = acos(costh1), th2 = acos(costh2);
        return r * r * (th1 - costh1 * sinth1) + a.r * a.r * (th2 - costh2 * sinth2);
    }
    // 过圆外一点圆的切线
    vector<L> tangent(const P &a) const {
        const int t = is_in(a);
        if (t == 1) return vector<L>();
        if (t == -1) {
            const P v = {-(a - c).y, (a - c).x};
            return vector<L>{{a, v}};
        }
        P e = a - c; e = unit(e) * r;
        const ld costh = r / c.dis(a);
        const ld sinth = sqrt(1 - costh * costh);
        const P t1 = c + e.rot(costh, -sinth);
        const P t2 = c + e.rot(costh, sinth);
        return vector<L>{{a, t1 - a}, {a, t2 - a}};
    }
    // 两圆的公切线
    vector<L> tangent(const Circle &a) const {
        const int t = relation(a);
        vector<L> Ls;
        if (t == -1 || t == 4) return Ls;
        if (t == 1 || t == 3) {
            const P p = inter(a)[0], v = {-(a.c - c).y, (a.c - c).x};
            Ls.push_back({p, v});
        }
        const ld d = c.dis(a.c);
        const P e = unit(a.c - c);
        if (t <= 2) {
            const ld costh = (r - a.r) / d;
            const ld sinth = sqrt(1 - costh * costh);
            const P d1 = e.rot(costh, -sinth), d2 = e.rot(costh, sinth);
            const P u1 = c + d1 * r, u2 = c + d2 * r;
            const P v1 = a.c + d1 * a.r, v2 = a.c + d2 * a.r;
            Ls.push_back({u1, v1 - u1}); 
            Ls.push_back({u2, v2 - u2});
        }
        if (t == 0) {
            const ld costh = (r + a.r) / d;
            const ld sinth = sqrt(1 - costh * costh);
            const P d1 = e.rot(costh, -sinth), d2 = e.rot(costh, sinth);
            const P u1 = c + d1 * r, u2 = c + d2 * r;
            const P v1 = a.c - d1 * a.r, v2 = a.c - d2 * a.r;
            Ls.push_back({u1, v1 - u1}); 
            Ls.push_back({u2, v2 - u2});
        }
        return Ls;
    }
};
