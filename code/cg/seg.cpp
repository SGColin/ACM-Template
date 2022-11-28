struct seg {
    vec p1, p2;
    vec proj(const vec &b) {return p1 + (p2 - p1).proj(b - p1);}
    vec refl(const vec &b) {return p1 + (p2 - p1).refl(b - p1);}
    bool cross(const seg &b) const{ // 判断两线段是否相交
        ld w1 = (p2 - p1).cross(b.p1 - p1);
        ld w2 = (p2 - p1).cross(b.p2 - p1);
        ld w3 = (b.p2 - b.p1).cross(p1 - b.p1);
        ld w4 = (b.p2 - b.p1).cross(p2 - b.p1);
        if (w1 * w2 > 0 || w3 * w4 > 0) return 0;
        if (w1 * w2 < 0 || w3 * w4 < 0) return 1;
        ld v1 = (b.p1 - p1).dot(b.p1 - p2);
        ld v2 = (b.p2 - p1).dot(b.p2 - p2);
        ld v3 = (p1 - b.p1).dot(p1 - b.p2);
        ld v4 = (p2 - b.p1).dot(p2 - b.p2);
        return (v1 <= 0 || v2 <= 0 || v3 <= 0 || v4 <= 0);
    }
    vec cross_point(const seg &b) const { // 相交且不平行的情况下求交点
        vec v = p2 - p1, u1 = b.p1 - p1, u2 = b.p2 - p1;
        ld s1 = fabs(v.cross(u1)) / 2, s2 = fabs(v.cross(u2)) / 2;
        return p1 + u1 * (s2 / (s1 + s2)) + u2 * (s1 / (s1 + s2));
    }
    ld dis(const vec &b) const { // 点到线段距离
        if ((p2 - p1).dot(b - p1) < 0 || (p1 - p2).dot(b - p2) < 0)
            return min(p1.dis(b), p2.dis(b)); // 垂足不在线段上
        return fabs((p2 - p1).cross(b - p1)) / (p2 - p1).len(); 
    }
    ld dis(const seg &b) const { // 线段到线段距离
        if (cross(b)) return 0.0;
        return min(min(dis(b.p1), dis(b.p2)), min(b.dis(p1), b.dis(p2)));
    }
};