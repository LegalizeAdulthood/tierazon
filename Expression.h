/////////////////////////////////////////////////////////////////////////////
// Expression.h
//
//
//---------------------------------------------------------------------------
//#ifndef Unit1H
//#define Unit1H
//---------------------------------------------------------------------------
//#include <math>
//---------------------------------------------------------------------------
class MExpression							// abstract base class
{
	public:
    MExpression* Operand1;
		MExpression* Operand2;

		MExpression( MExpression* Op1 = 0, MExpression* Op2 = 0 )
		{
      Operand1 = Op1;
			Operand2 = Op2;
		}

		~MExpression()
		{
			if ( Operand1 ) delete Operand1;
			if ( Operand2 ) delete Operand2;
		}

		virtual cmplx Do() = 0;	// pure virtual function
};

class MAddExpr : public MExpression
{
	public:
		MAddExpr( MExpression* Op1, MExpression* Op2 )
			: MExpression( Op1, Op2 ) {}
		cmplx Do() { return ( Operand1->Do() + Operand2->Do() ); }
};

class MSubtractExpr : public MExpression
{
	public:
		MSubtractExpr( MExpression* Op1, MExpression* Op2 )
			: MExpression( Op1, Op2 ) {}
		cmplx Do() { return ( Operand1->Do() - Operand2->Do() ); }
};

class MMultiplyExpr : public MExpression
{
	public:
		MMultiplyExpr( MExpression* Op1, MExpression* Op2 )
			: MExpression( Op1, Op2 ) {}
		cmplx Do() { return ( Operand1->Do() * Operand2->Do() ); }
};

class MDivideExpr : public MExpression
{
	public:
		MDivideExpr( MExpression* Op1, MExpression* Op2 )
			: MExpression( Op1, Op2 ) {}
		cmplx Do() { return ( Operand1->Do() / Operand2->Do() ); }
};

class MExponentExpr : public MExpression
{
	public:
		MExponentExpr( MExpression* Op1, MExpression* Op2 )
			: MExpression( Op1, Op2 ) {}
		cmplx Do() { return ( Operand1->Do() ^ Operand2->Do() ); }
};

class MUnaryMinusExpr : public MExpression
{
	public:
		MUnaryMinusExpr( MExpression* Op1 ) : MExpression( Op1 ) {}
		cmplx Do() { return ( -( Operand1->Do() ) ); }
};

class MZExpr : public MExpression
{
	public:
		CTierazonView* pView;
    MZExpr( CTierazonView* pview ) : MExpression() { pView = pview; };
		cmplx Do() { return pView->z; }  	// z from the caller's view
};

class MCExpr : public MExpression
{
	public:
		CTierazonView* pView;
		MCExpr( CTierazonView* pview ) : MExpression() { pView = pview; };
		cmplx Do() { return pView->c; }	  // c from the caller's view
};

class MLeafExpr : public MExpression
{
	public:
		cmplx LeafOperand;
		MLeafExpr( cmplx leafOp ) : MExpression() { LeafOperand = leafOp; }
		cmplx Do() { return LeafOperand; }
};

class MSinExpr : public MExpression
{
	public:
		MSinExpr( MExpression* Op1 ) : MExpression( Op1 ) {}
		cmplx Do() { return ( Operand1->Do().csin() ); }
};

class MASinExpr : public MExpression
{
	public:
		MASinExpr( MExpression* Op1 ) : MExpression( Op1 ) {}
		cmplx Do() { return asin( (cmplx&) Operand1->Do() ); }
};

class MSinhExpr : public MExpression
{
	public:
		MSinhExpr( MExpression* Op1 ) : MExpression( Op1 ) {}
		cmplx Do() { return sinh( (cmplx&) Operand1->Do() ); }
};

class MCosExpr : public MExpression
{
	public:
		MCosExpr( MExpression* Op1 ) : MExpression( Op1 ) {}
		cmplx Do() { return ( Operand1->Do().ccos() ); }
};

class MACosExpr : public MExpression
{
	public:
		MACosExpr( MExpression* Op1 ) : MExpression( Op1 ) {}
		cmplx Do() { return acos( (cmplx&) Operand1->Do() ); }
};

class MTanExpr : public MExpression
{
	public:
		MTanExpr( MExpression* Op1 ) : MExpression( Op1 ) {}
		cmplx Do() { return tangent( (cmplx&) Operand1->Do() ); }
};

class MATanExpr : public MExpression
{
	public:
		MATanExpr( MExpression* Op1 ) : MExpression( Op1 ) {}
		cmplx Do() { return arctan( (cmplx&) Operand1->Do() ); }
};

class MLogExpr : public MExpression
{
	public:
		MLogExpr( MExpression* Op1 ) : MExpression( Op1 ) {}
		cmplx Do() { return ( Operand1->Do().clog() ); }
};

class MUnknownExpr : public MExpression
{
	public:
		MUnknownExpr( MExpression* Op1 ) : MExpression( Op1 ) {}
		cmplx Do() { return ( Operand1->Do().unknown() ); }
};

class MRealExpr : public MExpression
{
	public:
		MRealExpr( MExpression* Op1 ) : MExpression( Op1 ) {}
		cmplx Do() { return ( Operand1->Do().Real() ); }
};

class MImagExpr : public MExpression
{
	public:
		MImagExpr( MExpression* Op1 ) : MExpression( Op1 ) {}
		cmplx Do() { return ( Operand1->Do().Imag() ); }
};


//---------------------------------------------------------------------------
//#endif
