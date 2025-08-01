/**
 * SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
 *
 *  SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#include <stdint.h>
#include "soc/soc.h"
#ifdef __cplusplus
extern "C" {
#endif

/** CSI_BRIG_CLK_EN_REG register
 *  csi bridge register mapping unit clock gating.
 */
#define CSI_BRIG_CLK_EN_REG (DR_REG_CSI_BRIG_BASE + 0x0)
/** CSI_BRIG_CLK_EN : R/W; bitpos: [0]; default: 0;
 *  0: enable clock gating. 1: disable clock gating, clock always on.
 */
#define CSI_BRIG_CLK_EN    (BIT(0))
#define CSI_BRIG_CLK_EN_M  (CSI_BRIG_CLK_EN_V << CSI_BRIG_CLK_EN_S)
#define CSI_BRIG_CLK_EN_V  0x00000001U
#define CSI_BRIG_CLK_EN_S  0

/** CSI_BRIG_CSI_EN_REG register
 *  csi bridge enable.
 */
#define CSI_BRIG_CSI_EN_REG (DR_REG_CSI_BRIG_BASE + 0x4)
/** CSI_BRIG_CSI_BRIG_EN : R/W; bitpos: [0]; default: 0;
 *  0: disable csi bridge. 1: enable csi bridge.
 */
#define CSI_BRIG_CSI_BRIG_EN    (BIT(0))
#define CSI_BRIG_CSI_BRIG_EN_M  (CSI_BRIG_CSI_BRIG_EN_V << CSI_BRIG_CSI_BRIG_EN_S)
#define CSI_BRIG_CSI_BRIG_EN_V  0x00000001U
#define CSI_BRIG_CSI_BRIG_EN_S  0
/** CSI_BRIG_CSI_BRIG_RST : R/W; bitpos: [1]; default: 0;
 *  0: release csi bridge reset. 1: enable csi bridge reset.
 */
#define CSI_BRIG_CSI_BRIG_RST    (BIT(1))
#define CSI_BRIG_CSI_BRIG_RST_M  (CSI_BRIG_CSI_BRIG_RST_V << CSI_BRIG_CSI_BRIG_RST_S)
#define CSI_BRIG_CSI_BRIG_RST_V  0x00000001U
#define CSI_BRIG_CSI_BRIG_RST_S  1

/** CSI_BRIG_DMA_REQ_CFG_REG register
 *  dma request configuration.
 */
#define CSI_BRIG_DMA_REQ_CFG_REG (DR_REG_CSI_BRIG_BASE + 0x8)
/** CSI_BRIG_DMA_BURST_LEN : R/W; bitpos: [11:0]; default: 128;
 *  DMA burst length.
 */
#define CSI_BRIG_DMA_BURST_LEN    0x00000FFFU
#define CSI_BRIG_DMA_BURST_LEN_M  (CSI_BRIG_DMA_BURST_LEN_V << CSI_BRIG_DMA_BURST_LEN_S)
#define CSI_BRIG_DMA_BURST_LEN_V  0x00000FFFU
#define CSI_BRIG_DMA_BURST_LEN_S  0
/** CSI_BRIG_DMA_CFG_UPD_BY_BLK : R/W; bitpos: [12]; default: 0;
 *  1: reg_dma_burst_len & reg_dma_burst_len will be updated by dma block finish. 0:
 *  updated by frame.
 */
#define CSI_BRIG_DMA_CFG_UPD_BY_BLK    (BIT(12))
#define CSI_BRIG_DMA_CFG_UPD_BY_BLK_M  (CSI_BRIG_DMA_CFG_UPD_BY_BLK_V << CSI_BRIG_DMA_CFG_UPD_BY_BLK_S)
#define CSI_BRIG_DMA_CFG_UPD_BY_BLK_V  0x00000001U
#define CSI_BRIG_DMA_CFG_UPD_BY_BLK_S  12
/** CSI_BRIG_DMA_FORCE_RD_STATUS : R/W; bitpos: [16]; default: 0;
 *  1: mask dma request when reading frame info. 0: disable mask.
 */
#define CSI_BRIG_DMA_FORCE_RD_STATUS    (BIT(16))
#define CSI_BRIG_DMA_FORCE_RD_STATUS_M  (CSI_BRIG_DMA_FORCE_RD_STATUS_V << CSI_BRIG_DMA_FORCE_RD_STATUS_S)
#define CSI_BRIG_DMA_FORCE_RD_STATUS_V  0x00000001U
#define CSI_BRIG_DMA_FORCE_RD_STATUS_S  16
/** CSI_BRIG_CSI_DMA_FLOW_CONTROLLER : R/W; bitpos: [17]; default: 1;
 *  0: dma as flow controller. 1: csi_bridge as flow controller
 */
