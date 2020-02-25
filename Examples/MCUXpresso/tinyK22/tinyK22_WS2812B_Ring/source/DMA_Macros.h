/*
 * Copyright (c) 2020, Erich Styger
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef DMA_MACROS_H_
#define DMA_MACROS_H_

#define PDD_DISABLE 0u
#define PDD_ENABLE  1u

/* DMA - Register accessors */
#define DMA_CR_REG(base)                         ((base)->CR)
#define DMA_ES_REG(base)                         ((base)->ES)
#define DMA_ERQ_REG(base)                        ((base)->ERQ)
#define DMA_EEI_REG(base)                        ((base)->EEI)
#define DMA_CEEI_REG(base)                       ((base)->CEEI)
#define DMA_SEEI_REG(base)                       ((base)->SEEI)
#define DMA_CERQ_REG(base)                       ((base)->CERQ)
#define DMA_SERQ_REG(base)                       ((base)->SERQ)
#define DMA_CDNE_REG(base)                       ((base)->CDNE)
#define DMA_SSRT_REG(base)                       ((base)->SSRT)
#define DMA_CERR_REG(base)                       ((base)->CERR)
#define DMA_CINT_REG(base)                       ((base)->CINT)
#define DMA_INT_REG(base)                        ((base)->INT)
#define DMA_ERR_REG(base)                        ((base)->ERR)
#define DMA_HRS_REG(base)                        ((base)->HRS)
#define DMA_EARS_REG(base)                       ((base)->EARS)
#define DMA_DCHPRI3_REG(base)                    ((base)->DCHPRI3)
#define DMA_DCHPRI2_REG(base)                    ((base)->DCHPRI2)
#define DMA_DCHPRI1_REG(base)                    ((base)->DCHPRI1)
#define DMA_DCHPRI0_REG(base)                    ((base)->DCHPRI0)
#define DMA_DCHPRI7_REG(base)                    ((base)->DCHPRI7)
#define DMA_DCHPRI6_REG(base)                    ((base)->DCHPRI6)
#define DMA_DCHPRI5_REG(base)                    ((base)->DCHPRI5)
#define DMA_DCHPRI4_REG(base)                    ((base)->DCHPRI4)
#define DMA_DCHPRI11_REG(base)                   ((base)->DCHPRI11)
#define DMA_DCHPRI10_REG(base)                   ((base)->DCHPRI10)
#define DMA_DCHPRI9_REG(base)                    ((base)->DCHPRI9)
#define DMA_DCHPRI8_REG(base)                    ((base)->DCHPRI8)
#define DMA_DCHPRI15_REG(base)                   ((base)->DCHPRI15)
#define DMA_DCHPRI14_REG(base)                   ((base)->DCHPRI14)
#define DMA_DCHPRI13_REG(base)                   ((base)->DCHPRI13)
#define DMA_DCHPRI12_REG(base)                   ((base)->DCHPRI12)
#define DMA_SADDR_REG(base,index)                ((base)->TCD[index].SADDR)
#define DMA_SOFF_REG(base,index)                 ((base)->TCD[index].SOFF)
#define DMA_ATTR_REG(base,index)                 ((base)->TCD[index].ATTR)
#define DMA_NBYTES_MLNO_REG(base,index)          ((base)->TCD[index].NBYTES_MLNO)
#define DMA_NBYTES_MLOFFNO_REG(base,index)       ((base)->TCD[index].NBYTES_MLOFFNO)
#define DMA_NBYTES_MLOFFYES_REG(base,index)      ((base)->TCD[index].NBYTES_MLOFFYES)
#define DMA_SLAST_REG(base,index)                ((base)->TCD[index].SLAST)
#define DMA_DADDR_REG(base,index)                ((base)->TCD[index].DADDR)
#define DMA_DOFF_REG(base,index)                 ((base)->TCD[index].DOFF)
#define DMA_CITER_ELINKNO_REG(base,index)        ((base)->TCD[index].CITER_ELINKNO)
#define DMA_CITER_ELINKYES_REG(base,index)       ((base)->TCD[index].CITER_ELINKYES)
#define DMA_DLAST_SGA_REG(base,index)            ((base)->TCD[index].DLAST_SGA)
#define DMA_CSR_REG(base,index)                  ((base)->TCD[index].CSR)
#define DMA_BITER_ELINKNO_REG(base,index)        ((base)->TCD[index].BITER_ELINKNO)
#define DMA_BITER_ELINKYES_REG(base,index)       ((base)->TCD[index].BITER_ELINKYES)

