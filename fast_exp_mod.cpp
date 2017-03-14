unsigned long long fast_exp(unsigned long long  base, unsigned long long exp){
    base%=MOD;
    unsigned long long result = 1;
    while(exp>0){
        if (exp & 1){
            result = (result*base)%MOD;
        }
        base = (base*base)%MOD;
        exp>>=1;
    }
    return result;
}
