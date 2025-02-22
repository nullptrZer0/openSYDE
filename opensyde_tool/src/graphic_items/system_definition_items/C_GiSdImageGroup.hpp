//----------------------------------------------------------------------------------------------------------------------
/*!
   \file
   \brief       Implementation for drawing element image in system definition (header)

   See cpp file for detailed description

   \copyright   Copyright 2017 Sensor-Technik Wiedemann GmbH. All rights reserved.
*/
//----------------------------------------------------------------------------------------------------------------------
#ifndef C_GISDIMAGEGROUP_H
#define C_GISDIMAGEGROUP_H

/* -- Includes ------------------------------------------------------------------------------------------------------ */
#include "C_GiBiImageGroup.hpp"
#include "C_PuiSdDataElement.hpp"

/* -- Namespace ----------------------------------------------------------------------------------------------------- */
namespace stw
{
namespace opensyde_gui
{
/* -- Global Constants ---------------------------------------------------------------------------------------------- */

/* -- Types --------------------------------------------------------------------------------------------------------- */

class C_GiSdImageGroup :
   public C_GiBiImageGroup,
   public stw::opensyde_gui_logic::C_PuiSdDataElement
{
public:
   C_GiSdImageGroup(const int32_t & ors32_Index, const uint64_t & oru64_Id, const QString & orc_ImagePath,
                    QGraphicsItem * const opc_Parent = NULL);
   C_GiSdImageGroup(const int32_t & ors32_Index, const uint64_t & oru64_Id, const float64_t of64_Width,
                    const float64_t of64_Height, const QPixmap & orc_Image, QGraphicsItem * const opc_Parent = NULL);

   void LoadData(void) override;
   void UpdateData(void) override;
   void DeleteData(void) override;
};

/* -- Extern Global Variables --------------------------------------------------------------------------------------- */
}
} //end of namespace

#endif
