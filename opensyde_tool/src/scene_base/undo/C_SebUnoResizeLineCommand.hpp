//----------------------------------------------------------------------------------------------------------------------
/*!
   \file
   \brief       Resize line undo command (header)

   See cpp file for detailed description

   \copyright   Copyright 2016 Sensor-Technik Wiedemann GmbH. All rights reserved.
*/
//----------------------------------------------------------------------------------------------------------------------
#ifndef C_SEBUNOTOPRESIZELINECOMMAND_H
#define C_SEBUNOTOPRESIZELINECOMMAND_H

/* -- Includes ------------------------------------------------------------------------------------------------------ */

#include "C_SebUnoBaseCommand.hpp"

/* -- Namespace ----------------------------------------------------------------------------------------------------- */
namespace stw
{
namespace opensyde_gui_logic
{
/* -- Global Constants ---------------------------------------------------------------------------------------------- */

/* -- Types --------------------------------------------------------------------------------------------------------- */

class C_SebUnoTopResizeLineCommand :
   public C_SebUnoBaseCommand
{
public:
   C_SebUnoTopResizeLineCommand(QGraphicsScene * const opc_Scene, const std::vector<uint64_t> & orc_Ids,
                                const int32_t & ors32_InteractionPointId, const QPointF & orc_PositionDifference,
                                QUndoCommand * const opc_Parent = NULL);
   ~C_SebUnoTopResizeLineCommand() override;
   void undo(void) override;
   void redo(void) override;

private:
   const int32_t ms32_InteractionPointId;
   const QPointF mc_PositionDifference;

   void m_UndoSingle(QGraphicsItem * const opc_Item) const;
   void m_RedoSingle(QGraphicsItem * const opc_Item) const;
};

/* -- Extern Global Variables --------------------------------------------------------------------------------------- */
}
} //end of namespace

#endif
