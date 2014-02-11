//Geographics.h


template<typename CObj> 
const CObj& Clamp(const CObj& xV,const CObj& xMin, const CObj& xMax) {
 if(xMin>xV)	{return xMin;}	else if(xV>xMax){return xMax;}	else{return xV;};
};