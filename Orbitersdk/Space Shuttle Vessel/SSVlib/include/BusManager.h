#ifndef _BUSMANAGER_H_
#define _BUSMANAGER_H_


#include <vector>
#include "BusDefs.h"


class BusTerminal;

class BusManager
{
	private:
		std::vector<BusTerminal*> terminals[___LAST___BUS_ID_SIZE];

	public:
		BusManager( void );
		virtual ~BusManager( void );

		/**
		 * Connects BusTerminal-derived class to a bus.
		 * @arg id		bus id
		 * @arg terminal	pointer to BusTerminal-derived class
		 */
		void Connect( const BUS_ID id, BusTerminal* terminal );
		/**
		 * Transmits data to all terminals in the indicated bus, except the source (assumes only transmitters or receivers are enabled).
		 * @arg id		bus id
		 * @arg data		pointer to data
		 * @arg datalen		number of native words in data
		 * @arg src		pointer to BusTerminal-derived class sending data
		 */
		void Tx( const BUS_ID id, void* data, const unsigned short datalen, BusTerminal* src );
};

#endif// _BUSMANAGER_H_