/* DMA - Register instance definitions */
/* DMA */
#define DMA_CR                                   DMA_CR_REG(DMA_BASE_PTR)
#define DMA_ES                                   DMA_ES_REG(DMA_BASE_PTR)
#define DMA_ERQ                                  DMA_ERQ_REG(DMA_BASE_PTR)
#define DMA_EEI                                  DMA_EEI_REG(DMA_BASE_PTR)
#define DMA_CEEI                                 DMA_CEEI_REG(DMA_BASE_PTR)
#define DMA_SEEI                                 DMA_SEEI_REG(DMA_BASE_PTR)
#define DMA_CERQ                                 DMA_CERQ_REG(DMA_BASE_PTR)
#define DMA_SERQ                                 DMA_SERQ_REG(DMA_BASE_PTR)
#define DMA_CDNE                                 DMA_CDNE_REG(DMA_BASE_PTR)
#define DMA_SSRT                                 DMA_SSRT_REG(DMA_BASE_PTR)
#define DMA_CERR                                 DMA_CERR_REG(DMA_BASE_PTR)
#define DMA_CINT                                 DMA_CINT_REG(DMA_BASE_PTR)
#define DMA_INT                                  DMA_INT_REG(DMA_BASE_PTR)
#define DMA_ERR                                  DMA_ERR_REG(DMA_BASE_PTR)
#define DMA_HRS                                  DMA_HRS_REG(DMA_BASE_PTR)
#define DMA_EARS                                 DMA_EARS_REG(DMA_BASE_PTR)
#define DMA_DCHPRI3                              DMA_DCHPRI3_REG(DMA_BASE_PTR)
#define DMA_DCHPRI2                              DMA_DCHPRI2_REG(DMA_BASE_PTR)
#define DMA_DCHPRI1                              DMA_DCHPRI1_REG(DMA_BASE_PTR)
#define DMA_DCHPRI0                              DMA_DCHPRI0_REG(DMA_BASE_PTR)
#define DMA_DCHPRI7                              DMA_DCHPRI7_REG(DMA_BASE_PTR)
#define DMA_DCHPRI6                              DMA_DCHPRI6_REG(DMA_BASE_PTR)
#define DMA_DCHPRI5                              DMA_DCHPRI5_REG(DMA_BASE_PTR)
#define DMA_DCHPRI4                              DMA_DCHPRI4_REG(DMA_BASE_PTR)
#define DMA_DCHPRI11                             DMA_DCHPRI11_REG(DMA_BASE_PTR)
#define DMA_DCHPRI10                             DMA_DCHPRI10_REG(DMA_BASE_PTR)
#define DMA_DCHPRI9                              DMA_DCHPRI9_REG(DMA_BASE_PTR)
#define DMA_DCHPRI8                              DMA_DCHPRI8_REG(DMA_BASE_PTR)
#define DMA_DCHPRI15                             DMA_DCHPRI15_REG(DMA_BASE_PTR)
#define DMA_DCHPRI14                             DMA_DCHPRI14_REG(DMA_BASE_PTR)
#define DMA_DCHPRI13                             DMA_DCHPRI13_REG(DMA_BASE_PTR)
#define DMA_DCHPRI12                             DMA_DCHPRI12_REG(DMA_BASE_PTR)
#define DMA_TCD0_SADDR                           DMA_SADDR_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_SOFF                            DMA_SOFF_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_ATTR                            DMA_ATTR_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_NBYTES_MLNO                     DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_NBYTES_MLOFFNO                  DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_NBYTES_MLOFFYES                 DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_SLAST                           DMA_SLAST_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_DADDR                           DMA_DADDR_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_DOFF                            DMA_DOFF_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_CITER_ELINKNO                   DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_CITER_ELINKYES                  DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_DLASTSGA                        DMA_DLAST_SGA_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_CSR                             DMA_CSR_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_BITER_ELINKNO                   DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,0)
#define DMA_TCD0_BITER_ELINKYES                  DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,0)
#define DMA_TCD1_SADDR                           DMA_SADDR_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_SOFF                            DMA_SOFF_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_ATTR                            DMA_ATTR_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_NBYTES_MLNO                     DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_NBYTES_MLOFFNO                  DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_NBYTES_MLOFFYES                 DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_SLAST                           DMA_SLAST_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_DADDR                           DMA_DADDR_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_DOFF                            DMA_DOFF_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_CITER_ELINKNO                   DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_CITER_ELINKYES                  DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_DLASTSGA                        DMA_DLAST_SGA_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_CSR                             DMA_CSR_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_BITER_ELINKNO                   DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,1)
#define DMA_TCD1_BITER_ELINKYES                  DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,1)
#define DMA_TCD2_SADDR                           DMA_SADDR_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_SOFF                            DMA_SOFF_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_ATTR                            DMA_ATTR_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_NBYTES_MLNO                     DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_NBYTES_MLOFFNO                  DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_NBYTES_MLOFFYES                 DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_SLAST                           DMA_SLAST_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_DADDR                           DMA_DADDR_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_DOFF                            DMA_DOFF_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_CITER_ELINKNO                   DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_CITER_ELINKYES                  DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_DLASTSGA                        DMA_DLAST_SGA_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_CSR                             DMA_CSR_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_BITER_ELINKNO                   DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,2)
#define DMA_TCD2_BITER_ELINKYES                  DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,2)
#define DMA_TCD3_SADDR                           DMA_SADDR_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_SOFF                            DMA_SOFF_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_ATTR                            DMA_ATTR_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_NBYTES_MLNO                     DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_NBYTES_MLOFFNO                  DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_NBYTES_MLOFFYES                 DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_SLAST                           DMA_SLAST_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_DADDR                           DMA_DADDR_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_DOFF                            DMA_DOFF_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_CITER_ELINKNO                   DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_CITER_ELINKYES                  DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_DLASTSGA                        DMA_DLAST_SGA_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_CSR                             DMA_CSR_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_BITER_ELINKNO                   DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,3)
#define DMA_TCD3_BITER_ELINKYES                  DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,3)
#define DMA_TCD4_SADDR                           DMA_SADDR_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_SOFF                            DMA_SOFF_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_ATTR                            DMA_ATTR_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_NBYTES_MLNO                     DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_NBYTES_MLOFFNO                  DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_NBYTES_MLOFFYES                 DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_SLAST                           DMA_SLAST_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_DADDR                           DMA_DADDR_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_DOFF                            DMA_DOFF_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_CITER_ELINKNO                   DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_CITER_ELINKYES                  DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_DLASTSGA                        DMA_DLAST_SGA_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_CSR                             DMA_CSR_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_BITER_ELINKNO                   DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,4)
#define DMA_TCD4_BITER_ELINKYES                  DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,4)
#define DMA_TCD5_SADDR                           DMA_SADDR_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_SOFF                            DMA_SOFF_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_ATTR                            DMA_ATTR_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_NBYTES_MLNO                     DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_NBYTES_MLOFFNO                  DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_NBYTES_MLOFFYES                 DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_SLAST                           DMA_SLAST_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_DADDR                           DMA_DADDR_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_DOFF                            DMA_DOFF_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_CITER_ELINKNO                   DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_CITER_ELINKYES                  DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_DLASTSGA                        DMA_DLAST_SGA_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_CSR                             DMA_CSR_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_BITER_ELINKNO                   DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,5)
#define DMA_TCD5_BITER_ELINKYES                  DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,5)
#define DMA_TCD6_SADDR                           DMA_SADDR_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_SOFF                            DMA_SOFF_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_ATTR                            DMA_ATTR_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_NBYTES_MLNO                     DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_NBYTES_MLOFFNO                  DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_NBYTES_MLOFFYES                 DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_SLAST                           DMA_SLAST_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_DADDR                           DMA_DADDR_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_DOFF                            DMA_DOFF_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_CITER_ELINKNO                   DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_CITER_ELINKYES                  DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_DLASTSGA                        DMA_DLAST_SGA_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_CSR                             DMA_CSR_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_BITER_ELINKNO                   DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,6)
#define DMA_TCD6_BITER_ELINKYES                  DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,6)
#define DMA_TCD7_SADDR                           DMA_SADDR_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_SOFF                            DMA_SOFF_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_ATTR                            DMA_ATTR_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_NBYTES_MLNO                     DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_NBYTES_MLOFFNO                  DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_NBYTES_MLOFFYES                 DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_SLAST                           DMA_SLAST_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_DADDR                           DMA_DADDR_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_DOFF                            DMA_DOFF_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_CITER_ELINKNO                   DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_CITER_ELINKYES                  DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_DLASTSGA                        DMA_DLAST_SGA_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_CSR                             DMA_CSR_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_BITER_ELINKNO                   DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,7)
#define DMA_TCD7_BITER_ELINKYES                  DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,7)
#define DMA_TCD8_SADDR                           DMA_SADDR_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_SOFF                            DMA_SOFF_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_ATTR                            DMA_ATTR_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_NBYTES_MLNO                     DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_NBYTES_MLOFFNO                  DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_NBYTES_MLOFFYES                 DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_SLAST                           DMA_SLAST_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_DADDR                           DMA_DADDR_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_DOFF                            DMA_DOFF_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_CITER_ELINKNO                   DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_CITER_ELINKYES                  DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_DLASTSGA                        DMA_DLAST_SGA_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_CSR                             DMA_CSR_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_BITER_ELINKNO                   DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,8)
#define DMA_TCD8_BITER_ELINKYES                  DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,8)
#define DMA_TCD9_SADDR                           DMA_SADDR_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_SOFF                            DMA_SOFF_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_ATTR                            DMA_ATTR_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_NBYTES_MLNO                     DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_NBYTES_MLOFFNO                  DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_NBYTES_MLOFFYES                 DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_SLAST                           DMA_SLAST_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_DADDR                           DMA_DADDR_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_DOFF                            DMA_DOFF_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_CITER_ELINKNO                   DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_CITER_ELINKYES                  DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_DLASTSGA                        DMA_DLAST_SGA_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_CSR                             DMA_CSR_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_BITER_ELINKNO                   DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,9)
#define DMA_TCD9_BITER_ELINKYES                  DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,9)
#define DMA_TCD10_SADDR                          DMA_SADDR_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_SOFF                           DMA_SOFF_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_ATTR                           DMA_ATTR_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_NBYTES_MLNO                    DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_NBYTES_MLOFFNO                 DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_NBYTES_MLOFFYES                DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_SLAST                          DMA_SLAST_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_DADDR                          DMA_DADDR_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_DOFF                           DMA_DOFF_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_CITER_ELINKNO                  DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_CITER_ELINKYES                 DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_DLASTSGA                       DMA_DLAST_SGA_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_CSR                            DMA_CSR_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_BITER_ELINKNO                  DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,10)
#define DMA_TCD10_BITER_ELINKYES                 DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,10)
#define DMA_TCD11_SADDR                          DMA_SADDR_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_SOFF                           DMA_SOFF_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_ATTR                           DMA_ATTR_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_NBYTES_MLNO                    DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_NBYTES_MLOFFNO                 DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_NBYTES_MLOFFYES                DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_SLAST                          DMA_SLAST_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_DADDR                          DMA_DADDR_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_DOFF                           DMA_DOFF_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_CITER_ELINKNO                  DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_CITER_ELINKYES                 DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_DLASTSGA                       DMA_DLAST_SGA_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_CSR                            DMA_CSR_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_BITER_ELINKNO                  DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,11)
#define DMA_TCD11_BITER_ELINKYES                 DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,11)
#define DMA_TCD12_SADDR                          DMA_SADDR_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_SOFF                           DMA_SOFF_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_ATTR                           DMA_ATTR_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_NBYTES_MLNO                    DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_NBYTES_MLOFFNO                 DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_NBYTES_MLOFFYES                DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_SLAST                          DMA_SLAST_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_DADDR                          DMA_DADDR_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_DOFF                           DMA_DOFF_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_CITER_ELINKNO                  DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_CITER_ELINKYES                 DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_DLASTSGA                       DMA_DLAST_SGA_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_CSR                            DMA_CSR_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_BITER_ELINKNO                  DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,12)
#define DMA_TCD12_BITER_ELINKYES                 DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,12)
#define DMA_TCD13_SADDR                          DMA_SADDR_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_SOFF                           DMA_SOFF_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_ATTR                           DMA_ATTR_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_NBYTES_MLNO                    DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_NBYTES_MLOFFNO                 DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_NBYTES_MLOFFYES                DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_SLAST                          DMA_SLAST_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_DADDR                          DMA_DADDR_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_DOFF                           DMA_DOFF_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_CITER_ELINKNO                  DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_CITER_ELINKYES                 DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_DLASTSGA                       DMA_DLAST_SGA_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_CSR                            DMA_CSR_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_BITER_ELINKNO                  DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,13)
#define DMA_TCD13_BITER_ELINKYES                 DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,13)
#define DMA_TCD14_SADDR                          DMA_SADDR_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_SOFF                           DMA_SOFF_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_ATTR                           DMA_ATTR_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_NBYTES_MLNO                    DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_NBYTES_MLOFFNO                 DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_NBYTES_MLOFFYES                DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_SLAST                          DMA_SLAST_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_DADDR                          DMA_DADDR_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_DOFF                           DMA_DOFF_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_CITER_ELINKNO                  DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_CITER_ELINKYES                 DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_DLASTSGA                       DMA_DLAST_SGA_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_CSR                            DMA_CSR_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_BITER_ELINKNO                  DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,14)
#define DMA_TCD14_BITER_ELINKYES                 DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,14)
#define DMA_TCD15_SADDR                          DMA_SADDR_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_SOFF                           DMA_SOFF_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_ATTR                           DMA_ATTR_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_NBYTES_MLNO                    DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_NBYTES_MLOFFNO                 DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_NBYTES_MLOFFYES                DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_SLAST                          DMA_SLAST_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_DADDR                          DMA_DADDR_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_DOFF                           DMA_DOFF_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_CITER_ELINKNO                  DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_CITER_ELINKYES                 DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_DLASTSGA                       DMA_DLAST_SGA_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_CSR                            DMA_CSR_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_BITER_ELINKNO                  DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,15)
#define DMA_TCD15_BITER_ELINKYES                 DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,15)

