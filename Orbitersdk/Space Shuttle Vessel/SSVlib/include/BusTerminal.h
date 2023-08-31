#ifndef _BUSTERMINAL_H_
#define _BUSTERMINAL_H_

#include "BusDefs.h"


/**
 * Calculate parity of an unsigned int value.
 * @arg val	value to calculate parity
 * @return	0 = even, 1 = odd
 */
unsigned int CalcParity( const unsigned int val );


class BusManager;


class BusTerminal
{
	friend class BusManager;

	private:
		BusManager* busmanager;

	protected:
		/**
		 * Creates a connection to a bus.
		 * @arg id		bus id
		 */
		void BusConnect( const BUS_ID id );

		/**
		 * Transmits data over a bus.
		 * @arg id		bus id
		 * @arg data		pointer to data
		 * @arg datalen		number of native words in data
		 */
		void Tx( const BUS_ID id, void* data, const unsigned short datalen );
		/**
		 * Receives data from a bus.
		 * @arg id		bus id
		 * @arg data		pointer to data
		 * @arg datalen		number of native words in data
		 */
		virtual void Rx( const BUS_ID id, void* data, const unsigned short datalen ) = 0;

	public:
		explicit BusTerminal( BusManager* busmanager );
		virtual ~BusTerminal( void );
};

#endif// _BUSTERMINAL_H_