#define CSI_BRIG_CSI_DMA_FLOW_CONTROLLER    (BIT(17))
#define CSI_BRIG_CSI_DMA_FLOW_CONTROLLER_M  (CSI_BRIG_CSI_DMA_FLOW_CONTROLLER_V << CSI_BRIG_CSI_DMA_FLOW_CONTROLLER_S)
#define CSI_BRIG_CSI_DMA_FLOW_CONTROLLER_V  0x00000001U
#define CSI_BRIG_CSI_DMA_FLOW_CONTROLLER_S  17

/** CSI_BRIG_BUF_FLOW_CTL_REG register
 *  csi bridge buffer control.
 */
#define CSI_BRIG_BUF_FLOW_CTL_REG (DR_REG_CSI_BRIG_BASE + 0xc)
/** CSI_BRIG_CSI_BUF_AFULL_THRD : R/W; bitpos: [13:0]; default: 2040;
 *  buffer almost full threshold.
 */
#define CSI_BRIG_CSI_BUF_AFULL_THRD    0x00003FFFU
#define CSI_BRIG_CSI_BUF_AFULL_THRD_M  (CSI_BRIG_CSI_BUF_AFULL_THRD_V << CSI_BRIG_CSI_BUF_AFULL_THRD_S)
#define CSI_BRIG_CSI_BUF_AFULL_THRD_V  0x00003FFFU
#define CSI_BRIG_CSI_BUF_AFULL_THRD_S  0
/** CSI_BRIG_CSI_BUF_DEPTH : RO; bitpos: [29:16]; default: 0;
 *  buffer data count.
 */
#define CSI_BRIG_CSI_BUF_DEPTH    0x00003FFFU
#define CSI_BRIG_CSI_BUF_DEPTH_M  (CSI_BRIG_CSI_BUF_DEPTH_V << CSI_BRIG_CSI_BUF_DEPTH_S)
#define CSI_BRIG_CSI_BUF_DEPTH_V  0x00003FFFU
#define CSI_BRIG_CSI_BUF_DEPTH_S  16

/** CSI_BRIG_DATA_TYPE_CFG_REG register
 *  pixel data type configuration.
 */
#define CSI_BRIG_DATA_TYPE_CFG_REG (DR_REG_CSI_BRIG_BASE + 0x10)
/** CSI_BRIG_DATA_TYPE_MIN : R/W; bitpos: [5:0]; default: 24;
 *  the min value of data type used for pixel filter.
 */
#define CSI_BRIG_DATA_TYPE_MIN    0x0000003FU
#define CSI_BRIG_DATA_TYPE_MIN_M  (CSI_BRIG_DATA_TYPE_MIN_V << CSI_BRIG_DATA_TYPE_MIN_S)
#define CSI_BRIG_DATA_TYPE_MIN_V  0x0000003FU
#define CSI_BRIG_DATA_TYPE_MIN_S  0
/** CSI_BRIG_DATA_TYPE_MAX : R/W; bitpos: [13:8]; default: 47;
 *  the max value of data type used for pixel filter.
 */
#define CSI_BRIG_DATA_TYPE_MAX    0x0000003FU
#define CSI_BRIG_DATA_TYPE_MAX_M  (CSI_BRIG_DATA_TYPE_MAX_V << CSI_BRIG_DATA_TYPE_MAX_S)
#define CSI_BRIG_DATA_TYPE_MAX_V  0x0000003FU
#define CSI_BRIG_DATA_TYPE_MAX_S  8

/** CSI_BRIG_FRAME_CFG_REG register
 *  frame configuration.
 */
#define CSI_BRIG_FRAME_CFG_REG (DR_REG_CSI_BRIG_BASE + 0x14)
/** CSI_BRIG_VADR_NUM : R/W; bitpos: [11:0]; default: 480;
 *  vadr of frame data.
 */
#define CSI_BRIG_VADR_NUM    0x00000FFFU
#define CSI_BRIG_VADR_NUM_M  (CSI_BRIG_VADR_NUM_V << CSI_BRIG_VADR_NUM_S)
#define CSI_BRIG_VADR_NUM_V  0x00000FFFU
#define CSI_BRIG_VADR_NUM_S  0
/** CSI_BRIG_HADR_NUM : R/W; bitpos: [23:12]; default: 480;
 *  hadr of frame data.
 */
#define CSI_BRIG_HADR_NUM    0x00000FFFU
#define CSI_BRIG_HADR_NUM_M  (CSI_BRIG_HADR_NUM_V << CSI_BRIG_HADR_NUM_S)
#define CSI_BRIG_HADR_NUM_V  0x00000FFFU
#define CSI_BRIG_HADR_NUM_S  12
/** CSI_BRIG_HAS_HSYNC_E : R/W; bitpos: [24]; default: 1;
 *  0: frame data doesn't contain hsync. 1: frame data contains hsync.
 */
