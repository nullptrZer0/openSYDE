//----------------------------------------------------------------------------------------------------------------------
/*!
   \file
   \brief       Connection of any item to bus (header)

   See cpp file for detailed description

   \copyright   Copyright 2017 Sensor-Technik Wiedemann GmbH. All rights reserved.
*/
//----------------------------------------------------------------------------------------------------------------------
#ifndef C_GILIBUSCONNECTORBASE_H
#define C_GILIBUSCONNECTORBASE_H

/* -- Includes ------------------------------------------------------------------------------------------------------ */
#include "C_GiLiLineGroup.hpp"
#include "C_GiBiCustomToolTip.hpp"
#include "C_GiUnique.hpp"
#include "C_GiLiBus.hpp"

/* -- Namespace ----------------------------------------------------------------------------------------------------- */
namespace stw
{
namespace opensyde_gui
{
/* -- Global Constants ---------------------------------------------------------------------------------------------- */

/* -- Types --------------------------------------------------------------------------------------------------------- */

class C_GiLiBusConnectorBase :
   public C_GiLiLineGroup,
   public C_GiBiCustomToolTip,
   public stw::opensyde_gui_logic::C_GiUnique
{
   Q_OBJECT

public:
   enum E_ConnectState
   {
      eTO_BUS,
      eTO_GENERIC,
      eTO_GENERIC_AND_BUS
   };

   C_GiLiBusConnectorBase(const uint64_t & oru64_Id, const QPointF & orc_TriggerPos,
                          const C_GiLiBus * const opc_BusItem, const bool oq_MiddleLine = false,
                          QGraphicsItem * const opc_Parent = NULL);
   C_GiLiBusConnectorBase(const uint64_t & oru64_Id, const std::vector<QPointF> & orc_InteractionPoints,
                          const C_GiLiBus * const opc_BusItem, const bool oq_MiddleLine = false,
                          QGraphicsItem * const opc_Parent = NULL);
   ~C_GiLiBusConnectorBase(void) override;
   QPointF GetPos(void) const override;
   std::vector<QPointF> GetPointsScenePos(void) const;
   virtual void SetPoints(const std::vector<QPointF> & orc_ScenePos);
   const C_GiLiBus * GetBusItem(void) const;
   const C_GiBiConnectableItem * GetGenericPositionItem(void) const;
   void RestoreZetOrder(void);
   void GetNodeInteractionScenePos(QPointF & orc_ScenePos) const;
   void GetBusInteractionScenePos(QPointF & orc_ScenePos) const;
   void RevertBus(const stw::opensyde_gui::C_GiLiBus * const opc_StartingBus,
                  const stw::opensyde_gui::C_GiLiBus * const opc_LastBus, const QPointF & orc_ScenePos);

   //GI base
   void SetZetValueCustom(const float64_t of64_ZetValue) override;

   //The signals keyword is necessary for Qt signal slot functionality
   //lint -save -e1736

Q_SIGNALS:
   //lint -restore
   void SigStartConnect(const E_ConnectState & ore_ConnectState, QGraphicsItem * const opc_Item,
                        const stw::opensyde_core::C_OscSystemBus::E_Type * ope_Type,
                        C_GiLiBusConnectorBase * const opc_Connector);
   void SigHideToolTip(void);
   void SigPrepareMove(const C_GiLiBusConnectorBase * const opc_BusConnector);
   void SigStopConnect(void);
   void SigShowToolTip(const QPointF & orc_ScenePos, const C_GiBiCustomToolTip * const opc_Item);

protected:
   int32_t ms32_ConnIndex;      ///< Connection item this connection is connected to
   int32_t ms32_KnownLineCount; ///< Number of known bus segments to detect new / deleted
   ///< points
   float64_t mf64_ConnProgress;                            ///< Connection item progress
   const C_GiLiBus * mpc_LastKnownBusItem;                 ///< Last valid bus item this was connected to
   C_GiBiConnectableItem * mpc_GenericSignalItem;          ///< Generic item this connection is connected to (signals)
   C_GiBiConnectableItem * mpc_LastKnownGenericSignalItem; ///< Last generic node item this was connected to (signals)
   C_GiBiConnectableItem * mpc_GenericPositionItem;        ///< Generic item this connection is connected to
   ///< (position)
   C_GiBiConnectableItem * mpc_LastKnownGenericPositionItem; ///< Last valid generic item this was connected to
   ///< (position)
   QPointF mc_KnownLocalPosGeneric; ///< Last known generic local position, used to avoid
   ///< always searching for the nearest valid position
   bool mq_InAir; ///< Indicator if connection is currently moved by
   ///< user and therefore can be invalid / not connected

   void mousePressEvent(QGraphicsSceneMouseEvent * const opc_Event) override;
   void hoverLeaveEvent(QGraphicsSceneHoverEvent * const opc_Event) override;
   void mouseReleaseEvent(QGraphicsSceneMouseEvent * const opc_Event) override;

   void m_SetBus(const C_GiLiBus * const opc_Bus);
   void m_UpdateBus(const QPointF & orc_Pos, const C_GiLiBus * const opc_BusItem);
   void m_UpdateConnection(const QPointF & orc_ScenePos);
   C_GiLiLineConnection * m_GetCurrentConn(void) const;
   void m_CalcConnProgress(const C_GiLiLineConnection * const opc_Conn, const QPointF & orc_ScenePos);
   void m_UpdateExternal(void);
   void m_UpdateInternal(void);
   int32_t m_GetBusInteractionIndex(void) const;
   void m_UpdatePointBus(void);
   void m_CalcConnPos(const C_GiLiLineConnection * const opc_Conn, QPointF & orc_OutPos) const;
   void m_UpdateGenericPoint(void);
   static int32_t mh_GetGenericInteractionIndex(void);
   void m_CalcInitialLocalPos(const QPointF & orc_InPos);
   void m_UpdateGenericItem(C_GiBiConnectableItem * const opc_NewItem);
   virtual void m_Reconnect(void);
   virtual void m_OnInteractionPointMove(void);
   virtual void m_OnIterationBusInteractionPointMoveCleanUp(QGraphicsItem * const opc_HighestParentItem,
                                                            bool & orq_RestoreMouseCursor);
   virtual void m_OnIterationGenericInteractionPointMove(QGraphicsItem * const opc_HighestParentItem,
                                                         const QPointF & orc_CurPos, bool & orq_RestoreMouseCursor) = 0;
   virtual bool m_OnGenericInteractionPointMouseRelease(const QPointF & orc_ScenePos) = 0;
   virtual void m_OnBusChange(const QPointF & orc_ScenePos) = 0;
   virtual void m_AdaptStyleToBus(const C_GiLiBus * const opc_Bus);

private:
   //Avoid call
   C_GiLiBusConnectorBase(const C_GiLiBusConnectorBase &);
   C_GiLiBusConnectorBase & operator =(const C_GiLiBusConnectorBase &) &; //lint !e1511 //we want to hide the base func.

   const C_GiLiBus * mpc_BusItem; ///< Bus item this connection is connected to
   std::vector<QPointF> mc_LastKnownBusScenePoints;

   bool m_CheckAnyRelevantBusPointChanged(void) const;
   bool m_CheckOnlyOneBusPointMoved(void) const;
   void m_UpdateLastKnownBusPoints(void);
   void m_CommonInit(void);
};

/* -- Extern Global Variables --------------------------------------------------------------------------------------- */
}
} //end of namespace

#endif
