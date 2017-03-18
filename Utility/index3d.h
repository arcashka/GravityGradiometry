#ifndef INDEX3D_H
#define INDEX3D_H


class Index3D
{
private:
    int i, j ,k;
public:
    Index3D();
    Index3D(int i, int j, int k);

    // accessors
    int geti() { return i; }
    int getj() { return j; }
    int getk() { return k; }

    // mutators
    void seti(int i) { Index3D::i = i; }
    void setj(int j) { Index3D::j = j; }
    void setk(int k) { Index3D::k = k; }
};

Index3D::Index3D() {

}

Index3D::Index3D(int i, int j, int k) {
    Index3D::i = i;
    Index3D::j = j;
    Index3D::k = k;
}

#endif // INDEX3D_H