#define CSI_BRIG_HAS_HSYNC_E    (BIT(24))
#define CSI_BRIG_HAS_HSYNC_E_M  (CSI_BRIG_HAS_HSYNC_E_V << CSI_BRIG_HAS_HSYNC_E_S)
#define CSI_BRIG_HAS_HSYNC_E_V  0x00000001U
#define CSI_BRIG_HAS_HSYNC_E_S  24
/** CSI_BRIG_VADR_NUM_CHECK : R/W; bitpos: [25]; default: 0;
 *  0: disable vadr check. 1: enable vadr check.
 */
#define CSI_BRIG_VADR_NUM_CHECK    (BIT(25))
#define CSI_BRIG_VADR_NUM_CHECK_M  (CSI_BRIG_VADR_NUM_CHECK_V << CSI_BRIG_VADR_NUM_CHECK_S)
#define CSI_BRIG_VADR_NUM_CHECK_V  0x00000001U
#define CSI_BRIG_VADR_NUM_CHECK_S  25

/** CSI_BRIG_ENDIAN_MODE_REG register
 *  data endianness order configuration.
 */
#define CSI_BRIG_ENDIAN_MODE_REG (DR_REG_CSI_BRIG_BASE + 0x18)
/** CSI_BRIG_BYTE_ENDIAN_ORDER : R/W; bitpos: [0]; default: 0;
 *  endianness order in bytes. 2'h0 is normal mode and 2'h3 is useful to YUV420(Legacy)
 *  when isp is bapassed.
 */
#define CSI_BRIG_BYTE_ENDIAN_ORDER    (BIT(0))
#define CSI_BRIG_BYTE_ENDIAN_ORDER_M  (CSI_BRIG_BYTE_ENDIAN_ORDER_V << CSI_BRIG_BYTE_ENDIAN_ORDER_S)
#define CSI_BRIG_BYTE_ENDIAN_ORDER_V  0x00000001U
#define CSI_BRIG_BYTE_ENDIAN_ORDER_S  0
/** CSI_BRIG_BIT_ENDIAN_ORDER : R/W; bitpos: [1]; default: 0;
 *  N/A
 */
#define CSI_BRIG_BIT_ENDIAN_ORDER    (BIT(1))
#define CSI_BRIG_BIT_ENDIAN_ORDER_M  (CSI_BRIG_BIT_ENDIAN_ORDER_V << CSI_BRIG_BIT_ENDIAN_ORDER_S)
#define CSI_BRIG_BIT_ENDIAN_ORDER_V  0x00000001U
#define CSI_BRIG_BIT_ENDIAN_ORDER_S  1

/** CSI_BRIG_INT_RAW_REG register
 *  csi bridge interrupt raw.
 */
#define CSI_BRIG_INT_RAW_REG (DR_REG_CSI_BRIG_BASE + 0x1c)
/** CSI_BRIG_VADR_NUM_GT_INT_RAW : R/WTC/SS; bitpos: [0]; default: 0;
 *  reg_vadr_num is greater than real interrupt raw.
 */
#define CSI_BRIG_VADR_NUM_GT_INT_RAW    (BIT(0))
#define CSI_BRIG_VADR_NUM_GT_INT_RAW_M  (CSI_BRIG_VADR_NUM_GT_INT_RAW_V << CSI_BRIG_VADR_NUM_GT_INT_RAW_S)
#define CSI_BRIG_VADR_NUM_GT_INT_RAW_V  0x00000001U
#define CSI_BRIG_VADR_NUM_GT_INT_RAW_S  0
/** CSI_BRIG_VADR_NUM_LT_INT_RAW : R/WTC/SS; bitpos: [1]; default: 0;
 *  reg_vadr_num is less than real interrupt raw.
 */
#define CSI_BRIG_VADR_NUM_LT_INT_RAW    (BIT(1))
#define CSI_BRIG_VADR_NUM_LT_INT_RAW_M  (CSI_BRIG_VADR_NUM_LT_INT_RAW_V << CSI_BRIG_VADR_NUM_LT_INT_RAW_S)
#define CSI_BRIG_VADR_NUM_LT_INT_RAW_V  0x00000001U
#define CSI_BRIG_VADR_NUM_LT_INT_RAW_S  1
/** CSI_BRIG_DISCARD_INT_RAW : R/WTC/SS; bitpos: [2]; default: 0;
 *  an incomplete frame of data was sent interrupt raw.
 */
#define CSI_BRIG_DISCARD_INT_RAW    (BIT(2))
#define CSI_BRIG_DISCARD_INT_RAW_M  (CSI_BRIG_DISCARD_INT_RAW_V << CSI_BRIG_DISCARD_INT_RAW_S)
#define CSI_BRIG_DISCARD_INT_RAW_V  0x00000001U
#define CSI_BRIG_DISCARD_INT_RAW_S  2
/** CSI_BRIG_CSI_BUF_OVERRUN_INT_RAW : R/WTC/SS; bitpos: [3]; default: 0;
 *  buffer overrun interrupt raw.
 */
