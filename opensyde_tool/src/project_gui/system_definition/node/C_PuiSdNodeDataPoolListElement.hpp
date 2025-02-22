//----------------------------------------------------------------------------------------------------------------------
/*!
   \file
   \brief       Data class for data pool list element UI part (header)

   See cpp file for detailed description

   \copyright   Copyright 2017 Sensor-Technik Wiedemann GmbH. All rights reserved.
*/
//----------------------------------------------------------------------------------------------------------------------
#ifndef C_PUISDNODEDATAPOOLLISTELEMENT_H
#define C_PUISDNODEDATAPOOLLISTELEMENT_H

/* -- Includes ------------------------------------------------------------------------------------------------------ */
#include "stwtypes.hpp"

/* -- Namespace ----------------------------------------------------------------------------------------------------- */
namespace stw
{
namespace opensyde_gui_logic
{
/* -- Global Constants ---------------------------------------------------------------------------------------------- */

/* -- Types --------------------------------------------------------------------------------------------------------- */

class C_PuiSdNodeDataPoolListElement
{
public:
   C_PuiSdNodeDataPoolListElement(void);

   void CalcHash(uint32_t & oru32_HashValue) const;

   bool q_AutoMinMaxActive;
   bool q_InterpretAsString;
};

/* -- Extern Global Variables --------------------------------------------------------------------------------------- */
}
} //end of namespace

#endif
