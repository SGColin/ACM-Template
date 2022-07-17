const ld a90 = atan(1) * 2;
const ld a180 = a90 * 2, a270 = a90 * 3, a360 = a90 * 4;
const ld dlt[2][2] = {0, a180, a360, a180};
struct vec {
    ld x, y;
    vec (ld _x = 0, ld _y = 0){x = _x; y = _y;}
    vec operator + (const vec &b) const {return (vec){x + b.x, y + b.y};} 
    vec operator - (const vec &b) const {return (vec){x - b.x, y - b.y};} 
    vec operator * (const ld &k) const {return (vec){x * k, y * k};}
    ld dot (const vec &b) const {return x * b.x + y * b.y;} 
    ld cross (const vec &b) const {return x * b.y - y * b.x;}
    ld norm () const {return x * x + y * y;}
    ld len () const {return sqrt(norm());}
    ld dis (const vec &b) const {return ((*this) - b).len();}
    ld dis2 (const vec &b) const {return ((*this) - b).norm();}    
    ld angle() const { // 与 x 正半轴夹角，逆时针旋转
        if (fabs(x) < 1e-15) return a90 * (1 + 2 * (y < 0));
        else return atan(y / x) + dlt[y < 0][x < 0];
    }
    vec turn (const ld &ang) { // 逆时针旋转 ang 角度
        ld cosa = cos(ang), sina = sin(ang);
        return (vec){x * cosa - y * sina, x * sina + y * cosa};
    }
    vec proj (const vec &b) {return (*this) * (dot(b) / this -> norm());}
    vec refl (const vec &b) {return proj(b) * 2 - b;} //对称
    //找最下的点里，最靠左的，把其他点控制在一二象限和x正半轴
    bool up() const {return (y > 0 || (y == 0 && x > 0));}
    bool operator < (const vec &b) const{
        return y == b.y ? x < b.x : y < b.y;
    }
};