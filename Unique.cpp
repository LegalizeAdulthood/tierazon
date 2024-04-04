//////////////////////////////
// Unique Parser by Gerry Myers
// Unique.cpp  4/29/97
//

#include "stdafx.h"
#include "Tierazon.h"

#include "TierazonDoc.h"
#include "TierazonView.h"
#include <math.h>
#include "unique.h"

//---------------------------------------------------------------------------
//#include <vcl\vcl.h>
//#pragma hdrstop

//#include "Unit1.h"
//---------------------------------------------------------------------------
//#pragma resource "*.dfm"
//TForm1 *Form1;

//
// A simple class that could be used for exception
// handling chores.
//

class MyEHClass {
  public:
    MyEHClass(int error, char* msg)
    {
      ErrorCode = error;
      Msg = msg;
    }
    int Error()
    {
      return ErrorCode;
    }
    CString Message()
    {
      return Msg;
    }
    int Message(char* buff, int buffsize)
		{
      if (Msg.GetLength() < buffsize) {
        strcpy(buff, Msg);
        //strcpy(buff, Msg.c_str());
        return Msg.GetLength();
      }
      else {
        strcpy(buff, "");
        return 0;
      }
    }
private:
  int ErrorCode;
  CString Msg;
};

//---------------------------------------------------------------------------
//double __fastcall TForm1::ParseExpression( const char* str, int& index )
CTierazonView::MExpression* CTierazonView::ParseExpression( const char* str, int& index )
{
	try
	{
		//
		// Parse out the first operand of this expression.
		//
		MExpression* Operand1 = ParseOperand( str, index );

		//
		// Determine the operation.  The next character should be an operator.
		// Prime the pump.
		//
		while ( str[ index ] == ' ' ) index++;		// eat whitespace
		char Operation = str[ index ];

		// Repeat this block as long as there is more expression left.  If this
		// is a "two operand" expression, this loop will only execute once.
		// However, if this is a three, four, or more operand expression, this
		// loop will execute once for each operand (except for the first operand).
		// The current progress is always held as operand 1.
		while ( ( Operation != '\0' ) && ( Operation != ')' ) )
		{
			//
			// Parse out the second operand in this expression.
			//
			MExpression* Operand2 = ParseOperand( str, ++index );

			//
			// Perform the operation with the two operands.
			//
			switch ( Operation )
			{
				case '+':
					Operand1 = new MAddExpr( Operand1, Operand2 );
					break;
				
        case '-':
					Operand1 = new MSubtractExpr( Operand1, Operand2 );
					break;
				
        case '*':
					Operand1 = new MMultiplyExpr( Operand1, Operand2 );
					break;
				
        case '/':
					Operand1 = new MDivideExpr( Operand1, Operand2 );
					break;

        case '^':
					Operand1 = new MExponentExpr( Operand1, Operand2 );
					break;

				default:
          throw MyEHClass( 0, "Bad Expression" );
			}

			while ( str[ index ] == ' ' ) index++;		// eat whitespace
			Operation = str[ index ];
		}

		// Return the accumulated result.
		return Operand1;
	}
	catch ( MyEHClass& )
	{
		throw;	// re-throw it for the next level up.
	}
  return new MLeafExpr(cmplx(0, 0));
}