#define CSI_BRIG_CSI_BUF_OVERRUN_INT_RAW    (BIT(3))
#define CSI_BRIG_CSI_BUF_OVERRUN_INT_RAW_M  (CSI_BRIG_CSI_BUF_OVERRUN_INT_RAW_V << CSI_BRIG_CSI_BUF_OVERRUN_INT_RAW_S)
#define CSI_BRIG_CSI_BUF_OVERRUN_INT_RAW_V  0x00000001U
#define CSI_BRIG_CSI_BUF_OVERRUN_INT_RAW_S  3
/** CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_RAW : R/WTC/SS; bitpos: [4]; default: 0;
 *  buffer overflow interrupt raw.
 */
#define CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_RAW    (BIT(4))
#define CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_RAW_M  (CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_RAW_V << CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_RAW_S)
#define CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_RAW_V  0x00000001U
#define CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_RAW_S  4
/** CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_RAW : R/WTC/SS; bitpos: [5]; default: 0;
 *  dma configuration update complete interrupt raw.
 */
#define CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_RAW    (BIT(5))
#define CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_RAW_M  (CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_RAW_V << CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_RAW_S)
#define CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_RAW_V  0x00000001U
#define CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_RAW_S  5

/** CSI_BRIG_INT_CLR_REG register
 *  csi bridge interrupt clr.
 */
#define CSI_BRIG_INT_CLR_REG (DR_REG_CSI_BRIG_BASE + 0x20)
/** CSI_BRIG_VADR_NUM_GT_REAL_INT_CLR : WT; bitpos: [0]; default: 0;
 *  reg_vadr_num is greater than real interrupt clr.
 */
#define CSI_BRIG_VADR_NUM_GT_REAL_INT_CLR    (BIT(0))
#define CSI_BRIG_VADR_NUM_GT_REAL_INT_CLR_M  (CSI_BRIG_VADR_NUM_GT_REAL_INT_CLR_V << CSI_BRIG_VADR_NUM_GT_REAL_INT_CLR_S)
#define CSI_BRIG_VADR_NUM_GT_REAL_INT_CLR_V  0x00000001U
#define CSI_BRIG_VADR_NUM_GT_REAL_INT_CLR_S  0
/** CSI_BRIG_VADR_NUM_LT_REAL_INT_CLR : WT; bitpos: [1]; default: 0;
 *  reg_vadr_num is less than real interrupt clr.
 */
#define CSI_BRIG_VADR_NUM_LT_REAL_INT_CLR    (BIT(1))
#define CSI_BRIG_VADR_NUM_LT_REAL_INT_CLR_M  (CSI_BRIG_VADR_NUM_LT_REAL_INT_CLR_V << CSI_BRIG_VADR_NUM_LT_REAL_INT_CLR_S)
#define CSI_BRIG_VADR_NUM_LT_REAL_INT_CLR_V  0x00000001U
#define CSI_BRIG_VADR_NUM_LT_REAL_INT_CLR_S  1
/** CSI_BRIG_DISCARD_INT_CLR : WT; bitpos: [2]; default: 0;
 *  an incomplete frame of data was sent interrupt clr.
 */
#define CSI_BRIG_DISCARD_INT_CLR    (BIT(2))
#define CSI_BRIG_DISCARD_INT_CLR_M  (CSI_BRIG_DISCARD_INT_CLR_V << CSI_BRIG_DISCARD_INT_CLR_S)
#define CSI_BRIG_DISCARD_INT_CLR_V  0x00000001U
#define CSI_BRIG_DISCARD_INT_CLR_S  2
/** CSI_BRIG_CSI_BUF_OVERRUN_INT_CLR : WT; bitpos: [3]; default: 0;
 *  buffer overrun interrupt clr.
 */
#define CSI_BRIG_CSI_BUF_OVERRUN_INT_CLR    (BIT(3))
#define CSI_BRIG_CSI_BUF_OVERRUN_INT_CLR_M  (CSI_BRIG_CSI_BUF_OVERRUN_INT_CLR_V << CSI_BRIG_CSI_BUF_OVERRUN_INT_CLR_S)
#define CSI_BRIG_CSI_BUF_OVERRUN_INT_CLR_V  0x00000001U
#define CSI_BRIG_CSI_BUF_OVERRUN_INT_CLR_S  3
/** CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_CLR : WT; bitpos: [4]; default: 0;
 *  buffer overflow interrupt clr.
 */
#define CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_CLR    (BIT(4))
#define CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_CLR_M  (CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_CLR_V << CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_CLR_S)
#define CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_CLR_V  0x00000001U
#define CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_CLR_S  4
/** CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_CLR : WT; bitpos: [5]; default: 0;
 *  dma configuration update complete interrupt clr.
 */
