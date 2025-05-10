// Matrix
//
const int m = 100; // size of matrix
 
struct Matrix{ 
  int mat[m][m];

  Matrix(){
    memset(mat, 0, sizeof mat);
  }
 
  Matrix operator * (const Matrix &p){
    Matrix ans;
    for(int i = 0; i < m; i++){
      for(int j = 0; j < m; j++){
        for(int k = 0; k < m; k++){
          ans.mat[i][k] = (ans.mat[i][k] + (mat[i][j] * p.mat[j][k])%mod)%mod;
        }
      }
    }
    return ans;
  }
};