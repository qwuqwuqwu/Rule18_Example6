#ifndef _INVESTMENT_H_
#define _INVESTMENT_H_

class Investment
{
public:
    Investment( const int &nDaysHeld );
    ~Investment();

    const int& GetDaysHeld( void );

    bool IsTaxFree( void ) const;

private:
    int m_nDaysHeld;
};
#endif