#define CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_CLR    (BIT(5))
#define CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_CLR_M  (CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_CLR_V << CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_CLR_S)
#define CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_CLR_V  0x00000001U
#define CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_CLR_S  5

/** CSI_BRIG_INT_ST_REG register
 *  csi bridge interrupt st.
 */
#define CSI_BRIG_INT_ST_REG (DR_REG_CSI_BRIG_BASE + 0x24)
/** CSI_BRIG_VADR_NUM_GT_INT_ST : RO; bitpos: [0]; default: 0;
 *  reg_vadr_num is greater than real interrupt st.
 */
#define CSI_BRIG_VADR_NUM_GT_INT_ST    (BIT(0))
#define CSI_BRIG_VADR_NUM_GT_INT_ST_M  (CSI_BRIG_VADR_NUM_GT_INT_ST_V << CSI_BRIG_VADR_NUM_GT_INT_ST_S)
#define CSI_BRIG_VADR_NUM_GT_INT_ST_V  0x00000001U
#define CSI_BRIG_VADR_NUM_GT_INT_ST_S  0
/** CSI_BRIG_VADR_NUM_LT_INT_ST : RO; bitpos: [1]; default: 0;
 *  reg_vadr_num is less than real interrupt st.
 */
#define CSI_BRIG_VADR_NUM_LT_INT_ST    (BIT(1))
#define CSI_BRIG_VADR_NUM_LT_INT_ST_M  (CSI_BRIG_VADR_NUM_LT_INT_ST_V << CSI_BRIG_VADR_NUM_LT_INT_ST_S)
#define CSI_BRIG_VADR_NUM_LT_INT_ST_V  0x00000001U
#define CSI_BRIG_VADR_NUM_LT_INT_ST_S  1
/** CSI_BRIG_DISCARD_INT_ST : RO; bitpos: [2]; default: 0;
 *  an incomplete frame of data was sent interrupt st.
 */
#define CSI_BRIG_DISCARD_INT_ST    (BIT(2))
#define CSI_BRIG_DISCARD_INT_ST_M  (CSI_BRIG_DISCARD_INT_ST_V << CSI_BRIG_DISCARD_INT_ST_S)
#define CSI_BRIG_DISCARD_INT_ST_V  0x00000001U
#define CSI_BRIG_DISCARD_INT_ST_S  2
/** CSI_BRIG_CSI_BUF_OVERRUN_INT_ST : RO; bitpos: [3]; default: 0;
 *  buffer overrun interrupt st.
 */
#define CSI_BRIG_CSI_BUF_OVERRUN_INT_ST    (BIT(3))
#define CSI_BRIG_CSI_BUF_OVERRUN_INT_ST_M  (CSI_BRIG_CSI_BUF_OVERRUN_INT_ST_V << CSI_BRIG_CSI_BUF_OVERRUN_INT_ST_S)
#define CSI_BRIG_CSI_BUF_OVERRUN_INT_ST_V  0x00000001U
#define CSI_BRIG_CSI_BUF_OVERRUN_INT_ST_S  3
/** CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_ST : RO; bitpos: [4]; default: 0;
 *  buffer overflow interrupt st.
 */
#define CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_ST    (BIT(4))
#define CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_ST_M  (CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_ST_V << CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_ST_S)
#define CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_ST_V  0x00000001U
#define CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_ST_S  4
/** CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_ST : RO; bitpos: [5]; default: 0;
 *  dma configuration update complete interrupt st.
 */
#define CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_ST    (BIT(5))
#define CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_ST_M  (CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_ST_V << CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_ST_S)
#define CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_ST_V  0x00000001U
#define CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_ST_S  5

/** CSI_BRIG_INT_ENA_REG register
 *  csi bridge interrupt enable.
 */
#define CSI_BRIG_INT_ENA_REG (DR_REG_CSI_BRIG_BASE + 0x28)
/** CSI_BRIG_VADR_NUM_GT_INT_ENA : R/W; bitpos: [0]; default: 0;
 *  reg_vadr_num is greater than real interrupt enable.
 */
#define CSI_BRIG_VADR_NUM_GT_INT_ENA    (BIT(0))
#define CSI_BRIG_VADR_NUM_GT_INT_ENA_M  (CSI_BRIG_VADR_NUM_GT_INT_ENA_V << CSI_BRIG_VADR_NUM_GT_INT_ENA_S)
#define CSI_BRIG_VADR_NUM_GT_INT_ENA_V  0x00000001U
#define CSI_BRIG_VADR_NUM_GT_INT_ENA_S  0
/** CSI_BRIG_VADR_NUM_LT_INT_ENA : R/W; bitpos: [1]; default: 0;
 *  reg_vadr_num is less than real interrupt enable.
 */
