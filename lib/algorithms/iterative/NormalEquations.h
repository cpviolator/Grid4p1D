#ifndef GRID_NORMAL_EQUATIONS_H
#define GRID_NORMAL_EQUATIONS_H

namespace Grid {

  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  // Take a matrix and form a Red Black solver calling a Herm solver
  // Use of RB info prevents making SchurRedBlackSolve conform to standard interface
  ///////////////////////////////////////////////////////////////////////////////////////////////////////
  template<class Field> class NormalEquations : public OperatorFunction<Field>{
  private:
    SparseMatrixBase<Field> & _Matrix;
    OperatorFunction<Field> & _HermitianSolver;

  public:

    /////////////////////////////////////////////////////
    // Wrap the usual normal equations Schur trick
    /////////////////////////////////////////////////////
  NormalEquations(SparseMatrixBase<Field> &Matrix, OperatorFunction<Field> &HermitianSolver) 
    :  _Matrix(Matrix), _HermitianSolver(HermitianSolver) {}; 

    void operator() (const Field &in, Field &out){
 
      Field src(in._grid);

      _Matrix.Mdag(in,src);
      _HermitianSolver(src,out);  // Mdag M out = Mdag in
 
    }     
  };

}
#endif
