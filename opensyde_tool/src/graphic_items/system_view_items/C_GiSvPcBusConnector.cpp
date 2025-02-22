//----------------------------------------------------------------------------------------------------------------------
/*!
   \file
   \brief       PC bus connection (implementation)

   PC bus connection

   \copyright   Copyright 2017 Sensor-Technik Wiedemann GmbH. All rights reserved.
*/
//----------------------------------------------------------------------------------------------------------------------

/* -- Includes ------------------------------------------------------------------------------------------------------ */
#include "precomp_headers.hpp"

#include "stwtypes.hpp"
#include "gitypes.hpp"
#include "constants.hpp"
#include "C_GiSvPcBusConnector.hpp"
#include "C_PuiSvHandler.hpp"

/* -- Used Namespaces ----------------------------------------------------------------------------------------------- */
using namespace stw::opensyde_gui;
using namespace stw::opensyde_gui_logic;

/* -- Module Global Constants --------------------------------------------------------------------------------------- */

/* -- Types --------------------------------------------------------------------------------------------------------- */

/* -- Global Variables ---------------------------------------------------------------------------------------------- */

/* -- Module Global Variables --------------------------------------------------------------------------------------- */

/* -- Module Global Function Prototypes ----------------------------------------------------------------------------- */

/* -- Implementation ------------------------------------------------------------------------------------------------ */

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Default constructor

   Set up GUI with all elements.

   \param[in]     ou64_UniqueId           Unique ID
   \param[in]     ou32_ViewIndex          View index
   \param[in]     orc_InteractionPoints   Interaction points
   \param[in]     opc_BusItem             Bus item for initial connection
   \param[in,out] opc_GenericItem         PC item to connect to