#define CSI_BRIG_VADR_NUM_LT_INT_ENA    (BIT(1))
#define CSI_BRIG_VADR_NUM_LT_INT_ENA_M  (CSI_BRIG_VADR_NUM_LT_INT_ENA_V << CSI_BRIG_VADR_NUM_LT_INT_ENA_S)
#define CSI_BRIG_VADR_NUM_LT_INT_ENA_V  0x00000001U
#define CSI_BRIG_VADR_NUM_LT_INT_ENA_S  1
/** CSI_BRIG_DISCARD_INT_ENA : R/W; bitpos: [2]; default: 0;
 *  an incomplete frame of data was sent interrupt enable.
 */
#define CSI_BRIG_DISCARD_INT_ENA    (BIT(2))
#define CSI_BRIG_DISCARD_INT_ENA_M  (CSI_BRIG_DISCARD_INT_ENA_V << CSI_BRIG_DISCARD_INT_ENA_S)
#define CSI_BRIG_DISCARD_INT_ENA_V  0x00000001U
#define CSI_BRIG_DISCARD_INT_ENA_S  2
/** CSI_BRIG_CSI_BUF_OVERRUN_INT_ENA : R/W; bitpos: [3]; default: 0;
 *  buffer overrun interrupt enable.
 */
#define CSI_BRIG_CSI_BUF_OVERRUN_INT_ENA    (BIT(3))
#define CSI_BRIG_CSI_BUF_OVERRUN_INT_ENA_M  (CSI_BRIG_CSI_BUF_OVERRUN_INT_ENA_V << CSI_BRIG_CSI_BUF_OVERRUN_INT_ENA_S)
#define CSI_BRIG_CSI_BUF_OVERRUN_INT_ENA_V  0x00000001U
#define CSI_BRIG_CSI_BUF_OVERRUN_INT_ENA_S  3
/** CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_ENA : R/W; bitpos: [4]; default: 0;
 *  buffer overflow interrupt enable.
 */
#define CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_ENA    (BIT(4))
#define CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_ENA_M  (CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_ENA_V << CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_ENA_S)
#define CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_ENA_V  0x00000001U
#define CSI_BRIG_CSI_ASYNC_FIFO_OVF_INT_ENA_S  4
/** CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_ENA : R/W; bitpos: [5]; default: 0;
 *  dma configuration update complete interrupt enable.
 */
#define CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_ENA    (BIT(5))
#define CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_ENA_M  (CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_ENA_V << CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_ENA_S)
#define CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_ENA_V  0x00000001U
#define CSI_BRIG_DMA_CFG_HAS_UPDATED_INT_ENA_S  5

/** CSI_BRIG_DMA_REQ_INTERVAL_REG register
 *  DMA interval configuration.
 */
#define CSI_BRIG_DMA_REQ_INTERVAL_REG (DR_REG_CSI_BRIG_BASE + 0x2c)
/** CSI_BRIG_DMA_REQ_INTERVAL : R/W; bitpos: [15:0]; default: 1;
 *  16'b1: 1 cycle. 16'b11: 2 cycle. ... ... 16'hFFFF: 16 cycle.
 */
#define CSI_BRIG_DMA_REQ_INTERVAL    0x0000FFFFU
#define CSI_BRIG_DMA_REQ_INTERVAL_M  (CSI_BRIG_DMA_REQ_INTERVAL_V << CSI_BRIG_DMA_REQ_INTERVAL_S)
#define CSI_BRIG_DMA_REQ_INTERVAL_V  0x0000FFFFU
#define CSI_BRIG_DMA_REQ_INTERVAL_S  0

/** CSI_BRIG_DMABLK_SIZE_REG register
 *  DMA block size configuration.
 */
#define CSI_BRIG_DMABLK_SIZE_REG (DR_REG_CSI_BRIG_BASE + 0x30)
/** CSI_BRIG_DMABLK_SIZE : R/W; bitpos: [12:0]; default: 8191;
 *  the number of reg_dma_burst_len in a block
 */
#define CSI_BRIG_DMABLK_SIZE    0x00001FFFU
#define CSI_BRIG_DMABLK_SIZE_M  (CSI_BRIG_DMABLK_SIZE_V << CSI_BRIG_DMABLK_SIZE_S)
#define CSI_BRIG_DMABLK_SIZE_V  0x00001FFFU
#define CSI_BRIG_DMABLK_SIZE_S  0

/** CSI_BRIG_HOST_CTRL_REG register
 *  csi host control by csi bridge.
 */
#define CSI_BRIG_HOST_CTRL_REG (DR_REG_CSI_BRIG_BASE + 0x40)
/** CSI_BRIG_CSI_ENABLECLK : R/W; bitpos: [0]; default: 1;
 *  enable clock lane module of csi phy.
 */
