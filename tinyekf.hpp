#include <stdlib.h>
#include <strings.h>

#define N 8
#define M 4

class TinyEKF {

    private:

        int n;
        int m;

        double * x;      // state

        double P[N][N];   // prediction error covariance
        double Q[N][N];   // process noise covariance
        double R[M][M];   // measurement error covariance

        double G[N][M];   // Kalman gain; a.k.a. K
        double F[N][N];   // Jacobian of process model
        double H[M][N];   // Jacobian of measurement model

        double Ht[N][M];  // transpose of measurement Jacobian
        double Ft[N][N];  // transpose of process Jacobian
        double Pp[N][N];  // P, post-prediction, pre-update

        double fx[N];     // f(x)
        double hx[N];     // h(x)

        // temporary storage
        double tmp1[N*N];
        double tmp2[M*N];
        double tmp3[M*M];
        double tmp4[M*M];
        double tmp5[M];

    protected:

        TinyEKF(int n, int m);

        ~TinyEKF();

        virtual void f(double x[N], double fx[N], double F[N][N]) = 0;

        virtual void h(double fx[N], double hx[N], double H[M][N]) = 0;    

    public:

        void setP(int i, int j, double value);

        void setQ(int i, int j, double value);

        void setR(int i, int j, double value);

        void setX(int i, double value);

        double getX(int i);

        void step(double * Z);
};
