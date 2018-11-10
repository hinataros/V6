/**
   @author Sho Miyahara 2018
*/

#include "config.hpp"
#include "model.hpp"
#include "desiredValueGenerator.hpp"

void RLS::DesiredValueGenerator::desiredValueGenerator(const double &t)
{
  if(debug) DEBUG;

  (this->*baseTranslation_ptr)(t);
  (this->*baseRotation_ptr)(t);

  for(int i=0; i<info->controlNodeNum; i++){
    (this->*controlNodeTranslation_ptr[i])(i, t);
    (this->*controlNodeRotation_ptr[i])(i, t);
    (this->*controlNodeForce_ptr[i])(i, t);
    (this->*controlNodeMoment_ptr[i])(i, t);
  }

  (this->*com_ptr)(t);
  (this->*dcm_ptr)(t);
  (this->*externalWrench_ptr)(t);
}
