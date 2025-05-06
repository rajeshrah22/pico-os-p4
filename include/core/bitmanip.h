#ifndef BITMANIP_H__
#define BITMANIP_H__

#define bit_is_set(REG, BIT)	((REG) & (1u << (BIT)))
#define bit_is_clear(REG, BIT)	(!((REG) & (1u << (BIT))))

#define loop_until_bit_is_set(REG, BIT) \
	do {} while(bit_is_clear(REG, BIT))

#define loop_until_bit_is_clear(REG, BIT) \
	do {} while(bit_is_set(REG, BIT))

#endif