//---------------------------------------------------------------------------
//double __fastcall TForm1::ParseOperand( const char* str, int& index )
CTierazonView::MExpression* CTierazonView::ParseOperand( const char* str, int& index )
{
	try
	{
		// Get rid of any leading blanks.
		while ( str[ index ] == ' ' ) index++;

		switch ( str[ index ] )
		{
			// Is this a sub-expression?
			case '(':
			{
				index++;
				MExpression* d = ParseExpression( str, index );

				// Get rid of any leading blanks.
				while ( str[ index ] == ' ' ) index++;

				// The current character (left over from the above sub-expression)
				// should be ')'.  If not, the entire expression is bad.
				if ( str[ index++ ] != ')' ) throw MyEHClass( 0, "Bad Expression" );

				// Store the first operand.
				return d;
			}

			// Is this the Z data member?
			case 'z':
			case 'Z':
				index++;						// advance to the next character
				return new MZExpr( this );

			// Is this the U data member?
			case 'u':
			case 'U':
				index++;						// advance to the next character
				return new MLeafExpr( uu );

			// Is this the V data member?
			case 'v':
			case 'V':
				index++;						// advance to the next character
				return new MLeafExpr( vv );

			// Is this the W data member?
			case 'w':
			case 'W':
				index++;						// advance to the next character
				return new MLeafExpr( ww );

			// Is this the C data member?
			case 'c':
			case 'C':
				// Is it the cos() function?
				if ( strncmp( &( str[ index ] ), "cos(", 4 ) == 0 )
				{
					index += 3;
					return new MCosExpr( ParseOperand( str, index ) );
				}
        else 
        {
          index++;						// advance to the next character
				return new MCExpr( this );
        }

			// Is this a number?
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '.':
			{
				double d = atof( &( str[ index ] ) );

				// Move to the end of this number.
				while ( ( ( str[ index ] >= '0' ) && ( str[ index ] <= '9' ) ) ||
									( str[ index ] == '.' ) )
					index++;
				return new MLeafExpr( cmplx( d, 0 ) );
			}

			// Is this the unary minus?  If so, break down any sub-expression that
			// may be sitting behind it.
			case '-':
				return new MUnaryMinusExpr( ParseExpression( str, ++index ) );

			// If none of the above options used, something is wrong with the
			// expression.
			default:
				// Is it the sin() function?
				// All values used inside the sin(), cos(), and tan() are in radians
				// where 2 pi radians = 360 degrees.
				if ( strncmp( &( str[ index ] ), "sin(", 4 ) == 0 )
				{
					index += 3;
					//return sin( ParseOperand( str, index ) );
					return new MSinExpr( ParseOperand( str, index ) );
				}

				// Is it the sinh() function?
				else if ( strncmp( &( str[ index ] ), "sinh(", 5 ) == 0 )
				{
					index += 4;
					return new MSinhExpr( ParseOperand( str, index ) );
        
        }

				// Is it the asin() function?
				else if ( strncmp( &( str[ index ] ), "asin(", 5 ) == 0 )
				{
					index += 4;
					return new MASinExpr( ParseOperand( str, index ) );
				}

				// Is it the acos() function?
				else if ( strncmp( &( str[ index ] ), "acos(", 5 ) == 0 )
				{
					index += 4;
					return new MACosExpr( ParseOperand( str, index ) );
				}

				// Is it the tan() function?
				else if ( strncmp( &( str[ index ] ), "tan(", 4 ) == 0 )
				{
					index += 3;
					return new MTanExpr( ParseOperand( str, index ) );
				}

				// Is it the atan() function?
				else if ( strncmp( &( str[ index ] ), "atan(", 5 ) == 0 )
				{
					index += 4;
					return new MATanExpr( ParseOperand( str, index ) );
				}

				// Is it the log() function?
				else if ( strncmp( &( str[ index ] ), "log(", 4 ) == 0 )
				{
					index += 3;
					return new MLogExpr( ParseOperand( str, index ) );
				}

				// Is it the lost() function?
				else if ( strncmp( &( str[ index ] ), "lost(", 5 ) == 0 )
				{
					index += 4;
					return new MUnknownExpr( ParseOperand( str, index ) );
				}

				// Is it the real() function?
				else if ( strncmp( &( str[ index ] ), "real(", 5 ) == 0 )
				{
					index += 4;
					return new MRealExpr( ParseOperand( str, index ) );
				}

				// Is it the imag() function?
				else if ( strncmp( &( str[ index ] ), "imag(", 5 ) == 0 )
				{
					index += 4;
					return new MImagExpr( ParseOperand( str, index ) );
				}

				// If execution gets to here, something is wrong with the expression.
				else
				{
					//char cstr[100];
					//CString sz = str[index];
					//wsprintf(cstr,"Bad expression, index=%d, str=%s",index, sz);
					//AfxMessageBox(cstr);
					
					throw MyEHClass( 0, "Bad Expression" );
					//throw MyEHClass( 0, cstr );

				}

				// new end
		}
	}
	catch ( MyEHClass& )
	{
		throw;	// re-throw it for the next level up.
	}
  return new MLeafExpr(cmplx(0, 0));
}

/////////////////////////////////////////////////////////////////////////////
// CUnique dialog

CUnique::CUnique(CWnd* pParent /*=NULL*/)
	: CDialog(CUnique::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUnique)
	m_u_imag = 0.0;
	m_u_real = 0.0;
	m_v_real = 0.0;
	m_w_real = 0.0;
	m_Formulae = _T("");
	m_v_imag = 0.0;
	m_w_imag = 0.0;
	m_Radio = -1;
	//}}AFX_DATA_INIT
}


