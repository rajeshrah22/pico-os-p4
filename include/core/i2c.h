#ifndef I2C_H__
#define I2C_H__

extern struct {
/* 00 */	volatile unsigned con;
/* 04 */	volatile unsigned tar;
/* 08 */	volatile unsigned sar;
/* 0c */	unsigned __padding_0;
/* 10 */	volatile unsigned data_cmd;
/* 14 */	volatile unsigned ss_scl_hcnt;
/* 18 */	volatile unsigned ss_scl_lcnt;
/* 1c */	volatile unsigned fs_scl_hcnt;
/* 20 */	volatile unsigned fs_scl_lcnt;
/* 24,28 */	unsigned __padding_1[2];
/* 2c */	volatile unsigned intr_stat;
/* 30 */	volatile unsigned intr_mask;
/* 34 */	volatile unsigned raw_intr_stat;
/* 38 */	volatile unsigned rx_tl;
/* 3c */	volatile unsigned tx_tl;
/* 40 */	volatile unsigned ctrl_intr;
/* 44 */	struct {
/* 44 */		volatile unsigned rx_under;
/* 48 */		volatile unsigned rx_over;
/* 4c */		volatile unsigned tx_over;
/* 50 */		volatile unsigned rd_req;
/* 54 */		volatile unsigned tx_abrt;
/* 58 */		volatile unsigned rx_done;
/* 5c */		volatile unsigned activity;
/* 60 */		volatile unsigned stop_det;
/* 64 */		volatile unsigned start_det;
/* 68 */		volatile unsigned gen_call;
/*    */	} clr;
/* 6c */	volatile unsigned enable;
/* 70 */	volatile unsigned status;
/* 74 */	volatile unsigned txflr;
/* 78 */	volatile unsigned rxflr;
/* 7c */	volatile unsigned sda_hold;
/* 80 */	volatile unsigned tx_abrt_source;
/* 84 */	volatile unsigned slv_data_nack_only;
/* 88 */	struct {
/* 88 */		volatile unsigned cr;
/* 8c */		volatile unsigned tdlr;
/* 90 */		volatile unsigned rdlr;
/*    */	} dma;
/* 94 */	volatile unsigned ic_sda_setup;
/* 98 */	volatile unsigned ic_ack_general_call;
/* 9c */	volatile unsigned ic_enable_status;
/* a0 */	volatile unsigned ic_fs_spklen;
/* a4 */	volatile unsigned ic_clr_restart_det;
/* meh */
// /* f4 */	volatile unsigned ic_comp_param_1;
// /* f8 */	volatile unsigned ic_comp_version;
// /* fc */	volatile unsigned ic_comp_type;
} I2C0, I2C1;

#endif	/* I2C_H__ */
