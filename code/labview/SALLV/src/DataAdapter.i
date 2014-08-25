// ============================================================================
//
// = CONTEXT
//   SALLV Generic Client for LabVIEW
//
// = FILENAME
//   DataAdapter.i
//
// = AUTHOR
//   Nicolas Leclercq - SOLEIL : SAL adaptation : Dave Mills - LSST
//
// ============================================================================

//=============================================================================
// DataAdapter::instance
//=============================================================================
LV_INLINE DataAdapter* DataAdapter::instance (void)
{
  return DataAdapter::instance_;
}