/* DMA - Register array accessors */
#define DMA_SADDR(index)                         DMA_SADDR_REG(DMA_BASE_PTR,index)
#define DMA_SOFF(index)                          DMA_SOFF_REG(DMA_BASE_PTR,index)
#define DMA_ATTR(index)                          DMA_ATTR_REG(DMA_BASE_PTR,index)
#define DMA_NBYTES_MLNO(index)                   DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,index)
#define DMA_NBYTES_MLOFFNO(index)                DMA_NBYTES_MLOFFNO_REG(DMA_BASE_PTR,index)
#define DMA_NBYTES_MLOFFYES(index)               DMA_NBYTES_MLOFFYES_REG(DMA_BASE_PTR,index)
#define DMA_SLAST(index)                         DMA_SLAST_REG(DMA_BASE_PTR,index)
#define DMA_DADDR(index)                         DMA_DADDR_REG(DMA_BASE_PTR,index)
#define DMA_DOFF(index)                          DMA_DOFF_REG(DMA_BASE_PTR,index)
#define DMA_CITER_ELINKNO(index)                 DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,index)
#define DMA_CITER_ELINKYES(index)                DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,index)
#define DMA_DLAST_SGA(index)                     DMA_DLAST_SGA_REG(DMA_BASE_PTR,index)
#define DMA_CSR(index)                           DMA_CSR_REG(DMA_BASE_PTR,index)
#define DMA_BITER_ELINKNO(index)                 DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,index)
#define DMA_BITER_ELINKYES(index)                DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,index)

