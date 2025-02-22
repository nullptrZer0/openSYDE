//----------------------------------------------------------------------------------------------------------------------
/*!
   \file
   \brief       Header view for tables with both headers (header)

   See cpp file for detailed description

   \copyright   Copyright 2017 Sensor-Technik Wiedemann GmbH. All rights reserved.
*/
//----------------------------------------------------------------------------------------------------------------------
#ifndef C_SDNDEDPLISTDATASETHEADERVIEW_H
#define C_SDNDEDPLISTDATASETHEADERVIEW_H

/* -- Includes ------------------------------------------------------------------------------------------------------ */
#include "C_SdNdeDpListTableHeaderView.hpp"

/* -- Namespace ----------------------------------------------------------------------------------------------------- */
namespace stw
{
namespace opensyde_gui
{
/* -- Global Constants ---------------------------------------------------------------------------------------------- */

/* -- Types --------------------------------------------------------------------------------------------------------- */

class C_SdNdeDpListDataSetHeaderView :
   public C_SdNdeDpListTableHeaderView
{
   Q_OBJECT

public:
   C_SdNdeDpListDataSetHeaderView(const Qt::Orientation & ore_Orientation, QWidget * const opc_Parent = NULL);
};

/* -- Extern Global Variables --------------------------------------------------------------------------------------- */
}
} //end of namespace

#endif
