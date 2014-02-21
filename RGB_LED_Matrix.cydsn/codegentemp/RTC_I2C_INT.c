/*******************************************************************************
* File Name: RTC_I2C_INT.c
* Version 1.10
*
* Description:
*  This file provides the source code to the Interrupt Servive Routine for
*  the SCB Component in I2C mode.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "RTC_PVT.h"
#include "RTC_I2C_PVT.h"


/*******************************************************************************
* Function Name: RTC_I2C_ISR
********************************************************************************
*
* Summary:
*  Handles Interrupt Service Routine for SCB I2C mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
CY_ISR(RTC_I2C_ISR)
{
    uint32 diffCount;
    uint32 endTransfer;
    uint8 enableInterrupts;

    #if(RTC_CHECK_I2C_ACCEPT_ADDRESS_CONST)
        uint32 address;
    #endif /* (RTC_CHECK_I2C_ACCEPT_ADDRESS_CONST) */

    endTransfer = 0u; /* Continue active transfer */

    /* Call customer routine if registered */
    if(NULL != RTC_customIntrHandler)
    {
        RTC_customIntrHandler();
    }

    if(RTC_CHECK_INTR_I2C_EC_MASKED(RTC_INTR_I2C_EC_WAKE_UP))
    {
        /* Mask-off after wakeup */
        RTC_SetI2CExtClkInterruptMode(RTC_NO_INTR_SOURCES);
    }

    /* Master and Slave error tracking:
    * Add master state check to track only master errors when master is active or track
    * slave errors when slave active or idle.
    * Specil MMS case: on address phase with misplaced Start: master sets LOST_ARB and
    * slave BUS_ERR. The valid event is LOST_ARB from master.
    */
    if(RTC_CHECK_I2C_FSM_MASTER)
    {
        #if(RTC_I2C_MASTER)
        {
            /* INTR_MASTER_I2C_BUS_ERROR:
            * Misplaced Start or Stop condition was occurred on the bus: complete transaction.
            * The interrupt is cleared in the I2C_FSM_EXIT_IDLE.
            */
            if(RTC_CHECK_INTR_MASTER_MASKED(RTC_INTR_MASTER_I2C_BUS_ERROR))
            {
                RTC_mstrStatus |= (uint16) (RTC_I2C_MSTAT_ERR_XFER |
                                                         RTC_I2C_MSTAT_ERR_BUS_ERROR);

                endTransfer = RTC_I2C_CMPLT_ANY_TRANSFER;
            }

            /* INTR_MASTER_I2C_ARB_LOST:
            * MultiMaster lost arbitrage while transaction: complete transaction.
            * Misplaced Start or Stop condition treats as lost arbitration when master drives SDA.
            * The interrupt is cleared in the I2C_FSM_EXIT_IDLE.
            */
            if(RTC_CHECK_INTR_MASTER_MASKED(RTC_INTR_MASTER_I2C_ARB_LOST))
            {
                RTC_mstrStatus |= (uint16) (RTC_I2C_MSTAT_ERR_XFER |
                                                         RTC_I2C_MSTAT_ERR_ARB_LOST);

                endTransfer = RTC_I2C_CMPLT_ANY_TRANSFER;
            }

            #if(RTC_I2C_MULTI_MASTER_SLAVE)
            {
                /* I2C_MASTER_CMD_M_START_ON_IDLE:
                * MultiMaster-Slave does not generate start, because Slave was addressed
                * earlier: pass control the slave FSM.
                */
                if(RTC_CHECK_I2C_MASTER_CMD(RTC_I2C_MASTER_CMD_M_START_ON_IDLE))
                {
                    RTC_mstrStatus |= (uint16) (RTC_I2C_MSTAT_ERR_XFER |
                                                             RTC_I2C_MSTAT_ERR_ABORT_XFER);

                    endTransfer = RTC_I2C_CMPLT_ANY_TRANSFER;
                }
            }
            #endif

            /* Error handling common part:
            * Set completion flag of master transcation and pass control to:
            *  - I2C_FSM_EXIT_IDLE - to complete transcation in case of: ARB_LOST or BUS_ERR.
            *  - I2C_FSM_IDLE      - to take chanse for slave to process incomming transcation.
            */
            if(0u != endTransfer)
            {
                /* Set completion before FSM change */
                RTC_mstrStatus |= (uint16) RTC_GET_I2C_MSTAT_CMPLT;

                #if(RTC_I2C_MULTI_MASTER_SLAVE)
                {
                    if(RTC_CHECK_I2C_FSM_ADDR)
                    {
                        /* The Start generation was set after enother master start accessing the Slave.
                        * Clean-up the master and turn to slave. Set state to IDLE.
                        */
                        if(RTC_CHECK_I2C_MASTER_CMD(RTC_I2C_MASTER_CMD_M_START_ON_IDLE))
                        {
                            RTC_I2C_MASTER_CLEAR_START;

                            endTransfer = RTC_I2C_CMPLT_ANY_TRANSFER; /* Pass control to Slave */
                        }
                        /* The valid arbitration lost on address phase happens only when: master LOST_ARB set and
                        * slave BUS_ERR is cleared. Only in that case set state to IDLE without SCB IP re-enable.
                        */
                        else if((!RTC_CHECK_INTR_SLAVE_MASKED(RTC_INTR_SLAVE_I2C_BUS_ERROR))
                               && RTC_CHECK_INTR_MASTER_MASKED(RTC_INTR_MASTER_I2C_ARB_LOST))
                        {
                            endTransfer = RTC_I2C_CMPLT_ANY_TRANSFER; /* Pass control to Slave */
                        }
                        else
                        {
                            endTransfer = 0u; /* Causes I2C_FSM_EXIT_IDLE to be set below */
                        }

                        if(0u != endTransfer) /* Clean-up master to proceed with slave */
                        {
                            RTC_CLEAR_TX_FIFO; /* Shifter keeps address, clear it */

                            RTC_DISABLE_MASTER_AUTO_DATA_ACK; /* In case of reading disable autoACK */

                            /* Clean-up master interrupt sources */
                            RTC_ClearMasterInterruptSource(RTC_INTR_MASTER_ALL);

                            /* Disable data processing interrupts: they should be cleared before */
                            RTC_SetRxInterruptMode(RTC_NO_INTR_SOURCES);
                            RTC_SetTxInterruptMode(RTC_NO_INTR_SOURCES);

                            RTC_state = RTC_I2C_FSM_IDLE;
                        }
                        else
                        {
                            /* Set I2C_FSM_EXIT_IDLE for BUS_ERR and ARB_LOST (that is really bus error) */
                            RTC_state = RTC_I2C_FSM_EXIT_IDLE;
                        }
                    }
                    else
                    {
                        /* Set I2C_FSM_EXIT_IDLE if any other state than address */
                        RTC_state = RTC_I2C_FSM_EXIT_IDLE;
                    }
                }
                #else
                {
                    /* In case of LOST*/
                    RTC_state = RTC_I2C_FSM_EXIT_IDLE;
                }
                #endif
            }
        }
        #endif
    }
    else /* (RTC_CHECK_I2C_FSM_SLAVE) */
    {
        #if(RTC_I2C_SLAVE)
        {
            /* INTR_SLAVE_I2C_BUS_ERROR or RTC_INTR_SLAVE_I2C_ARB_LOST:
            * Misplaced Start or Stop condition was occurred on the bus: set flag
            * to notify error condition.
            */
            if(RTC_CHECK_INTR_SLAVE_MASKED(RTC_INTR_SLAVE_I2C_BUS_ERROR |
                                                        RTC_INTR_SLAVE_I2C_ARB_LOST))
            {
                if(RTC_CHECK_I2C_FSM_RD)
                {
                    /* TX direction: master reads from slave */
                    RTC_slStatus &= (uint8) ~RTC_I2C_SSTAT_RD_BUSY;
                    RTC_slStatus |= (uint8) (RTC_I2C_SSTAT_RD_ERR |
                                                          RTC_I2C_SSTAT_RD_CMPLT);
                }
                else
                {
                    /* RX direction: master writes into slave */
                    RTC_slStatus &= (uint8) ~RTC_I2C_SSTAT_WR_BUSY;
                    RTC_slStatus |= (uint8) (RTC_I2C_SSTAT_WR_ERR |
                                                          RTC_I2C_SSTAT_WR_CMPLT);
                }

                RTC_state = RTC_I2C_FSM_EXIT_IDLE;
            }
        }
        #endif
    }

    /* States description:
    * Any Master operation starts from: ADDR_RD/WR state as the master generates traffic on the bus.
    * Any Slave operation starts from: IDLE state as slave always waiting actions from the master.
    */

    /* FSM Master */
    if(RTC_CHECK_I2C_FSM_MASTER)
    {
        #if(RTC_I2C_MASTER)
        {
            /* INTR_MASTER_I2C_STOP:
            * Stop condition was generated by the master: end of transction.
            * Set completion flags to notify API.
            */
            if(RTC_CHECK_INTR_MASTER_MASKED(RTC_INTR_MASTER_I2C_STOP))
            {
                RTC_ClearMasterInterruptSource(RTC_INTR_MASTER_I2C_STOP);

                RTC_mstrStatus |= (uint16) RTC_GET_I2C_MSTAT_CMPLT;
                RTC_state       = RTC_I2C_FSM_IDLE;
            }
            else
            {
                if(RTC_CHECK_I2C_FSM_ADDR) /* Address stage */
                {
                    /* INTR_MASTER_I2C_NACK:
                    * Master send address but it was NACKed by the slave: complete transaction.
                    */
                    if(RTC_CHECK_INTR_MASTER_MASKED(RTC_INTR_MASTER_I2C_NACK))
                    {
                        RTC_ClearMasterInterruptSource(RTC_INTR_MASTER_I2C_NACK);

                        RTC_mstrStatus |= (uint16) (RTC_I2C_MSTAT_ERR_XFER |
                                                                 RTC_I2C_MSTAT_ERR_ADDR_NAK);

                        endTransfer = RTC_I2C_CMPLT_ANY_TRANSFER;
                    }
                    /* INTR_TX_UNDERFLOW. The address byte was sent:
                    *  - TX direction: the clock is stretched after ACK phase, because TX FIFO is
                    *    EMPTY. The TX EMPTY clean all TX interrupt sources.
                    *  - RX direction: the 1st byte is receiving, but there is no ACK permision,
                    *    clock is stretched after 1 byte will be received.
                    */
                    else
                    {
                        if(RTC_CHECK_I2C_FSM_RD) /* Reading */
                        {
                            RTC_state = RTC_I2C_FSM_MSTR_RD_DATA;
                        }
                        else /* Writing */
                        {
                            RTC_state = RTC_I2C_FSM_MSTR_WR_DATA;
                            RTC_SetTxInterruptMode(RTC_INTR_TX_EMPTY);
                        }
                    }
                }

                if(RTC_CHECK_I2C_FSM_DATA) /* Data phase */
                {
                    if(RTC_CHECK_I2C_FSM_RD) /* Reading */
                    {
                        /* INTR_RX_FULL:
                        * RX direction: master received 8 bytes, the 9th byte is receiving.
                        * Get data from RX FIFO and decide whether to ACK or  NACK following bytes.
                        */
                        if(RTC_CHECK_INTR_RX_MASKED(RTC_INTR_RX_FULL))
                        {
                            /* Calculate difference */
                            diffCount =  RTC_mstrRdBufSize -
                                        (RTC_mstrRdBufIndex + RTC_GET_RX_FIFO_ENTRIES);

                            /* Proceed transaction or end it when RX FIFO
                             * become FULL again .
                            */
                            if(diffCount > RTC_FIFO_SIZE)
                            {
                                diffCount = RTC_FIFO_SIZE;
                            }
                            else
                            {
                                if(0u == diffCount)
                                {
                                    RTC_DISABLE_MASTER_AUTO_DATA_ACK;

                                    diffCount   = RTC_FIFO_SIZE;
                                    endTransfer = RTC_I2C_CMPLT_ANY_TRANSFER;
                                }
                            }

                            for(;(0u != diffCount);diffCount--)
                            {
                                RTC_mstrRdBufPtr[RTC_mstrRdBufIndex] = (uint8)
                                                                                        RTC_RX_FIFO_RD_REG;
                                RTC_mstrRdBufIndex++;
                            }
                        }
                        /* INTR_RX_NOT_EMPTY:
                        * RX direction: master received one data byte need to ACK or NACK.
                        * The last byte is stored and NACKed by the master. The NACK and Stop is
                        * generated by one command generate Stop.
                        */
                        else if(RTC_CHECK_INTR_RX_MASKED(RTC_INTR_RX_NOT_EMPTY))
                        {
                            /* Put data in the component buffer */
                            RTC_mstrRdBufPtr[RTC_mstrRdBufIndex] = (uint8) RTC_RX_FIFO_RD_REG;
                            RTC_mstrRdBufIndex++;

                            if(RTC_mstrRdBufIndex < RTC_mstrRdBufSize)
                            {
                                RTC_I2C_MASTER_GENERATE_ACK;
                            }
                            else
                            {
                               endTransfer = RTC_I2C_CMPLT_ANY_TRANSFER;
                            }
                        }
                        else
                        {
                            /* Does nothing */
                        }

                        RTC_ClearRxInterruptSource(RTC_INTR_RX_ALL);
                    }
                    else /* Writing */
                    {
                        /* INTR_MASTER_I2C_NACK :
                        * Master writes data to the slave and NACK was received: not all bytes were
                        * written to the slave from TX FIFO. Revert index if there is data in
                        * TX FIFO and pass control to complete transfer.
                        */
                        if(RTC_CHECK_INTR_MASTER_MASKED(RTC_INTR_MASTER_I2C_NACK))
                        {
                            RTC_ClearMasterInterruptSource(RTC_INTR_MASTER_I2C_NACK);

                            /* Rollback the write buffer index: the NACKed byte remains in the shifter */
                            RTC_mstrWrBufIndexTmp -= (RTC_GET_TX_FIFO_ENTRIES +
                                                                   RTC_GET_TX_FIFO_SR_VALID);

                            /* Update number of transfered bytes */
                            RTC_mstrWrBufIndex = RTC_mstrWrBufIndexTmp;

                            RTC_mstrStatus |= (uint16) (RTC_I2C_MSTAT_ERR_XFER |
                                                                     RTC_I2C_MSTAT_ERR_SHORT_XFER);

                            RTC_CLEAR_TX_FIFO;

                            endTransfer = RTC_I2C_CMPLT_ANY_TRANSFER;
                        }
                        /* INTR_TX_EMPTY :
                        * TX direction: the TX FIFO is EMPTY, the data from buffer need be put there.
                        * When there is no data in the component buffer, underflow interrupt is
                        * enabled to catch when all data will be transfered.
                        */
                        else if(RTC_CHECK_INTR_TX_MASKED(RTC_INTR_TX_EMPTY))
                        {
                            while(RTC_FIFO_SIZE != RTC_GET_TX_FIFO_ENTRIES)
                            {
                                /* The temporary mstrWrBufIndexTmp is used because slave could NACK the byte and index
                                * roll-back required in this case. The mstrWrBufIndex is updated at the end of transfer
                                */
                                if(RTC_mstrWrBufIndexTmp < RTC_mstrWrBufSize)
                                {
                                    /* Put data into TX FIFO */
                                    RTC_TX_FIFO_WR_REG = (uint32) RTC_mstrWrBufPtr[RTC_mstrWrBufIndexTmp];
                                    RTC_mstrWrBufIndexTmp++;
                                }
                                else
                                {
                                    break; /* No more data to put */
                                }
                            }

                            if(RTC_mstrWrBufIndexTmp == RTC_mstrWrBufSize)
                            {
                                RTC_SetTxInterruptMode(RTC_INTR_TX_UNDERFLOW);
                            }

                            RTC_ClearTxInterruptSource(RTC_INTR_TX_ALL);
                        }
                        /* INTR_TX_UNDERFLOW:
                        * TX direction: all data from TX FIFO was transfered to the slave.
                        * The transaction need to be completed.
                        */
                        else if(RTC_CHECK_INTR_TX_MASKED(RTC_INTR_TX_UNDERFLOW))
                        {
                            /* Update number of transfered bytes */
                            RTC_mstrWrBufIndex = RTC_mstrWrBufIndexTmp;

                            endTransfer = RTC_I2C_CMPLT_ANY_TRANSFER;
                        }
                        else
                        {
                            /* Does nothing */
                        }
                    }
                }

                if(0u != endTransfer) /* Complete transfer */
                {
                    /* Clean-up master after reading: only in case of NACK */
                    RTC_DISABLE_MASTER_AUTO_DATA_ACK;

                    /* Disable data processing interrupts: they should be cleared before */
                    RTC_SetRxInterruptMode(RTC_NO_INTR_SOURCES);
                    RTC_SetTxInterruptMode(RTC_NO_INTR_SOURCES);

                    if(RTC_CHECK_I2C_MODE_NO_STOP(RTC_mstrControl))
                    {
                        /* On-going transaction is suspend: the ReStart is generated by API request */
                        RTC_mstrStatus |= (uint16) (RTC_I2C_MSTAT_XFER_HALT |
                                                                 RTC_GET_I2C_MSTAT_CMPLT);

                        RTC_state = RTC_I2C_FSM_MSTR_HALT;
                    }
                    else
                    {
                        /* Complete transaction: exclude data processing state and generate Stop.
                        * The completion status will be set after Stop generation.
                        * Specail case is read: because NACK and Stop is genered.
                        * The lost arbitration could occur while NACK generation
                        * (other master still reading and ACK is generated)
                        */
                        RTC_I2C_MASTER_GENERATE_STOP;
                    }
                }
            }

        } /* (RTC_I2C_MASTER) */
        #endif

    } /* (RTC_CHECK_I2C_FSM_MASTER) */


    /* FSM Slave */
    else if(RTC_CHECK_I2C_FSM_SLAVE)
    {
        #if(RTC_I2C_SLAVE)
        {
            /* INTR_SLAVE_NACK:
            * The master completes reading the slave: the approprite flags have to be set.
            * The TX FIFO cleared after overflow condition is set.
            */
            if(RTC_CHECK_INTR_SLAVE_MASKED(RTC_INTR_SLAVE_I2C_NACK))
            {
                RTC_ClearSlaveInterruptSource(RTC_INTR_SLAVE_I2C_NACK);

                /* All entries that remain in TX FIFO max value is 9: 8 (FIFO) + 1 (SHIFTER) */
                diffCount = (RTC_GET_TX_FIFO_ENTRIES + RTC_GET_TX_FIFO_SR_VALID);

                if(RTC_slOverFlowCount > diffCount) /* Overflow */
                {
                    RTC_slStatus |= (uint8) RTC_I2C_SSTAT_RD_OVFL;
                }
                else /* No Overflow */
                {
                    /* Roll-back the temporay index */
                    RTC_slRdBufIndexTmp -= (diffCount - RTC_slOverFlowCount);
                }

                /* Update slave of tranfered bytes */
                RTC_slRdBufIndex = RTC_slRdBufIndexTmp;

                /* Clean-up TX FIFO */
                RTC_SetTxInterruptMode(RTC_NO_INTR_SOURCES);
                RTC_slOverFlowCount = 0u;
                RTC_CLEAR_TX_FIFO;

                /* Complete master reading */
                RTC_slStatus &= (uint8) ~RTC_I2C_SSTAT_RD_BUSY;
                RTC_slStatus |= (uint8)  RTC_I2C_SSTAT_RD_CMPLT;
                RTC_state     =  RTC_I2C_FSM_IDLE;
            }


            /* INTR_SLAVE_I2C_WRITE_STOP:
            * The master completes writing to slave: the approprite flags have to be set.
            * The RX FIFO contains 1-8 bytes from previous transcation which need to be read.
            * There is possibility that RX FIFO contains address, it needs to leave it there.
            */
            if(RTC_CHECK_INTR_SLAVE_MASKED(RTC_INTR_SLAVE_I2C_WRITE_STOP))
            {
                RTC_ClearSlaveInterruptSource(RTC_INTR_SLAVE_I2C_WRITE_STOP);

                RTC_DISABLE_SLAVE_AUTO_DATA;

                while(0u != RTC_GET_RX_FIFO_ENTRIES)
                {
                    #if(RTC_CHECK_I2C_ACCEPT_ADDRESS)
                    {
                        if((1u == RTC_GET_RX_FIFO_ENTRIES) &&
                           (RTC_CHECK_INTR_SLAVE_MASKED(RTC_INTR_SLAVE_I2C_ADDR_MATCH)))
                        {
                            break; /* Leave address in RX FIFO */
                        }
                    }
                    #endif

                    /* Put data in the component buffer */
                    RTC_slWrBufPtr[RTC_slWrBufIndex] = (uint8) RTC_RX_FIFO_RD_REG;
                    RTC_slWrBufIndex++;
                }

                if(RTC_CHECK_INTR_RX(RTC_INTR_RX_OVERFLOW))
                {
                    RTC_slStatus |= (uint8) RTC_I2C_SSTAT_WR_OVFL;
                }

                /* Clears RX interrupt sources triggered on data receiving */
                RTC_ClearRxInterruptSource(RTC_INTR_RX_ALL);

                /* Complete master writing */
                RTC_slStatus &= (uint8) ~RTC_I2C_SSTAT_WR_BUSY;
                RTC_slStatus |= (uint8)  RTC_I2C_SSTAT_WR_CMPLT;
                RTC_state     =  RTC_I2C_FSM_IDLE;
            }


            /* INTR_SLAVE_I2C_ADDR_MATCH:
            * The address match event starts the slave operation: after leaving the TX or RX
            * direction has to chosen.
            * The wakeup interrupt must be cleared only after address match is set.
            */
            if(RTC_CHECK_INTR_SLAVE_MASKED(RTC_INTR_SLAVE_I2C_ADDR_MATCH))
            {
                #if(RTC_CHECK_I2C_ACCEPT_ADDRESS) /* Address in RX FIFO */
                {
                    address  = RTC_RX_FIFO_RD_REG;

                    /* Clears RX sources if address was received in the RX FIFO */
                    RTC_ClearRxInterruptSource(RTC_INTR_RX_ALL);

                    if(0u != address)
                    {
                        /* Suppress compiler warning */
                    }
                }
                #endif

                if(RTC_CHECK_I2C_STATUS(RTC_I2C_STATUS_S_READ))
                /* TX direction: master reads from slave */
                {
                    RTC_SetTxInterruptMode(RTC_INTR_TX_EMPTY);

                    /* Set temporary index to address buffer clear from API */
                    RTC_slRdBufIndexTmp = RTC_slRdBufIndex;

                    /* Start master reading */
                    RTC_slStatus |= (uint8) RTC_I2C_SSTAT_RD_BUSY;
                    RTC_state     = RTC_I2C_FSM_SL_RD;
                }
                else
                /* RX direction: master writes into slave */
                {
                    /* Calculate available buffer size */
                    diffCount = (RTC_slWrBufSize - RTC_slWrBufIndex);

                    if(diffCount < RTC_FIFO_SIZE)
                    /* Receive data: byte-by-byte */
                    {
                        RTC_SetRxInterruptMode(RTC_INTR_RX_NOT_EMPTY);
                    }
                    else
                    /* Receive data: into RX FIFO */
                    {
                        if(diffCount == RTC_FIFO_SIZE)
                        {
                            /* NACK when RX FIFO become FULL */
                            RTC_ENABLE_SLAVE_AUTO_DATA;
                        }
                        else
                        {
                            /* Stretch clock when RX FIFO becomes FULL */
                            RTC_ENABLE_SLAVE_AUTO_DATA_ACK;
                            RTC_SetRxInterruptMode(RTC_INTR_RX_FULL);
                        }
                    }

                    /* Start master reading */
                    RTC_slStatus |= (uint8) RTC_I2C_SSTAT_WR_BUSY;
                    RTC_state     = RTC_I2C_FSM_SL_WR;
                }

                /* Clear interrupts before ACK address */
                RTC_ClearI2CExtClkInterruptSource(RTC_INTR_I2C_EC_WAKE_UP);
                RTC_ClearSlaveInterruptSource(RTC_INTR_SLAVE_ALL);

                /* The preparation complete: ACK the address */
                RTC_I2C_SLAVE_GENERATE_ACK;
            }

            /* RTC_INTR_RX_FULL":
            * Get data from RX FIFO and decide whether to ACK or NACK following bytes
            */
            if(RTC_CHECK_INTR_RX_MASKED(RTC_INTR_RX_FULL))
            {
                /* Calculate available buffer size take to account that RX FIFO is FULL */
                diffCount =  RTC_slWrBufSize -
                            (RTC_slWrBufIndex + RTC_FIFO_SIZE);

                if(diffCount > RTC_FIFO_SIZE) /* Proceed transaction */
                {
                    diffCount   = RTC_FIFO_SIZE;
                    endTransfer = 0u;  /* Continue active transfer */
                }
                else /* End when FIFO becomes FULL again */
                {
                    endTransfer = RTC_I2C_CMPLT_ANY_TRANSFER;
                }

                for(;(0u != diffCount);diffCount--)
                {
                    /* Put data in the component buffer */
                    RTC_slWrBufPtr[RTC_slWrBufIndex] = (uint8) RTC_RX_FIFO_RD_REG;
                    RTC_slWrBufIndex++;
                }

                if(0u != endTransfer) /* End transfer sending NACK */
                {
                    RTC_ENABLE_SLAVE_AUTO_DATA_NACK;

                    /* The INTR_RX_FULL triggers earlier then INTR_SLAVE_I2C_STOP:
                    * disable all RX interrupt sources.
                    */
                    RTC_SetRxInterruptMode(RTC_NO_INTR_SOURCES);
                }

                RTC_ClearRxInterruptSource(RTC_INTR_RX_FULL);
            }
            /* RTC_INTR_RX_NOT_EMPTY:
            * The buffer size is less than 8: it requires processing in byte-by-byte mode.
            */
            else if(RTC_CHECK_INTR_RX_MASKED(RTC_INTR_RX_NOT_EMPTY))
            {
                diffCount = RTC_RX_FIFO_RD_REG;

                if(RTC_slWrBufIndex < RTC_slWrBufSize)
                {
                    RTC_I2C_SLAVE_GENERATE_ACK;

                    /* Put data into component buffer */
                    RTC_slWrBufPtr[RTC_slWrBufIndex] = (uint8) diffCount;
                    RTC_slWrBufIndex++;
                }
                else /* Overflow: there is no space in the write buffer */
                {
                    RTC_I2C_SLAVE_GENERATE_NACK;

                    RTC_slStatus |= (uint8) RTC_I2C_SSTAT_WR_OVFL;
                }

                RTC_ClearRxInterruptSource(RTC_INTR_RX_NOT_EMPTY);
            }
            else
            {
                /* Does nothing */
            }


            /* RTC_INTR_TX_EMPTY:
            * Master reads slave: provide data to read or 0xFF in case end of the buffer
            * The overflow condition must be captured, but not set until the end of transaction.
            * There is possibility of false overflow due of TX FIFO utilization.
            */
            if(RTC_CHECK_INTR_TX_MASKED(RTC_INTR_TX_EMPTY))
            {
                while(RTC_FIFO_SIZE != RTC_GET_TX_FIFO_ENTRIES)
                {
                    /* The temporary slRdBufIndexTmp is used because master could NACK the byte and
                    * index roll-back required in this case. The slRdBufIndex is updated at the end
                    * of the read transfer.
                    */
                    if(RTC_slRdBufIndexTmp < RTC_slRdBufSize)
                    /* Data from buffer */
                    {
                        RTC_TX_FIFO_WR_REG = (uint32) RTC_slRdBufPtr[RTC_slRdBufIndexTmp];
                        RTC_slRdBufIndexTmp++;
                    }
                    else
                    /* Probably Overflow */
                    {
                        RTC_TX_FIFO_WR_REG = RTC_I2C_SLAVE_OVFL_RETURN;

                        if(0u == (RTC_INTR_TX_OVERFLOW & RTC_slOverFlowCount))
                        {
                            /* Get counter in range of the byte: the value 10 is overflow */
                            RTC_slOverFlowCount++;
                        }
                    }
                }

                RTC_ClearTxInterruptSource(RTC_INTR_TX_EMPTY);
            }

        }  /* (RTC_I2C_SLAVE) */
        #endif
    }


    /* FSM EXIT:
    * Interrupt sources get here are errors:
    * Slave:  INTR_SLAVE_I2C_BUS_ERROR, INTR_SLAVE_I2C_ARB_LOST
    * Master: INTR_MASTER_I2C_BUS_ERROR, INTR_MASTER_I2C_ARB_LOST.
    */
    else
    {
        /* Clean the Slave and Master sources before reset */
        RTC_ClearSlaveInterruptSource(RTC_INTR_SLAVE_ALL);
        RTC_ClearMasterInterruptSource(RTC_INTR_MASTER_ALL);

        /* Re-enable SCB block: this resets part of functions */
        enableInterrupts = CyEnterCriticalSection();
        RTC_SCB_SW_RESET;
        CyExitCriticalSection(enableInterrupts);

        /* Clenup:
        * All other status and control bits can be cleared later.
        * Slave AUTO data ACK never happens before address ACK.
        * Slave TX and RX sources are used only after address match.
        * Master AUTO data ACK is under API control.
        * Master interrupt sources does not care after any error.
        * Master TX and RX sources are under API control.
        */

        /* Disable auto NACK before clear the FIFOs */
        RTC_DISABLE_SLAVE_AUTO_DATA_ACK;
        RTC_DISABLE_MASTER_AUTO_DATA_ACK;

        RTC_SetRxInterruptMode(RTC_NO_INTR_SOURCES);
        RTC_SetTxInterruptMode(RTC_NO_INTR_SOURCES);
        RTC_ClearTxInterruptSource(RTC_INTR_RX_ALL);
        RTC_ClearRxInterruptSource(RTC_INTR_TX_ALL);

        RTC_state = RTC_I2C_FSM_IDLE;
    }
}


/* [] END OF FILE */