/* DMA data transfer block size. */
  #define DMA_PDD_8_BIT   0U                       /**< 8-bit transfer size. */
  #define DMA_PDD_16_BIT  0x1U                     /**< 16-bit transfer size. */
  #define DMA_PDD_32_BIT  0x2U                     /**< 32-bit transfer size. */
  #define DMA_PDD_16_BYTE 0x4U                     /**< 16-byte transfer size. */
  #define DMA_PDD_32_BYTE 0x5U                     /**< 32-byte transfer size. */

/* DMA channel number constants */
  #define DMA_PDD_CHANNEL_0  0U                    /**< Channel 0. */
  #define DMA_PDD_CHANNEL_1  0x1U                  /**< Channel 1. */
  #define DMA_PDD_CHANNEL_2  0x2U                  /**< Channel 2. */
  #define DMA_PDD_CHANNEL_3  0x3U                  /**< Channel 3. */
  #define DMA_PDD_CHANNEL_4  0x4U                  /**< Channel 4. */
  #define DMA_PDD_CHANNEL_5  0x5U                  /**< Channel 5. */
  #define DMA_PDD_CHANNEL_6  0x6U                  /**< Channel 6. */
  #define DMA_PDD_CHANNEL_7  0x7U                  /**< Channel 7. */
  #define DMA_PDD_CHANNEL_8  0x8U                  /**< Channel 8. */
  #define DMA_PDD_CHANNEL_9  0x9U                  /**< Channel 9. */
  #define DMA_PDD_CHANNEL_10 0xAU                  /**< Channel 10. */
  #define DMA_PDD_CHANNEL_11 0xBU                  /**< Channel 11. */
  #define DMA_PDD_CHANNEL_12 0xCU                  /**< Channel 12. */
  #define DMA_PDD_CHANNEL_13 0xDU                  /**< Channel 13. */
  #define DMA_PDD_CHANNEL_14 0xEU                  /**< Channel 14. */
  #define DMA_PDD_CHANNEL_15 0xFU                  /**< Channel 15. */