#define CSI_BRIG_CSI_ENABLECLK    (BIT(0))
#define CSI_BRIG_CSI_ENABLECLK_M  (CSI_BRIG_CSI_ENABLECLK_V << CSI_BRIG_CSI_ENABLECLK_S)
#define CSI_BRIG_CSI_ENABLECLK_V  0x00000001U
#define CSI_BRIG_CSI_ENABLECLK_S  0
/** CSI_BRIG_CSI_CFG_CLK_EN : R/W; bitpos: [1]; default: 1;
 *  enable cfg_clk of csi host module.
 */
#define CSI_BRIG_CSI_CFG_CLK_EN    (BIT(1))
#define CSI_BRIG_CSI_CFG_CLK_EN_M  (CSI_BRIG_CSI_CFG_CLK_EN_V << CSI_BRIG_CSI_CFG_CLK_EN_S)
#define CSI_BRIG_CSI_CFG_CLK_EN_V  0x00000001U
#define CSI_BRIG_CSI_CFG_CLK_EN_S  1
/** CSI_BRIG_LOOPBK_TEST_EN : R/W; bitpos: [2]; default: 0;
 *  for phy test by loopback dsi phy to csi phy.
 */
#define CSI_BRIG_LOOPBK_TEST_EN    (BIT(2))
#define CSI_BRIG_LOOPBK_TEST_EN_M  (CSI_BRIG_LOOPBK_TEST_EN_V << CSI_BRIG_LOOPBK_TEST_EN_S)
#define CSI_BRIG_LOOPBK_TEST_EN_V  0x00000001U
#define CSI_BRIG_LOOPBK_TEST_EN_S  2

/** CSI_BRIG_HOST_CM_CTRL_REG register
 *  CSI HOST color mode convert configuration.
 */
#define CSI_BRIG_HOST_CM_CTRL_REG (DR_REG_CSI_BRIG_BASE + 0x48)
/** CSI_BRIG_CSI_HOST_CM_EN : R/W; bitpos: [0]; default: 1;
 *  Configures whether to enable cm output
 */
#define CSI_BRIG_CSI_HOST_CM_EN    (BIT(0))
#define CSI_BRIG_CSI_HOST_CM_EN_M  (CSI_BRIG_CSI_HOST_CM_EN_V << CSI_BRIG_CSI_HOST_CM_EN_S)
#define CSI_BRIG_CSI_HOST_CM_EN_V  0x00000001U
#define CSI_BRIG_CSI_HOST_CM_EN_S  0
/** CSI_BRIG_CSI_HOST_CM_BYPASS : R/W; bitpos: [1]; default: 1;
 *  Configures whether to bypass cm
 */
#define CSI_BRIG_CSI_HOST_CM_BYPASS    (BIT(1))
#define CSI_BRIG_CSI_HOST_CM_BYPASS_M  (CSI_BRIG_CSI_HOST_CM_BYPASS_V << CSI_BRIG_CSI_HOST_CM_BYPASS_S)
#define CSI_BRIG_CSI_HOST_CM_BYPASS_V  0x00000001U
#define CSI_BRIG_CSI_HOST_CM_BYPASS_S  1
/** CSI_BRIG_CSI_HOST_CM_RX : R/W; bitpos: [3:2]; default: 0;
 *  Configures whether to bypass cm
 */
#define CSI_BRIG_CSI_HOST_CM_RX    0x00000003U
#define CSI_BRIG_CSI_HOST_CM_RX_M  (CSI_BRIG_CSI_HOST_CM_RX_V << CSI_BRIG_CSI_HOST_CM_RX_S)
#define CSI_BRIG_CSI_HOST_CM_RX_V  0x00000003U
#define CSI_BRIG_CSI_HOST_CM_RX_S  2
/** CSI_BRIG_CSI_HOST_CM_RX_RGB_FORMAT : R/W; bitpos: [6:4]; default: 0;
 *  Configures whether to bypass cm
 */
#define CSI_BRIG_CSI_HOST_CM_RX_RGB_FORMAT    0x00000007U
#define CSI_BRIG_CSI_HOST_CM_RX_RGB_FORMAT_M  (CSI_BRIG_CSI_HOST_CM_RX_RGB_FORMAT_V << CSI_BRIG_CSI_HOST_CM_RX_RGB_FORMAT_S)
#define CSI_BRIG_CSI_HOST_CM_RX_RGB_FORMAT_V  0x00000007U
#define CSI_BRIG_CSI_HOST_CM_RX_RGB_FORMAT_S  4
/** CSI_BRIG_CSI_HOST_CM_RX_YUV422_FORMAT : R/W; bitpos: [8:7]; default: 0;
 *  Configures whether to bypass cm
 */
#define CSI_BRIG_CSI_HOST_CM_RX_YUV422_FORMAT    0x00000003U
#define CSI_BRIG_CSI_HOST_CM_RX_YUV422_FORMAT_M  (CSI_BRIG_CSI_HOST_CM_RX_YUV422_FORMAT_V << CSI_BRIG_CSI_HOST_CM_RX_YUV422_FORMAT_S)
#define CSI_BRIG_CSI_HOST_CM_RX_YUV422_FORMAT_V  0x00000003U
#define CSI_BRIG_CSI_HOST_CM_RX_YUV422_FORMAT_S  7
/** CSI_BRIG_CSI_HOST_CM_TX : R/W; bitpos: [10:9]; default: 0;
 *  Configures whether to bypass cm
 */
