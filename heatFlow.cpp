#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

// Definition Domain of mesh(m)
constexpr double domainX = 0.40;
constexpr double domainY = 0.60;

// Defintion Delta X/Y (m)
constexpr double deltaX = 0.01;
constexpr double deltaY = 0.01;

// Definition Delta T (sec)
constexpr double deltaT = 1.0 / 30.0;

// Definition Heat Source Cercle Range (m)
constexpr double r = 0.10;

// Definition Mesh Size
constexpr int sizeX = (int)(domainX / deltaX);
constexpr int sizeY = (int)(domainY / deltaY);
constexpr int centerX = sizeX / 2;
constexpr int centerY = sizeY / 2;

// Definition Square function
constexpr double square(double x) {
  return x * x;
}

// Definition Dirichlet Condition area(773K or 0)
constexpr double dirichlet(int x, int y) {
  return square((centerX - x) * deltaX) + square((centerY - y) * deltaY) <= r*r ? 773.0 : 0;
};

// Definition Thermal Diffusivity as kappa m^2/sec
constexpr double kappa = 12.4e-6;
constexpr double lambdaX(double x) {
  return x * kappa * deltaT / deltaX / deltaX;
}
constexpr double lambdaY(double y) {
  return y * kappa * deltaT / deltaY / deltaY;
}

class Mesh {
  private:
    std::vector<std::vector<double>> meshTable;
  
  public:
    Mesh();
    Mesh(Mesh* m);
    int iter;
    static double eval(int x, int y);
    static double eval(int x, int y, Mesh* m);
    double get(int x, int y);
    ~Mesh();
};

double Mesh::eval(int x, int y) {
  double dirich = dirichlet(x, y);
  return dirich ? dirich : 300.0;
}

double Mesh::eval(int x, int y, Mesh* m){
  double dirich = dirichlet(x, y);
  if(dirich) {
    return dirich;
  } else if(x == 0) {
    return m->get(x+1,y);
  } else if(x == sizeX - 1) {
    return m->get(x-1,y);
  } else if(y == 0) {
    return m->get(x,y+1);
  } else if(y == sizeY - 1) {
    return m->get(x,y-1);
  } else {
    double ret = m->get(x,y) +
          lambdaX(m->get(x-1,y) + m->get(x+1,y) - 2*m->get(x,y)) +
          lambdaY(m->get(x,y-1) + m->get(x,y+1) - 2*m->get(x,y));
    return ret;
  }
}

Mesh::Mesh() {
  iter = 0;
  meshTable = std::vector<std::vector<double>>(sizeY, std::vector<double>(sizeX, 300.0));

  std::stringstream filename;
  filename << "./dat/" << iter << ".mesh.dat";

  std::ofstream ofs(filename.str());

  for (int i = 0; i < sizeY; i++) {
    for (int j = 0; j < sizeX; j++) {
      meshTable[i][j] = Mesh::eval(j,i);
      ofs << j << " " << i << " " << std::to_string(meshTable[i][j]) << std::endl;
    }
    ofs << std::endl;
  }
  ofs.close();
}

Mesh::Mesh(Mesh* m) {
  iter = 1 + m->iter;

  std::stringstream filename;
  filename << "./dat/" << iter << ".mesh.dat";

  std::ofstream ofs(filename.str());

  meshTable = std::vector<std::vector<double>>(sizeY, std::vector<double>(sizeX, 300.0));
  for (int i = 0; i < sizeY; i++) {
    for (int j = 0; j < sizeX; j++) {
      meshTable[i][j] = Mesh::eval(j,i, m);
      ofs << j << " " << i << " " << std::to_string(meshTable[i][j]) << std::endl;
    }
    ofs << std::endl;
  }
  ofs.close();
}

Mesh::~Mesh() {
}

double Mesh::get(int x, int y) {
  return meshTable[y][x];
}

int main(int argc, char const* argv[])
{
  Mesh* m = new Mesh();
  for (int i = 0; i < (1000 / deltaT) - 1; i++) {
    Mesh* _m = new Mesh(m);
    delete m;
    m = _m;
  }
  return 0;
}