/* Circular buffer size constants */
  #define DMA_PDD_CIRCULAR_BUFFER_DISABLED   0U    /**< Circular buffer disabled. */
  #define DMA_PDD_CIRCULAR_BUFFER_2_BYTES    0x1U  /**< 2 bytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_4_BYTES    0x2U  /**< 4 bytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_8_BYTES    0x3U  /**< 8 bytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_16_BYTES   0x4U  /**< 16 bytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_32_BYTES   0x5U  /**< 32 bytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_64_BYTES   0x6U  /**< 64 bytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_128_BYTES  0x7U  /**< 128 bytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_256_BYTES  0x8U  /**< 256 bytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_512_BYTES  0x9U  /**< 512 bytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_1_KBYTE    0xAU  /**< 1 Kbyte circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_2_KBYTES   0xBU  /**< 2 Kbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_4_KBYTES   0xCU  /**< 4 Kbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_8_KBYTES   0xDU  /**< 8 Kbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_16_KBYTES  0xEU  /**< 16 Kbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_32_KBYTES  0xFU  /**< 32 Kbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_64_KBYTES  0x10U /**< 64 Kbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_128_KBYTES 0x11U /**< 128 Kbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_256_KBYTES 0x12U /**< 256 Kbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_512_KBYTES 0x13U /**< 512 Kbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_1_MBYTE    0x14U /**< 1 Mbyte circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_2_MBYTES   0x15U /**< 2 Mbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_4_MBYTES   0x16U /**< 4 Mbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_8_MBYTES   0x17U /**< 8 Mbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_16_MBYTES  0x18U /**< 16 Mbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_32_MBYTES  0x19U /**< 32 Mbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_64_MBYTES  0x1AU /**< 64 Mbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_128_MBYTES 0x1BU /**< 128 Mbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_256_MBYTES 0x1CU /**< 256 Mbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_512_MBYTES 0x1DU /**< 512 Mbytes circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_1_GBYTE    0x1EU /**< 1 Gbyte circular buffer. */
  #define DMA_PDD_CIRCULAR_BUFFER_2_GBYTES   0x1FU /**< 2 Gbytes circular buffer. */

