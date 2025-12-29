/* Implements the getpath API for compiling with no functionality */

#include "Python.h"
#include "pycore_pathconfig.h"

TyStatus
_TyConfig_InitPathConfig(PyConfig *config, int compute_path_config)
{
    return TyStatus_Error("path configuration is unsupported");
}
