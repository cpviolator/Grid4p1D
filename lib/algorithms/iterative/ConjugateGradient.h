#ifndef GRID_CONJUGATE_GRADIENT_H
#define GRID_CONJUGATE_GRADIENT_H

namespace Grid {

    /////////////////////////////////////////////////////////////
    // Base classes for iterative processes based on operators
    // single input vec, single output vec.
    /////////////////////////////////////////////////////////////

  template<class Field> 
    class ConjugateGradient :  public OperatorFunction<Field> {
public:                                                
    RealD   Tolerance;
    Integer MaxIterations;

    ConjugateGradient(RealD tol,Integer maxit) : Tolerance(tol), MaxIterations(maxit) { 
      std::cout << Tolerance<<std::endl;
    };

    void operator() (HermitianOperatorBase<Field> &Linop,const Field &src, Field &psi){

      RealD cp,c,a,d,b,ssq,qq,b_pred;
      
      Field   p(src);
      Field mmp(src);
      Field   r(src);
      
      //Initial residual computation & set up
      RealD guess = norm2(psi);
      
      Linop.OpAndNorm(psi,mmp,d,b);
      
      r= src-mmp;
      p= r;
      
      a  =norm2(p);
      cp =a;
      ssq=norm2(src);
      
      std::cout <<std::setprecision(4)<< "ConjugateGradient: guess "<<guess<<std::endl;
      std::cout <<std::setprecision(4)<< "ConjugateGradient:   src "<<ssq  <<std::endl;
      std::cout <<std::setprecision(4)<< "ConjugateGradient:    mp "<<d    <<std::endl;
      std::cout <<std::setprecision(4)<< "ConjugateGradient:   mmp "<<b    <<std::endl;
      std::cout <<std::setprecision(4)<< "ConjugateGradient:     r "<<cp   <<std::endl;
      std::cout <<std::setprecision(4)<< "ConjugateGradient:     p "<<a    <<std::endl;
      
      RealD rsq =  Tolerance* Tolerance*ssq;
      
      //Check if guess is really REALLY good :)
      if ( cp <= rsq ) {
	return;
      }
      
      std::cout << std::setprecision(4)<< "ConjugateGradient: k=0 residual "<<cp<<" rsq"<<rsq<<std::endl;
      
      int k;
      for (k=1;k<=MaxIterations;k++){
	
	c=cp;
	
	Linop.OpAndNorm(p,mmp,d,qq);
	  
	a      = c/d;
	b_pred = a*(a*qq-d)/c;
	
	cp = axpy_norm(r,mmp,r,-a);
	b = cp/c;
	
	// Fuse these loops ; should be really easy
	psi= a*p+psi;
	p  = p*b+r;
	  
	std::cout << "Iteration " <<k<<" residual "<<cp<< " target"<< rsq<<std::endl;
	// Stopping condition
	if ( cp <= rsq ) { 
	  
	  Linop.Op(p,mmp);
	  p=mmp-src;
	  
	  RealD mmpnorm = sqrt(norm2(mmp));
	  RealD psinorm = sqrt(norm2(psi));
	  RealD srcnorm = sqrt(norm2(src));
	  RealD resnorm = sqrt(norm2(p));
	  RealD true_residual = resnorm/srcnorm;
	  std::cout<<"ConjugateGradient: true   residual  is "<<true_residual<<" sol "<<psinorm<<" src "<<srcnorm<<std::endl;
	  std::cout<<"ConjugateGradient: target residual was "<<Tolerance<<std::endl;
	}
      }
      std::cout<<"ConjugateGradient did NOT converge"<<std::endl;
      assert(0);
    }
  };
}
#endif
