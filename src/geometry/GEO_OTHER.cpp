// triangle incenter 
// verify : aoj 1301
P incenter(P d, P e, P f){
    R a=abs(e-f),b=abs(f-d),c=abs(d-e);
    return (a*d+b*e+c*f)/(a+b+c);
}
