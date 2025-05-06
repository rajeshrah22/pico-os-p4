#ifndef DMA_H__
#define DMA_H__

extern struct {
	struct {
		volatile unsigned read_addr;
		volatile unsigned write_addr;
		volatile unsigned trans_count;
		volatile unsigned ctrl_trig;
		struct {
			volatile unsigned ctrl;
			volatile unsigned read_addr;
			volatile unsigned write_addr;
			volatile unsigned trans_count_trig;
		} alias[3];

	} channel[12];
	volatile unsigned intr;
	struct {
		volatile unsigned inte;
		volatile unsigned intf;
		volatile unsigned ints;
	} irq[2];
	volatile unsigned timer[4];
	volatile unsigned multi_chan_trigger;
	volatile unsigned sniff_ctrl;
	volatile unsigned fifo_levels;
	volatile unsigned chan_abort;
	volatile unsigned n_channels;
} DMA;

#endif	/* DMA_H__ */
