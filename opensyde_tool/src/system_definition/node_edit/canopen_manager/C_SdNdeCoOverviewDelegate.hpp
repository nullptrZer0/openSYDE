//----------------------------------------------------------------------------------------------------------------------
/*!
   \file
   \brief       Short description
   \copyright   Copyright 2022 Sensor-Technik Wiedemann GmbH. All rights reserved.
*/
//----------------------------------------------------------------------------------------------------------------------
#ifndef C_SDNDECOOVERVIEWDELEGATE_H
#define C_SDNDECOOVERVIEWDELEGATE_H

/* -- Includes ------------------------------------------------------------------------------------------------------ */
#include <QStyledItemDelegate>
#include <QAbstractTableModel>
#include "stwtypes.hpp"

/* -- Namespace ----------------------------------------------------------------------------------------------------- */
namespace stw
{
namespace opensyde_gui_logic
{
/* -- Global Constants ---------------------------------------------------------------------------------------------- */

/* -- Types --------------------------------------------------------------------------------------------------------- */

class C_SdNdeCoOverviewDelegate :
   public QStyledItemDelegate
{
public:
   C_SdNdeCoOverviewDelegate(QObject * const opc_Parent = NULL);

   void paint(QPainter * const opc_Painter, const QStyleOptionViewItem & orc_Option,
              const QModelIndex & orc_Index) const override;
   bool SetHoveredRow(const int32_t & ors32_Value);
   void SetModel(const QAbstractTableModel * const opc_Value);

private:
   const QAbstractTableModel * mpc_Model;
   int32_t ms32_HoveredRow;
};

/* -- Extern Global Variables --------------------------------------------------------------------------------------- */
}
} //end of namespace

#endif