#define DMA_PDD_EnableMinorLoopMapping(PeripheralBase, State) ( \
    DMA_CR_REG(PeripheralBase) = \
     (uint32_t)(( \
      (uint32_t)(DMA_CR_REG(PeripheralBase) & (uint32_t)(~(uint32_t)DMA_CR_EMLM_MASK))) | ( \
      (uint32_t)((uint32_t)(State) << DMA_CR_EMLM_SHIFT))) \
  )
#define DMA_PDD_SetByteCount32(PeripheralBase, Channel, Value) ( \
    DMA_NBYTES_MLNO_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(Value) \
  )
#define DMA_PDD_SetSourceAddressModulo(PeripheralBase, Channel, Modulo) ( \
    DMA_ATTR_REG(PeripheralBase,(Channel)) = \
     (uint16_t)(( \
      (uint16_t)(( \
       DMA_ATTR_REG(PeripheralBase,(Channel))) & ( \
       (uint16_t)(~(uint16_t)DMA_ATTR_SMOD_MASK)))) | ( \
      (uint16_t)((uint16_t)(Modulo) << DMA_ATTR_SMOD_SHIFT))) \
  )
#define DMA_PDD_SetSourceAddressOffset(PeripheralBase, Channel, Offset) ( \
    DMA_SOFF_REG(PeripheralBase,(Channel)) = \
     (uint16_t)(Offset) \
  )