void CUnique::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUnique)
	DDX_Text(pDX, IDC_U_IMAG, m_u_imag);
	DDX_Text(pDX, IDC_U_REAL, m_u_real);
	DDX_Text(pDX, IDC_V_REAL, m_v_real);
	DDX_Text(pDX, IDC_W_REAL, m_w_real);
	DDX_Text(pDX, IDC_FORMULAE, m_Formulae);
	DDX_Text(pDX, IDC_V_IMAG, m_v_imag);
	DDX_Text(pDX, IDC_W_IMAG, m_w_imag);
	DDX_Radio(pDX, IDC_RADIO_M, m_Radio);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUnique, CDialog)
	//{{AFX_MSG_MAP(CUnique)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CUnique message handlers

void CTierazonView::OnDrawUnique()
{
  CUnique cu;

	cu.m_Radio = nFormulaType;

  cu.m_u_real = u_real;
  cu.m_u_imag = u_imag;

  cu.m_v_real = v_real;
  cu.m_v_imag = v_imag;

  cu.m_w_real = w_real;
  cu.m_w_imag = w_imag;

  cu.m_Formulae = strFormulae;

  if (cu.DoModal() == IDOK)
  {
		nFormulaType = cu.m_Radio;

    u_real = cu.m_u_real;
    u_imag = cu.m_u_imag;

    v_real = cu.m_v_real;
    v_imag = cu.m_v_imag;

    w_real = cu.m_w_real;
    w_imag = cu.m_w_imag;

    uu.set_real(cu.m_u_real);
    uu.set_imag(cu.m_u_imag);

    vv.set_real(cu.m_v_real);
    vv.set_imag(cu.m_v_imag);

    ww.set_real(cu.m_w_real);
    ww.set_imag(cu.m_w_imag);
    
    strFormulae = cu.m_Formulae;

    int i_try = 0;
    try
	  {
      //char cstr[120];
      //temp = ParseExpression( strFormulae, i_try );
      
      uu.set_real(u_real);
      uu.set_imag(u_imag);

      vv.set_real(v_real);
      vv.set_imag(v_imag);

      ww.set_real(w_real);
      ww.set_imag(w_imag);

      ParsedExpr = ParseExpression( strFormulae, i_try );

      if (nFormulaType == 0)
				OnDraw101();  // M-Set
			else
				OnDraw118();  // N-Set
    }
	  catch ( MyEHClass& )
	  {
		  //Application->MessageBox( "Something wrong in the expression!",
			  //"Invalid Expression", MB_OK | MB_ICONEXCLAMATION );
      AfxMessageBox("Invalid Expression");
	  }
  }
}

void CUnique::OnOK() 
{
  /*
  try
	{
		// If there is nothing in the string, do nothing.
		if ( ExpressionEdit->Text.Length() <= 0 ) return;

		u = atof( URealEdit->Text.c_str() );
		v = atof( VRealEdit->Text.c_str() );
		w = atof( WRealEdit->Text.c_str() );
		int i = 0;
		z_real = ParseExpression( ExpressionEdit->Text.c_str(), i );
		DebugLabel->Caption = AnsiString( z );
	}
	catch ( MyEHClass& )
	{
		Application->MessageBox( "Something wrong in the expression!",
			"Invalid Expression", MB_OK | MB_ICONEXCLAMATION );

		DebugLabel->Caption = "Invalid Expression.";
	}
  */
  
	CDialog::OnOK();
}

void CTierazonView::OnDraw101() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "101) M-Set Method";
	nDistortion = 101;
	GoDoFractal();
}

void CTierazonView::OnUpdateDraw101(CCmdUI* pCmdUI) 
{
	if (nDistortion == 101) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}

void CTierazonView::OnDraw118() 
{
	jul 		 = 0;
	jul_save = 1;

	dMagnification = 1;
	CRMID = 0;
	CIMID = 0;

	ActiveTitle = "118) N-Set method";
	nDistortion = 118;
	GoDoFractal();	
}

void CTierazonView::OnUpdateDraw118(CCmdUI* pCmdUI) 
{
	if (nDistortion == 118) pCmdUI->SetCheck(TRUE);	
	else  pCmdUI->SetCheck(FALSE);
}