#define CSI_BRIG_CSI_HOST_CM_TX    0x00000003U
#define CSI_BRIG_CSI_HOST_CM_TX_M  (CSI_BRIG_CSI_HOST_CM_TX_V << CSI_BRIG_CSI_HOST_CM_TX_S)
#define CSI_BRIG_CSI_HOST_CM_TX_V  0x00000003U
#define CSI_BRIG_CSI_HOST_CM_TX_S  9
/** CSI_BRIG_CSI_HOST_CM_LANE_NUM : R/W; bitpos: [11]; default: 1;
 *  Configures lane number that csi used, valid only rgb888 to rgb888. 0: 1-lane, 1:
 *  2-lane
 */
#define CSI_BRIG_CSI_HOST_CM_LANE_NUM    (BIT(11))
#define CSI_BRIG_CSI_HOST_CM_LANE_NUM_M  (CSI_BRIG_CSI_HOST_CM_LANE_NUM_V << CSI_BRIG_CSI_HOST_CM_LANE_NUM_S)
#define CSI_BRIG_CSI_HOST_CM_LANE_NUM_V  0x00000001U
#define CSI_BRIG_CSI_HOST_CM_LANE_NUM_S  11
/** CSI_BRIG_CSI_HOST_CM_16BIT_SWAP : R/W; bitpos: [12]; default: 0;
 *  Configures whether to swap idi32 high and low 16-bit
 */
#define CSI_BRIG_CSI_HOST_CM_16BIT_SWAP    (BIT(12))
#define CSI_BRIG_CSI_HOST_CM_16BIT_SWAP_M  (CSI_BRIG_CSI_HOST_CM_16BIT_SWAP_V << CSI_BRIG_CSI_HOST_CM_16BIT_SWAP_S)
#define CSI_BRIG_CSI_HOST_CM_16BIT_SWAP_V  0x00000001U
#define CSI_BRIG_CSI_HOST_CM_16BIT_SWAP_S  12
/** CSI_BRIG_CSI_HOST_CM_8BIT_SWAP : R/W; bitpos: [13]; default: 0;
 *  Configures whether to swap idi32 high and low 8-bit
 */
#define CSI_BRIG_CSI_HOST_CM_8BIT_SWAP    (BIT(13))
#define CSI_BRIG_CSI_HOST_CM_8BIT_SWAP_M  (CSI_BRIG_CSI_HOST_CM_8BIT_SWAP_V << CSI_BRIG_CSI_HOST_CM_8BIT_SWAP_S)
#define CSI_BRIG_CSI_HOST_CM_8BIT_SWAP_V  0x00000001U
#define CSI_BRIG_CSI_HOST_CM_8BIT_SWAP_S  13

/** CSI_BRIG_HOST_SIZE_CTRL_REG register
 *  CSI HOST color mode convert configuration.
 */
#define CSI_BRIG_HOST_SIZE_CTRL_REG (DR_REG_CSI_BRIG_BASE + 0x4c)
/** CSI_BRIG_CSI_HOST_CM_VNUM : R/W; bitpos: [11:0]; default: 0;
 *  Configures idi32 image size in y-direction, row_num - 1, valid only when
 *  yuv422_to_yuv420_en = 1
 */
#define CSI_BRIG_CSI_HOST_CM_VNUM    0x00000FFFU
#define CSI_BRIG_CSI_HOST_CM_VNUM_M  (CSI_BRIG_CSI_HOST_CM_VNUM_V << CSI_BRIG_CSI_HOST_CM_VNUM_S)
#define CSI_BRIG_CSI_HOST_CM_VNUM_V  0x00000FFFU
#define CSI_BRIG_CSI_HOST_CM_VNUM_S  0
/** CSI_BRIG_CSI_HOST_CM_HNUM : R/W; bitpos: [23:12]; default: 0;
 *  Configures idi32 image size in x-direction, line_pix_num*bits_per_pix/32 - 1, valid
 *  only when yuv422_to_yuv420_en = 1
 */
#define CSI_BRIG_CSI_HOST_CM_HNUM    0x00000FFFU
#define CSI_BRIG_CSI_HOST_CM_HNUM_M  (CSI_BRIG_CSI_HOST_CM_HNUM_V << CSI_BRIG_CSI_HOST_CM_HNUM_S)
#define CSI_BRIG_CSI_HOST_CM_HNUM_V  0x00000FFFU
#define CSI_BRIG_CSI_HOST_CM_HNUM_S  12

#ifdef __cplusplus
}
#endif