#define DMA_PDD_SetSourceDataTransferSize(PeripheralBase, Channel, Size) ( \
    DMA_ATTR_REG(PeripheralBase,(Channel)) = \
     (uint16_t)(( \
      (uint16_t)(( \
       DMA_ATTR_REG(PeripheralBase,(Channel))) & ( \
       (uint16_t)(~(uint16_t)DMA_ATTR_SSIZE_MASK)))) | ( \
      (uint16_t)((uint16_t)(Size) << DMA_ATTR_SSIZE_SHIFT))) \
  )
#define DMA_PDD_SetDestinationAddress(PeripheralBase, Channel, Address) ( \
    DMA_DADDR_REG(PeripheralBase,(Channel)) = \
     (uint32_t)(Address) \
  )
#define DMA_PDD_SetDestinationAddressModulo(PeripheralBase, Channel, Modulo) ( \
    DMA_ATTR_REG(PeripheralBase,(Channel)) = \
     (uint16_t)(( \
      (uint16_t)(( \
       DMA_ATTR_REG(PeripheralBase,(Channel))) & ( \
       (uint16_t)(~(uint16_t)DMA_ATTR_DMOD_MASK)))) | ( \
      (uint16_t)((uint16_t)(Modulo) << DMA_ATTR_DMOD_SHIFT))) \
  )
#define DMA_PDD_SetDestinationAddressOffset(PeripheralBase, Channel, Offset) ( \
    DMA_DOFF_REG(PeripheralBase,(Channel)) = \
     (uint16_t)(Offset) \
  )
  #define DMA_PDD_SetDestinationDataTransferSize(PeripheralBase, Channel, Size) ( \
      DMA_ATTR_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_ATTR_REG(PeripheralBase,(Channel))) & ( \
         (uint16_t)(~(uint16_t)DMA_ATTR_DSIZE_MASK)))) | ( \
        (uint16_t)(Size))) \
    )
  #define DMA_PDD_EnableRequestAutoDisable(PeripheralBase, Channel, State) ( \
      DMA_CSR_REG(PeripheralBase,(Channel)) = \
       (uint16_t)(( \
        (uint16_t)(( \
         DMA_CSR_REG(PeripheralBase,(Channel))) & ( \
         (uint16_t)(~(uint16_t)DMA_CSR_DREQ_MASK)))) | ( \
        (uint16_t)((uint16_t)(State) << DMA_CSR_DREQ_SHIFT))) \
    )
  #define DMA_PDD_ClearDoneFlag(PeripheralBase, Channel) ( \
      DMA_CDNE_REG(PeripheralBase) = \
       (uint8_t)(Channel) \
    )
  #define DMA_PDD_SetSourceAddress(PeripheralBase, Channel, Address) ( \
      DMA_SADDR_REG(PeripheralBase,(Channel)) = \
       (uint32_t)(Address) \
    )
#define DMA_PDD_SetCurrentMajorLoopCount15(PeripheralBase, Channel, Value) ( \
    DMA_CITER_ELINKNO_REG(PeripheralBase,(Channel)) = \
     (uint16_t)(( \
      (uint16_t)(( \
       DMA_CITER_ELINKNO_REG(PeripheralBase,(Channel))) & ( \
       (uint16_t)(~(uint16_t)DMA_CITER_ELINKNO_CITER_MASK)))) | ( \
      (uint16_t)(Value))) \
  )
#define DMA_PDD_SetBeginningMajorLoopCount15(PeripheralBase, Channel, Value) ( \
    DMA_BITER_ELINKNO_REG(PeripheralBase,(Channel)) = \
     (uint16_t)(( \
      (uint16_t)(( \
       DMA_BITER_ELINKNO_REG(PeripheralBase,(Channel))) & ( \
       (uint16_t)(~(uint16_t)DMA_BITER_ELINKNO_BITER_MASK)))) | ( \
      (uint16_t)(Value))) \
  )
 #define DMA_PDD_GetDoneFlag(PeripheralBase, Channel) ( \
      (uint16_t)(DMA_CSR_REG(PeripheralBase,(Channel)) & DMA_CSR_DONE_MASK) \
    )
#define FTM_PDD_DisableChannelDma(PeripheralBase, ChannelIdx) ( \
    FTM_CnSC_REG(PeripheralBase,(ChannelIdx)) &= \
     (uint32_t)(( \
      (uint32_t)(~(uint32_t)FTM_CnSC_DMA_MASK)) & ( \
      (uint32_t)(~(uint32_t)FTM_CnSC_CHF_MASK))) \
  )


#endif /* DMA_MACROS_H_ */