*/
//----------------------------------------------------------------------------------------------------------------------
C_GiSvPcBusConnector::C_GiSvPcBusConnector(const uint64_t ou64_UniqueId, const uint32_t ou32_ViewIndex,
                                           const std::vector<QPointF> & orc_InteractionPoints,
                                           const C_GiLiBus * const opc_BusItem,
                                           C_GiBiConnectableItem * const opc_GenericItem) :
   C_GiLiBusConnectorBase(ou64_UniqueId, orc_InteractionPoints, opc_BusItem),
   mu32_ViewIndex(ou32_ViewIndex)
{
   this->SetEditMode(false);
   this->m_UpdateGenericItem(opc_GenericItem);
   this->mpc_GenericPositionItem = opc_GenericItem;
   if (orc_InteractionPoints.size() > static_cast<uint32_t>(C_GiLiBusConnectorBase::mh_GetGenericInteractionIndex()))
   {
      this->m_CalcInitialLocalPos(orc_InteractionPoints[static_cast<uint32_t>(C_GiLiBusConnectorBase::
                                                                              mh_GetGenericInteractionIndex())]);
   }
   this->m_UpdateExternal();
   this->m_UpdateInternal();
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Returns the type of this item

   \return  ID
*/
//----------------------------------------------------------------------------------------------------------------------
int32_t C_GiSvPcBusConnector::type(void) const
{
   return ms32_GRAPHICS_ITEM_PC_CONNECTION;
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Generate hint
*/
//----------------------------------------------------------------------------------------------------------------------
//lint -e{9175} intentionally no functionality in this implementation
void C_GiSvPcBusConnector::GenerateHint(void)
{
   //No hint
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Set animation status

   \param[in] oq_Active          Animation active flag
   \param[in] oq_Inverse         Optional flag to animate in inverse direction
   \param[in] oq_SpeedUp         Optional flag to speed up the animation
   \param[in] oc_Polygon         Optional polygon to use for animation
   \param[in] oq_ShowOrignalLine Optional flag to hide or show the original line
*/
//----------------------------------------------------------------------------------------------------------------------
void C_GiSvPcBusConnector::SetAnimated(const bool oq_Active, const bool oq_Inverse, const bool oq_SpeedUp,
                                       const QPolygonF oc_Polygon, const bool oq_ShowOrignalLine)
{
   Q_UNUSED(oq_ShowOrignalLine)
   if (oq_Active == false)
   {
      C_GiLiBusConnectorBase::SetAnimated(oq_Active, oq_Inverse, oq_SpeedUp, oc_Polygon, true);
   }
   else
   {
      C_GiLiBusConnectorBase::SetAnimated(oq_Active, oq_Inverse, oq_SpeedUp, oc_Polygon, false);
   }
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Update data
*/
//----------------------------------------------------------------------------------------------------------------------
void C_GiSvPcBusConnector::UpdateData(void) const
{
   C_PuiBsLineBase c_UiData;

   this->m_UpdateBasicData(c_UiData);
   C_PuiSvHandler::h_GetInstance()->SetViewPcConnection(this->mu32_ViewIndex, c_UiData);
   if (this->GetBusItem() != NULL)
   {
      C_PuiSvHandler::h_GetInstance()->SetViewPcConnected(this->mu32_ViewIndex, true, this->GetBusItem()->GetIndex());
   }
   else
   {
      C_PuiSvHandler::h_GetInstance()->SetViewPcConnected(this->mu32_ViewIndex, false, 0);
   }
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Switch edit mode

   \param[in] oq_Active Edit mode active flag
*/
//----------------------------------------------------------------------------------------------------------------------
void C_GiSvPcBusConnector::SetEditMode(const bool oq_Active)
{
   if (oq_Active == true)
   {
      this->setFlag(QGraphicsItem::ItemIsMovable, true);
      this->setFlag(QGraphicsItem::ItemIsSelectable, true);
      this->SetDefaultCursor(Qt::SizeAllCursor);
   }
   else
   {
      this->setFlag(QGraphicsItem::ItemIsMovable, false);
      this->setFlag(QGraphicsItem::ItemIsSelectable, false);
      this->SetDefaultCursor(Qt::ArrowCursor);
   }
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Handle generic item interaction point move item iteration

   Active:
   * Iteration over current scene items
   * Generic interation point moving

   \param[in,out] opc_HighestParentItem  Highest parent of current item
   \param[in]     orc_CurPos             Current hover position
   \param[in,out] orq_RestoreMouseCursor Restore mouse cursor flag (Only write false allowed if necessary)

   \return
   True  Default
   False Do not restore mouse cursor
*/
//----------------------------------------------------------------------------------------------------------------------
void C_GiSvPcBusConnector::m_OnIterationGenericInteractionPointMove(QGraphicsItem * const opc_HighestParentItem,
                                                                    const QPointF & orc_CurPos,
                                                                    bool & orq_RestoreMouseCursor)
{
   //Not allowed -> only cursor handling
   Q_UNUSED(orc_CurPos)
   m_OnIterationBusInteractionPointMoveCleanUp(opc_HighestParentItem, orq_RestoreMouseCursor);
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Handle generic interaction point mouse release

   \param[in] orc_ScenePos Scene position

   \return
   True  Default
   False No revert
*/
//----------------------------------------------------------------------------------------------------------------------
bool C_GiSvPcBusConnector::m_OnGenericInteractionPointMouseRelease(const QPointF & orc_ScenePos)
{
   QPointF c_Pos;

   this->mpc_GenericPositionItem->FindClosestPoint(orc_ScenePos, c_Pos);
   this->m_CalcInitialLocalPos(c_Pos);
   //Never revert (should automatically align to closest image border
   return false;
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Handle bus change

   \param[in] orc_ScenePos Scene position
*/
//----------------------------------------------------------------------------------------------------------------------
void C_GiSvPcBusConnector::m_OnBusChange(const QPointF & orc_ScenePos)
{
   //Manually stop reconnection mode
   m_Reconnect();
   Q_UNUSED(orc_ScenePos)
}

//----------------------------------------------------------------------------------------------------------------------
/*! \brief   Adapt own style to bus

   \param[in] opc_Bus Connected bus item
*/
//----------------------------------------------------------------------------------------------------------------------
void C_GiSvPcBusConnector::m_AdaptStyleToBus(const C_GiLiBus * const opc_Bus)
{
   this->SetWidth(opc_Bus->GetWidth() / 2L);
   //Never changing
   this->SetColor(mc_STYLE_GUIDE_COLOR_9);
   this->SetMiddleLineColor(opc_Bus->GetMiddleLineColor());
   this->SetMiddleLine(false);
   this->mpc_LinePath->SetLineStyle(stw::opensyde_gui_logic::C_PuiBsLineArrow::E_LineType::eDASH);
}
