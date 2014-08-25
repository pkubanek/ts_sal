// ============================================================================
//
// = CONTEXT
//   SALLV Generic Client for LabVIEW
//
// = FILENAME
//   ErrorStack.i
//
// = AUTHOR
//   Nicolas Leclercq - SOLEIL : SAL adaptation : Dave Mills - LSST
//
// ============================================================================

//=============================================================================
// ErrorStack::instance
//=============================================================================
LV_INLINE ErrorStack* ErrorStack::instance (void)
{
  return ErrorStack::instance_;
}

