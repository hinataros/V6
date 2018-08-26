/**
   @author Sho Miyahara 2017
*/

#include "config.hpp"
#include "model.hpp"
#include "rlsDynamics.hpp"

void RLS::RlsDynamics::initializeReferenceMap()
{
  if(debug) DEBUG;

  baseTranslationReferenceName
    = baseOrientationReferenceName
    = endEffectorReferenceName
    = comReferenceName
    = dcmReferenceName
    = externalWrenchReferenceName
    = "default";

  // mapping
  // ********************************
  // base translation
  map_baseTranslationReference["default"]
    = &RLS::RlsDynamics::baseTranslationReferencePI;

  // base orientation
  map_baseOrientationReference["default"]
    = &RLS::RlsDynamics::baseOrientationReferencePI;

  // end effector
  map_endEffectorReference["default"]
    = &RLS::RlsDynamics::endEffectorReferencePI;

  // com
  map_comReference["default"]
    = &RLS::RlsDynamics::comReferencePI;
  map_comReference["dcmControl"]
    = &RLS::RlsDynamics::comReferenceDcmControl;

  // dcm
  map_dcmReference["default"]
    = &RLS::RlsDynamics::dcmReferencePI;

  // external wrench
  map_externalWrenchReference["default"]
    = &RLS::RlsDynamics::externalWrenchReferenceFF;
}
